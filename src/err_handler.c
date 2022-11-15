// CLAS12 RG-E Analyser.
// Copyright (C) 2022 Bruno Benkel
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

#include "../lib/err_handler.h"

int extractsf_usage() {
    fprintf(stderr, "Usage: extract_sf [-f] [-n NEVENTS] file\n");
    fprintf(stderr, " * -f: Use FMT data. If unspecified, program will only use DC data.\n");
    fprintf(stderr, " * -n NEVENTS: Specify number of events to be processed with optarg.\n");
    fprintf(stderr, " * file: ROOT file to be processed.\n");
    return 1;
}

int extractsf_err(int errcode, char ** in_filename) {
    switch (errcode) {
        case 0:
            return 0;
        case 1:
            fprintf(stderr, "Error. %s is not a valid ROOT file.\n", * in_filename);
            break;
        case 2:
            fprintf(stderr, "Error. Invalid EC layer. Check bank data or add layer to constants.\n");
            break;
        case 3:
            fprintf(stderr, "Error. A particle is in an invalid sector. Check bank integrity.\n");
            break;
        case 4:
            fprintf(stderr, "Error. Could not create sf_results file.\n");
            break;
        default:
            fprintf(stderr, "Programmer Error. Error code %d not implemented in \n", errcode);
            fprintf(stderr, "make_ntuples_err()! You're on your own.\n");
            break;
    }
    free(* in_filename);
    return 1;
}

int extractsf_handle_args_err(int errcode, char ** in_filename) {
    switch (errcode) {
        case 0:
            return 0;
        case 1:
            return extractsf_usage();
        case 2:
            fprintf(stderr, "Error. nevents should be a number greater than 0.\n");
            return extractsf_usage();
        case 3:
            fprintf(stderr, "Error. input file (%s) should be a root file.\n", * in_filename);
            free(* in_filename);
            return 1;
        case 4:
            fprintf(stderr, "Error. %s does not exist!\n", * in_filename);
            free(* in_filename);
            return 1;
        case 5:
            fprintf(stderr, "Error. No file name provided.\n");
            return extractsf_usage();
        default:
            fprintf(stderr, "Programmer Error. Error code %d not implemented in ", errcode);
            fprintf(stderr, "extractsf_handle_args()! You're on your own.\n");
            return 1;
    }
}
