// Amount of time to run simulation
#define RUN_TIME 100
// SIM_TIME is the number of iterations to run the simulation
#define SIM_TIME RUN_TIME/DELTA_TIME
// NUM_OSC is the number of oscillators in the simulation
#define NUM_OSC  36
// WIDTH is the number of oscillators in a row in the simulation
#define WIDTH 6
// HEIGHT is the number of rows in the simulation
#define HEIGHT NUM_OSC/WIDTH
// GAMMA is a constant used in the simulation
#define GAMMA 0.2
// DELTA_TIME is the time step for each iteration
#define DELTA_TIME 0.01
// EPSILON is a small value used in the simulation
#define EPSILON 0.03

// Define a macro to find the minimum of two values
#define min(a,b) (((a) < (b)) ? (a) : (b))
