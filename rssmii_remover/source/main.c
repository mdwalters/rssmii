#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "wc24/wc24.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

u64 rssmiititleid = 0x0001000846454544LL; // Title ID for RSS-Feed mail: 00010008-FEED.
nwc24dl_record nwc24record;
nwc24dl_entry nwc24entry;

int main(int argc, char **argv) {

    // Initialise the video system
    VIDEO_Init();

    // This function initialises the attached controllers
    WPAD_Init();

    // Obtain the preferred video mode from the system
    // This will correspond to the settings in the Wii menu
    rmode = VIDEO_GetPreferredMode(NULL);

    // Allocate memory for the display in the uncached region
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    // Initialise the console, required for printf
    console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

    // Set up the video registers with the chosen mode
    VIDEO_Configure(rmode);

    // Tell the video hardware where our display memory is
    VIDEO_SetNextFramebuffer(xfb);

    // Make the display visible
    VIDEO_SetBlack(FALSE);

    // Flush the video register changes to the hardware
    VIDEO_Flush();

    // Wait for Video setup to complete
    VIDEO_WaitVSync();
    if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

    printf("\x1b[2;0H");
    printf("Welcome to the RSSMii Remover!\n\n");
    
    // Initialize WC24
    printf("Init WiiConnect24...\n");
    s32 ret = WC24_Init();
    if (ret < 0) {
        printf("ERROR: WC24_Init returned %d, exiting\n", ret);
        exit(0);
    }
    
    // Go through each record with our Title ID and delete it
    printf("Deleting...\n");
    int count = 0;
    while( (ret = WC24_FindRecord((u32)rssmiititleid, &nwc24record)) != LIBWC24_ENOENT) {
        WC24_DeleteRecord((u32)ret);
        count++;
    }
    printf("Deleted %i entries.\n", count);
    
    // Shutdown WC24
    printf("Shutting down WiiConnect24...\n");
    ret = WC24_Shutdown();
    if (ret < 0) {
        printf("ERROR: WC24_Shutdown returned %d, exiting\n", ret);
        exit(0);
    }
    
    printf("\nFinished, press HOME to exit!\n");

    while(1) {
        // Call WPAD_ScanPads each loop, this reads the latest controller states
        WPAD_ScanPads();

        // WPAD_ButtonsDown tells us which buttons were pressed in this loop
        // this is a "one shot" state which will not fire again until the button has been released
        u32 pressed = WPAD_ButtonsDown(0);
        
        if (pressed & WPAD_BUTTON_HOME) {
            printf("Exiting...");
            exit(0);
        }

        // Wait for the next frame
        VIDEO_WaitVSync();
    }

    return 0;
}
