#include <iostream>
using namespace std;

int main( int argc, char ** argv ){
	cout << "The argument count = " << argc << endl;
	cout << "The argument tokens are: " << endl;
	for( int i = 0; i < 3; i++ ){
		cout << "argv[ " << i << " ] = " << argv[ i ] << endl;
	}
	cout << "Bye!\n";
}
