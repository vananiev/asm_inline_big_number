//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#define S 3
//---------------------------------------------------------------------------
void dec(int i,int D=1);
typedef unsigned long int T1;
T1 A[S],B[S],C[S];
int R=sizeof A[0];
#pragma argsused
int main(int argc, char* argv[])
{
        R==R;
      for(int i=0;i<S;i++)
                {if(A[i]<B[i]) dec(i+1);
                C[i]=A[i]-B[i];}
        return 0;
}
//---------------------------------------------------------------------------
void dec(int i,int D)
{
        if(A[i]<D) dec(i+1);
        A[i]=A[i]-D;
}
//---------------------------------------------------------------------------
