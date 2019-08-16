#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

int main(){
	string write_msg, msg_read;
	const short MSG_SIZE = 25;
	char msg_write[ MSG_SIZE ];
	char read_msg[ MSG_SIZE ];
	int fd[2];
	pid_t pid;
	pipe( fd );
	pid = fork();
	if( pid > 0 ){	// in parent
		cout	<< "Process: "
				<< getpid()
				<< " is now a parent!"
				<< endl
				<< "Parent is preparing to communicate with the child: "
				<< pid
				<< endl;
			close( fd[0] );	// close unused Read End
		while( write_msg != "done" ){
			cout << "Enter a message to send: ";
			cin >> write_msg;
			cout << "In parent, sending: " << write_msg << endl;
			unsigned int size = write_msg.length();
			write_msg.copy( msg_write, write_msg.length(), 0 );
			write( fd[1], msg_write, MSG_SIZE );
			for( int i = 0; i < MSG_SIZE; i++ )
				msg_write[ i ] = '\0';	// overwrite the message local array
			//write( fd[1], msg_write, MSG_SIZE );	// overwrite the shared memory area
		}
		close( fd[1] );	// all done, close the pipe!
		cout << "Parent process about to exit\n";
	}
	else{
		cout	<< "Child process: "
				<< getpid()
				<< " has been created!\n"
				<< "child process preparing to get data from parent process: "
				<< getppid()
				<< endl;
		close( fd [1] );	// close unused write end
		while( msg_read != "done" ){
			read( fd[0], read_msg, MSG_SIZE );
			cout << "In child, msg read: " << read_msg << endl;
			msg_read = read_msg;
		}
		close( fd[0] );	// all done, close the pipe!
		cout << "Child process about to exit\n";
	}
	exit(0);
}
