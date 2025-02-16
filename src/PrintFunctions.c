#include "SyncConstants.h"
#include <time.h>
#include <stdio.h>

void PrintLog(char outputFileName1[], int LinkType, int NetworkType, double S[]) {
    FILE* LogFile = fopen("..//data//Log.txt", "a");
    if (LogFile == NULL) {
        printf("Error opening Log file!\n");
        return;
    }
    fprintf(LogFile, "Output File: %s\n", outputFileName1);
    fprintf(LogFile, "\tLinkType: %d\n", LinkType);
    fprintf(LogFile, "\tNetworkType: %d\n", NetworkType);
    fprintf(LogFile, "\tParameters:\n");
    fprintf(LogFile, "\t\tS[0]: %lf\n", S[0]);
    fprintf(LogFile, "\t\tGAMMA: %lf\n", GAMMA);
    fprintf(LogFile, "\t\tDELTA_TIME: %lf\n", DELTA_TIME);
    fprintf(LogFile, "\t\tEPSILON: %lf\n", EPSILON);
    fprintf(LogFile, "\t\tNUM_OSC: %d\n", NUM_OSC);
    fprintf(LogFile, "\t\tWIDTH: %d\n", WIDTH);
    fprintf(LogFile, "\t\tHEIGHT: %d\n", HEIGHT);
    fprintf(LogFile, "\t\tSIM_TIME: %lf\n", SIM_TIME);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(LogFile, "Date: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(LogFile);
}
