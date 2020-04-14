/* See LICENSE file for copyright and license details. */


#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include "marvin.h"

WINDOW * initWindows(int totrs, int totcols);
void drawTitle(WINDOW * updWin, int totrs, int totcols);
void statusbarUpdate(WINDOW * updWin, int totrs, int totcols, int phase);
void checkColor(int tr, int tc);
void initPanels();
void drawControls(WINDOW * updWin, int totrs, int totcols, char wch);
void initwelcomeWin(int totrs, int totcols);
void initJDKWin(int totrs, int totcols);
void initASDKWin(int totrs, int totcols);
void initeditorsetupWin(int totrs, int totcols);
void initAVDWin(int totrs, int totcols);
void initfinalWin(int totrs, int totcols);

char progName[] = "Marvin";
WINDOW * welcomeWindow, * JDKWindow, * ASDKWindow, * editorsetupWindow, * AVDWindow, * finalWindow; int trows,tcolms;
PANEL *welcomePanel, * JDKPanel, * ASDKPanel, * editorsetupPanel, * AVDPanel, * finalPanel, * topPanel;
static chtype COLOR_GRAY;
int cho;
static int jdkInstalled = 1;
static int sdkDownloaded = 1;
static int isAvdInst = 1;
static int editorsetUp = 1;
static char * ASDKloc;


void drawTitle(WINDOW * updWin, int totrs, int totcols) {
	if(can_change_color()) {
		init_color(COLOR_GRAY,GRAY,GRAY,GRAY);
		wbkgd(welcomeWindow,COLOR_GRAY);
	}
	werase(updWin);
	wrefresh(updWin);
	wattron(updWin,COLOR_PAIR(6));
	box(updWin,0,0);
	wattroff(updWin,COLOR_PAIR(6));
	wattron(updWin,COLOR_PAIR(4));
	wattron(updWin,A_BOLD);
	mvwprintw(updWin, 0, (totcols - strlen(progName))/2," %s ",progName);
	wattroff(updWin,COLOR_PAIR(4));
	wattroff(updWin,A_BOLD);
	wrefresh(updWin);
}

