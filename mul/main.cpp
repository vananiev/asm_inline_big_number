//---------------------------------------------------------------------------

#include <vcl.h>
#include<math.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma argsused
#define S 3

typedef long unsigned int T1;
typedef short unsigned int T2;

template <class _T> void inc(_T *A,int i,int D=1);

T1 A[S],B[S],C[S];
T2 X[2*S],Y[2*S],M[2*S];
union T3
        {T1 temp;
        T2 t[2];};

unsigned int R=sizeof A[0];
unsigned int MAX=(pow(256,R)-1);
unsigned int MAX2=(pow(256,R/2)-1);

int main(int argc, char* argv[])
{
        register T1 j;
        register T3 m;

        for(register unsigned int k=0;k<2*S;k++)
                for(register unsigned int i=0;i<=k;i++)
                        {j=k-i;
                        m.temp=X[i]*Y[j];
                        if(M[k]>MAX2-m.t[0]) inc(M,k+1);
                        M[k]=M[k]+m.t[0];
                        if(M[k+1]>MAX2-m.t[1]) inc(M,k+2);
                        M[k+1]=M[k+1]+m.t[1];
                        }
        return 0;
}
//---------------------------------------------------------------------------
template <class _T> void inc(_T *A,int i,int D)
{
        if(A[i]>MAX-D) inc(A,i+1);
        A[i]=A[i]+D;
}
//---------------------------------------------------------------------------