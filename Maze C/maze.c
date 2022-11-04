#include <stdio.h>
#include <stdlib.h>

int dl[]={-1,0,1,0},dc[]={0,1,0,-1}; 
int n,m,count,li,ci,lfinal,cfinal,i,j; 
int v[201][201],**T;

FILE* g;

void afis(int **T)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(T[i][j]!=0)
                fprintf(g,"."); 
            else fprintf(g,"%c",(char)v[i][j]); 
        }
        fprintf(g,"\n");
    }
}

void Back(int l,int c,int pas)
{
    int i,li,ci; 
    for(i=0;i<4;i++)
    {
        li=l+dl[i]; 
        ci=c+dc[i]; 
        if(li>=1 && li<=n && ci>=1 && ci<=m)
        {
	        if(((char)v[li][ci]==' ' && T[li][ci]==0) || (char)v[li][ci]=='E') 
            {
                T[li][ci]=pas;

                if(li==lfinal && ci==cfinal) 
                {
                    afis(T); 
                }
                else
                {
                    Back(li,ci,pas+1); 
                }
                T[li][ci]=0; 
            }
        }
    }
}

int main()
{
    char c;

    FILE* f=fopen("maze.txt","r");

    if(f==NULL)
    {
        printf("ERROR ON READ!"); 
        return -1; 
    }
    
    g=fopen("mazeout.txt","w"); 
    
    if(g==NULL)
    {
	      printf("ERROR ON WRITE!"); 
	      return -1; 
    }
    
    fscanf(f,"%c",&c); 
    
    while(c!='\n') 
    {
        m++; 
        fscanf(f,"%c",&c);
    }
    
    for(i=1;i<=m;i++)
        v[1][i]=35; 
        
    n=2;
    count=1;
    
    while(!feof(f)) 
    {
        fscanf(f,"%c",&c); 
        v[n][count]=c; 
        if(c=='S') 
        {
            li=n;
            ci=count;
        }
        if(c=='E')
        {
            lfinal=n;
            cfinal=count;
        }
        if(count==m+1)
        {
            n++;
            count=1;
        }
        else count++;
    }
    n--;

    T=(int **)malloc((n+1)*sizeof(int*)); 
    for(i=1;i<=n;i++)
        T[i]=(int *)malloc((m+1)*sizeof(int)); 
    
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            T[i][j]=0; 

    T[li][ci]=1; 
    Back(li,ci,2);
    
    for(i=1;i<=n;i++) 
        free(T[i]); 
    free(T); 

    fclose(f); 
    fclose(g); 
    return 0;
}