void statusbarUpdate(WINDOW * updWin, int totrs, int totcols, int phase) {
	float cfquart = (totcols/4);
	float cthirdquart = cfquart * 3;
	float dbt = cthirdquart - ((int)cfquart);
	float rpos = (totrs * 3 / 4);
	wattron(updWin, A_BOLD);
	mvwaddch(updWin, (int)rpos, (int)cfquart, '|');
	mvwaddch(updWin, (int)rpos, (int)cthirdquart, '|');
	int i;
	wattron(updWin, A_BOLD);
	if(phase == 1) {
		if(jdkInstalled == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=(((int)cfquart)+1); i<((((int)dbt)/4)+((int)cfquart)); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=(((int)cfquart)+1); i<((((int)dbt)/4)+((int)cfquart)); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
	}
	if(phase == 2 || phase == 3) {
		if(jdkInstalled == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=((int)cfquart)+1; i<((((int)dbt)/4)+((int)cfquart)); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=((int)cfquart)+1; i<((((int)dbt)/4)+((int)cfquart)); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
		if(sdkDownloaded == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=(((int)dbt)/4)+((int)cfquart); i<(((int)dbt)*2/4)+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=(((int)dbt)/4)+((int)cfquart); i<(((int)dbt)*2/4)+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
		if(phase == 3) {
			if(sdkDownloaded == 0) {
				wattron(updWin, COLOR_PAIR(2));
				for (i=(((int)dbt)*2/4)+((int)cfquart); i<(((int)dbt)*3/4)+((int)cfquart); i++) {
					mvwaddch(updWin, (int)rpos, i, '|');
				}
				wattroff(updWin, COLOR_PAIR(2));
			} else {
				wattron(updWin, COLOR_PAIR(3));
				for (i=(((int)dbt)*2/4)+((int)cfquart); i<(((int)dbt)*3/4)+((int)cfquart); i++) {
					mvwaddch(updWin, (int)rpos, i, '|');
				}
				wattroff(updWin, COLOR_PAIR(3));
			}
		}
	}
	
	if(phase == 4) {
		if(jdkInstalled == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=((int)cfquart)+1; i<(((int)dbt)/4)+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=((int)cfquart)+1; i<((((int)dbt)/4)+((int)cfquart)); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
		if(sdkDownloaded == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=(((int)dbt)/4)+((int)cfquart); i<(((int)dbt)*3/4)+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=(((int)dbt)/4)+((int)cfquart); i<(((int)dbt)*3/4)+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
		if(editorsetUp == 0) {
			wattron(updWin, COLOR_PAIR(2));
			for (i=(((int)dbt)*3/4)+((int)cfquart); i<(((int)dbt))+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(2));
		} else {
			wattron(updWin, COLOR_PAIR(3));
			for (i=(((int)dbt)*3/4)+((int)cfquart); i<(((int)dbt))+((int)cfquart); i++) {
				mvwaddch(updWin, (int)rpos, i, '|');
			}
			wattroff(updWin, COLOR_PAIR(3));
		}
	}
	wattroff(updWin, A_BOLD);
	wrefresh(updWin);
}

void checkColor(int tr, int tc) {

	char choice[1];

	if (!has_colors()) {
		WINDOW *nocolorWindow;
		nocolorWindow = newwin(3,73,(tr-3)/2,(tc-69)/2);
		box(nocolorWindow,0,0);
		mvwprintw(nocolorWindow,1,2,"%s","This terminal does not support color. Continue without color?(Y/N): ");
		refresh();
		wrefresh(nocolorWindow);
		mvwscanw(nocolorWindow,1,70,"%1s",choice);
		if(strcmp(choice,"N") == 0|| strcmp(choice,"n") == 0) {
			endwin();
			exit(0);
		}
		else if (strcmp(choice,"y") == 0|| strcmp(choice,"y") == 0) {
		}
		 else {
			curs_set(0);
			werase(nocolorWindow);
			wrefresh(nocolorWindow);
			WINDOW *exitingWindow = newwin(3,26,(tr-3)/2,(tc-26)/2);
			mvwprintw(exitingWindow,1,2,"%s","Invalid Choice! Exiting.");
			refresh();
			wrefresh(exitingWindow);
			getch();
			endwin();
			exit(0);
		}
	} else {
		start_color();
	}
}

WINDOW * initWindows(int totrs, int totcols) {
	WINDOW * localWin;
	localWin = newwin(totrs,totcols,0,0);
	wrefresh(localWin);

	return localWin;
}

void initPanels() {
	
	welcomePanel = new_panel(welcomeWindow);
	JDKPanel = new_panel(JDKWindow);
	ASDKPanel = new_panel(ASDKWindow);
	editorsetupPanel = new_panel(editorsetupWindow);
	AVDPanel = new_panel(AVDWindow);
	finalPanel = new_panel(finalWindow);

	set_panel_userptr(welcomePanel,JDKPanel);
	set_panel_userptr(JDKPanel,ASDKPanel);
	set_panel_userptr(ASDKPanel,AVDPanel);
	set_panel_userptr(AVDPanel,editorsetupPanel);
	set_panel_userptr(editorsetupPanel,finalPanel);

	topPanel = welcomePanel;
	update_panels();
	doupdate();
}

void drawControls(WINDOW * updWin, int totrs, int totcols, char wch) {
			wattron(updWin,COLOR_PAIR(3));
			wattron(updWin,A_BOLD);
			mvwprintw(updWin,(totrs-2),((totcols-16)/2),"%s"," | q/Q - Quit | ");
			wattroff(updWin,COLOR_PAIR(3));
			wattron(updWin,COLOR_PAIR(2));
			if(wch != 'w') {
				mvwaddch(updWin,(totrs-2),((totcols-17)/2),ACS_LARROW);
			}
			if(wch != 'f') {
				mvwaddch(updWin,(totrs-2),((totcols+16)/2),ACS_RARROW);
			}
			wattroff(updWin,A_BOLD);
			wattroff(updWin,COLOR_PAIR(2));
			wrefresh(updWin);
}

void initwelcomeWin(int totrs, int totcols) {
	drawTitle(welcomeWindow, totrs, totcols);

	mvwprintw(welcomeWindow, (totrs/2)-2, (totcols - 30)/2, "%s", "Welcome to Easy Android Setup.");
	mvwprintw(welcomeWindow, (totrs/2)-1, (totcols - 60)/2, "%s", "These are the things which this wizard will help you set up.");
	wattron(welcomeWindow,COLOR_PAIR(1));
	wattron(welcomeWindow,A_BOLD);
	mvwprintw(welcomeWindow, (totrs/2), (totcols - 24)/2, "%s", "1. Java development Kit.");
	mvwprintw(welcomeWindow, (totrs/2)+1, (totcols - 70)/2, "%s", "2. Android SDK, and all the SDK tools reuired for Android development.");
	mvwprintw(welcomeWindow, (totrs/2)+2, (totcols - 26)/2, "%s", "3. Android Virtual Device.");
	mvwprintw(welcomeWindow, (totrs/2)+3, (totcols - 58)/2, "%s", "4. The editor which you intend to use for Android Development.");
	wattroff(welcomeWindow,COLOR_PAIR(1));
	wattroff(welcomeWindow,A_BOLD);
	wrefresh(welcomeWindow);

	drawControls(welcomeWindow, totrs, totcols, 'w');

	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_RIGHT:
					topPanel = JDKPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initJDKWin(totrs,totcols);
				break;
			default:
				continue;
		}
	}
}

void initJDKWin(int totrs, int totcols) {
	int ynch;
	drawTitle(JDKWindow, totrs, totcols);
	if(jdkInstalled != 0 ){
		def_prog_mode();
		endwin();
		jdkInstalled = system("java --version > /dev/null"); 
		reset_prog_mode();
		refresh();
	}
	if(jdkInstalled != 0) {
		char * JDKloc = malloc(sizeof(char) * 256);
		char * fullJDKStuff = malloc(sizeof(char) * 500);
		wattron(JDKWindow,COLOR_PAIR(3));
		wattron(JDKWindow,A_BOLD);
		mvwprintw(JDKWindow,totrs/2,totcols/7,"%s","JDK is not installed in this system.");
		wattroff(JDKWindow,A_BOLD);
		wattroff(JDKWindow,COLOR_PAIR(3));
		mvwprintw(JDKWindow,(totrs/2)+1,totcols/7,"%s","Enter the directory(full path) where you want to install JDK(openJDK 13): ");
		curs_set(1);
		echo();
		wrefresh(JDKWindow);
		wscanw(JDKWindow, "%256s", JDKloc);
		noecho();
		curs_set(0);
		wrefresh(JDKWindow);
		sprintf(fullJDKStuff,"/bin/bash ./JDKinstaller.sh %256s",JDKloc);
		def_prog_mode();
		endwin();
		if(system(fullJDKStuff) == 0) {
			jdkInstalled = 0;
			reset_prog_mode();
			refresh();
			drawTitle(JDKWindow, totrs, totcols);
			wattron(JDKWindow,COLOR_PAIR(2));
			wattron(JDKWindow,A_BOLD);
			mvwprintw(JDKWindow, totrs/2, (totcols-32)/2, "%s", "JDK is now installed in this system.");
			wattroff(JDKWindow,COLOR_PAIR(2));
			wattroff(JDKWindow,A_BOLD);
			statusbarUpdate(JDKWindow, totrs, totcols,1);
			drawControls(JDKWindow, totrs, totcols, 'j');
			wrefresh(JDKWindow);
			free(JDKloc);
			free(fullJDKStuff);
		} else {
			reset_prog_mode();
			refresh();
			drawTitle(JDKWindow, totrs, totcols);
			wattron(JDKWindow,COLOR_PAIR(5));
			wattron(JDKWindow,A_BOLD);
			mvwprintw(JDKWindow,(totrs)/2,(totcols-42)/2,"%s","JDK couldn't be installed in this system.");
			wattroff(JDKWindow,COLOR_PAIR(5));
			wattron(JDKWindow,COLOR_PAIR(3));
			mvwprintw(JDKWindow,(totrs/2)+1,(totcols-17)/2,"%s","Try again?(Y/N): ");
			wattroff(editorsetupWindow,A_BOLD);
			wattroff(editorsetupWindow,COLOR_PAIR(3));
			curs_set(1);
			echo();
			wattroff(JDKWindow,A_BOLD);
			wattroff(JDKWindow,COLOR_PAIR(3));
			wrefresh(JDKWindow);
			ynch = wgetch(JDKWindow);
			noecho();
			curs_set(0);
			if(ynch == 'y' || ynch == 'Y') {
				free(JDKloc);
				free(fullJDKStuff);
				initJDKWin(totrs,totcols);
			}
			else {
				drawTitle(JDKWindow, totrs, totcols);
				wattron(JDKWindow, COLOR_PAIR(1));
				wattron(JDKWindow, A_BOLD);
				mvwprintw(JDKWindow,(totrs)/2,(totcols-24)/2,"%s","JDK installation skipped.");
				wattroff(JDKWindow, COLOR_PAIR(1));
				wattroff(JDKWindow, A_BOLD);
				statusbarUpdate(JDKWindow, totrs, totcols,1);
				drawControls(JDKWindow, totrs, totcols, 'j');
				wrefresh(JDKWindow);	
				free(JDKloc);
				free(fullJDKStuff);
			}
		}
	}
	else {
		wattron(JDKWindow,COLOR_PAIR(2));
		wattron(JDKWindow,A_BOLD);
		mvwprintw(JDKWindow, totrs/2, (totcols-32)/2, "%s", "JDK is installed in this system.");
		wattroff(JDKWindow,COLOR_PAIR(2));
		wattroff(JDKWindow,A_BOLD);
		statusbarUpdate(JDKWindow, totrs, totcols,1);
		drawControls(JDKWindow, totrs, totcols, 'j');
		wrefresh(JDKWindow);
	}

	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_RIGHT:
				topPanel = ASDKPanel;
				top_panel(topPanel);
				update_panels();
				doupdate();
				cho = '\0';
				getmaxyx(stdscr,totrs,totcols);
				initASDKWin(totrs, totcols);
				break;
			case KEY_LEFT:
				topPanel = welcomePanel;
				top_panel(topPanel);
				update_panels();
				doupdate();
				cho = '\0';
				getmaxyx(stdscr,totrs,totcols);
				initwelcomeWin(totrs,totcols);
				break;
			default:
				continue;
		}
	}
}


void initASDKWin(int totrs, int totcols) {
	char lit;
	char * SDKMcom;
	char * fullASDKStuff = malloc(sizeof(char) * 500);
	char * toolName;
	
	drawTitle(ASDKWindow, totrs, totcols);
	if(sdkDownloaded != 0) {
		wattron(ASDKWindow,COLOR_PAIR(3));
		wattron(ASDKWindow,A_BOLD);
		mvwprintw(ASDKWindow, (totrs/2)-1, (totcols)/7, "%s", "Android SDK manager is not installed.");
		wattroff(ASDKWindow,A_BOLD);
		wattroff(ASDKWindow,COLOR_PAIR(3));
		mvwprintw(ASDKWindow, (totrs/2), (totcols)/7, "%s", "Enter the directory where you want to install the Android SDK manager: ");
		curs_set(1);
		echo();
		wrefresh(ASDKWindow);
		ASDKloc = malloc(sizeof(char) * 256);
		wscanw(ASDKWindow, "%256s", ASDKloc);
		drawControls(ASDKWindow, totrs, totcols, 'a');
		sprintf(fullASDKStuff, "/bin/bash ./ASDKinstaller.sh %256s",ASDKloc);
		curs_set(0);
		noecho();
		wrefresh(ASDKWindow);
		def_prog_mode();
		endwin();
		sdkDownloaded = system(fullASDKStuff); 
		if(sdkDownloaded == 0) {
			reset_prog_mode();
			refresh();
			free(fullASDKStuff);
			while(cho != 9) {
				drawTitle(ASDKWindow, totrs, totcols);
				wattron(ASDKWindow,COLOR_PAIR(5));
				wattron(ASDKWindow,A_BOLD);
				mvwprintw(ASDKWindow, (totrs/2)-3, (totcols-47)/2, "%s", "Press 'l' to list all the available tools/SDKs.");
				wattroff(ASDKWindow,COLOR_PAIR(5));
				wattron(ASDKWindow,COLOR_PAIR(6));
				mvwprintw(ASDKWindow, (totrs/2)-2, (totcols-43)/2, "%s", "Press 'i' to install an available tool/SDK.");
				wattroff(ASDKWindow,COLOR_PAIR(6));
				wattron(ASDKWindow,COLOR_PAIR(3));
				mvwprintw(ASDKWindow, (totrs/2)-1, (totcols-44)/2, "%s", "Press 'Tab' to finish installing tools/SDKs.");
				wattroff(ASDKWindow,A_BOLD);
				wattroff(ASDKWindow,COLOR_PAIR(3));
				mvwprintw(ASDKWindow, (totrs/2)+1, (totcols-19)/2, "%s", "Enter your choice: ");
				curs_set(1);
				echo();
				wrefresh(ASDKWindow);
				cho = getch();
				curs_set(0);
				noecho();
				wrefresh(ASDKWindow);
				switch(cho) {
					case 9:
						drawTitle(ASDKWindow, totrs, totcols);
						statusbarUpdate(ASDKWindow, totrs, totcols,2);
						drawControls(ASDKWindow, totrs, totcols, 'a');
						wattron(ASDKWindow, COLOR_PAIR(1));
						wattron(ASDKWindow, A_BOLD);
						mvwprintw(ASDKWindow, totrs/2, (totcols-32)/2, "%s", "SDK/tools installation finished.");
						wattroff(ASDKWindow, COLOR_PAIR(1));
						wattroff(ASDKWindow, A_BOLD);
						wrefresh(ASDKWindow);
						break;
					case 'l':
						SDKMcom = malloc(sizeof(char) * 468);
						sprintf(SDKMcom, "/bin/bash %s/cmdline-tools/latest/bin/sdkmanager --list; echo 'Press Enter/Return to exit.'; read",ASDKloc);
						def_prog_mode();
						endwin();
						if(system(SDKMcom) != 0) {
							reset_prog_mode();
							refresh();
							drawTitle(ASDKWindow, totrs, totcols);
							wattron(ASDKWindow, COLOR_PAIR(3));
							mvwprintw(ASDKWindow, totrs/2, (totcols-26)/2, "%s", "SDKs/tools listing failed.");
							wattroff(ASDKWindow, COLOR_PAIR(3));
							wrefresh(ASDKWindow);
							sleep(1);
						} else {	
							reset_prog_mode();
							refresh();
							drawTitle(ASDKWindow, totrs, totcols);
							wattron(ASDKWindow, COLOR_PAIR(2));
							mvwprintw(ASDKWindow, totrs/2, (totcols-31)/2, "%s", "SDKs/tools listing successfull.");
							wattroff(ASDKWindow, COLOR_PAIR(2));
							wrefresh(ASDKWindow);
							sleep(1);
						}
						free(SDKMcom);
						reset_prog_mode();
						refresh();
						break;
					case 'i':
						toolName = malloc(sizeof(char) * 200);
						drawTitle(ASDKWindow, totrs, totcols);
						mvwprintw(ASDKWindow, totrs/2, (totcols-31)/2, "%s", "Enter the name of the tool/SDK: ");
						wrefresh(ASDKWindow);
						curs_set(1);
						echo();
						wscanw(ASDKWindow,"%200s",toolName);
						curs_set(0);
						noecho();
						def_prog_mode();
						endwin();
						SDKMcom = malloc(sizeof(char) * 600);
						sprintf(SDKMcom, "/bin/bash %s/cmdline-tools/latest/bin/sdkmanager --install %s", ASDKloc, toolName);
						if(system(SDKMcom) != 0) {
							reset_prog_mode();
							refresh();
							drawTitle(ASDKWindow, totrs, totcols);
							wattron(ASDKWindow, COLOR_PAIR(3));
							mvwprintw(ASDKWindow, totrs/2, (totcols-20)/2, "%s", "Installation failed.");
							wattroff(ASDKWindow, COLOR_PAIR(3));
							wrefresh(ASDKWindow);
							sleep(1);
						} else {	
							reset_prog_mode();
							refresh();
							drawTitle(ASDKWindow, totrs, totcols);
							wattron(ASDKWindow, COLOR_PAIR(2));
							mvwprintw(ASDKWindow, totrs/2, (totcols-25)/2, "%s", "Installation successfull.");
							wattroff(ASDKWindow, COLOR_PAIR(2));
							wrefresh(ASDKWindow);
							sleep(1);
						}
						free(toolName);
						free(SDKMcom);
						reset_prog_mode();
						refresh();
						drawControls(ASDKWindow, totrs, totcols, 'a');
						break;
					default:
						continue;
				}
			}
			cho = '\0';
		} else {
			reset_prog_mode();
			refresh();
			free(fullASDKStuff);
			drawTitle(ASDKWindow, totrs, totcols);
			wattron(ASDKWindow,COLOR_PAIR(5));
			wattron(ASDKWindow,A_BOLD);
			mvwprintw(ASDKWindow, totrs/2, (totcols-30)/2, "%s", "Failed to install SDK manager.");
			wattroff(ASDKWindow,COLOR_PAIR(5));
			wattron(ASDKWindow,COLOR_PAIR(3));
			mvwprintw(ASDKWindow, (totrs/2)+1, (totcols-17)/2, "%s", "Try again?(Y/N): ");
			wattroff(ASDKWindow,COLOR_PAIR(3));
			wattroff(ASDKWindow,A_BOLD);
			curs_set(1);
			echo();
			wrefresh(ASDKWindow);
			lit = getch();
			curs_set(0);
			noecho();
			wrefresh(ASDKWindow);
			if(lit == 'y' || lit == 'Y') {
				free(ASDKloc);
				initASDKWin(totrs, totcols);
			}
			drawTitle(ASDKWindow, totrs, totcols);
			statusbarUpdate(ASDKWindow, totrs, totcols,2);
			drawControls(ASDKWindow, totrs, totcols, 'a');
			wattron(ASDKWindow, COLOR_PAIR(1));
			wattron(ASDKWindow, A_BOLD);
			mvwprintw(ASDKWindow, totrs/2, (totcols-36)/2, "%s", "Installation of SDK manager skipped.");
			wattroff(ASDKWindow, COLOR_PAIR(1));
			wattroff(ASDKWindow, A_BOLD);
			wrefresh(ASDKWindow);
			free(ASDKloc);
		}
	} else {
		statusbarUpdate(ASDKWindow, totrs, totcols, 2);
		drawControls(ASDKWindow, totrs, totcols, 'a');
		wattron(ASDKWindow, COLOR_PAIR(1));
		wattron(ASDKWindow, A_BOLD);
		mvwprintw(ASDKWindow, totrs/2, (totcols-25)/2, "%s", "SDK Manager is installed.");
		wattroff(ASDKWindow, COLOR_PAIR(1));
		wattroff(ASDKWindow, A_BOLD);
		wrefresh(ASDKWindow);
	}
	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_RIGHT:
					topPanel = AVDPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initAVDWin(totrs, totcols);
				break;
			case KEY_LEFT:
					topPanel = JDKPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initJDKWin(totrs, totcols);
				break;
			default:
				continue;
		}
	}
}

