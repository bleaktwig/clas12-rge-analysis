#include "../lib/utilities.h"

// Pass from radians to degrees.
double to_deg(double radians) {
    return radians * (180.0 / M_PI);
}

// Compute a vector's magnitude from its components.
double calc_magnitude(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

// Get angle between two vectors.
double calc_angle(double x1, double y1, double z1, double x2, double y2, double z2) {
    return acos((x1*x2 + y1*y2 + z1*z2)/(calc_magnitude(x1,y1,z1) * calc_magnitude(x2,y2,z2)));
}

// Rotate a vector around the y axis by theta.
void rotate_y(double *x, double *z, double th) {
    double x_prev = *x;
    double z_prev = *z;
    *x =  x_prev*cos(th) + z_prev*sin(th);
    *z = -x_prev*sin(th) + z_prev*cos(th);
}

// Rotate a vector around the z axis by theta.
void rotate_z(double *x, double *y, double th) {
    double x_prev = *x;
    double y_prev = *y;
    *x = x_prev*cos(th) - y_prev*sin(th);
    *y = x_prev*sin(th) + y_prev*cos(th);
}

// Catch a string within a list.
int catch_string(const char * list[], int size) {
    double x;
    while (true) {
        char str[32];
        printf(">>> ");
        scanf("%31s", str);

        for (int i = 0; i < size; ++i) if (!strcmp(str, list[i])) x = i;
        if (x != -1) break;
    }

    return x;
}

// Catch a long value from stdin.
long catch_long() {
    long r;
    while (true) {
        char str[32];
        char * endptr;
        printf(">>> ");
        scanf("%31s", str);
        r = strtol(str, &endptr, 10);

        if (endptr != str) break;
    }

    return r;
}

// Catch a double value from stdin.
double catch_double() {
    double r;
    while (true) {
        char str[32];
        char * endptr;
        printf(">>> ");
        scanf("%31s", str);
        r = strtod(str, &endptr);

        if (endptr != str) break;
    }

    return r;
}

int find_ntuple(char ** tuplename, const char * list[], int x) {
    for (int i = 0; i < METADATA_LIST_SIZE; ++i) {
        if (!strcmp(list[x], METADATA_LIST[i])) {
            * tuplename = (char *) malloc(strlen(METADATA_STR) + 1);
            strcpy(* tuplename, METADATA_STR);
            return 0;
        }
    }
    for (int i = 0; i < PARTICLE_LIST_SIZE; ++i) {
        if (!strcmp(list[x], PARTICLE_LIST[i])) {
            * tuplename = (char *) malloc(strlen(PARTICLE_STR) + 1);
            strcpy(* tuplename, PARTICLE_STR);
            return 0;
        }
    }
    for (int i = 0; i < CALORIMETER_LIST_SIZE; ++i) {
        if (!strcmp(list[x], CALORIMETER_LIST[i])) {
            * tuplename = (char *) malloc(strlen(CALORIMETER_STR) + 1);
            strcpy(* tuplename, CALORIMETER_STR);
            return 0;
        }
    }
    for (int i = 0; i < SCINTILLATOR_LIST_SIZE; ++i) {
        if (!strcmp(list[x], SCINTILLATOR_LIST[i])) {
            * tuplename = (char *) malloc(strlen(SCINTILLATOR_STR) + 1);
            strcpy(* tuplename, SCINTILLATOR_STR);
            return 0;
        }
    }
    for (int i = 0; i < SIDIS_LIST_SIZE; ++i) {
        if (!strcmp(list[x], SIDIS_LIST[i])) {
            * tuplename = (char *) malloc(strlen(SIDIS_STR) + 1);
            strcpy(* tuplename, SIDIS_STR);
            return 0;
        }
    }

    return 1;
}

// Insert a 1-dimensional histogram of floating point numbers into a map.
int insert_TH1F(std::map<const char *, TH1 *> *map, const char *k, const char *n, const char *xn,
               int bins, double min, double max) {
    map->insert(std::pair<const char *, TH1 *>
            (n, new TH1F(Form("%s: %s", k, n), Form("%s;%s", n, xn), bins, min, max)));
    return 0;
}

// Insert a 2-dimensional histogram of floating point numbers into a map.
int insert_TH2F(std::map<const char *, TH1 *> *map, const char *k,
                const char *n, const char *nx, const char *ny,
                int xbins, double xmin, double xmax, int ybins, double ymin, double ymax) {
    map->insert(std::pair<const char *, TH1 *>
            (n, new TH2F(Form("%s: %s", k, n), Form("%s;%s;%s", n, nx, ny),
                         xbins, xmin, xmax, ybins, ymin, ymax)));
    return 0;
}
