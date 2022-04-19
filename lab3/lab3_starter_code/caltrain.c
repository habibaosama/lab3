#include <pthread.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
	// FILL ME IN
    pthread_mutex_init(&station->train_mutex,NULL);
    pthread_cond_init(&station->waiting_train,NULL );
    pthread_cond_init(&station->train_leave,NULL );
    station->available_seats=0;
    station->passengers_on_board=0;
    station->people_in_station=0;
}

void
station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&station->train_mutex);
    //start of critical section
    station->available_seats=count;
    //using condition variables to control that it load only if there is empty seats and people in station
    //check if there is empty seats & passengers else will leave
    if(station->available_seats!=0 && station->people_in_station!=0){
        //broadcast all the passengers(threads) able to get into train
        //wakeup all waiting passengers
        pthread_cond_broadcast(&station->waiting_train);
        //wait until passengers be on board
        pthread_cond_wait(&station->train_leave,&station->train_mutex);
    }
    //train will leave
    station->available_seats=0;
    //end of critical section
    pthread_mutex_unlock(&station->train_mutex);
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->train_mutex);
    //start of critical section
    station->people_in_station++;

    //if there is no empty seats or number of people on board =no. of seats will wait on condition variable
    while(station->available_seats==0 || (station->passengers_on_board==station->available_seats)){
        // wait until there is a free seat
        // sleep and release the lock then aquire the lock again when signalled on the  same condition variable
        // wakes up when a train arrived
        pthread_cond_wait(&station->waiting_train,&station->train_mutex);
    }
    //increase passengers on board
    station->passengers_on_board++;
    //end of critical section
    pthread_mutex_unlock(&station->train_mutex);

}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->train_mutex);

    station->available_seats--;
    station->people_in_station--;
    station->passengers_on_board--;
    if( station->available_seats == 0 || ( station->passengers_on_board == 0 && station->people_in_station == 0) ){
        pthread_cond_signal( &station->train_leave );
    }
    pthread_mutex_unlock(&station->train_mutex);
}