void initAVDWin(int totrs, int totcols) {
	char * avdPKGName;
	char * avdName;
	char * avdID;
	char * avdPath;
	char * avdInst;
	if(sdkDownloaded == 0) {
		if(isAvdInst != 0) {
			while(cho != 9) {
				drawTitle(AVDWindow, totrs, totcols);
				wattron(AVDWindow,COLOR_PAIR(5));
				wattron(AVDWindow,A_BOLD);
				mvwprintw(AVDWindow, (totrs/2)-3, (totcols-52)/2, "%s", "Press 'l' to list all the available virtual devices.");
				wattroff(AVDWindow,COLOR_PAIR(5));
				wattron(AVDWindow,COLOR_PAIR(6));
				mvwprintw(AVDWindow, (totrs/2)-2, (totcols-37)/2, "%s", "Press 'i' to install a virtual device.");
				wattroff(AVDWindow,COLOR_PAIR(6));
				wattron(AVDWindow,COLOR_PAIR(3));
				mvwprintw(AVDWindow, (totrs/2)-1, (totcols-49)/2, "%s", "Press 'Tab' to finish installing virtual devices.");
				wattroff(AVDWindow,A_BOLD);
				wattroff(AVDWindow,COLOR_PAIR(3));
				mvwprintw(AVDWindow, (totrs/2)+1, (totcols-19)/2, "%s", "Enter your choice: ");
				curs_set(1);
				echo();
				wrefresh(AVDWindow);
				cho = getch();
				switch(cho) {
					case 9:
						drawTitle(AVDWindow, totrs, totcols);
						statusbarUpdate(AVDWindow, totrs, totcols,3);
						drawControls(AVDWindow, totrs, totcols, 'a');
						wattron(AVDWindow, COLOR_PAIR(1));
						wattron(AVDWindow, A_BOLD);
						mvwprintw(AVDWindow, totrs/2, (totcols-36)/2, "%s", "Virtual device installation finished.");
						wattroff(AVDWindow, COLOR_PAIR(1));
						wattroff(AVDWindow, A_BOLD);
						curs_set(0);
						noecho();
						wrefresh(AVDWindow);
						isAvdInst = 0;
						break;
					case 'l':
						def_prog_mode();
						endwin();
						avdInst = malloc(sizeof(char) * 356);
						sprintf(avdInst, "/bin/bash %s/cmdline-tools/latest/bin/avdmanager list", ASDKloc);
						if(system(avdInst) != 0) {
							drawTitle(AVDWindow, totrs, totcols);
							wattron(AVDWindow, COLOR_PAIR(3));
							mvwprintw(AVDWindow, totrs/2, (totcols-19)/2, "%s", "AVD listing failed.");
							wattroff(AVDWindow, COLOR_PAIR(3));
							wrefresh(AVDWindow);
							sleep(1);
						} else {	
							drawTitle(AVDWindow, totrs, totcols);
							wattron(AVDWindow, COLOR_PAIR(2));
							mvwprintw(AVDWindow, totrs/2, (totcols-24)/2, "%s", "AVD listing successfull.");
							wattroff(AVDWindow, COLOR_PAIR(2));
							wrefresh(AVDWindow);
							sleep(1);
						}
						reset_prog_mode();
						refresh();
						break;
					case 'i':
						drawTitle(AVDWindow, totrs, totcols);
						avdPKGName = malloc(sizeof(char) * 100);
						wattron(AVDWindow, COLOR_PAIR(4));
						mvwprintw(AVDWindow, (totrs/2)-1, (totcols)/7, "%s", "(e.g. 'system-images;android-19;google_apis;x86')");
						wattron(AVDWindow, A_BOLD);
						mvwprintw(AVDWindow, (totrs/2)-2, (totcols)/7, "%s", "Enter the package name of the AVD: ");
						wattroff(AVDWindow, COLOR_PAIR(4));
						wattroff(AVDWindow, A_BOLD);
						wrefresh(AVDWindow);
						wscanw(AVDWindow, "%100s", avdPKGName);
						avdName = malloc(sizeof(char) * 100);
						wattron(AVDWindow, COLOR_PAIR(5));
						wattron(AVDWindow, A_BOLD);
						mvwprintw(AVDWindow, (totrs/2), (totcols)/7, "%s", "Enter the name of the AVD: ");
						wattroff(AVDWindow, COLOR_PAIR(5));
						wattroff(AVDWindow, A_BOLD);
						wrefresh(AVDWindow);
						wscanw(AVDWindow, "%100s", avdName);
						avdID = malloc(sizeof(char) * 20);
						wattron(AVDWindow, COLOR_PAIR(1));
						wattron(AVDWindow, A_BOLD);
						mvwprintw(AVDWindow, totrs/2+1, (totcols)/7, "%s", "Enter the device Index/ID of the AVD: ");
						wattroff(AVDWindow, COLOR_PAIR(1));
						wattroff(AVDWindow, A_BOLD);
						wrefresh(AVDWindow);
						wscanw(AVDWindow, "%20s", avdID);
						avdPath = malloc(sizeof(char) * 256);
						wattron(AVDWindow, COLOR_PAIR(6));
						wattron(AVDWindow, A_BOLD);
						mvwprintw(AVDWindow, (totrs/2)+2, (totcols)/7, "%s", "Enter the path where the AVD has to be installed: ");
						wattroff(AVDWindow, COLOR_PAIR(6));
						wattroff(AVDWindow, A_BOLD);
						wrefresh(AVDWindow);
						wscanw(AVDWindow, "%256s", avdPath);
						curs_set(0);
						noecho();
						wrefresh(AVDWindow);
						avdInst = malloc(sizeof(char) * 476);
						sprintf(avdInst, "/bin/bash %s/cmdline-tools/latest/bin/avdmanager -f -n %s -d %s -p %s -k %s", ASDKloc, avdName, avdID, avdPath, avdPKGName);
						def_prog_mode();
						endwin();
						if(system(avdInst) == 0){
							drawTitle(AVDWindow, totrs, totcols);
							wattron(AVDWindow, COLOR_PAIR(3));
							mvwprintw(AVDWindow, totrs/2, (totcols-24)/2, "%s", "AVD installation failed.");
							wattroff(AVDWindow, COLOR_PAIR(3));
							wrefresh(AVDWindow);
							sleep(1);
						} else {	
							drawTitle(AVDWindow, totrs, totcols);
							wattron(AVDWindow, COLOR_PAIR(2));
							mvwprintw(AVDWindow, totrs/2, (totcols-29)/2, "%s", "AVD installation successfull.");
							wattroff(AVDWindow, COLOR_PAIR(2));
							wrefresh(AVDWindow);
							sleep(1);
						}
						reset_prog_mode();
						refresh();
						free(avdPKGName);
						free(avdName);
						free(avdID);
						free(avdPath);
						free(avdInst);
						break;
					default:
						continue;
				}
			}
			cho = '\0';
		} else {
			drawTitle(AVDWindow, totrs, totcols);
			statusbarUpdate(AVDWindow, totrs, totcols,3);
			drawControls(AVDWindow, totrs, totcols, 'a');
			wattron(AVDWindow, COLOR_PAIR(1));
			wattron(AVDWindow, A_BOLD);
			mvwprintw(AVDWindow, totrs/2, (totcols-36)/2, "%s", "Virtual device installation finished.");
			wattroff(AVDWindow, COLOR_PAIR(1));
			wattroff(AVDWindow, A_BOLD);
			wrefresh(AVDWindow);
		}
	} else {
		drawTitle(AVDWindow, totrs, totcols);
		wattron(AVDWindow, COLOR_PAIR(2));
		wattron(AVDWindow, A_BOLD);
		mvwprintw(AVDWindow, (totrs/2)-1, (totcols-85)/2, "%s", "AVD Manager + SDK Manager + other tools are downloaded as a part of the previous step.");
		wattroff(AVDWindow, COLOR_PAIR(2));
		wattron(AVDWindow, COLOR_PAIR(5));
		mvwprintw(AVDWindow, totrs/2, (totcols-83)/2, "%s", "Virtual devices can't be managed without completing the previous step successfully.");
		wattroff(AVDWindow, COLOR_PAIR(5));
		wattroff(AVDWindow, A_BOLD);
		mvwprintw(AVDWindow, (totrs/2)+1, (totcols-30)/2, "%s", "Do you want to go back?(Y/N): ");
		echo();
		curs_set(1);
		wrefresh(AVDWindow);
		cho = getch();
		noecho();
		curs_set(0);
		wrefresh(AVDWindow);
		if(cho == 'y' || cho == 'Y') {
			initASDKWin(totrs, totcols);
		}
		drawTitle(AVDWindow, totrs, totcols);
		statusbarUpdate(AVDWindow, totrs, totcols,3);
		drawControls(AVDWindow, totrs, totcols, 'a');
		wattron(AVDWindow, COLOR_PAIR(1));
		wattron(AVDWindow, A_BOLD);
		mvwprintw(AVDWindow, totrs/2, (totcols-25)/2, "%s", "AVD installation skipped.");
		wattroff(AVDWindow, A_BOLD);
		wattroff(AVDWindow, COLOR_PAIR(1));
		wrefresh(AVDWindow);
	}
	
	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_RIGHT:
					topPanel = editorsetupPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initeditorsetupWin(totrs, totcols);
				break;
			case KEY_LEFT:
					topPanel = ASDKPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initASDKWin(totrs, totcols);
				break;
			default:
				continue;
		}
	}
}

