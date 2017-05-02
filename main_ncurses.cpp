#include <ncurses.h>
#include "board.h"


void init_interface() {

	initscr();                  // lancer curses
	cbreak();
	raw();                      // pas de mise en cache par ligne ( => pas besoin de taper Entrée)
	noecho();                   // on désactive l'affichage des entrées
	keypad(stdscr, true);       // active les touches du clavier (Fonc, flèches...)
	/*
	start_color();              // on lance la fonctionnalité de gestion des couleurs
	init_pair(1, COLOR_CYAN, COLOR_BLACK); // paire de couleurs (à approfondir)
	*/
}

void end_interface() {
	endwin();                   // termine curses et nettoie la mémoire
	
}

//void center_board(WINDOW* boardwin, int sel_x, int sel_y,

int main(int argc, char* argv[]) {
	
	init_interface();
	
	/*
	 * PARAMÈTRES DU PLATEAU
	 */
	char live('@'), dead(' '), wall('#');
	int w(15), h(11);
	
	
	Board b(w, h, live, dead, wall);
	
	int cursor_i(0), cursor_j(0);
	
	b.toggle(7, 4);
	b.toggle(6, 5);
	b.toggle(7, 5);
	b.toggle(8, 5);
	b.toggle(7, 6);
	
	int ch;
	do {
		clear();
		printw(b.tostring().c_str());
		mvchgat(cursor_j, cursor_i, 1, A_REVERSE, 0, NULL);
		refresh();
		ch = getch();
		switch(ch) {
			case KEY_UP:        // Flèches du clavier = déplacer la sélection de cellule
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
			case (int)'q':      // q / Q = quitter
			case (int)'Q':
				ch = 3;         // façon un peu sale de quitter
		}
	} while(ch != 3);           // 3 == CTRL-C
	
	end_interface();
}
