#ifndef _CHUNKEDARRAY_H_
#define _CHUNKEDARRAY_H_
#include <assert.h>
#include <iostream>

/*!
 *
 * \class ChunkedArray
 * \brief overloads some operators to provide user-friendly interface
 *
 *
 *
 * */

class ChunkedArray
{
    private:
    int nx;                 
    int ny;                
    int nz;        
    double *P=nullptr; 

public:
ChunkedArray(int n0,int n1, int n2); /*!< constructor */
 
double &operator()( int i, int j, int k ); /*!< Op overloded */

~ChunkedArray(); /*!< Destructor */



};


#endif
