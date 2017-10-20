#include <wiiuse/wpad.h>
#include <wc24/wc24.h>
#include <fat.h>
#include <mxml.h>

#define BUF_SIZE 2047

#define msg(x) messages[lang][x]

int lang;

enum {MSG_INIT, MSG_INIT_RET, MSG_DEL_PREV, MSG_CREATE, MSG_CREATE_RET, MSG_DOWNLOAD, MSG_ERR_FATAL, MSG_ERR_DOWNLOAD, MSG_ERR_SAVE,
	MSG_SHUTDOWN, MSG_SHUTDOWN_RET, MSG_DONE, MSG_ERR_GO_BACK, MSG_WELCOME, MSG_RSS_FEEDS, MSG_SURE, MSG_GO_BACK};

static char *messages[][256] = {
	{ /* Japanese - TODO */
		"Initializing WC24...\n",
		"WC24_Init returned %d\n",
		"Deleting previous records&entries...\n",
		"Creating record&entry...\n",
		"WC24_CreateRecord returned %d\n",
		"Downloading %s...\n",
		"FATAL ERROR: Couldn't find entry\n",
		"Error while Downloading: %d\n",
		"Error while Saving: %d\n",
		"Shutting down WC24...\n",
		"WC24_Shutdown returned %d\n",
		"Done.\n",
		"Error: %i\nGet back to the Loader by pressing the HOME-Button.",
		"Welcome to rssmii!\n\n",
		"The following RSS-Feeds were read from the SD-Card and you will subscribe to them while all previous subscriptions will be deleted:\n",
		"\n\nAre you sure? (A: Continue; HOME: Abort)",
		"\nGet back to the Loader with the HOME-Button."
	},
	{ /* English */
		"Initializing WC24...\n",
		"WC24_Init returned %d\n",
		"Deleting previous records&entries...\n",
		"Creating record&entry...\n",
		"WC24_CreateRecord returned %d\n",
		"Downloading %s...\n",
		"FATAL ERROR: Couldn't find entry\n",
		"Error while Downloading: %d\n",
		"Error while Saving: %d\n",
		"Shutting down WC24...\n",
		"WC24_Shutdown returned %d\n",
		"Done.\n",
		"Error: %i\nGet back to the Loader by pressing the HOME-Button.",
		"Welcome to rssmii!\n\n",
		"The following RSS-Feeds were read from the SD-Card and you will subscribe to them while all previous subscriptions will be deleted:\n",
		"\n\nAre you sure? (A: Continue; HOME: Abort)",
		"\nGet back to the Loader with the HOME-Button."
	},
	{ /* German */
		"WC24 initialisieren...",
		"WC24_Init returned %d\n",
		"Vorherige records&entries loeschen...\n",
		"Record&entry erstellen...\n",
		"WC24_CreateRecord ergab %d\n",
		"%s herunterladen...\n",
		"SCHWERWIEGENDER FEHLER: entry konnte nicht gefunden werden\n",
		"Fehler beim Downloaden: %d\n",
		"Fehler beim Speichern: %d\n",
		"WC24 herunterfahren...\n",
		"WC24_Shutdown ergab %d\n",
		"Fertig.\n",
		"Fehler: %i\nMit HOME zurueck zum Loader.",
		"Willkommen bei rssmii!\n\n",
		"Die folgenden RSS-Feeds wurden von der SD-Karte gelesen und werden abonniert und alle vorherigen Abonnements werden geloescht:\n",
		"\n\nSind sie sicher? (A: Fortsetzen; HOME: Abbrechen)",
		"\nMit HOME zurueck zum Loader.",
	},
	{ /* French */
		"Initialisation de WiiConnect24...",
		"WC24_Init a retourné %d\n",
		"Suppression des anciennes entrées...\n",
		"Création des nouvelles entrées...\n",
		"WC24_CreateRecord a retourné %d\n",
		"Téléchargement de %s...\n",
		"ERREUR FATALE: Entrée introuvable\n",
		"Erreur lors du téléchargement :  %d\n",
		"Erreur lors de la sauvegarde :  %d\n",
		"Arrêt de WiiConnect24...\n",
		"WC24_Shutdown a retourné %d\n",
		"Terminé.\n",
		"Erreur : %i\nRetournez sur le loader Homebrew en appuyant sur le bouton HOME.",
		"Bienvenue sur rssmii !\n\n",
		"Les flux RSS suivants ont été lus depuis la carte SD et vous allez vous abonnez à ces dernières tandis que les anciens abonnements seront supprimés :\n",
		"\n\nÊtes-vous sûr ? (A: Continuer; HOME: Annuler)",
		"\nRetournez sur le loader Homebrew en appuyant sur le bouton HOME.",
	},
	{ /* Spanish */
		"Iniciando WC24...",
		"WC24_Init devuelto %d\n",
		"Eliminando datos y entradas previas...\n",
		"Creando datos y entradas...\n",
		"WC24_CreateRecord devuelto %d\n",
		"Descargando %s...\n",
		"ERROR FATAL: No se pudo encontrar la entrada.\n",
		"Error al descargar:  %d\n",
		"Error al guardar:  %d\n",
		"Apagando WC24...\n",
		"WC24_Shutdown devuelto %d\n",
		"Hecho.\n",
		"Error: %i\nVuelve al cargador usando el botón HOME.",
		"Bienvenido a rssmii!\n\n",
		"Los siguientes RSS-Feeds han sido leidos desde la tarjeta SD y tu serás suscrito a ellos, todas las suscripciones anteriores serán eliminadas:\n",
		"\n\nEstás seguro?: (A: Continuar; HOME: Cancelar)",
		"\nVuelve al cargador con el botón HOME.",
	},
	{ /* Italian - TODO */
		"Initializing WC24...\n",
		"WC24_Init returned %d\n",
		"Deleting previous records&entries...\n",
		"Creating record&entry...\n",
		"WC24_CreateRecord returned %d\n",
		"Downloading %s...\n",
		"FATAL ERROR: Couldn't find entry\n",
		"Error while Downloading: %d\n",
		"Error while Saving: %d\n",
		"Shutting down WC24...\n",
		"WC24_Shutdown returned %d\n",
		"Done.\n",
		"Error: %i\nGet back to the Loader by pressing the HOME-Button.",
		"Welcome to rssmii!\n\n",
		"The following RSS-Feeds were read from the SD-Card and you will subscribe to them while all previous subscriptions will be deleted:\n",
		"\n\nAre you sure? (A: Continue; HOME: Abort)",
		"\nGet back to the Loader with the HOME-Button."
	},
	{ /* Dutch */
		"WC24 aan het opstarten...",
		"WC24_Init meldde %d\n",
		"Bezig met verwijderen vorige opnames en registraties...\n",
		"Bezig met maken nieuwe opname en registratie...\n",
		"WC24_CreateRecord meldde %d\n",
		"Downloaden %s...\n",
		"KRITIEKE FOUT: Kon registratie niet vinden\n",
		"Fout tijdens het downloaden:  %d\n",
		"Fout tijdens het opslaan:  %d\n",
		"WC24 aan het afsluiten...\n",
		"WC24_Shutdown meldde %d\n",
		"Klaar.\n",
		"Fout: %i\nKeer terug naar de Loader door op de HOME-knop te drukken.",
		"Welkom bij rssmii!\n\n",
		"De volgende RSS-feeds zijn afkomstig van jouw SD-kaart en je zal geabboneerd worden op die feeds, terwijl alle vorige abbonementen worden verwijderd:\n",
		"\n\nWeet je het zeker? (A: Verder gaan; HOME: Afsluiten)",
		"\nGa terug naar jouw loader door op de HOME-knop te drukken.",
	}
};

