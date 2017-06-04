#include<iostream>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

int main()
{
    fstream input;
    fstream output;
    string buffer;
    string numstr;
    stringstream stream;
    bool flag=false;
    int format;
    int addr=0;
    int Fpoint,Bpoint;
    int i,num;

    input.open("format.txt",ios::in);
    output.open("Loc_addr.txt",ios::out);
    if(!input)
    {
        cout<<"format not found"<<endl;
    }
    else
    {
        while(!input.eof())
        {
            getline(input,buffer);
            if(buffer[0]=='\0')
            {
                break;
            }
            if(buffer[buffer.length()-2]=='5')
            {
                stream<<buffer[buffer.length()-1];
                stream>>format;
                stream.clear();
                format+=50;
            }
            else
            {
                stream<<buffer[buffer.length()-1];
                stream>>format;
                stream.clear();
            }
            switch(format)
            {
                case 51:
                    addr+=1;
                    break;
                case 52:
                    addr+=3;
                    break;
                case 53:
                    for(i=buffer.length()-3;i>=0;i--)
                    {
                        if(buffer[i]!=' ')
                        {
                            if(flag==false)
                            {
                                Bpoint=i;
                            }
                            flag=true;
                            Fpoint=i;
                        }
                        else if(flag==true)
                        {
                            break;
                        }
                    }
                    flag=false;
                    numstr=numstr.assign(buffer,Fpoint,Bpoint-Fpoint+1);
                    stream<<numstr;
                    stream>>num;
                    stream.clear();
                    addr+=num;
                    break;
                case 54:
                    for(i=buffer.length()-3;i>=0;i--)
                    {
                        if(buffer[i]!=' ')
                        {
                            if(flag==false)
                            {
                                Bpoint=i;
                            }
                            flag=true;
                            Fpoint=i;
                        }
                        else if(flag==true)
                        {
                            break;
                        }
                    }
                    flag=false;
                    numstr.assign(buffer,Fpoint,Bpoint-Fpoint+1);
                    stream<<numstr;
                    stream>>num;
                    stream.clear();
                    addr+=num*3;
                    break;
                default:
                    addr+=format;
                    break;
            }
            output<<addr<<endl;
        }
        input.close();
        output.close();
        cout<<"Loc_addr finish"<<endl;
    }
}
