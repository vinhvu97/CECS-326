// Vinh Vu, 015347252
// pThread lab

#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

using namespace std;
int value = 10;
char letter;
bool mode_flag = true; // true is up, false is down
bool en_flag = true; // true is enabled, false is disabled
bool stop_flag = true; // true for running, false for stop
int speed_flag = 3; // Flag for speed, 0-3 with 0 slowest speed


void *inputReader( void *param );
void *countDownThread( void *param );

int main( int argc, char ** argv ){
	// cout << "Initially, value = " << value << endl;
	pthread_t tid_reader, tid_evenChecker, tid_countDownThread;
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_create( &tid_reader, &attr, inputReader, NULL );	// create the thread
	pthread_create( &tid_countDownThread, &attr, countDownThread, NULL );	// create the thread
	cout << "Main thread blocking until worker threads finish\n";
	pthread_join( tid_reader, NULL );
	pthread_join( tid_countDownThread, NULL );
	cout << "Main thread is unblocked and exits\n";
}

void *inputReader( void *param ){
	cout << "Reader Thread Running!\n";
	while(stop_flag == true){
		cin >> letter;	// BLOCKING operation
		if( !((letter=='+')||(letter=='-')||(letter=='d')||(letter=='s')||(letter=='a'))){
			cin.clear();
			cin.ignore();
		}
		// Logic block for changing count up/count down mode
		if (letter == 'd'){
			if (mode_flag == true){
				mode_flag = false;
			}
			else if (mode_flag == false){
				mode_flag = true;
			}
		}
		// Logic block for speed up
		if (letter == '+'){
			if (speed_flag == 0){
				speed_flag = 1;
			}
			else if (speed_flag == 1){
				speed_flag = 2;
			}
			else if (speed_flag == 2){
				speed_flag = 3;
			}
			else if (speed_flag == 3){
				speed_flag = 3;
			}
		}

		// Logic block for speed down
		if (letter == '-'){
			if (speed_flag == 3){
				speed_flag = 2;
			}
			else if (speed_flag == 2){
				speed_flag = 1;
			}
			else if (speed_flag == 1){
				speed_flag = 0;
			}
			else if (speed_flag == 0){
				speed_flag = 0;
			}
		}

		//Logic block for Enable/Disable
		if (letter == 's'){
			if (en_flag == true){
				en_flag = false;
			}
			else if (en_flag == false){
				en_flag = true;
			}
		}

		if (letter == 'a'){
			stop_flag = false;
		}

	} //end of input while
	cout << "inputReader thread exited\n";
	pthread_exit( 0 );
}

void *countDownThread( void *param ){
	cout << "Count Down Thread Running!\n";
	struct timespec timing;
	timing.tv_sec = 0;

	while(stop_flag == true){

		// Logic block for changing count up/count down mode
		if(mode_flag == false){
			cout << --value << flush;
			while (value == 0){
				value = 99;
			}
		}
		else if (mode_flag == true){
			cout << ++value << flush;
			while (value == 99){
				value = 0;
			}
		}

		// Logic block for setting various speeds
		if (speed_flag == 0){
			sleep (1);
		}
		else if (speed_flag == 1){
			timing.tv_nsec = 500000000L;
			nanosleep( &timing, NULL );

		}
		else if (speed_flag == 2){
			timing.tv_nsec = 250000000L;
			nanosleep( &timing, NULL );

		}
		else if (speed_flag == 3){
			timing.tv_nsec = 125000000L;
			nanosleep( &timing, NULL );

		}

		//Logic block for Enable/Disable
		while ((en_flag == false) && (stop_flag == true)){
			cout << value <<flush;
			cout << "\b\b\b\b\b\b       \b\b\b\b\b\b";
			cout << "\b\b\b\b\b\b";
		}

		if (en_flag == true){
			if (mode_flag == true){
				cout << ++value <<flush;
				while (value == 99){
					value = 0;
				}

			}
			else if (mode_flag == false){
				cout << --value << flush;
				while (value == 0){
					value = 99;
				}
			}
		}

		cout << "\r			\r";
		cout << "\b\b\b\b\b\b       \b\b\b\b\b\b";
		cout << "\b\b\b\b\b\b";
	}
	cout << "countDownThread thread exited\n";
	pthread_exit( 0 );
}
