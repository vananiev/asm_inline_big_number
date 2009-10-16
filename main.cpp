//---------------------------------------------------------------------------

#include <vcl.h>
#include <big_math.h>
#include<fstream.h>
#include<iostream.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused
#define _p 227000
T1 a[S],b[S],c[S],d[S],N[S],t[S];
uint P[_p];
uint Stopping[_p];
uint L=4;
int cnt=0,ind;
int start,str;
int main(int argc, char* argv[])
{
        ifstream in("p.txt");
        ifstream in2("stopping.txt");
        ofstream out2("super_p.txt",ios::app);
        for(cnt=0; cnt<_p && in2;cnt++)
                in2>>Stopping[cnt];
        in2.close();
        ofstream out("stopping.txt",ios::app);
        if(cnt!=0)
                str=Stopping[cnt-2];
                else str=0;
        cout<<"Start:"<<endl;
        cout<<str;
        for(int i=0,cnt=0; i<_p && in;i++)
                {in>>P[i];
                cnt++;}
        for(ind=0;ind<cnt;ind++)
                if(str<=P[ind])
                        break;
        start=ind;
        for(int i=ind; i<_p;i++)
                {out<<P[i]<<endl;
                set_null(b);
                 set_bit(b,P[i],1);
                 dec(b,0);
                set_null(d);
                 d[0]=4;
                for(uint j=1;j<P[i];j++)
                        {mul(d,d,a);
                        dec(a,0,2);
                        div(a,b,c,d);}
                //вычет Ћюка Ч Ћемера
                if(!compare(d,N))
                        {out2<<P[i]<<endl;
                        break;}
                }
        in.close();
        out.close();
        out2.close();return 0;
}
//---------------------------------------------------------------------------
