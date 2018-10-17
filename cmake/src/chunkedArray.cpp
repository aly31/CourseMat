#include "chunkedArray.h" 


ChunkedArray::ChunkedArray(int n0,int n1,int n2)
{

nx=n0;
ny=n1;
nz=n2;

int arraySize=nx*ny*nz;

P = new ( std::nothrow ) double[arraySize];

}


double &ChunkedArray::operator()( int i, int j, int k )
{
     return P[ ( i + nx * j + nx * ny * k )];
}
 
ChunkedArray::~ChunkedArray()
 {
   delete[] P;
 }
 