void initeditorsetupWin(int totrs, int totcols) {
	int tryAgain;
	char * editorsetupSh;
	drawTitle(editorsetupWindow, totrs, totcols);
	if(editorsetUp != 0) {
		wattron(editorsetupWindow, COLOR_PAIR(6));
		wattron(editorsetupWindow, A_BOLD);
		mvwprintw(editorsetupWindow, (totrs/2)-1, (totcols/7), "%s", "a. Vim.");
		mvwprintw(editorsetupWindow, (totrs/2), (totcols/7), "%s", "b. Visual Studio Code.");
		mvwprintw(editorsetupWindow, (totrs/2)+1, (totcols/7), "%s", "c. Eclipse");
		wattroff(editorsetupWindow, COLOR_PAIR(6));
		wattron(editorsetupWindow, COLOR_PAIR(5));
		mvwprintw(editorsetupWindow, (totrs/2)+2, (totcols/7), "%s", "Editor you intend to use(a-b)");
		wattroff(editorsetupWindow, COLOR_PAIR(5));
		wattron(editorsetupWindow, COLOR_PAIR(4));
		mvwprintw(editorsetupWindow, (totrs/2)+2, (totcols/7)+29, "%s", " / ");
		wattroff(editorsetupWindow, COLOR_PAIR(4));
		wattron(editorsetupWindow, COLOR_PAIR(3));
		mvwprintw(editorsetupWindow, (totrs/2)+2, (totcols/7)+32, "%s", "Tab to skip : ");
		wattroff(editorsetupWindow, COLOR_PAIR(3));
		wattroff(editorsetupWindow, A_BOLD);
		echo();
		curs_set(1);
		wrefresh(editorsetupWindow);
		cho = getch();
		noecho();
		curs_set(0);
		wrefresh(editorsetupWindow);
		switch(cho) {
			case 9:
				drawTitle(editorsetupWindow, totrs, totcols);
				wattron(editorsetupWindow, COLOR_PAIR(1));
				wattron(editorsetupWindow, A_BOLD);
				mvwprintw(editorsetupWindow, totrs/2, (totcols-42)/2, "%s", "Editor installation/configuration skipped.");
				wattroff(editorsetupWindow, A_BOLD);
				wattroff(editorsetupWindow, COLOR_PAIR(1));
				wrefresh(editorsetupWindow);
				statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
				drawControls(editorsetupWindow, totrs, totcols, 'e');
				break;
			case 'b':
				def_prog_mode();
				endwin();
				if(system("code --install-extension adelphes.android-dev-ext") == 0) {
					editorsetUp = 0;
					reset_prog_mode();
					refresh();
					drawTitle(editorsetupWindow, totrs, totcols);
					wattron(editorsetupWindow, COLOR_PAIR(2));
					wattron(editorsetupWindow, A_BOLD);
					mvwprintw(editorsetupWindow, totrs/2, (totcols-43)/2, "%s", "Editor installation/configuration finished.");
					wattroff(editorsetupWindow, A_BOLD);
					wattroff(editorsetupWindow, COLOR_PAIR(2));
					wrefresh(editorsetupWindow);
					statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
					drawControls(editorsetupWindow, totrs, totcols, 'e');
				} else {
					reset_prog_mode();
					refresh();
					drawTitle(editorsetupWindow, totrs, totcols);
					wattron(editorsetupWindow,A_BOLD);
					wattron(editorsetupWindow,COLOR_PAIR(5));
					mvwprintw(editorsetupWindow, totrs/2, (totcols-41)/2, "%s", "Editor installation/configuration failed.");
					mvwprintw(editorsetupWindow, (totrs/2)+1, (totcols-27)/2, "%s", "(Make sure VSC is installed)");
					wattroff(editorsetupWindow,COLOR_PAIR(5));
					wattron(editorsetupWindow,COLOR_PAIR(3));
					mvwprintw(editorsetupWindow, (totrs/2)+2, (totcols-17)/2, "%s", "Try again?(Y/N): ");
					wattroff(editorsetupWindow,A_BOLD);
					wattroff(editorsetupWindow,COLOR_PAIR(3));
					curs_set(1);
					echo();
					wrefresh(editorsetupWindow);
					tryAgain = getch();
					curs_set(0);
					noecho();
					wrefresh(editorsetupWindow);
					if(tryAgain == 'y' || tryAgain == 'Y') {
						initeditorsetupWin(totrs, totcols);
					} else {
						drawTitle(editorsetupWindow, totrs, totcols);
						wattron(editorsetupWindow, COLOR_PAIR(1));
						wattron(editorsetupWindow, A_BOLD);
						mvwprintw(editorsetupWindow, totrs/2, (totcols-42)/2, "%s", "Editor installation/configuration skipped.");
						wattroff(editorsetupWindow, A_BOLD);
						wattroff(editorsetupWindow, COLOR_PAIR(1));
						wrefresh(editorsetupWindow);
						statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
						drawControls(editorsetupWindow, totrs, totcols, 'e');
					}
				}
				break;
			case 'a':
			case 'c':
				editorsetupSh = malloc(sizeof(char) * 30);
				sprintf(editorsetupSh, "/bin/bash ./editorSetup.sh %c", cho);
				def_prog_mode();
				endwin();
				if(system(editorsetupSh) == 0) {
					editorsetUp = 0;
					free(editorsetupSh);
					reset_prog_mode();
					refresh();
					drawTitle(editorsetupWindow, totrs, totcols);
					wattron(editorsetupWindow, COLOR_PAIR(2));
					wattron(editorsetupWindow, A_BOLD);
					mvwprintw(editorsetupWindow, totrs/2, (totcols-43)/2, "%s", "Editor installation/configuration finished.");
					wattroff(editorsetupWindow, A_BOLD);
					wattroff(editorsetupWindow, COLOR_PAIR(2));
					wrefresh(editorsetupWindow);
					statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
					drawControls(editorsetupWindow, totrs, totcols, 'e');
				}
				else {
					free(editorsetupSh);
					reset_prog_mode();
					refresh();
					drawTitle(editorsetupWindow, totrs, totcols);
					wattron(editorsetupWindow,COLOR_PAIR(5));
					mvwprintw(editorsetupWindow, totrs/2, (totcols-41)/2, "%s", "Editor installation/configuration failed.");
					wattroff(editorsetupWindow,COLOR_PAIR(5));
					wattron(editorsetupWindow,COLOR_PAIR(3));
					wattron(editorsetupWindow,A_BOLD);
					mvwprintw(editorsetupWindow, (totrs/2)+1, (totcols-17)/2, "%s", "Try again?(Y/N): ");
					curs_set(1);
					echo();
					wrefresh(editorsetupWindow);
					tryAgain = getch();
					curs_set(0);
					noecho();
					wrefresh(editorsetupWindow);
					if(tryAgain == 'y' || tryAgain == 'Y') {
						initeditorsetupWin(totrs, totcols);
					} else {
						drawTitle(editorsetupWindow, totrs, totcols);
						wattron(editorsetupWindow, COLOR_PAIR(1));
						wattron(editorsetupWindow, A_BOLD);
						mvwprintw(editorsetupWindow, totrs/2, (totcols-42)/2, "%s", "Editor installation/configuration skipped.");
						wattroff(editorsetupWindow, A_BOLD);
						wattroff(editorsetupWindow, COLOR_PAIR(1));
						wrefresh(editorsetupWindow);
						statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
						drawControls(editorsetupWindow, totrs, totcols, 'e');
					}
				}
				break;
			default:
				drawTitle(editorsetupWindow, totrs, totcols);
				wattron(editorsetupWindow, COLOR_PAIR(3));
				wattron(editorsetupWindow,A_BOLD);
				mvwprintw(editorsetupWindow, totrs/2, (totcols-15)/2, "%s", "Invalid choice.");
				wattroff(editorsetupWindow,A_BOLD);
				wattroff(editorsetupWindow, COLOR_PAIR(3));
				wrefresh(editorsetupWindow);
				sleep(1);
				initeditorsetupWin(totrs, totcols);
				break;
		}
	} else {
		drawTitle(editorsetupWindow, totrs, totcols);
		wattron(editorsetupWindow, COLOR_PAIR(2));
		wattron(editorsetupWindow, A_BOLD);
		mvwprintw(editorsetupWindow, totrs/2, (totcols-43)/2, "%s", "Editor installation/configuration finished.");
		wattroff(editorsetupWindow, A_BOLD);
		wattroff(editorsetupWindow, COLOR_PAIR(2));
		wrefresh(editorsetupWindow);
		statusbarUpdate(editorsetupWindow, totrs, totcols, 4);
		drawControls(editorsetupWindow, totrs, totcols, 'e');
	}

	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_RIGHT:
				topPanel = finalPanel;
				top_panel(topPanel);
				update_panels();
				doupdate();
				cho = '\0';
				getmaxyx(stdscr,totrs,totcols);
				initfinalWin(totrs, totcols);
				break;
			case KEY_LEFT:
				topPanel = AVDPanel;
				top_panel(topPanel);
				update_panels();
				doupdate();
				cho = '\0';
				getmaxyx(stdscr,totrs,totcols);
				initAVDWin(totrs, totcols);
				break;
			default:
				continue;
		}
	}
}

