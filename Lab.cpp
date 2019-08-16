// Vinh Vu, 015347252
// Lab: Command Line Argument Processing

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

int main( int argc, char ** argv ){
  if( argc == 1 ){
    cout << "ERROR: no arguments entered, I'm done\n"
		<< endl;
  }
  else if( (1 < argc) && (argc < 4) ){
    cout << "ERROR: Please enter more than 3 numerical arguments\n"
    << endl;
  }
  else if ( ( argc >= 4) && (argc < 12) )
  {

    int summation = 0;
    int length = argc - 1;
    float arrayAverage = 0.f;
    int max = atoi( argv[ 1 ] );
    int min = atoi( argv[ 1 ] );
    for ( int i = 0 ; i < length ; i++){
      if ((atoi(argv[i+1]) < -100) || (atoi(argv[i+1]) > 100)){
        cout<<"Input values are out of bounds."<<endl;
        exit(0);
      }
    }
    for ( int i = 0 ; i < length ; i++){
      cout<<"numbersArray["<<i<<"] = "<< atoi( argv[ i+1 ] )<<endl;
      summation = summation + atoi( argv[ i+1 ] ) ;
    }
    for (int j = 0; j < length ; j++){
      if (atoi(argv[j+1]) > max){
        max = atoi( argv[ j+1 ] );
      }
      else if ( atoi( argv[ j+1 ] ) < min ){
        min = atoi( argv[ j+1 ] );
      }
    }
    arrayAverage = float(summation) / float(length) ;
    cout<<"The sum is "<< summation <<endl;
    cout<<"The average is "<< arrayAverage <<endl;
    int arrayRange = max - min;
    cout<<"The range is "<< arrayRange<<endl;
  }
  else
  {
    cout<<"The range is out of bound."<<endl;
  }
 exit ( 0 );
}
