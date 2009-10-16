#ifndef _BIGMATH
#define _BIGMATH

#define OFL 0 //отображать ли на экране сообщение переполнения

#include <math.h>
#if OFL>0
        #include<iostream.h>
#endif

#define S 3125000    //количество блоков (по 32 бита) достаточных для величины (2^(50 000 000)-1)^2

typedef long unsigned int uint;
typedef long unsigned int T1;
typedef short unsigned int T2;
union T3
        {T1 temp;
        T2 t[2];};

uint pow(uint x,uint y){uint res=1;for(register uint i=0;i<y;i++)res=res*x;return res;};
inline template <class _T> void dec(_T *A,unsigned int i,unsigned int D=1);
inline template <class _T> void inc(_T *A,unsigned int i,unsigned int D=1);
void set_null(T1 *A,uint data=0);
inline uint find_null_bit(T1 *A);
inline void set_bit(T1 *A,uint n, uint value);
inline void L_bit(T1 *A,uint n);
inline void R_bit(T1 *A,uint n);
inline void set_bit(T1 *A,uint n, uint value);
inline void copy(T1 *A,T1 *B);

T1 *A,*B,*C;
T2 *X,*Y,*M;
T1 F[S],G[S];        //вспомогательная промежуточная величина

uint R=sizeof A[0];
uint MAX=(pow(256,R)-1);
uint MAX2=(pow(256,R/2)-1);
uint b_bit=pow(2,8*R-1);
uint bits=8*R;

