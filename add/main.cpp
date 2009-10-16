//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop
#define S 3
//---------------------------------------------------------------------------
typedef unsigned char T1;
void inc(T1 *A, int i,int D=1);
T1 A[S],B[S],C[S];
unsigned int R=sizeof A[0];
unsigned int MAX=(pow(256,R)-1);
#pragma argsused
int main(int argc, char* argv[])
{
        A[0]=16;
        A[1]=39;
        B[0]=255;
        B[1]=78;
      for(int i=0;i<S;i++)
                {if(A[i]>MAX-B[i]) inc(A,i+1);
                C[i]=A[i]+B[i];}
        return 0;
}
//---------------------------------------------------------------------------
void inc(T1 *A,int i,int D)
{
        if(A[i]>MAX-D) inc(A,i+1);
        A[i]=A[i]+D;
}
//---------------------------------------------------------------------------
