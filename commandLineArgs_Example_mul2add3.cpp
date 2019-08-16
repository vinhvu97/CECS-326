#include <iostream>
using namespace std;

int main( int argc, char ** argv ){
	if( argc == 3 ){
		int x = atoi( argv[ 1 ] );
		int y = atoi( argv[ 2 ] );
		cout << x << " and " << y << " were received through command line\n";
		cout << "x * y = " << x << " * " << y << " = " << ( x * y ) << endl;
	}
	else if( argc == 4 ){
		int x = atoi( argv[ 1 ] );
		int y = atoi( argv[ 2 ] );
		int z = atoi( argv[ 3 ] );
		cout << x << ", " << y << " and " << z << " were received through command line\n";
		cout << "x + y + z = " << x << " + " << y << " + " << z 
		<< " = " << ( x + y + z ) << endl;
	}
	else{
		cout << "ERROR: run the program and enter either 2 or 3 decimal value command line arguments\n"
		<< endl;
	}
	exit( 0 );
	
	
}