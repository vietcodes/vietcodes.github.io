#include<iostream>
#include<algorithm>
#define fr(a,b,c) for(a=b;a<=c;a++)
#define frr(a,b,c) for(a=b;a>=c;a--)
#define maxn 100100
#define oo 1000000000
using namespace std;
	
int n,b[maxn][3],p[maxn],a[maxn*2],c[maxn*2],d[maxn],e[maxn][18],f[maxn][18],g[maxn][18],h[maxn],u,v,hh;
 
	
void visit(int x,int y,int v,int u)
{
    d[x]=v; h[x]=u; e[x][0]=y; hh=max(hh,u);
    int i;
    fr(i,p[x]+1,p[x+1])
      if (a[i]!=y) visit(a[i],x,c[i],u+1); 
}
	
 
	
void query(int x,int y)
{
   int lg,t,i; 
   v=oo,u=-oo;
   if (h[x]<h[y]) swap(x,y);
   for (lg=0;1<<lg<=h[x];lg++); lg--;
   frr(i,lg,0)
     if (h[x]-(1<<i)>=h[y])
     {
        u=max(u,f[x][i]);
        v=min(v,g[x][i]);
        x=e[x][i];                   
     }  
   if (x==y) return;
   frr(i,lg,0)
     if (e[x][i] && e[x][i]!=e[y][i])
     {
        u=max(u,max(f[x][i],f[y][i]));
        v=min(v,min(g[x][i],g[y][i]));
        x=e[x][i]; y=e[y][i]; 
     }
   u=max(u,max(d[x],d[y]));
   v=min(v,min(d[x],d[y]));
}
 
int main()
{
    int i,j,q,x,y;
    scanf("%d",&n);
    fr(i,1,n-1)
    {
       fr(j,0,2) scanf("%d",&b[i][j]);
       p[b[i][0]]++; p[b[i][1]]++;     
    }
    fr(i,2,n+1) p[i]+=p[i-1];
    fr(i,1,n-1)
    {
       a[p[b[i][0]]]=b[i][1];
       c[p[b[i][0]]--]=b[i][2];
       a[p[b[i][1]]]=b[i][0];        
       c[p[b[i][1]]--]=b[i][2];
    }
    //pre-compute
    visit(1,0,0,0);
    fr(i,2,n) f[i][0]=g[i][0]=d[i];
    for (j=1;1<<j<=hh;j++)
      fr(i,1,n)
        if (e[i][j-1])
        {
           e[i][j]=e[e[i][j-1]][j-1];
           f[i][j]=max(f[i][j-1],f[e[i][j-1]][j-1]);
           g[i][j]=min(g[i][j-1],g[e[i][j-1]][j-1]);
        } 
    //query
    scanf("%d",&q);
    while (q--)
    {
       scanf("%d%d",&x,&y);
       query(x,y);
       printf("%d %d\n",v,u);
       //system("pause");
    }
    return 0;
}
