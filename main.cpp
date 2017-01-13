#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
int a[27][27];
char m[27][27];
int p[27][27];
int n,nivel,mine,tip,liber,ok,incercare,nrFlaguri,u;
int v1[]={0,0,-1,1,-1,-1,1,1};
int v2[]={-1,1,0,0,-1,1,-1,1};
void afisare()
{
    int i,j;char c;
    cout<<"     ";
    for(i=0;i<n;++i)
    { c='a';
        c=c+i;
        cout<<" "<<c<<" ";}
    cout<<endl;
    cout<<"     ";
    for(i=0;i<n;++i)
        cout<<" - ";
        cout<<endl;
    for(i=0;i<n;++i)
    {c='a';c=c+i;
        cout<<" "<<c<<" | ";
        for(j=0;j<n;++j)
            cout<<" "<<m[i][j]<<" ";
        cout<<" | "<<c<<endl;
    }
    cout<<"     ";
    for(i=0;i<n;++i)
        cout<<" - ";
    cout<<endl<<"     ";
    for(i=0;i<n;++i)
        {   c='a';c=c+i;
            cout<<" "<<c<<" ";}
            cout<<endl<<endl<<endl;
}
void initializare()
{
    int i,j;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
           m[i][j]='+';
}
void initializarea()
{
    int mn=mine,j,z;

        while(mn!=0)
        {
            j=rand() % n;
            z=rand() % n;
            if(a[j][z]!=1)
            {a[j][z]=1;--mn;}
        }

}
void afisarea()
{
    int i,j;
    for(i=0;i<n;++i)
    {for(j=0;j<n;++j)
        cout<<a[i][j]<<" ";
        cout<<endl;
    }
}
int bordura(int i,int j)
{
    if(i>=0&&i<n)
        if(j>=0&&j<n)
        return 1;
    return 0;
}
void vecin(int i,int j,char &c)
{
    int z;char b='0';
    for(z=0;z<8;++z)
        if(a[i+v1[z]][j+v2[z]]==1)
        b=b+1;
        c=b;
}
void selectare(int i,int j)
{
    int z;char c='0';
    if(bordura(i,j))
        if(p[i][j]==0)
        { if(a[i][j]==0)
            {p[i][j]=1;
            vecin(i,j,c);
             m[i][j]=c;
             if(c=='0')
            {
                for(z=0;z<8;++z)
            {
                int q=i+v1[z],w=j+v2[z];
                selectare(q,w);
            }}
         }}

}
void afisarep()
{
    int i,j;
    for(i=0;i<n;++i)
    {for(j=0;j<n;++j)
           cout<<p[i][j]<<" ";
           cout<<endl;}
           cout<<endl;
}
int libere()
{
    int i,j,nr=0;
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        if(p[i][j]==1)
        ++nr;
    if(liber - nr==0)
        return 1;
    return 0;
}
void descopera()
{
    int i,j;
    for(i=0;i<n;++i)
        for(j=1;j<n;++j)
           if(a[i][j]==1&&p[i][j]==0)
            m[i][j]='M';
           afisare();
}
void inlocuire(int i,int j)
{
    p[i][j]=1;int nr=0; int k=i,t=j;a[i][j]=0;
    while(nr==0)
    {
        k=rand()%n;
        t=rand()%n;
        if(p[k][t]==0&&a[k][t]==0)
        {a[k][t]==1;++nr;}
    }
}
void smecherie(int i,int j)
{
    if(m[i][j]!='0'&&m[i][j]!='+'&&m[i][j]!='F')
    {
        int k;
        for(k=0;k<8;++k)
            if(m[i+v1[k]][j+v2[k]]=='F'&&a[i+v1[k]][j+v2[k]]!=1)
            {cout<<"mort";ok=-1;m[i][j]='X';p[i][j]=1;descopera();break;}
            else
                if(a[i+v1[k]][j+v2[k]]==0&&p[i+v1[k]][j+v2[k]]==0)
                   {int q=i+v1[k];int w=j+v2[k];selectare(q,w);}
    }
}

void joc()
{
    cout<<"nivel 1:"<<endl;
    cout<<"nivel 2:"<<endl;
    cout<<"nivel 3:"<<endl<<endl;
    cout<<"selectare nivel: ";
    cin>>nivel;cout<<endl;
    int i,j;char p1,p2;
    if(nivel==1)
        {n=5;mine=5;liber=n*n-mine;nrFlaguri=mine;}
    else
        if(nivel==2)
        {n=15;mine=80;liber=n*n-mine;nrFlaguri=mine;}
    else
        {n=26;mine=250;liber=n*n-mine;nrFlaguri=mine;}
    initializare();
    cout<<"nrFlaguri: "<<nrFlaguri<<endl;
    afisare();
    initializarea();
    while(!libere() || ok==0)
    {
        cout<<"coordonate: ";
        cin>>p1>>p2;i=p1-'a';j=p2-'a';
        cout<<endl<<"tip: ";
        cin>>tip;
        if(m[i][j]=='+')
            {if(tip==2)
            {if(nrFlaguri!=0)
                {m[i][j]='F'; --nrFlaguri;}}
        else
          if(incercare==0)
            {if(a[i][j]==1)
             {
                 inlocuire(i,j);p[i][j]=0;
                 ++incercare;
             }
             else
                ++incercare;

        }
        if(tip==1)
           {if(a[i][j]==1)
           {cout<<"mort"<<endl;ok=-1;p[i][j]=1;m[i][j]='X';
           descopera();
           break;}
            else
               selectare(i,j);}
        }
           else
            if(tip==2)
            if(m[i][j]=='F')
                {m[i][j]='+'; ++nrFlaguri;}
                if(tip==3)
                    {smecherie(i,j);
                    if(ok==-1)
                    {cout<<"mort"<<endl;
                        descopera();
                    break;}
                    }


            if(libere())
        {
            ok=1;
            cout<<"victorie"<<endl;afisare();
            break;
        }
        cout<<"nrFlaguri: "<<nrFlaguri<<endl;
        afisare();
    }


}
void replay()
{
    int ce;--incercare;
    cout<<" 1-joc nou ; 2-gata: ";
    cin>>ce;
    if(ce==1)
        joc();
}

int main()

 {
         joc();
         replay();
        return 0;
}
