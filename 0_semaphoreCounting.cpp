#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
// Counting semaphores to allow a certain number of threads to access CS concurrently

sem_t U;

void *runner( void *arg){
	usleep( 999999 );
	sem_wait( &U );
	cout << "Thread in CS\n";
	usleep( 999999 );
	cout << "Thread leaving CS\n";
	sem_post( &U );
	pthread_exit( 0 );
}

int main(){
	sem_init( &U, 0, 3 );	// 0 for pshared, 3 for initial value of U
	pthread_t tids[ 10 ];
	for( int i = 0; i < 10; i++ )
		pthread_create( &tids[ i ], NULL, runner, NULL );
		
	for( int i = 0; i < 10; i++ )
		pthread_join( tids[ i ], NULL );
	sem_destroy( &U );
}