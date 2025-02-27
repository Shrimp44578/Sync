#include "SyncConstants.h"

void FourWay2dLinkage(double x[], int i) {          
    // Find the row and column of the osc
    int row, col;
    col = i % WIDTH;
    row = (i - col)/WIDTH;
    int j;
                    
    // Update the values of the neighbori
    if (col < WIDTH - 1) {
        j = row*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0) {
        j = row*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row > 0) {
        j = (row - 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
}

void GlobalLinkage(double x[], int i) {
    for (int j = 0; j < NUM_OSC; j++) {
        if (i != j) {
            // Ensure that the updated value does not exceed 1
            x[j] = min(1, x[j] + EPSILON);
        }
    }
}

void FourWayTaurusLinkage(double x[], int i) {
    // Find the row and column of the oscillator
    int row, col;
    col = i % WIDTH;
    row = (i - col)/WIDTH;
    int j;
    
    // Update the values of the neighboring oscillators
    if (col < WIDTH - 1) {
        j = row*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = row*WIDTH;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0) {
        j = row*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = row*WIDTH + WIDTH - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row > 0) {
        j = (row)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = (HEIGHT - 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    
    return;
}

void EightWayTorusLinkage(double x[], int i) {          
    // Find the row and column of the osc
    int row, col;
    col = i % WIDTH;
    row = (i - col)/WIDTH;
    int j;
                    
    // Update the values of the neighbor
    if (col < WIDTH - 1) {
        j = row*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = row*WIDTH;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col < WIDTH - 1 && row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0) {
        j = row*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = row*WIDTH + WIDTH - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0 && row > 0) {
        j = (row - 1)*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0 && row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row > 0) {
        j = (row - 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    else {
        j = (HEIGHT - 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col < WIDTH - 1 && row > 0) {
        j = (row - 1)*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
}

void EightWay2dLinkage(double x[], int i) {          
    // Find the row and column of the osc
    int row, col;
    col = i % WIDTH;
    row = (i - col)/WIDTH;
    int j;
                    
    // Update the values of the neighbor
    if (col < WIDTH - 1) {
        j = row*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col < WIDTH - 1 && row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0) {
        j = row*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0 && row > 0) {
        j = (row - 1)*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col > 0 && row < HEIGHT - 1) {
        j = (row + 1)*WIDTH + col - 1;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (row > 0) {
        j = (row - 1)*WIDTH + col;
        x[j] = min(1, x[j] + EPSILON);
    }
    if (col < WIDTH - 1 && row > 0) {
        j = (row - 1)*WIDTH + col + 1;
        x[j] = min(1, x[j] + EPSILON);
    }
}
