#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
	const int SIZE = 4096;

	char *message;
	int x = 1;
	const char *name = "Challenger";

	int shm_fd;
	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(shm_fd, SIZE);

	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
while (x == 1){
		cout<< "1: Value to write into shared memory: ";
		cin >> message;

		//sprintf((char *)ptr, "%d", stoi(message));
		//cout << (char *) ptr<<" and "<< message <<endl;
		sprintf((char *)ptr, "%s", message);

		cout << "1: Awaiting new data in shared memory region."<<endl;

		cout << "1: Enter 1 to continue and read from shared memory region: ";
		cin >> x;

		cout << "1: Value Received: " << (char *)ptr << endl;
}
	cout << "1: Attempting to close shared memory region" << endl;

	if(shm_unlink(name) == -1){
		cout << "1: ERROR: Error removing shared memory region " << name << endl;
		exit(-1);
	}
	cout << "1: Successfully closed shared memory region" << endl;

	return 0;

}
