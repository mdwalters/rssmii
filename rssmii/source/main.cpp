#include <wiiuse/wpad.h>
#include <wc24/wc24.h>
#include <fat.h>
#include <mxml.h>

#define LANG_GER lang == 2
#define LANG_FRE lang == 3
#define LANG_SPA lang == 4
#define LANG_DUT lang == 6
int lang;

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

nwc24dl_record myrec;
nwc24dl_entry myent;

struct RSS_Job {
	char url[256];
	char name[256];
	char final_url[512];
} newone;

RSS_Job * jobs;
int ijobs;

void AddJobs()
{
	int which;
	//u64 homebrewtitleid = 0x0001000848424D4CLL;//TitleID for wiibrew+hackmii mail: 00010008-HBML. This is only an ID used for WC24, it's not a real NAND title.
	u64 homebrewtitleid = 0x0001000846454544LL; //TitleID for RSS-Feed mail: 00010008-FEED.
	if (LANG_GER) printf("WC24 initialisieren...");
	else if (LANG_FRE) printf("Initialisation de WiiConnect24...");
	else if (LANG_SPA) printf("Iniciando WC24...");
	else if (LANG_DUT) printf("WC24 aan het opstarten...");
	else printf("Initializing WC24...\n");

	s32 retval = WC24_Init();
	if(retval<0)
	{
		if (LANG_GER) printf("WC24_Init returned %d\n", retval);
		else if (LANG_FRE) printf("WC24_Init a retourné %d\n", retval);
		else if (LANG_SPA) printf("WC24_Init regresó %d\n", retval);
		else if (LANG_DUT) printf("WC24_Init meldde %d\n", retval);
		else printf("WC24_Init returned %d\n", retval);
		return;
	}

	if (LANG_GER) printf("Vorherige records&entries loeschen...\n");
	else if (LANG_FRE) printf("Suppression des anciennes entrées...\n");
	else if (LANG_SPA) printf("Eliminando datos y entradas previas...\n");
	else if (LANG_DUT) printf("Bezig met verwijderen vorige opnames en registraties...\n");
	else printf("Deleting previous records&entries...\n");

	while((retval=WC24_FindRecord((u32)homebrewtitleid, &myrec))!=LIBWC24_ENOENT)
	{
		WC24_DeleteRecord((u32)retval);
	}

	printf("\n");
	for (int i = 0; i < ijobs; i++)
	{
		if (LANG_GER)
		{
			which = 60;
			printf("Record&entry erstellen...\n");
			//Will now compose url:
			memset(jobs[i].final_url, 0, 512);
			snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s&title=%s", jobs[i].url, jobs[i].name);
			s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
			if (retval<0)
			{
				printf("WC24_CreateRecord ergab %d\n", retval);
			}
		}
		else if (LANG_FRE)
		{
			which = 60;
			printf("Création des nouvelles entrées...\n");
			//Will now compose url:
			memset(jobs[i].final_url, 0, 512);
			snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s&title=%s", jobs[i].url, jobs[i].name);
			s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
			if (retval<0)
			{
				printf("WC24_CreateRecord a retourné %d\n", retval);
			}
		}
		else if (LANG_SPA)
		{
			which = 60;
			printf("Creando datos y entradas...\n");
			//Will now compose url:
			memset(jobs[i].final_url, 0, 512);
			snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s&title=%s", jobs[i].url, jobs[i].name);
			s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
			if (retval<0)
			{
				printf("WC24_CreateRecord regresó %d\n", retval);
			}
		}
		else if (LANG_DUT)
		{
			which = 60;
			printf("Bezig met maken nieuwe opname en registratie...\n");
			//Will now compose url:
			memset(jobs[i].final_url, 0, 512);
			snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s&title=%s", jobs[i].url, jobs[i].name);
			s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
			if (retval<0)
			{
				printf("WC24_CreateRecord meldde %d\n", retval);
			}
		}
		else
		{
			which = 60;
			printf("Creating record&entry...\n");
			//Will now compose url:
			memset(jobs[i].final_url, 0, 512);
			snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s&title=%s", jobs[i].url, jobs[i].name);
			s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/ 0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
			if (retval<0)
			{
				printf("WC24_CreateRecord returned %d\n", retval);
			}
		}
		printf("\n\n");
	}
	printf("\n");

	for (int i = 0; i < ijobs; i++)
	{
		if (LANG_GER)
		{
			printf("%s herunterladen...\n", jobs[i].name);

			s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
			if (retval < 0)
			{
				printf("SCHWERWIEGENDER FEHLER: entry konnte nicht gefunden werden\n");
			}
			else
			{
				u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
				if (retval_download < 0) printf("Fehler beim Downloaden: %d\n", retval_download);

				//Save mail, so the mail content won't get overwritten
				u32 retval_save = KD_SaveMail();
				if (retval_save < 0) printf("Fehler beim Speichern: %d\n", retval_save);
			}
		}
		else if (LANG_FRE)
		{
			printf("Téléchargement de %s...\n", jobs[i].name);

			s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
			if (retval < 0)
			{
				printf("ERREUR FATALE: Entrée introuvable\n");
			}
			else
			{
				u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
				if (retval_download < 0) printf("Erreur lors du téléchargement :  %d\n", retval_download);

				//Save mail, so the mail content won't get overwritten
				u32 retval_save = KD_SaveMail();
				if (retval_save < 0) printf("Erreur lors de la sauvegarde :  %d\n", retval_save);
			}
		}
		else if (LANG_SPA)
		{
			printf("Descargando %s...\n", jobs[i].name);

			s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
			if (retval < 0)
			{
				printf("ERROR FATAL: No se pudo encontrar la entrada.\n");
			}
			else
			{
				u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
				if (retval_download < 0) printf("Error al descargar:  %d\n", retval_download);

				//Save mail, so the mail content won't get overwritten
				u32 retval_save = KD_SaveMail();
				if (retval_save < 0) printf("Error al guardar:  %d\n", retval_save);
			}
		}
		else if (LANG_DUT)
		{
			printf("Downloaden %s...\n", jobs[i].name);

			s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
			if (retval < 0)
			{
				printf("KRITIEKE FOUT: Kon registratie niet vinden\n");
			}
			else
			{
				u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
				if (retval_download < 0) printf("Fout tijdens het downloaden:  %d\n", retval_download);

				//Save mail, so the mail content won't get overwritten
				u32 retval_save = KD_SaveMail();
				if (retval_save < 0) printf("Fout tijdens het opslaan:  %d\n", retval_save);
			}
		}
		else
		{
			printf("Downloading %s...\n", jobs[i].name);

			s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
			if (retval < 0)
			{
				printf("FATAL ERROR: Couldn't find entry\n");
			}
			else
			{
				u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
				if (retval_download < 0) printf("Error while Downloading: %d\n", retval_download);

				//Save mail, so the mail content won't get overwritten
				u32 retval_save = KD_SaveMail();
				if (retval_save < 0) printf("Error while Saving: %d\n", retval_save);
			}
		}
		printf("\n");
	}

	if (LANG_GER) printf("WC24 herunterfahren...\n");
	else if (LANG_FRE) printf("Arrêt de WiiConnect24...\n");
	else if (LANG_SPA) printf("Apagando WC24...\n");
	else if (LANG_DUT) printf("WC24 aan het afsluiten...\n");
	else printf("Shutting down WC24...\n");

	retval = WC24_Shutdown();
	if(retval<0)
	{
		if (LANG_GER) printf("WC24_Shutdown ergab %d\n", retval);
		else if (LANG_FRE) printf("WC24_Shutdown a retourné %d\n", retval);
		else if (LANG_SPA) printf("WC24_Shutdown regresó %d\n", retval);
		else if (LANG_DUT) printf("WC24_Shutdown meldde %d\n", retval);
		else printf("WC24_Shutdown returned %d\n", retval);
		return;
	}
	printf("\n\n");
	if (LANG_GER) printf("Fertig.\n");
	else if (LANG_FRE) printf("Terminé.\n");
	else if (LANG_SPA) printf("Hecho.\n");
	else if (LANG_DUT) printf("Klaar.\n");
	else printf("Done.\n");
}

