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
        cout << "B, Q create fail!\n";
	    qid = msgget(
	        ftok(".",'u'),
	        IPC_EXCL | 0600
	        );
        if( qid < 0 ){
            cout << "B, Q access fail!\n";
            exit( -1 );
        }
    }

	struct buf {
		long mtype;
		char g[5];
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);

	do{
	    cout << "Enter a message"
	            " type to RECEIVE: ";
        cin >> msg.mtype;
        if( msg.mtype < 0 ) break;
			cout << "Checking queue...\n";
			msgrcv( qid, (struct msgbuf *)&msg,size,msg.mtype,0);
			cout << "B,Received: "<< msg.mtype<< endl;
			if (msg.mtype %2 == 1){
				msg.mtype = 3*msg.mtype + 1;
				cout<<"Odd Calculation: "<<msg.mtype<<endl;
			}
			else if (msg.mtype %2 == 0){
				msg.mtype = msg.mtype/2;
				cout<<"Even Calculation: "<<msg.mtype<<endl;
			}

	}while( msg.mtype > 0 );
	cout << "Removing queue\n";
	if( msgctl (qid, IPC_RMID, NULL) )
	    cout << "B, Q remove FAIL!\n";
    else
        cout << "B, Q remove SUCCSS!\n";
	exit(0);
}
