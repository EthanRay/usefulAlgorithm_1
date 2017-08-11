
#include"../stdfx.h"

void zigzag(int N)
{

    int s,i,j;
    int squa;
   // scanf("%d",&N);
    int **a=(int**)malloc(N*sizeof(int));
    if(a==NULL)
        return;
    for(int i=0;i<N;++i)
    {
        if((a[i]=(int*)malloc(N*sizeof(int)))==nullptr)
        {
            while(--i>=0)
                free(a[i]);
            free(a);
            return;
        }
    }

    squa=N*N;
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
    {
        s=i+j;
        if(s<N)
            a[i][j]=s*(s+1)/2+(((i+j)%2==0)?i:j);
        else
        {
            s=(N-1-i)+(N-1-j);
            a[i][j]=squa-s*(s+1)/2-(N-(((i+j)%2==0)?i:j));
        }
    }

    for(i=0;i<N;++i)
    {
        for(j=0;j<N;++j)
        {
            printf("%6d",a[i][j]);
        }
        printf("\n");
    }
}
