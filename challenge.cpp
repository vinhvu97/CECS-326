#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

#include <time.h>

#include <iostream>
using namespace std;

int main(/*int argc, char * argv[]*/){

	const int SIZE = 128;
	const char *name = "Challenge"; //name of shared memory region
	//char messageBuffer[5];
	short newValue = 0;
	short value = 0;
	int shm_fd; //file descriptor variable
	void *ptr; //shared memory pointer
	bool anotherRound = true;
	//create, truncate shared memory region
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	shm_fd = shm_open(name, O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	//point to shared memory region
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);



	if(shm_fd == -1){
		cout << "2: ERROR: Opening shared memory failed\n";
		exit(-1);
	}
	else if(ptr == MAP_FAILED){
		cout<< "2: ERROR: Map failed\n";
		exit(-1);
	}

	else{
		bool oldData = true;
		while(oldData){
			newValue = *((short *)ptr);
			if(newValue != value ){
				oldData = false;
			}
		} //end of while(oldData)
		value = newValue;
		cout << "2: FIRST Value Received: " << value << endl;

		if (value == 1){
		cout << "2: Cheater! Good Bye!"<<endl;
		exit(-1);
		}
		else{
			if (value %2 == 1){
			value = (3 * value) + 1;
			*((short *)ptr) = value;
			}
			else if (value % 2 == 0){
			value = value/2;
			*((short *)ptr) = value;
			}
		cout << "2: Value to write into shared memory: " << value << endl;
		cout << "2: Awaiting new data in shared memory region" << endl;

		}
	}
	do{
		bool oldData = true;
		while(oldData){
			newValue = *((short *)ptr);
			if(newValue != value ){
				oldData = false;
			}
		} //end of while(oldData)
		value = newValue;
		cout << "2: Value Received: " << value << endl;
		if((value == 1) ||(value == 2)){
			*((short *)ptr) = value;
			break;
		}else if(value % 2 == 1){ //if odd
			value = (3 * value) + 1;
			*((short *)ptr) = value;
		}
		else{ //if even
			value = value/2;
			*((short *)ptr) = value;
		}
		cout << "2: Value to write into shared memory: " << value << endl;
		cout << "2: Awaiting new data in shared memory region" << endl;

		//Hailstone sequence

	}while((value != 1) || (value != 2));
	//win
	if(newValue == 2){
		cout << "2: I WIN!" << endl;
	}
	else if(newValue == 1){
		cout <<"2: I lose!" << endl;
	}
	cout << "2: Attempting to close the shared memory region\n";
	if(shm_unlink(name) == -1 ){
		cout << "2: ERROR: Error removing shared memory region" << name << endl;
		exit(-1);
	}
	cout << "2: Successfully closed shared memory region" << endl;
	return 0;
}
