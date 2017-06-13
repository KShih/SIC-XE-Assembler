#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<string.h>
#include<iomanip>
using namespace std;

#define SIZE 100
char line[SIZE];
char line2[SIZE];

int linecount = 0;
int getformat(char* c);

int main(){
    fstream fi,fii;
    fstream fo;
    fi.open("SYMTAB.txt",ios::in);
    if(!fi){
        cout<<"no SYMTAB.txt"<<endl;
        return 0;
    }
    fo.open("Output.txt",ios::out);
    fo <<"=SYMTAB="<<endl;
    while(fi.getline(line,sizeof(line),'\n'))
        {
        fo <<line<<" "<<endl;
        }
    fi.close();
    fi.open("PRGRAM_BLOCKS.txt",ios::in);
    if(!fi){
        cout<<"no PRGRAM_BLOCKS.txt"<<endl;
        return 0;
    }
    fo <<"=PRGRAM BLOCKS="<<endl;
    while(fi.getline(line,sizeof(line),'\n'))
        {
            fo <<setw(3)<<linecount<<" "<<line<<" "<<endl;
        }

    fi.close();
    fo <<"=OBJECT CODES="<<endl;
    fi.open("Loc_addr.txt",ios::in);
    if(!fi){
        cout<<"no Loc_addr.txt"<<endl;
        return 0;
    }
    fii.open("OBJECT_CODE.txt",ios::in);
    if(!fii){
        cout<<"no OBJECT_CODE.txt"<<endl;
        return 0;
    }
    while(fi.getline(line,sizeof(line),'\n'))
        {
            fii.getline(line2,sizeof(line2),'\n');

            if(strcmp(line,"END")!=0)
            {


            if(strcmp(line,"Comment")!=0)
            {
                fo.setf(ios::left, ios::adjustfield);
                fo << setw(3)<<linecount+1<< setw(5)<<" L/B="<<line<<" ";
            }

        }


        if(strcmp(line2,"Comment")==0)
        {

            fo << setw(3)<<linecount+1<<" "<<line2;
        }
        else if(strcmp(line2,"END")==0)
        {
            fo << setw(3)<<linecount+1<<" "<<line2;
        }
        else
        {
            fo.setf(ios::left, ios::adjustfield);
            fo <<setw(5)<<line2;
        }
        fo <<endl;
        linecount ++;
        }
    fi.close();
    fii.close();
    fo.close();
    cout<<"Successfully create Output.txt!"<<endl;
    cout << "Check out the Output.txt for everything!! " << endl;
    return 0;
}
