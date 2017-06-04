#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<string.h>
using namespace std;

#define SIZE 100
char line[SIZE];

int linecount = 0;
int getformat(char* c);

int main(){
    fstream fi;
    fstream fo;
    fi.open("input.txt",ios::in);
    fo.open("format.txt",ios::out);
    while(fi.getline(line,sizeof(line),'\n'))
        {
        fo<<linecount<<" "<<line<<" "<<getformat(line)<<endl;
        linecount += 5;
        }
    fi.close();
    fo.close();
    system("PAUSE");
    return 0;
}

int getformat(char* c)
{
    int i = 0;



    for(i=0 ; i<strlen(c) ; i++)
    {
        if (c[i]=='S'&&c[i+1]=='T'&&c[i+2]=='A'&&c[i+3]=='R'&&c[i+4]=='T'){return 0;}
        if (c[i]=='E'&&c[i+1]=='N'&&c[i+2]=='D'){return 0;}
        if (c[i]=='B'&&c[i+1]=='Y'&&c[i+2]=='T'&&c[i+3]=='E'){return 51;}
        if (c[i]=='W'&&c[i+1]=='O'&&c[i+2]=='R'&&c[i+3]=='D'){return 52;}
        if (c[i]=='R'&&c[i+1]=='E'&&c[i+2]=='S'&&c[i+3]=='B'){return 53;}
        if (c[i]=='R'&&c[i+1]=='E'&&c[i+2]=='S'&&c[i+3]=='W'){return 54;}
        if (c[i]=='+')
        {
            return 4;
        }

        if(c[i]==' '&&c[i+2]==','&&c[i+3]!='x')
        {
            return 2;
        }
        if(c[i]==' '&&c[i+2]!=' '&&(i+2)==strlen(c))
        {
            return 2;
        }

    }
    return 3;
}

