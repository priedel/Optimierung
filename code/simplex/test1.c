/*
 * test1.c -- 
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <stdlib.h>
#include <simplex.h>

int	main(int argc, char *argv[]) {

	simplex_tableau_t	*tableau = simplex_tableau_new(3, 2);
	simplex_tableau_set(tableau, 0, 0, 2);
	simplex_tableau_set(tableau, 0, 1, 3);
	simplex_tableau_set(tableau, 0, 5, 0);

	simplex_tableau_set(tableau, 1, 0, -1);
	simplex_tableau_set(tableau, 1, 1, 3);
	simplex_tableau_set(tableau, 1, 5, 12);

	simplex_tableau_set(tableau, 2, 0, 1);
	simplex_tableau_set(tableau, 2, 1, 3);
	simplex_tableau_set(tableau, 2, 5, 18);

	simplex_tableau_set(tableau, 3, 0, 4);
	simplex_tableau_set(tableau, 3, 1, 1);
	simplex_tableau_set(tableau, 3, 5, 28);

	simplex_tableau_show(stdout, tableau);

	simplex_tableau_compute(tableau);

	simplex_tableau_show(stdout, tableau);

	exit(EXIT_SUCCESS);
}
