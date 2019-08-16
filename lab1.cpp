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
    pid = fork();
    if (pid == 0){
      cout<<"CHILD1: about fork and show a long list of directory contents:"<<endl;
      if( execlp( "ls", "ls", "-l", NULL ) == -1 ){
        cout << "ERROR: exec failed!\n";
        exit( 1 );
      }
    } //end of first execution
    wait (&pid);
    pid = fork();

    if (pid == 0) {
      cout<<"CHILD1: about fork and show hello.cpp contents:"<<endl;
      if( execlp( "more", "more", "hello.cpp", NULL ) == -1 ){
        cout << "ERROR: exec failed!\n";
        exit( 1 );
      }
    } // end of 2nd execution
    wait (&pid);
    
  cout << "CHILD1: about to do ./hello.out 2\n";
  if( execlp( "./hello.out", "./hello.out", "2", NULL ) == -1 ){
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
