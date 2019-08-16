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

// compile with: g++ writerOfInts.cpp -o 2_writer.out -lrt


int main(int argc, char * argv[]){
	const int SIZE = 128;
	int count = 0;
	short x;
	short odd, even;
	const char *name = "Challenge";	// name of shared memory region

	int shm_fd;	// file descriptor variable
	void *ptr;	// shared memory pointer

	// create, truncate shared memory region
	// shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	shm_fd = shm_open(name, O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	// point to shared memory region
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	// sequence = 8;	// test

	short newvalue = 0;
	short value = 0;
	short send = 0;

	// Sending first value
	cout << "1: Value to write into shared memory: ";
	cin >> value;
	if( x < 0 ){
				cout << "Negative value encountered, exiting!\n";
				return 0;
			}
	*((short *)ptr) = value;  // sending data

	while (value != 1){
			newvalue = *((short *)ptr);
			while ( newvalue == value ){
				newvalue = *((short *)ptr);
			}

		value = newvalue;
		if (value == 1){
			cout << "1: Value Received: " << value << endl;
			cout << "1: I lose."<<endl;
		}
		else{
		cout << "1: Value Received: " << value << endl;

		// even case
		if ( value % 2 == 0){
			value = value/2;
			cout << "1: Even value to write into shared memory: "<<value<<endl;
			*((short *)ptr) = value;  // sending data
			}
		// odd case
			else if ( value % 2 == 1){
				value = 3*value+1;
				cout << "1: Odd value to write into shared memory: "<<value<<endl;
				*((short *)ptr) = value ;  // sending data
				}
			}
	}

	if(shm_unlink(name) == -1){
		cout << "1: ERROR: Error removing shared memory region: " << name << endl;
		exit(-1);
	}
	cout << "1: Successfully closed shared memory region" << endl;

	return 0;

}
