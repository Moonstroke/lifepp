#include <ncurses.h>
#include "board.h"
#include "window.h"

void init_interface() {

	initscr();                  // lancer curses  (initialise LINES et COLS)
	cbreak();                   // pas de mise en cache par ligne ( => pas besoin de taper Entrée)
	raw();                      // idem
	noecho();                   // on désactive l'affichage des entrées
	keypad(stdscr, TRUE);       // active les touches du clavier (Fonc, flèches...)
	curs_set(0);
	/*
	start_color();              // on lance la fonctionnalité de gestion des couleurs
	init_pair(1, COLOR_CYAN, COLOR_BLACK); // paire de couleurs (à approfondir)
	*/
}

void init_board(Board* b) {
	//dessine un + de taille 3x3 :
	//  @
	// @@@
	//  @

	b->toggle(7, 4);
	b->toggle(6, 5);
	b->toggle(7, 5);
	b->toggle(8, 5);
	b->toggle(7, 6);
}

// void printw_board(Window *win, Board *brd) {
// 	unsigned int w, h;
// 	brd->get_dim(w, h);
// 	for(int j(0); j < h; ++j)
// 		for(int i(0); i < w; ++i)
// 			win->printw(i + 1, j + 1, brd->at(i, j));
// }

int main(int argc, char *argv[]) {

	init_interface();

	/*
	 * PARAMÈTRES DU PLATEAU
	 */
	char livechar('@'), deadchar(' ');
	unsigned int w(15), h(11);

	Window* bwin = new Window(w, h, COLS, LINES, true, true);
	bwin->draw();

	Board* b = new Board(w, h, livechar, deadchar);
	init_board(b);

	unsigned int cursor_i(0), cursor_j(0);

	bool quit(false);

	while(!quit) { // tout le boulot se passe là
		clear();
		bwin->draw('|', '-');
		bwin->printw(b);
		bwin->highlight(cursor_i, cursor_j, 1);
		bwin->refresh();
		int ch(bwin->getch());
		switch(ch) {
			case KEY_UP:        // Flèches du clavier = déplacer le curseur
				cursor_j = cursor_j > 0 ? cursor_j - 1 : bwin->h - 3;
				break;
			case KEY_DOWN:
				cursor_j = cursor_j < bwin->h - 3 ? cursor_j + 1 : 0;
				break;
			case KEY_LEFT:
				cursor_i = cursor_i > 0 ? cursor_i - 1 : bwin->w - 3;
				break;
			case KEY_RIGHT:
				cursor_i = cursor_i < bwin->w - 3 ? cursor_i + 1 : 0;
				break;
			case (int)' ':      // espace = inverser la cellule sélectionnée
				b->toggle(cursor_i, cursor_j);
				break;
			case (int)'\n':     // Entrée = génération suivante
				b->nextgen();
				break;
			case (int)'q':      // q / Q / 3 == CTRL-C = quitter
			case (int)'Q':
			case 3:
				quit = true;   // quitter
		}
	}

	endwin();                   // termine curses et nettoie la mémoire
	delete bwin;
	delete b;
}
