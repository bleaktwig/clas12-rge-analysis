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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <TFile.h>
#include "../lib/io_handler.h"

int run(char *gen_file, char *sim_file, std::vector<double> &b_Q2,
        std::vector<double> &b_nu,  std::vector<double> &b_zh,
        std::vector<double> &b_Pt2, std::vector<double> &b_phiPQ)
{
    printf("\n --- INPUT: ---\n");
    printf("b_Q2    = [");
    for (const double &i : b_Q2) printf("%5.2f, ", i);
    printf("]\nb_nu    = [");
    for (const double &i : b_nu) printf("%5.2f, ", i);
    printf("]\nb_zh    = [");
    for (const double &i : b_zh) printf("%5.2f, ", i);
    printf("]\nb_Pt2   = [");
    for (const double &i : b_Pt2) printf("%5.2f, ", i);
    printf("]\nb_phiPQ = [");
    for (const double &i : b_phiPQ) printf("%5.2f, ", i);
    printf("]\ngen_file = %s\n", gen_file);
    printf("sim_file = %s\n", sim_file);
    printf(" --- ------ ---\n\n");

    // Open input files and load TTrees.
    TFile *g_in = TFile::Open(gen_file, "READ");
    if (!g_in || g_in->IsZombie()) return 9;
    TFile *s_in = TFile::Open(sim_file, "READ");
    if (!s_in || s_in->IsZombie()) return 10;

    // Open output file.
    const char *out_file = "../data/acc_corr.txt";
    if (!access(out_file, F_OK)) return 11;
    FILE *t_out = fopen("../data/acc_corr.txt", "w");

    // TODO. Compute acceptance correction.
    // NOTE. A recursive solution would be much more elegant.
    // for (const double &i_Q2 : b_Q2) {
    //     for (const double &i_nu : b_nu) {
    //         for (const double &i_zh : b_zh) {
    //             for (const double &i_Pt2 : b_Pt2) {
    //                 for (const double &i_phiPQ : b_phiPQ) {
    //                     // TODO. Compute and store ratio to output file.
    //                 }
    //             }
    //         }
    //     }
    // }

    // Close input and output files.
    g_in->Close();
    s_in->Close();
    fclose(t_out);

    // Free up memory.
    free(gen_file);
    free(sim_file);

    return 0;
}

int usage() {
    fprintf(stderr,
            "Usage: acc_corr [q:n:z:p:f:] genfile simfile\n"
            " * -q ...  : Q2 bins.\n"
            " * -n ...  : nu bins.\n"
            " * -z ...  : z_h bins.\n"
            " * -p ...  : Pt2 bins.\n"
            " * -f ...  : phi_PQ bins.\n"
            " * genfile : generated events ROOT file.\n"
            " * simfile : simulated events ROOT file.\n\n"
            "    Get the 5-dimensional acceptance correction factors for Q2, nu"
            ", z_h, Pt2, and\n    phi_PQ. For each optional argument, an array "
            "of doubles is expected. The first\n    double will be the lower "
            "limit of the leftmost bin, the final double will be\n    the upper"
            " limit of the rightmost bin, and all doubles inbetween will be the"
            "\n    separators between each bin.\n\n"
    );
    return 1;
}

int handle_err(int errcode) {
    switch (errcode) {
        case 0:
            return 0;
        case 2:
            fprintf(stderr, "Error. All binnings should have *at least* two "
                            "values -- a minimum and a\n maximum.\n\n");
            break;
        case 3:
            fprintf(stderr, "Error. Generated file should be in root "
                            "format.\n\n");
            break;
        case 4:
            fprintf(stderr, "Error. Generated file does not exist!\n\n");
            break;
        case 5:
            fprintf(stderr, "Error. Simulated file should be in root "
                            "format.\n\n");
            break;
        case 6:
            fprintf(stderr, "Error. Simulated file does not exist!\n\n");
            break;
        case 7:
            fprintf(stderr, "Error. Please specify a generated file.\n\n");
            break;
        case 8:
            fprintf(stderr, "Error. Please specify a simulated file.\n\n");
            break;
        case 9:
            fprintf(stderr, "Error. Generated file is not a valid ROOT file."
                            "\n\n");
            break;
        case 10:
            fprintf(stderr, "Error. Simulated file is not a valid ROOT file."
                            "\n\n");
            break;
        case 11:
            fprintf(stderr, "Error. Output file already exists.\n\n");
            break;
        default:
            fprintf(stderr, "Error code %d not implemented!\n\n", errcode);
            return 1;
    }
    return usage();
}

int handle_args(int argc, char **argv, char **gen_file, char **sim_file,
        std::vector<double> &b_Q2, std::vector<double> &b_nu,
        std::vector<double> &b_zh, std::vector<double> &b_Pt2,
        std::vector<double> &b_phiPQ)
{
    // Handle optional arguments.
    int opt;
    while ((opt = getopt(argc, argv, "q:n:z:p:f:g:s:")) != -1) {
        switch (opt) {
            case 'q': grab_multiarg(argc, argv, &optind, b_Q2);    break;
            case 'n': grab_multiarg(argc, argv, &optind, b_nu);    break;
            case 'z': grab_multiarg(argc, argv, &optind, b_zh);    break;
            case 'p': grab_multiarg(argc, argv, &optind, b_Pt2);   break;
            case 'f': grab_multiarg(argc, argv, &optind, b_phiPQ); break;
            case 'g': grab_filename(optarg, gen_file);             break;
            case 's': grab_filename(optarg, sim_file);             break;
            default: break;
        }
    }

    // Check that all vectors have *at least* two values.
    if (b_Q2.size() < 2 || b_nu.size() < 2 || b_zh.size() < 2 ||
            b_Pt2.size() < 2 || b_phiPQ.size() < 2) {
        return 2;
    }

    // Check input file existence and validity.
    if (!(*gen_file)) return 7;
    int errcode = check_root_filename(*gen_file);
    if (errcode) return errcode;
    if (!(*sim_file)) return 8;
    errcode     = check_root_filename(*sim_file);
    if (errcode) return errcode + 2;

    return 0;
}

int main(int argc, char **argv) {
    char *gen_file = NULL;
    char *sim_file = NULL;
    std::vector<double> b_Q2;
    std::vector<double> b_nu;
    std::vector<double> b_zh;
    std::vector<double> b_Pt2;
    std::vector<double> b_phiPQ;

    int errcode = handle_args(argc, argv, &gen_file, &sim_file, b_Q2, b_nu,
            b_zh, b_Pt2, b_phiPQ);
    if (handle_err(errcode)) return 1;

    return handle_err(run(gen_file, sim_file, b_Q2, b_nu, b_zh, b_Pt2,
            b_phiPQ));
}
