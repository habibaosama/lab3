#include <pthread.h>

struct station {
	// FILL ME IN
       pthread_mutex_t train_mutex;
       pthread_cond_t waiting_train;
       pthread_cond_t train_leave;
      //number of people in station
      int people_in_station;
      //number of available seats
      int  available_seats;
      //passengers on board
      int  passengers_on_board;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
