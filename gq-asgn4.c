#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Struct to hold both the name and max number of people
typedef struct gateType {
	char *name;
	int max;
} gate;

int total = 0; // Total number of people in concert hall
pthread_mutex_t lock;

void *countSeats(void *arg) {
	// Creates the gate struct from the argument
	gate* thisGate = (gate*) arg;
	
	// Receives the gate's attributes from the struct
	char *gateName = thisGate->name;
	int gateMax = thisGate->max;
	
	// Frees up memory from the struct
	free(thisGate);
	
	// Number of people at this particular gate
	int count = 0;
	
	for (int i = 0; i < gateMax; i++) {
		
		pthread_mutex_lock(&lock);
		// Critical section, the only shared data to protect from other threads is total
		total++;
		// End of critical section
		pthread_mutex_unlock(&lock);
		
		// Increment this particular gate's count
		count++;
		
		// Every 500 people, print the gate's status
		if (count % 500 == 0) {
			printf("Gate %s has %d people, with %d people total in the concert hall.\n", gateName, count, total);
		}
	}
	pthread_exit(0);
}

int main() {
	// Creates the gate threads and mutex
	pthread_t east, west, north, south;
	pthread_mutex_init(&lock, NULL);
	
	// Creates struct for each gate
	gate *eastGate = malloc(sizeof(gate));
	eastGate->name = "east";
	eastGate->max = 5000;
	
	gate *westGate = malloc(sizeof(gate));
	westGate->name = "west";
	westGate->max = 5000;
	
	gate *northGate = malloc(sizeof(gate));
	northGate->name = "north";
	northGate->max = 10000;
	
	gate *southGate = malloc(sizeof(gate));
	southGate->name = "south";
	southGate->max = 15000;
	
	// Creates each gate thread
	if (pthread_create(&east, NULL, &countSeats, eastGate) != 0) {
		// Checks if the thread fails to be created
		printf("Error creating thread.");
		abort();
	}
	if (pthread_create(&west, NULL, &countSeats, westGate) != 0) {
		// Checks if the thread fails to be created
		printf("Error creating thread.");
		abort();
	}
	if (pthread_create(&north, NULL, &countSeats, northGate) != 0) {
		// Checks if the thread fails to be created
		printf("Error creating thread.");
		abort();
	}
	if (pthread_create(&south, NULL, &countSeats, southGate) != 0) {
		// Checks if the thread fails to be created
		printf("Error creating thread.");
		abort();
	}
	
	// Joins each gate thread
	if (pthread_join(east, NULL) != 0) {
		// Checks if the thread fails to be joined
		printf("Error joining thread.");
		abort();
	}
	if (pthread_join(west, NULL) != 0) {
		// Checks if the thread fails to be joined
		printf("Error joining thread.");
		abort();
	}
	if (pthread_join(north, NULL) != 0) {
		// Checks if the thread fails to be joined
		printf("Error joining thread.");
		abort();
	}
	if (pthread_join(south, NULL) != 0) {
		// Checks if the thread fails to be joined
		printf("Error joining thread.");
		abort();
	}
	
	// End program
	pthread_mutex_destroy(&lock);
	pthread_exit(NULL);
	return 0;
}