void initfinalWin(int totrs, int totcols) {
	drawTitle(finalWindow, totrs, totcols);
	drawControls(editorsetupWindow, totrs, totcols, 'f');
	wattron(finalWindow, A_BOLD);
	if(jdkInstalled == 0) {
		wattron(finalWindow, COLOR_PAIR(2));
	} else {
		wattron(finalWindow, COLOR_PAIR(3));
	}
	mvwprintw(finalWindow, (totrs/2)-2, (totcols-16)/2, "%s", "JDK installation");
	if(jdkInstalled == 0) {
		mvwaddch(finalWindow, (totrs/2)-2, ((totcols-16)/2)-2, ACS_DIAMOND);
		wattroff(finalWindow, COLOR_PAIR(2));
	} else {
		wattron(finalWindow, COLOR_PAIR(3));
	}
	if(sdkDownloaded == 0) {
		wattron(finalWindow, COLOR_PAIR(2));
	} else {
		wattron(finalWindow, COLOR_PAIR(3));
	}
	mvwprintw(finalWindow, totrs/2, (totcols-16)/2, "%s", "SDK installation");
	mvwprintw(finalWindow, (totrs/2)+2, (totcols-16)/2, "%s", "AVD installation");
	if(sdkDownloaded == 0) {
		mvwaddch(finalWindow, (totrs/2), ((totcols-16)/2)-2, ACS_DIAMOND);
		mvwaddch(finalWindow, (totrs/2)+2, ((totcols-16)/2)-2, ACS_DIAMOND);
		wattroff(finalWindow, COLOR_PAIR(2));
	} else {
		wattroff(finalWindow, COLOR_PAIR(3));
	}
	if(editorsetUp == 0) {
		wattron(finalWindow, COLOR_PAIR(2));
	} else {
		wattron(finalWindow, COLOR_PAIR(3));
	}
	mvwprintw(finalWindow, (totrs/2)+4, (totcols-33)/2, "%s", "Editor configuration/installation");
	if(editorsetUp == 0) {
		mvwaddch(finalWindow, (totrs/2)+4, ((totcols-33)/2)-2, ACS_DIAMOND);
		wattroff(finalWindow, COLOR_PAIR(2));
	} else {
		wattroff(finalWindow, COLOR_PAIR(3));
	}
	wattroff(finalWindow, A_BOLD);
	wrefresh(finalWindow);
	statusbarUpdate(finalWindow, totrs, totcols, 4);
	drawControls(finalWindow, totrs, totcols, 'f');
	
	while(1) {
		cho = getch();
		switch(cho) {
			case 'q':
			case 'Q':
				endwin();
				exit(0);
				break;
			case KEY_LEFT:
					topPanel = editorsetupPanel;
					top_panel(topPanel);
					update_panels();
					doupdate();
					cho = '\0';
					getmaxyx(stdscr,totrs,totcols);
					initeditorsetupWin(totrs, totcols);
				break;
			default:
				continue;
		}
	}
}

int main() {

	initscr();
	getmaxyx(stdscr,trows,tcolms);
	checkColor(trows,tcolms);
	noecho();
	raw();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);

	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);

	refresh();
	
	welcomeWindow = initWindows(trows, tcolms);	
	JDKWindow = initWindows(trows, tcolms);
	ASDKWindow = initWindows(trows, tcolms);
	editorsetupWindow = initWindows(trows, tcolms);
	AVDWindow = initWindows(trows, tcolms);
	finalWindow = initWindows(trows, tcolms);

	initPanels();

	initwelcomeWin(trows, tcolms);
	return 0;
}

