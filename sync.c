#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "constants.h"

struct Oscillator {
    int s;
    int x;
};


int main() {
    struct Oscillator osc[NUM_OSC];
    for (int i = 0; i < NUM_OSC; i++) {
        osc[i].s = 1;
        osc[i].x = (double)rand() / RAND_MAX;
        osc[i].x *= INIT_VAR;
    }
    
}