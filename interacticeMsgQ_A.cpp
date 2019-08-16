
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;
// Challenger first reads from the queue

int main() {

	int qid = msgget(
	        ftok(".",'u'),
	        IPC_EXCL | IPC_CREAT | 0600
	        );
    if( qid < 0 ){
        cout << "A, Q create FAIL!\n";
	    qid = msgget(
	        ftok(".",'u'),
	        IPC_EXCL | 0600
	        );
        if( qid < 0 ){
            cout << "A, Q access FAIL!\n";
            exit( -1 );
        }
    }
	else{
		cout << "Q create SUCCESS\n";
	}

	struct buf {
		long mtype;
		char g[5];
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	strcpy( msg.g, "From A");

	do{
	    cout << "Enter a message"
	            " TYPE to SEND: ";
        cin >> msg.mtype;
	    cout    << "A,Sending: "
                << msg.mtype
                << endl;
        if(
        	msgsnd( qid,(struct msgbuf *)&msg,size,0 )< 0 ){
            cout << "A, send FAIL!\n";
        }
	}while( msg.mtype > 0 );

	cout << "Removing queue\n";
	if( msgctl (qid, IPC_RMID, NULL) )
	    cout << "A, Q remove FAIL!\n";
    else
	    cout << "A, Q remove SUCCESS!\n";
	exit(0);
}
