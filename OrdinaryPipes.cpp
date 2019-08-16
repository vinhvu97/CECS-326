// Vinh Vu, 015347252
// Ordinary Pipes lab

#include <sys/types.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

int main(){
	string write_msg, msg_read, sign;
	const short MSG_SIZE = 25;
	char msg_write[ MSG_SIZE ];
	char read_msg[ MSG_SIZE ];
	int fd[2];
	string math[3];
	int a,b,total;
	pid_t pid;
	char testing_array [MSG_SIZE];
	pipe( fd );
	pid = fork();
	if( pid > 0 ){	// in parent
			close( fd[0] );	// close unused Read End
		for ( int i = 0; i<3; i++){
			cout << "PARENT: Enter a message to send:";
			cin >> write_msg;
			cout << "PARENT sending: " << write_msg << endl;
			unsigned int size = write_msg.length();
			write_msg.copy( msg_write, write_msg.length(), 0 );
			write( fd[1], msg_write, MSG_SIZE );
			for( int i = 0; i < MSG_SIZE; i++ )
				msg_write[ i ] = '\0';	// overwrite the message local array
			//write( fd[1], msg_write, MSG_SIZE );	// overwrite the shared memory area
		}
		close( fd[1] );	// all done, close the pipe!
		cout << "PARENT: Exit\n";
	}
	else{
		close( fd [1] );	// close unused write end
		for ( int j = 0; j < 3; j++){
			read( fd[0], read_msg, MSG_SIZE );
			cout << "CHILD msg read: " << read_msg << endl;
			msg_read = read_msg;
			math[j] = msg_read;
			if (j == 1){
				if ((msg_read != "-")  && (msg_read != "+") ){
					cout<<"Operation Invalid."<<endl;
					close(fd[0]);
					cout << "Child process about to exit due to error\n";
					exit(0);
				}
				else{
					if((msg_read == "-")){
						cout<<"CHILD: Operation Subtraction"<<endl;
					}
					else{
						cout<<"CHILD: Operation Addition"<<endl;
					}
				}
			}
		}

		if ((stoi(math[0]) >=100) || (stoi(math[0])<=0) || (stoi(math[2]) >=100) || (stoi(math[2])<= 0)){
						cout<<"The inputted integers are out of bound."<<endl;
						close(fd[0]);
						cout << "Child process about to exit due to error\n";
						exit(0);
					}

		if (math[1]=="-"){
			cout<<math[0]<<" - "<<math[2]<<" = "<< stoi(math[0])-stoi(math[2])<<endl;
		}
		if (math[1]=="+"){
			cout<<math[0]<<" + "<<math[2]<<" = "<< stoi(math[0])+stoi(math[2])<<endl;
		}
		close( fd[0] );	// all done, close the pipe!
		cout << "CHILD: Exit\n";
	}
	exit(0);
}
