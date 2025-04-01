#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "Sync.h"
#include "SyncConstants.h"

extern char *optarg;
extern int optind, opterr, optopt;

int main(int argc, char *argv[]) {
    // Seed the random number generator to ensure different results on each run
    srand(time(NULL));

    /* 
    Variable Definitions and Initial Values:
    
    - S: 
        - Array containing the baseline rate of change for each oscillator.
        - Currently, all oscillators share the same rate of change (S0).
    
    - epsilon:
        - Coupling strength between oscillators.
        - Determines how strongly oscillators influence each other.

    - gamma:
        - Damping factor for the oscillators.
        - Controls the rate at which oscillators lose energy.

    - dist:
        - Represents the change in the oscillator value for each iteration.
        - Calculated based on the interaction between oscillators.

    - LinkType:
        - Specifies the type of linkage between oscillators:
            - 1: Global Linkage (all oscillators are interconnected).
            - 2: Four-Way Linkage (each oscillator is connected to its four neighbors).
            - 3: Eight-Way Linkage (each oscillator is connected to its eight neighbors).

    - NetworkType:
        - Specifies the type of network topology:
            - 1: Torus Network (wrap-around connections in both dimensions).
            - 2: Cylindrical Network (wrap-around connections in one dimension).
            - 3: 2D Grid Network (no wrap-around connections).

    - newUpdate:
        - A flag indicating whether any oscillators have been updated during the current iteration.

    - updateDone:
        - An array used to track which oscillators have been updated during the current iteration.

    - opt:
        - Represents the option selected by the user via command-line arguments:
            - 'l': LinkType (type of linkage between oscillators).
            - 'n': NetworkType (type of network topology).
            - 'g': gamma (damping factor).
            - 'e': epsilon (coupling strength).
            - 's': S0 (baseline rate of change).
            - 'f': outputFileName (name of the output file).
    */

    double S[1] = {S0};       // Baseline rate of change for oscillators
    double epsilon = EPSILON; // Coupling strength
    double gamma = GAMMA;     // Damping factor
    double dist;              // Change in oscillator voltage per iteration
    double x[NUM_OSC];
    double change;            // Change in oscillator voltage
    int LinkType = 1;
    int NetworkType = 1;
    int newUpdate;
    int updateDone[NUM_OSC];
    int opt;
    char outputFileName[256];
    char directory[10] = "data/";



    #ifdef DEBUG
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
    #endif


    while((opt = getopt(argc, argv, ":f:s:g:e:l:n:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'l':
                sscanf(optarg, "%d", &LinkType);
                break;
            case 'n':
                sscanf(optarg, "%d", &NetworkType);
                break;
            case 'g':
                sscanf(optarg, "%lf", &gamma);
                break;
            case 'e':
                sscanf(optarg, "%lf", &epsilon);
                break;
            case 's':  
                sscanf(optarg, "%lf", &S[0]); 
                break;
            case 'f':  
                strcpy(outputFileName, optarg);  
                break;  
            case':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }  
    
    // Initialize the values of the oscillators to random values between 0 and 1
    for (int i = 0; i < NUM_OSC; i++) {
        x[i] = (double)rand() / RAND_MAX;
        x[i] *= INIT_VAR;
    }

    // Get the output file name from the user
    #ifdef DEBUG
        printf("Enter the output file name: ");
        scanf("%s", outputFileName);
    #endif
    
    char *outputFileName1 = strcat(directory, outputFileName); 
    
    // Open the output file for writing
    FILE *outputFile = fopen(outputFileName1, "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return 1;
    }

    PrintLog(outputFileName1, LinkType, NetworkType, S[0], gamma, epsilon);

    // Write the column headers to the output file
    for (int i = 0; i < NUM_OSC; i++) {
        fprintf(outputFile, "%6d\t\t", i); 
    }
    fprintf(outputFile, "\n");  

    // Run the simulation for SIM_TIME iterations
    for (int b = 0; b < SIM_TIME; b++) {
        // Update the value of each oscillator based on the baseline rate of change and the current value
        for (int i = 0; i < NUM_OSC; i++) {
            change = S[0] - gamma * x[i];
            dist = change * DELTA_TIME;
            x[i] += dist;
            updateDone[i] = 0;
        }
        newUpdate = 1;
        while (newUpdate) {
            newUpdate = 0;
            for (int i = 0; i < NUM_OSC; i++) {
            // If the oscillator value exceeds 1, update the values of all other oscillators
                if (x[i] >= 1 && updateDone[i] == 0) {
                    updateDone[i] = 1;
                    newUpdate += 1;
                    if (LinkType == 2 && NetworkType == 1) {
                        FourWayTaurusLinkage(x, i, epsilon);
                    }
                    else if (LinkType == 1) {
                        GlobalLinkage(x, i, epsilon);
                    }
                    else if (LinkType == 2 && NetworkType == 3) {
                        FourWay2dLinkage(x, i, epsilon);
                    }
                    else if (LinkType == 3 && NetworkType == 3) {
                        EightWay2dLinkage(x, i, epsilon);
                    }
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
