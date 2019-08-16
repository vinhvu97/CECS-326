#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {

	int qid = msgget(
	        ftok(".",'u'),
	        IPC_EXCL | IPC_CREAT | 0600
	        );
    if( qid < 0 ){
        cout << "CHallenger, Q create fail!\n";
	    qid = msgget(
	        ftok(".",'u'),
	        IPC_EXCL | 0600
	        );
        if( qid < 0 ){
            cout << "Challenger, Q access fail!\n";
            exit( -1 );
        }
    }

	struct buf {
		long mtype;
		char g[5];
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	mtype=0
	cout << "Checking queue...\n";
	msgrcv( qid,(struct msgbuf *)&msg, size, msg.mtype, 0); //Receive
	cout << "Challenger, Received: "<< msg.mtype<< endl;
	if (msg.mtype %2 == 1){
		msg.mtype = 3*msg.mtype + 1;
	}
	else if (msg.mtype %2 == 0){
		msg.mtype = msg.mtype/2;
	}
	cout<<"Challenge, Sending:"<<msg.mtype<<endl;
	if(msgsnd( qid, (struct msgbuf *)&msg, size, 0 )< 0 ){
			cout << "A, send FAIL!\n";
	} // Sending

	do{
		if (msg.mtype %2 == 1){
			msg.mtype = 3*msg.mtype + 1;
		}
		else if (msg.mtype %2 == 0){
			msg.mtype = msg.mtype/2;
		}
			cout << "Checking queue...\n";
			msgrcv( qid, (struct msgbuf *)&msg, size, msg.mtype, 0); //Receive
			cout << "Challenger, Received: "<< msg.mtype<< endl;
			if (msg.mtype %2 == 1){
				msg.mtype = 3*msg.mtype + 1;
			}
			else if (msg.mtype %2 == 0){
				msg.mtype = msg.mtype/2;
			}
			cout<<"Challenge, Sending:"<<msg.mtype<<endl;
			if(msgsnd( qid,(struct msgbuf *)&msg, size, 0 ) < 0 ){
					cout << "A, send FAIL!\n";
			} //Sending
	}while( msg.mtype != 1 );

	cout << "Challenge, Removing Q\n";
	if( msgctl (qid, IPC_RMID, NULL) )
	    cout << "Challenger, Q remove FAIL!\n";
    else
        cout << "Challenger, Q remove SUCCSS!\n";
	exit(0);
}
