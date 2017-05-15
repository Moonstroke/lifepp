#include <ncurses.h>
#include "board.h"


void init_interface();
void end_interface();

WINDOW* create_win(int height, int width, int startx, int starty, bool center = false, char hbord = 0, char vbord = 0) {
	WINDOW* win;
	int h(height + 2), w(width + 2), x, y;
	if(center)
		win = newwin(h, w, (starty - h) / 2, (startx - w) / 2);
	else
		win = newwin(h, w, starty, startx);
	box(win, hbord, vbord);
	
	return win;
}

//void center_board(WINDOW* boardwin, int sel_x, int sel_y,

int main(int argc, char* argv[]) {
	
	init_interface();
	
	/*
	 * PARAMÈTRES DU PLATEAU
	 */
	char live('@'), dead(' '), wall('#');
	int w(15), h(11);
	
	WINDOW* boardwin(create_win(h, w, COLS, LINES, true, '|', '-'));
	
	Board b(w, h, live, dead, wall);
	
	int cursor_i(0), cursor_j(0);
	
	b.toggle(7, 4);
	b.toggle(6, 5);
	b.toggle(7, 5);
	b.toggle(8, 5);
	b.toggle(7, 6);
	
	bool quit(false);
	while(!quit) {
		clear();
		wprintw(boardwin, b.tostring().c_str());
		mvwchgat(boardwin, cursor_j + 1, cursor_i + 1, 1, A_REVERSE, 0, NULL);
		wrefresh(boardwin);
		switch(wgetch(boardwin)) {
			case KEY_UP:        // Flèches du clavier = déplacer le curseur
				cursor_j = cursor_j > 0 ? cursor_j - 1 : h - 1;
				break;
			case KEY_DOWN:
				cursor_j = cursor_j < h ? cursor_j + 1 : 0;
				break;
			case KEY_LEFT:
				cursor_i = cursor_i > 0 ? cursor_i - 1 : w - 1;
				break;
			case KEY_RIGHT:
				cursor_i = cursor_i < w ? cursor_i + 1 : 0;
				break;
			case (int)' ':      // espace = inverser la cellule sélectionnée
				b.toggle(cursor_i, cursor_j);
				break;
			case (int)'\n':     // Entrée = génération suivante
				b.nextgen();
				break;
			case (int)'q':      // q / Q / 3 == CTRL-C = quitter
			case (int)'Q':
			case 3:
				quit = true;
		}
	}
	
	end_interface();
}


void init_interface() {

	initscr();                  // lancer curses  (initialise LINES et COLS)
	cbreak();                   // pas de mise en cache par ligne ( => pas besoin de taper Entrée)
	raw();                      // idem
	noecho();                   // on désactive l'affichage des entrées
	keypad(stdscr, TRUE);       // active les touches du clavier (Fonc, flèches...)
	/*
	start_color();              // on lance la fonctionnalité de gestion des couleurs
	init_pair(1, COLOR_CYAN, COLOR_BLACK); // paire de couleurs (à approfondir)
	*/
}

void end_interface() {
	endwin();                   // termine curses et nettoie la mémoire
	
}