int load_feeds()
{
	if (!fatInitDefault()) {
		return -1;
	}
	mxml_node_t *tree;
	mxml_node_t *rss;
	mxml_node_t *node;
	//printf("DEBUG: load_feeds()\n");
	FILE *fp = fopen("/feeds.xml", "rb");
	if (fp == NULL) {
		fclose(fp);
		//printf("DEBUG: File-Pointer is NULL!!!\n");
		return -2;
	}
	else {
		fseek (fp , 0, SEEK_END);
		long settings_size = ftell (fp);
		rewind (fp);

		if (settings_size > 0) {
			tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
			fclose(fp);
			rss = mxmlFindElement(tree, tree, "rss", NULL, NULL, MXML_DESCEND);
			if (rss == NULL) return -103;

			for (node = mxmlFindElement(rss, rss, "feed", NULL, NULL, MXML_DESCEND); node != NULL; node = mxmlFindElement(node, rss, "feed", NULL, NULL, MXML_DESCEND))
			{
				const char * feedurl = node->child->value.opaque;
				if (feedurl)
				{
					const char * sender = mxmlElementGetAttr(node, "name");
					if (sender)
					{
						//printf("DEBUG: Valid node found!!!\n");
						int old_length = ijobs;
						RSS_Job * tmp = new RSS_Job[old_length];
						for (int i = 0; i < old_length; i++)
						{
							//printf("DEBUG: Copying an element to the temp-Array...\n");
							tmp[i] = jobs[i];
						}
						jobs = new RSS_Job[ old_length + 1 ];
						for (int j = 0; j < old_length ; j++)
						{
							//printf("DEBUG: Copying an element back to the jobs-Array...\n");
							jobs[j] = tmp[j];
						}
						memset(newone.url, 0, 256);
						memset(newone.name, 0, 256);
						snprintf(newone.url, 255, feedurl);
						snprintf(newone.name, 255, sender);
						jobs[old_length] = newone;
						ijobs++;
						//printf("DEBUG: ijobs: %i\n", ijobs);
					}
					else
					{
						//printf("DEBUG: return -102\n");
						return -102;
					}
				}
				else
				{
					//printf("DEBUG: return -101\n");
					return -101;
				}
			}
			mxmlDelete(tree);
			//printf("File loaded.\n\n");
		}
		else {
			fclose(fp);
			//printf("DEBUG: return -1\n");
			return -3;
		}
	}
	return 0;
}

