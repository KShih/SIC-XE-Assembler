#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<string.h>
#include<vector>
using namespace std;

/*
FORMAT TABLE IN THIS CASE

UNREAL CODE ,START,END --> 0
FORMAT 2 --> 2
FORMAT 3 --> 3
FORMAT 4 --> 4
BYTE --> 51
WORD --> 52
RESB --> 53
RESW --> 54
CODE BLOCK -->
               DEFAULT BLOCK --> 40
               BLOCK1 --> 41
               BLOCK2 --> 42
               ETC....
*/

#define SIZE 100
char line[SIZE];

int linecount = 0;
int getformat(char* c);
int block_format = 48;
char blocktable[100][100];
int block_num = 41;


int main(){
    fstream fi;
    fstream fo;
    fi.open("FIN-codetest_2017.txt",ios::in);
    fo.open("format.txt",ios::out);
    while(fi.getline(line,sizeof(line),'\n'))
        {
        fo<<line<<" "<<getformat(line)<<endl;
        }

    /*
    for(int i =41 ; i< 45 ;i++)
    {
        cout<<blocktable[i];
        cout<<endl;
    }
    */

    fi.close();
    fo.close();
    cout << "Successfully create format.txt" << endl;
    return 0;
}

int getformat(char* c)
{
    int i = 0;
    int step = 1;
    /*
    (STEP1)   (STEP2)   (STEP3)
    MAXLEN     EQU      BUFEND-BUFFER
    */



    for(i=0 ; i<strlen(c) ; i++)
    {
        if (c[i]==' '&&c[i+1]!=' '){step++;}
        if (step==2&&c[i]=='S'&&c[i+1]=='T'&&c[i+2]=='A'&&c[i+3]=='R'&&c[i+4]=='T'){return 0;}
        if (step==2&&c[i]=='E'&&c[i+1]=='N'&&c[i+2]=='D'){return 0;}
        if (step==1&&c[i]=='.'){return 0;}
        if (step==2&&c[i]=='B'&&c[i+1]=='A'&&c[i+2]=='S'&&c[i+3]=='E'){return 0;}
        if (step==2&&c[i]=='E'&&c[i+1]=='Q'&&c[i+2]=='U'){return 0;}
        if (step==2&&c[i]=='B'&&c[i+1]=='Y'&&c[i+2]=='T'&&c[i+3]=='E'){return 51;}
        if (step==2&&c[i]=='W'&&c[i+1]=='O'&&c[i+2]=='R'&&c[i+3]=='D'){return 52;}
        if (step==2&&c[i]=='R'&&c[i+1]=='E'&&c[i+2]=='S'&&c[i+3]=='B'){return 53;}
        if (step==2&&c[i]=='R'&&c[i+1]=='E'&&c[i+2]=='S'&&c[i+3]=='W'){return 54;}
        if (step==2&&c[i]=='L'&&c[i+1]=='T'&&c[i+2]=='O'&&c[i+3]=='R'&&c[i+4]=='G'){return 60;}
        if (c[i]=='U'&&c[i+1]=='S'&&c[i+2]=='E'&&c[i+3]!=' '){return 40;}
        if (c[i]=='C'&&c[i+1]=='L'&&c[i+2]=='E'&&c[i+3]=='A'&&c[i+4]=='R'){return 2;}
        else if (c[i]=='U'&&c[i+1]=='S'&&c[i+2]=='E')
        {
            bool exist = false;
            char temp[100]="";
            int temp_num = 0;
            int k = 0;
            for(int j=i+3 ;j<strlen(c);j++)         /* get block name, TEMP keep the block name*/
            {
                if(c[j]!=' '&&c[j]!='\n')
                {
                temp[temp_num]=c[j];
                temp_num ++ ;
                }
            }

            if(strlen(temp)>1)
            {
            strcpy(blocktable[block_num],temp);      /* push temp into block_table*/
            block_num++;                             /*block num start with 41, default40*/
            }

            for(k=41;k<100;k++)
            {
                if(!strncmp(blocktable[k],temp,strlen(blocktable[k])))  /*if this blockname is exist,return it's block num*/
                {
                    return k;
                }
            }
        }

        if (step==2&&c[i]=='+')
        {
            return 4;
        }

        if(step==3&&c[i]==','&&c[i+1]!='X')
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

