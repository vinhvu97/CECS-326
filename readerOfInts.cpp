#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <unistd.h>

#include <iostream>
using namespace std;

// compile with: g++ readerOfInts.cpp -o 1_reader.out -lrt

int main(){

	const int SIZE = 128;
	const char *name = "Challenge";
	int shm_fd;
	void *ptr;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	// shm_fd = shm_open(name, O_RDWR, 0666);
	if(shm_fd == -1){
		cout << "reader: ERROR: Opening shared memory failed\n";
		exit(-1);
	}
	else{
		cout << "reader: opened shared memory\n";
	}

	ftruncate(shm_fd, SIZE);
	/*void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);	*/
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	if(ptr == MAP_FAILED){
		cout << "reader: ERROR: Map failed\n";
		exit(-1);
	}
	short newvalue = 0;
	short value = 0;
	value = *((short *)ptr);

while (value != 1){
			newvalue = *((short *)ptr);
			while ( newvalue == value ){
				cout<<"2: Awaiting new data in shared memory region."<<endl;
				newvalue = *((short *)ptr);
			}
		value = newvalue;
		if (value == 1){
			cout << "2: Value Received: " << value << endl;
			cout << "2: I lose."<<endl;
		}

		else{
		cout << "2: Value Received: " << value << endl;

		// even case
			if ( value % 2 == 0){
				value = value/2;
				cout << "2: Even value to write into shared memory: "<<value<<endl;
				*((short *)ptr) = value;  // sending data
				}
		// odd case
			else if ( value % 2 == 1){
				value = 3*value+1;
				cout << "2: Odd value to write into shared memory: "<<value<<endl;
				*((short *)ptr) = value;  // sending data
				}
			}
	}

	cout << "reader: Attempting to close the shared memory region\n";

	if(shm_unlink(name) == -1){
		cout << "reader: ERROR: Error removing shared memory region" << name << endl;
		exit(-1);
	}
	else
		cout << "reader: Successfully closed shared memory region" << endl;

	return 0;
}
