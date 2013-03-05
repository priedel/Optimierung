/*
 * backend.c -- backend for Simplex computations
 *
 * (c) 2013 Prof Dr Andreas Mueller
 */
#include <backend.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <globals.h>

typedef struct backend_registry_s {
	char	*name;
	backend_t	*backend;
} backend_registry_t;

#define	BACKEND_COUNT	10

static backend_registry_t	backend_registry[BACKEND_COUNT] = {
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
	{ .name = NULL, .backend = NULL },
};

/**
 * \brief Find the backend entry by name
 */
static int	backend_find(const char *name) {
	for (int i = 0; i < BACKEND_COUNT; i++) {
		if (backend_registry[i].name) {
			if (strcmp(backend_registry[i].name, name) == 0) {
				return i;
			}
		}
	}
	return -1;
}

/**
 * \brief register a backend
 */
int	backend_register(const char *name, backend_t *backend) {
	/* find out whether the backend already is in the list of
	   known backends */
	if (backend_find(name) >= 0) {
		return -1;
	}

	/* reserve new space for the backend */
	for (int i = 0; i < BACKEND_COUNT; i++) {
		if (NULL == backend_registry[i].name) {
			backend_registry[i].name = strdup(name);
			backend_registry[i].backend = backend;
			return 0;
		}
	}
	return -1;
}

/**
 * \brief unregister a backend
 */
int	backend_unregister(const char *name) {
	int	backendindex = backend_find(name);
	if (backendindex < 0) {
		return -1;
	}

	/* overwrite the backend structure */
	memset(&backend_registry[backendindex], 0, sizeof(backend_registry_t));
}

/**
 * \brief select the currently active backend
 */
static int	backend_active = -1;
int	backend_select(const char *name) {
	int	backendindex = backend_find(name);
	if (backendindex < 0) {
		fprintf(stderr, "backend not found\n");
		return -1;
	}
	return backend_active = backendindex;
}

/**
 * \brief initialize a backend
 */
int	backend_init() {
	if (backend_active < 0) {
		return -1;
	}
	backend_t	*backend = backend_registry[backend_active].backend;
	if (backend->init) {
		return backend->init(backend);
	}
	return 0;
}

int	backend_release() {
	if (backend_active < 0) {
		return -1;
	}
	backend_t	*backend = backend_registry[backend_active].backend;
	if (backend->release) {
		return backend->release(backend);
	}
	return 0;
}

int	backend_pivot(simplex_tableau_t *st, int row, int col) {
	if (backend_active < 0) {
		return -1;
	}
	backend_t	*backend = backend_registry[backend_active].backend;
	return backend->pivot(backend, st, row, col);
}
