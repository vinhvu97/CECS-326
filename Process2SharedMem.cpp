#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>

#include <iostream>
using namespace std;

int main(){

	const int SIZE = 4096;
	const char *name = "Challenger";
	char *message;
	int shm_fd;
	int x = 1;
	void *ptr;
	shm_fd = shm_open(name, O_RDWR, 0666);
	if(shm_fd == -1){
		cout << "2: ERROR: Opening shared memory failed\n";
		exit(-1);
	}

	/*void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);	*/
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	if(ptr == MAP_FAILED){
		cout << "2: ERROR: Map failed\n";
		exit(-1);
	}
	while (x==1){
	cout << "2: Value received: " << (char *)ptr << endl;
	cout << "2: Value to write into shared memory: "<<endl;
	cin >> message;
	sprintf((char *)ptr, "%s", message);

	cout << "2: Awaiting new data in shared memory region."<<endl;


	cout << "2: Enter a value to close the shared memory region\n";
	cin >> x;
}
	if(shm_unlink(name) == -1){
		cout << "2: ERROR: Error removing shared memory region " << name << endl;
		exit(-1);
	}
	cout << "2: Successfully closed shared memory region" << endl;
	return 0;
}
