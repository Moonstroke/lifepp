#include <ncurses.h>
#include "board.h"
#include "window.h"

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

void end_interface(Window* bwin, Board* b) {
	endwin();                   // termine curses et nettoie la mémoire
	delete bwin;
	delete b;
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

bool handle_input(Window* bwin, Board* b, uint cursor_i, uint cursor_j, uint w, uint h){
	clear();
	bwin->printw(b->tostring());
	//bwin->highlight(cursor_j + 1, cursor_i + 1, 1);
	bwin->refresh();
	switch(bwin->getch()) {
		case KEY_UP:        // Flèches du clavier = déplacer le curseur
			cursor_j = cursor_j > 0 ? cursor_j - 1 : bwin->h - 1;
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
			b->toggle(cursor_i, cursor_j);
			break;
		case (int)'\n':     // Entrée = génération suivante
			b->nextgen();
			break;
		case (int)'q':      // q / Q / 3 == CTRL-C = quitter
		case (int)'Q':
		case 3:
			return false;   // quitter
	}
	return true;            // continuer
}

int main(int argc, char* argv[]) {

	init_interface();

	/*
	 * PARAMÈTRES DU PLATEAU
	 */
	char live('@'), dead(' '), wall('#');
	uint w(15), h(11);

	Window* bwin = new Window(h, w, COLS, LINES, true);
	bwin->draw('|', '-');

	Board* b = new Board(w, h, live, dead, wall);
	init_board(b);

	uint i(0), j(0);

	while(handle_input(bwin, b, i, j, w, h)); // tout le boulot se passe là

	end_interface(bwin, b);
}
