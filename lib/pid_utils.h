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

#ifndef PID_UTILS
#define PID_UTILS

#include <float.h>
#include <map>
#include "../lib/err_handler.h"

/** Data associated to a particular PID. */
typedef struct {
    int charge;
    double mass;
    const char *name;
} pid_constants;

static pid_constants pid_constants_init(int c, double m, const char *);

int pid_invalid(int pid);
int get_charge(int pid, int *charge);
int get_mass(int pid, double *mass);
int print_pid_names();
int get_pidlist_size_by_charge(int charge, unsigned int *size);
int get_pidlist_by_charge(int charge, int pidlist[]);

#endif