void end()
{
	// In case it's used as a Channel
	u32 *stub = (u32 *)0x80001800;
	if( *stub )
		exit(0);
	SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
}

void fail(int val)
{
	if (LANG_GER) printf("Fehler: %i\nMit HOME zurueck zum Loader.", val);
	else if (LANG_FRE) printf("Erreur : %i\nRetournez sur le loader Homebrew en appuyant sur le bouton HOME.", val);
	else if (LANG_SPA) printf("Error: %i\nVuelve al cargador usando el botón HOME.", val);
	else if (LANG_DUT) printf("Fout: %i\nKeer terug naar de Loader door op de HOME-knop te drukken.", val);
	else printf("Error: %i\nGet back to the Loader by pressing the HOME-Button.", val);
	while (1)
	{
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
		{
			end();
		}
	}
}

int main(int argc, char **argv) {
	jobs = new RSS_Job[0];
	ijobs = 0;
	// Initialise the video system
	VIDEO_Init();

	//Get Language
	lang = CONF_GetLanguage();

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
	if (LANG_GER) printf("Willkommen bei rssmii!\n\n");
	else if (LANG_FRE) printf("Bienvenue sur rssmii !\n\n");
	else if (LANG_SPA) printf("Bienvenido a rssmii!\n\n");
	else if (LANG_DUT) printf("Welkom bij rssmii!\n\n");
	else printf("Welcome to rssmii!\n\n");

	int retval = load_feeds();
	if (retval != 0)
	{
		fail(retval);
	}

	if(LANG_GER) printf("Die folgenden RSS-Feeds wurden von der SD-Karte gelesen und werden abonniert und alle vorherigen Abonnements werden geloescht:\n");
	else if(LANG_FRE) printf("Les flux RSS suivants ont été lus depuis la carte SD et vous allez vous abonnez à ces dernières tandis que les anciens abonnements seront supprimés :\n");
	else if(LANG_SPA) printf("Los siguientes RSS-Feeds han sido leidos desde la tarjeta SD y tu serás suscrito a ellos y todas las suscripciones anteriores serán eliminadas:\n");
	else if(LANG_DUT) printf("De volgende RSS-feeds zijn afkomstig van jouw SD-kaart en je zal geabboneerd worden op die feeds, terwijl alle vorige abbonementen worden verwijderd:\n");
	else printf("The following RSS-Feeds were read from the SD-Card and you will subscribe to them while all previous subscriptions will be deleted:\n");
	for (int i = 0; i < ijobs; i++)
	{
		printf("   %s\n", jobs[i].name);
	}

	if (LANG_GER) printf("\n\nSind sie sicher? (A: Fortsetzen; HOME: Abbrechen)");
	else if (LANG_FRE) printf("\n\nÊtes-vous sûr ? (A: Continuer; HOME: Annuler)");
	else if (LANG_SPA) printf("\n\nEstás seguro?: (A: Continuar; HOME: Abortar)");
	else if (LANG_DUT) printf("\n\nWeet je het zeker? (A: Verder gaan; HOME: Afsluiten)");
	else printf("\n\nAre you sure? (A: Continue; HOME: Abort");

	while (1)
	{
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) end();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) break;
	}

	AddJobs();

	//printf("\n\nDone.");
	if (LANG_GER) printf("\nMit HOME zurueck zum Loader.");
	else if (LANG_FRE) printf("\nMit HOME zurueck zum Loader.");
	else if (LANG_SPA) printf("\nVuelve al cargador con el botón HOME.");
	else if (LANG_DUT) printf("\nGa terug naar jouw loader door op de HOME-knop te drukken.");
	else printf("\nRetournez sur le loader Homebrew en appuyant sur le bouton HOME.");

	while (1)
	{
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
	}
	end();
	//return 0;
}
