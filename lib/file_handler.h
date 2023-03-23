// CLAS12 RG-E Analyser.
// Copyright (C) 2022-2023 Bruno Benkel
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any
// later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
// details.
//
// You can see a copy of the GNU Lesser Public License under the LICENSE file.

#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "constants.h"

int get_sf_params(char *filename, double sf[NSECTORS][SF_NPARAMS][2]);
int get_bin_edges(FILE *file_in, long unsigned int *bin_nedges,
        double **bin_edges, long unsigned int *pids_size);
int get_binnings(FILE *file_in, long int *b_sizes, double **binnings,
        long unsigned int *pids_size);
int get_acc_corr(FILE *file_in, long unsigned int pids_size,
        long unsigned int nbins, long int *pids, int **n_thrown, int **n_simul);
int read_acc_corr_file(char *acc_filename, long unsigned int bin_nedges[5],
        double ***bin_edges, long unsigned int *pids_size,
        long unsigned int *nbins, long int **pids, int ***n_thrown,
        int ***n_simul);

#endif