static char _buffer[BUF_SIZE + 1];
static char *_hex = "0123456789abcdef";

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

char *url_encode(char *str, char *buf)
{
	int c;
	char *result = buf;
	for (; c = *str; str++) {
		if (('a' <= c && c <= 'z')
		    || ('A' <= c && c <= 'Z')
		    || ('0' <= c && c <= '9'))
			*buf++ = c;
		else {
			*buf++ ='%';
			*buf++ = _hex[c >> 4];
			*buf++ = _hex[c & 15];
		}
	}
	*buf = '\0';
	return result;
}

void AddJobs()
{
	int which;
	//u64 homebrewtitleid = 0x0001000848424D4CLL;//TitleID for wiibrew+hackmii mail: 00010008-HBML. This is only an ID used for WC24, it's not a real NAND title.
	u64 homebrewtitleid = 0x0001000846454544LL; //TitleID for RSS-Feed mail: 00010008-FEED.
	printf(msg(MSG_INIT));

	s32 retval = WC24_Init();
	if(retval<0)
	{
		printf(msg(MSG_INIT_RET), retval);
		return;
	}

	printf(msg(MSG_DEL_PREV));

	while((retval=WC24_FindRecord((u32)homebrewtitleid, &myrec))!=LIBWC24_ENOENT)
	{
		WC24_DeleteRecord((u32)retval);
	}

	printf("\n");
	for (int i = 0; i < ijobs; i++)
	{
		int offset = 0;
		which = 30;
		printf(msg(MSG_CREATE));
		//Will now compose url:
		memset(jobs[i].final_url, 0, 512);
		offset = snprintf(jobs[i].final_url, 511, "http://rss.wii.rc24.xyz/rss_displayer.php?feedurl=%s", url_encode(jobs[i].url, _buffer));
		snprintf(jobs[i].final_url + offset, 511, "&title=%s", url_encode(jobs[i].name, _buffer));
		s32 retval = WC24_CreateRecord(&myrec, &myent, (u32)homebrewtitleid, homebrewtitleid, /*0x4842*/ 0x4645, WC24_TYPE_MSGBOARD, WC24_RECORD_FLAGS_DEFAULT, WC24_FLAGS_HB, which, 0x5a0, 0, jobs[i].final_url, NULL);
		if (retval<0)
		{
			printf(msg(MSG_CREATE_RET), retval);
		}
		printf("\n\n");
	}
	printf("\n");

	for (int i = 0; i < ijobs; i++)
	{
		printf(msg(MSG_DOWNLOAD), jobs[i].name);

		s32 retval = WC24_FindEntry((u32)homebrewtitleid, jobs[i].final_url, &myent, 0);
		if (retval < 0)
		{
			printf(msg(MSG_ERR_FATAL));
		}
		else
		{
			u32 retval_download = KD_Download(KD_DOWNLOADFLAGS_MANUAL, (u16)retval, 0x0);
			if (retval_download < 0) printf(msg(MSG_ERR_DOWNLOAD), retval_download);
			//Save mail, so the mail content won't get overwritten
			u32 retval_save = KD_SaveMail();
			if (retval_save < 0) printf(msg(MSG_ERR_SAVE), retval_save);
		}
		printf("\n");
	}

	printf(msg(MSG_SHUTDOWN));

	retval = WC24_Shutdown();
	if(retval<0)
	{
		printf(msg(MSG_SHUTDOWN_RET), retval);
		return;
	}
	printf("\n\n");
	printf(msg(MSG_DONE));
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
	printf(msg(MSG_ERR_GO_BACK), val);
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
	printf(msg(MSG_WELCOME));

	int retval = load_feeds();
	if (retval != 0)
	{
		fail(retval);
	}

	printf(msg(MSG_RSS_FEEDS));
	for (int i = 0; i < ijobs; i++)
	{
		printf("   %s\n", jobs[i].name);
	}

	printf(msg(MSG_SURE));

	while (1)
	{
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) end();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) break;
	}

	AddJobs();

	//printf("\n\nDone.");
	printf(msg(MSG_GO_BACK));

	while (1)
	{
		WPAD_ScanPads();
		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) break;
	}
	end();
	//return 0;
}
