#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Sync.h"
#include "SyncConstants.h"

int main(int argc, char *argv[]) {
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
    int LinkType, NetworkType;
    
    // Get the LinkType and NetworkType from the user
    printf("Enter the LinkType\n");
    printf("Select 1 For Global Linkage\n");
    printf("Select 2 For Four Way Linkage\n");
    printf("Select 3 For Eight Way Linkage\n");
    scanf("%d", &LinkType);
    
    if (LinkType != 1) {
        printf("Enter the NetworkType\n");
        printf("Select 1 For Taurus Network\n");
        printf("Select 2 For Cylindrical Network\n");
        printf("Select 3 For 2d Network\n");
        scanf("%d", &NetworkType);
    }
    
    // Initialize the values of the oscillators to random values between 0 and 1
    for (int i = 0; i < NUM_OSC; i++) {
        x[i] = (double)rand() / RAND_MAX;
        x[i] *= 0.2;
    }

    // Get the output file name from the user
    char outputFileName[256];
    char directory[256] = "..//data//";
    printf("Enter the output file name: ");
    scanf("%s", outputFileName);
    char *outputFileName1 = strcat(directory, outputFileName);

    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName1, "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    PrintLog(outputFileName1, LinkType, NetworkType, S);

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
                if (LinkType == 2 && NetworkType == 1) {
                    FourWayTaurusLinkage(x, i);
                }
                else if (LinkType == 1) {
                    GlobalLinkage(x, i);
                }
                else if (LinkType == 2 && NetworkType == 3) {
                    FourWay2dLinkage(x, i);
                }
                else if (LinkType == 3 && NetworkType == 3) {
                    EightWay2dLinkage(x, i);
                }
            }
        }

        // Reset the value of any oscillator that has exceeded 1
        for (int i = 0; i < NUM_OSC; i++) {
            // Write the value of the oscillator to the output file
            fprintf(outputFile, "%lf\t", x[i]); 
            if (x[i] >= 1) {
                x[i] = 0.0;
            }
        }
        // Write a newline character to the output file
        fprintf(outputFile, "\n"); 
    }
    fclose(outputFile); 
    return 0;
}
