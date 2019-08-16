#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
// Counting semaphores to allow a certain number of threads to access CS concurrently
int a = 0;
sem_t S;

void *P1 (void *unused){
	sem_post(&S);
	int x = a;
	cout << "P1: x = "<<x<<endl;
	x+=10;
	a = x;
	sem_post(&S);
	cout << "P1: a = "<<a<<endl;
}

void *P2 (void *unused){
	sem_post(&S);
	int y = a;
	cout << "P2: y = "<<y<<endl;
	y+=20;
	a = y;
	sem_post(&S);
	cout << "P2: a = "<<a<<endl;
}

int main(){
	pthread_t p1,p2;
	sem_init( &S, 0, 1 );	// 0 for pshared, 3 for initial value of U
	pthread_create(&p1, NULL, P1, NULL);
	pthread_create(&p2, NULL, P2, NULL);
	pthread_join( p1, NULL);
	pthread_join( p2, NULL);
	cout << "Main: a = "<<a<<endl;
}