//---------------------------------------------------------------------------
void sub(T1 *A,T1 *B,T1 *C)
{
        asm{mov ebx,A;
        mov edx,B;
        mov edi,C;
        mov ecx,0xffffffff;
        pushf;
        start:
        inc ecx;
        cmp ecx,S;
        jae end;
                //выполнение сложения
                mov eax,[ebx+ecx*4];
                popf;
                sbb eax,[edx+ecx*4];
                pushf;
                /*jnc P;
                        //Обработка переполнения
                        mov esi,ecx;
                        carry:
                        inc esi;
                        cmp esi,S;
                        jae end_carry;
                        dec [edi+esi*4];
                        js carry;
                        end_carry: */
                mov [edi+ecx*4],eax;
        P:
        jmp start;
        end:
        popf;} //если флаг cf=1 то переполнение
        /*for(register unsigned int i=0;i<S;i++)
                {if(A[i]<B[i]) dec(A,i+1);
                C[i]=A[i]-B[i];}*/
}
//---------------------------------------------------------------------------
inline template <class _T> void dec(_T *A,unsigned int i,unsigned int D)
{
        #if OFL>0
        if(i>S*R/(sizeof A[0]))
                {cout<<"Overflow of decrement.\n";
                return;}
        #endif
                if(A[i]<D)
                        {A[i]=A[i]-D;
                        for(register uint j=i+1;j<S;j++)
                                {if(A[j]==0)
                                        A[j]=A[j]-1;
                                        else{
                                        A[j]=A[j]-1;
                                        break;}
                                }
                        }
                        else
                                A[i]=A[i]-D;

}
//---------------------------------------------------------------------------
void add(T1 *A,T1 *B,T1 *C)
{
      /*for(register unsigned int i=0;i<S;i++)
                {if(A[i]>MAX-B[i]) inc(A,i+1);
                C[i]=A[i]+B[i];}*/
        asm{mov ebx,A;
        mov edx,B;
        mov edi,C;
        mov ecx,0xffffffff;
        pushf;
        start:
        inc ecx;
        cmp ecx,S;
        jae end;
                //выполнение сложения
                mov eax,[ebx+ecx*4];
                popf;
                adc eax,[edx+ecx*4];
                pushf;
                /*jnc P;
                        //Обработка переполнения
                        mov esi,ecx;
                        carry:
                        inc esi;
                        jae end_carry;
                        inc [edi+esi*4];
                        jz carry;
                        end_carry:*/
                mov [edi+ecx*4],eax;
        P:
        jmp start;
        end:
        popf;} //если флаг cf=1 то переполнение
}
//---------------------------------------------------------------------------
inline template <class _T> void inc(_T *A,unsigned int i,unsigned int D)
{
        uint r=sizeof A[0];
        #if OFL>0
        if(i>S*R/r){
                cout<<"Overflow of increment.\n";
                retun;}
        #endif
                uint _T_MAX=(pow(256,r)-1);
                if(A[i]>_T_MAX-D)
                        {A[i]=A[i]+D;
                        for(register uint j=i+1;j<S;j++)
                                {if(A[i]==_T_MAX)
                                        A[j]=A[j]+1;
                                        else{
                                        A[j]=A[j]+1;
                                        break;}
                                }
                        }
                        else
                                A[i]=A[i]+D;
}
//---------------------------------------------------------------------------
void mul(T1 *A,T1 *B,T1 *C)
{
        set_null(C);
        X=(T2*)A;
	Y=(T2*)B;
	M=(T2*)C;
	register T1 j;
        register T3 m;

        uint x1=find_null_bit(A);
        uint x2=find_null_bit(B);
        uint mS=x1>x2?x1:x2;
        #if OFL>0
        if(2*mS>S*bits)
                cout<<"Overflow of multiplication.\n";
        #endif
        mS=4*(mS+1)/bits+1;      //количество байт данных
        if(mS>2*S) mS=2*S;
        for(register unsigned int k=0;k<mS;k++)
                for(register unsigned int i=0,j=k;i<=k;i++,j--)
                        if(X[i] && Y[j]){
                                m.temp=X[i]*Y[j];
                                if(M[k]>MAX2-m.t[0])
                                        inc(M,k+1);
                                M[k]=M[k]+m.t[0];
                                if(M[k+1]>MAX2-m.t[1])
                                        inc(M,k+2);
                                M[k+1]=M[k+1]+m.t[1];}
}
//---------------------------------------------------------------------------
void mul_2(T1 *A,T1 *B,T1 *C)
{
        set_null(C);
        copy(B,F);
        register uint j,r;
        register uint i=find_null_bit(F);
        if(i!=-1){
                 copy(A,G);
                 L_bit(G,i);
                 r=0;}
        while(i!=-1)
                {R_bit(G,r);
                add(C,G,C);
                set_bit(F,i,0);
                j=find_null_bit(F);
                r=i-j;
                i=j;}
}
//---------------------------------------------------------------------------
inline bool L_bit(T1 *A)
{
        bool result = A[S-1] & b_bit;
        A[S-1]=A[S-1]<<1;
        for(register unsigned int i=S-2;i!=-1;i--)
                {if(A[i] & b_bit)
                        A[i+1]++;
                A[i]=A[i]<<1;}
        return result;
}
//---------------------------------------------------------------------------
inline void L_bit(T1 *A,uint n)
{
        register uint i=n/bits;
        register uint j=n%bits;
        #if OFL>0
        if(i>=S)
                {cout<<"Overflow in L_bit.\n";
                return;}
        #endif
        if(i!=0)
                {for(register uint k=(S-1)-i;k!=-1;k--)
                        A[k+i]=A[k];
                for(register uint k=i-1;k!=-1;k--)
                        A[k]=0;}
        /*for(register uint k=0;k<j;k++)
               L_bit(A);*/
        if(j!=0)
                {T1 m=MAX;
                T1 tm;
                m<<(bits-j);
                A[S-1]=A[S-1]<<j;
                for(register uint k=S-2;k!=-1;k--)
                        {if(A[k]!=0)
                                {tm=A[k] & m;
                                tm=tm>>(bits-j);
                                A[k+1]=A[k+1] | tm;
                                A[k]=A[k]<<j;}}
                }
}
//---------------------------------------------------------------------------
inline bool R_bit(T1 *A)
{
        bool result=A[0] & 1;
        A[0]=A[0]>>1;
        for(register unsigned int i=1;i<S;i++)
                {if(A[i] & 1)
                        A[i-1]=A[i-1] + b_bit;
                A[i]=A[i]>>1;}
        return result;
}
//---------------------------------------------------------------------------
inline void R_bit(T1 *A,uint n)
{
        register uint i=n/bits;
        register uint j=n%bits;
        #if OFL>0
        if(i>=S)
                {cout<<"Overflow in R_bit.\n";
                return;}
        #endif
        if(i!=0)
                {for(register uint k=i;k<S;k++)
                        A[k-i]=A[k];
                for(register uint k=S-i+1;k<S;k++)
                        A[k]=0;}
        /*for(register uint k=0;k<j;k++)
               R_bit(A);*/
        if(j!=0)
                {T1 m=MAX;
                T1 tm;
                m>>(bits-j);
                A[0]=A[0]>>j;
                for(register uint k=1;k<S;k++)
                        if(A[k])
                                {tm=A[k] & m;
                                tm=tm<<(bits-j);
                                A[k-1]=A[k-1] | tm;
                                A[k]=A[k]>>j;}
                }
}
//---------------------------------------------------------------------------
inline uint find_null_bit(T1 *A)
{
        bool find;
        register uint i;
        register uint j=-1;
        T1 k;
        for(i=S-1,find=true;i!=-1 && find;i--)
                if(A[i]!=0)
                        for(j=bits-1,k=b_bit;j!=-1;k=k>>1,j--)
                                if(A[i] & k)
                                        {find=false;
                                        break;}
        if(j!=-1)
                return bits*(i+1)+j;
                else
                return -1;
}
//---------------------------------------------------------------------------
inline int compare(T1 *A,T1 *B)
{
        for(register uint i=S-1,find=true;i!=-1 && find;i--)
                if(A[i]>B[i])
                        return 1;
                        else if(A[i]<B[i])
                        return -1;

        return 0;
}
//---------------------------------------------------------------------------
inline void set_bit(T1 *A,uint n, uint value)
{
        int i=n/bits;
        int j=n%bits;
        #if OFL>0
        if(i>S){
                cout<<"Overflow in set_bit.\n";
                return;}
        #endif
                if(value==0)
                        A[i]=A[i]&(~(1<<j));
                        else
                        A[i]=A[i]|(1<<j);

}
//---------------------------------------------------------------------------
void set_null(T1 *A,uint data)
{
        asm{
        mov eax,A;
        mov edx,data;
        mov ecx,0xffffffff;
        start:  //
        inc ecx;
        cmp ecx,S;
        jae end;
                mov [eax+ecx*4],edx;
        jmp start;
        end:}
        /*for(register uint i=0;i<S;i++)
                A[i]=0;*/
}
//---------------------------------------------------------------------------
inline void copy(T1 *A,T1 *B)
{
        for(register uint i=0;i<S;i++)
                B[i]=A[i];
}
//---------------------------------------------------------------------------
void div(T1 *A,T1 *B,T1 *C,T1 *D)
{
        set_null(C);
        set_null(D);
        register uint bs=find_null_bit(B);
        register int n = find_null_bit(A) - bs;
        if(n<0)
                {copy(A,D);
                return;}

                else
                {copy(B,F);
                copy(A,D);
                L_bit(F,n);
                for(register uint i=n;i!=-1;i--)
                        {uint cmp=compare(D,F);
                        if(cmp == 1){
                                set_bit(C,i,1);
                                sub(D,F,D);}

                                else if (cmp == 0){
                                set_bit(C,i,1);
                                set_null(D);
                                return;}
                        R_bit(F);
                        }
                }
}
//---------------------------------------------------------------------------
#endif



