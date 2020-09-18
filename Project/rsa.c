#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<rsa.h>
//ong int p,q,n,t,flag,temp[100],j,m[100],en[100],i;

typedef short int pixel_t;

/*void main()
{

    printf("\nENTER FIRST PRIME NUMBER\n");
    scanf("%ld",&p);
    flag=prime(p);
    if(flag==0)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
    scanf("%ld",&q);
    flag=prime(q);
    if(flag==0||p==q)
    {
        printf("\nWRONG INPUT\n");
        exit(1);
    }
    printf("\nENTER MESSAGE\n");
    fflush(stdin);
    scanf("%s",msg);
    for(i=0;msg[i]!=0;i++)
        m[i]=msg[i];
    n=p*q;
    t=(p-1)*(q-1);
    ce();
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    for(i=0;i<j-1;i++)
        printf("\n%ld\t%ld",e[i],d[i]);
    encrypt();
    decrypt();
}*/
int prime(long int pr)
{
    int i,j;
    j=sqrt((double)pr);
    for(i=2;i<=j;i++)
    {
        if(pr%i==0)
            return 0;
    }
    return 1;
}
void ce(long int p, long int q, long int t, long int *e, long int *d)
{
    int i,j,k,flag;
    k=0;
    for(i=2;i<t;i++)
    {
        if(t%i==0)
            continue;
        flag=prime(i);
		j = sqrt((double)i);
        if(flag==1&&i!=p&&i!=q)
        {
            e[k]=i;
            flag=cd(e[k],t);
            if(flag>0)
            {
                d[k]=flag;
                k++;
            }
            if(k==99)
                break;
        }
    }
	 printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    for(i=0;i<j-1;i++)
        printf("%ld\t%ld\n",e[i],d[i]);
}
long int cd(long int x, long int  t)
{
    long int k=1;
    while(1)
    {
        k=k+t;
        if(k%x==0)
            return(k/x);
    }
}
void encrypt(long int *e,long int n, char *msg)
{
    long int pt,ct,key=e[0],k,len;
    int i=0, j;
	long int m[100], temp[100], en [100]; 
	 for(i=0;msg[i]!=0;i++)
        m[i]=msg[i];
    len=strlen(msg);
    while(i!=len)
    {
        pt=m[i];
        pt=pt-96;
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;
        en[i]=ct;
        i++;
    }
    en[i]=-1;
    printf("\nTHE ENCRYPTED MESSAGE IS\n");
    for(i=0;en[i]!=-1;i++)
        printf("%c",(char)en[i]);
}
void decrypt(long int *en, long int *temp, long int n )
{
    long int d[100], m[100];
    long int pt,i,j,ct,key=d[0],k;
    i=0;
    while(en[i]!=-1)
    {
        ct=temp[i];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*ct;
            k=k%n;
        }
        pt=k+96;
        m[i]=pt;
        i++;
    }
    m[i]=-1;
    printf("\nTHE DECRYPTED MESSAGE IS\n"); 
    for(i=0;m[i]!=-1;i++) 
        printf("%c",(char)m[i]); 
}

void encryptImage( pixel_t *image, int32_t  width, int32_t  height,long int *en, long int *e, long int *temp, long int n){
long int i,j ;
char msg[262145];
long int m[262145];
	for(i = 0; i <= width*height; i++){        
		msg[i] = image[i];
		m[i] = msg[i];
		//printf("%c ",(char)m[i]);	
		}

    long int pt,ct,key=e[0],k,len;
    i=0;
    len=width*height;
    while(i!=len)
    {
        pt=m[i];
        pt=pt-96;
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;
        en[i]=ct;
        i++;
    }
    en[i]=-1;
    printf("\n ENCRYPTED MESSAGE \n");
	for(i = 0; i <= width*height; i++){        
		image[i] = (pixel_t) en[i];	
		}

}
void decryptImage(pixel_t *image, int32_t  width, int32_t  height, long int *en, long int *temp, long int *d, long int n){


    long int m[262145];
    long int pt,i,j,ct,key=d[0],k;
    i=0;
    while(en[i]!=-1)
    {
        ct=temp[i];
        k=1;
        for(j=0;j<key;j++)
        {
            k=k*ct;
            k=k%n;
        }
        pt=k+96;
        m[i]=pt;
        i++;
    }
    m[i]=-1;
    printf("\nDECRYPTED MESSAGE \n"); 
    for(i = 0; i <= width*height; i++)    
		image[i] = (pixel_t) m[i];	

}

