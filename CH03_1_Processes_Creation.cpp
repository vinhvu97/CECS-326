/**
	This program will:
		launch an executable named repeatHello.out and pass the value 3 as an argument

	To use this program, compile and run all source files / executables in same directory:
		1. compile hello.cpp using: g++ hello.cpp -o repeatHello.out
		2. compile CH03_1_Processes_Creation.cpp (default executable name a.out is fine)
		3. run the executable created in step 2

	Study the way in which execlp is used in particular:
		* How the command to launch the executable is specified
		* How the command line argument is provided for the executable
*/

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
	pid_t pid;
	pid = fork();
	if( pid < 0 ){
		cout << "ERROR: Fork failed!\n";
		exit( 1 );	// abort!
	}
	else if( pid == 0 ){	// true inside child
		cout << "CHILD: about to do ./hello.out 1\n";
		execlp( "ls", "ls", "-l", NULL );
		if( execlp( "ls", "ls", "-l", NULL ) == -1 ){
      cout << "ERROR: exec failed!\n";
      exit( 1 );
	}
	}
	else{	// positive pid means parent
		cout << "\nPARENT: Waiting for child to exit...\n";
		wait( &pid );	// only wait if pd > 0 i.e. inside parent
		cout << "\nPARENT: Child finally finally exited\n";
	}
	exit( 0 );
}
