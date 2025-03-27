#include "SyncConstants.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <math.h>

void PrintLog(char outputFileName1[], int LinkType, int NetworkType, double S, double gamma, double epsilon) {
    FILE* LogFile = fopen(".//data//Log.txt", "a");
    if (LogFile == NULL) {
        printf("Error opening Log file!\n");
        return;
    }
    fprintf(LogFile, "\nOutput File: %s\n", outputFileName1);
    fprintf(LogFile, "\tLinkType: %d\n", LinkType);
    fprintf(LogFile, "\tNetworkType: %d\n", NetworkType);
    fprintf(LogFile, "\tParameters:\n");
    fprintf(LogFile, "\t\tS[0]: %lf\n", S);
    fprintf(LogFile, "\t\tGAMMA: %lf\n", gamma);
    fprintf(LogFile, "\t\tDELTA_TIME: %lf\n", DELTA_TIME);
    fprintf(LogFile, "\t\tEPSILON: %lf\n", epsilon);
    fprintf(LogFile, "\t\tNUM_OSC: %d\n", NUM_OSC);
    fprintf(LogFile, "\t\tWIDTH: %d\n", WIDTH);
    fprintf(LogFile, "\t\tHEIGHT: %d\n", HEIGHT);
    fprintf(LogFile, "\t\tSIM_TIME: %lf\n", SIM_TIME);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    double T = log(S / (S - gamma));
    T *= (1 / gamma);
    fprintf(LogFile, "\t\tIntrinsic Period: %lf\n", T);
    fprintf(LogFile, "Date: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(LogFile);
}
