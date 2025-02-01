#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// SIM_TIME is the number of iterations to run the simulation
#define SIM_TIME 200
// NUM_OSC is the number of oscillators in the simulation
#define NUM_OSC  10
// GAMMA is a constant used in the simulation
#define GAMMA 0.1
// DELTA_TIME is the time step for each iteration
#define DELTA_TIME 0.01
// EPSILON is a small value used in the simulation
#define EPSILON 0.03

// Define a macro to find the minimum of two values
#define min(a,b) (((a) < (b)) ? (a) : (b))

int main() {
    // Seed the random number generator
    srand(time(NULL));
    
    /* 
    Define variable and Initial values
    S is the baseline rate of change for each oscillator, currently all oscillators have the same rate of change
    dist is the change in the oscillator value for each iteration
    x is the value of each oscillator
    change is the change in the oscillator value based on the baseline rate of change and the current value
    */
    double S[1];
    S[0] = 5;
    double dist;
    double x[NUM_OSC];
    double change;
    
    // Initialize the values of the oscillators to random values between 0 and 1
    for (int i = 0; i < NUM_OSC; i++) {
        x[i] = (double)rand() / RAND_MAX;
    }

    // Get the output file name from the user
    char outputFileName[256];
    printf("Enter the output file name: ");
    scanf("%s", outputFileName);

    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    // Write the column headers to the output file
    for (int i = 0; i < NUM_OSC; i++) {
        fprintf(outputFile, "%6d\t\t", i); 
    }
    fprintf(outputFile, "\n");  

    // Run the simulation for SIM_TIME iterations
    for (int b = 0; b < SIM_TIME; b++) {
        // Update the value of each oscillator based on the baseline rate of change and the current value
        for (int i = 0; i < NUM_OSC; i++) {
            change = S[0] - GAMMA * x[i];
            dist = change * DELTA_TIME;
            x[i] += dist;
            // If the oscillator value exceeds 1, update the values of all other oscillators
            if (x[i] >= 1) {
                for (int j = 0; j < NUM_OSC; j++) {
                    if (i != j) {
                        // Ensure that the updated value does not exceed 1
                        x[j] = min(1, x[j] + EPSILON);
                    }
                }
            }
            // Write the value of the oscillator to the output file
            fprintf(outputFile, "%lf\t", x[i]); 
        }

        // Reset the value of any oscillator that has exceeded 1
        for (int i = 0; i < NUM_OSC; i++) {
            if (x[i] >= 1) {
                x[i] = 0.0;
            }
        }
        fprintf(outputFile, "\n"); 
    }
    
    fclose(outputFile); 
    return 0;
}

