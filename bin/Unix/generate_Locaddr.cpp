#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<ctype.h>

using namespace std;

int main()
{
    fstream input;
    fstream addr_output;
    fstream SYMTAB;
    fstream PRGRAM_BLOCKS;
    string buffer;
    string numstr;
    stringstream stream;
    bool flag=false;
    int format;
    int addr=0;
    int Fpoint,Bpoint;
    int i,num;
    int block=0;
    int block_addr[10]={0};
    int sum_addr=0;
    string block_name[10]={"\0"};
    string blockstr;
    string LTORG_name[10]={"\0"};
    string LTORGstr;
    bool LTORG_flag=true;
    bool absolute_flag=false;
    bool LTORG_outputflag=false;

    input.open("format.txt",ios::in);
    addr_output.open("Loc_addr.txt",ios::out);
    SYMTAB.open("SYMTAB.txt",ios::out);
    PRGRAM_BLOCKS.open("PRGRAM_BLOCKS.txt",ios::out);
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
            else if(buffer[0]=='.')
            {
                addr_output<<"Comment"<<endl;
                continue;
            }
            else if(buffer[11]=='E' && buffer[12]=='N' && buffer[13]=='D')
            {
                addr_output<<"END";
                continue;
            }
            if(buffer[20]=='=')
            {
                for(i=20;i<buffer.length()-2;i++)
                {
                    LTORGstr=LTORGstr+buffer[i];
                }
                for(i=0;i<=9;i++)
                {
                    if(LTORG_name[i]==LTORGstr)
                    {
                        LTORG_flag=false;
                        break;
                    }
                }
                if(LTORG_flag==true)
                {
                    for(i=0;i<=9;i++)
                    {
                        if(LTORG_name[i]=="\0")
                        {
                            LTORG_name[i]=LTORGstr;
                            break;
                        }
                    }
                }
                LTORG_flag=true;
                LTORGstr="\0";
            }
            if(buffer[11]=='E' && buffer[12]=='Q' && buffer[13]=='U')
            {
                for(i=20;i<buffer.length()-2;i++)
                {
                    if(buffer[i]=='-')
                    {
                        absolute_flag=true;
                    }
                }
            }
            if(buffer[0]!=' ')
            {
                for(i=0;i<=10;i++)
                {
                    SYMTAB<<buffer[i];
                }
                SYMTAB<<block<<"  "<<setw(4)<<setfill('0')<< hex << std::uppercase << block_addr[block]<<endl;
            }
            if(buffer[buffer.length()-2]=='5')
            {
                stream<<buffer[buffer.length()-1];
                stream>>format;
                stream.clear();
                format+=50;
            }
            else if(buffer[buffer.length()-2]=='4')
            {
                stream<<buffer[buffer.length()-1];
                stream>>block;
                stream.clear();
                format=40;
            }
            else if(buffer[buffer.length()-2]=='6')
            {
                format=60;
                addr_output<<setw(4)<<setfill('0')<<hex<< std::uppercase <<block_addr[block]<<"/-"<<endl;
                LTORG_outputflag=true;
            }
            else
            {
                stream<<buffer[buffer.length()-1];
                stream>>format;
                stream.clear();
            }
            if(absolute_flag==true)
            {
                addr_output<<setw(4)<<setfill('0')<<hex<< std::uppercase <<block_addr[block]<<"/-"<<endl;
            }
            else if(LTORG_outputflag!=true)
            {
                addr_output<<setw(4)<<setfill('0')<<hex<< std::uppercase <<block_addr[block]<<"/"<<block<<endl;
            }
            absolute_flag=false;
            LTORG_outputflag=false;
            switch(format)
            {
                case 40:
                    if(block==0)
                    {
                        block_name[block]="DEFAULT";
                    }
                    else
                    {
                        for(i=20;i<buffer.length()-3;i++)
                        {
                            blockstr=blockstr+buffer[i];
                        }
                        block_name[block]=blockstr;
                        blockstr="\0";
                    }
                    break;
                case 60:
                    for(i=0;i<=9;i++)
                    {
                        if(LTORG_name[i]!="\0")
                        {
                            SYMTAB<<left<<setw(11)<<setfill(' ')<<LTORG_name[i]<<block<<"  "<<right<<setw(4)<<setfill('0')<<hex<<block_addr[block]<<endl;
                            addr_output<<setw(4)<<setfill('0')<<hex<<block_addr[block]<<"/"<<block<<endl;
                            if(LTORG_name[i][1]=='C')
                            {
                                block_addr[block]+=3;
                            }
                            else if(LTORG_name[i][1]=='X')
                            {
                                block_addr[block]+=1;
                            }
                            LTORG_outputflag=true;
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                case 51:
                    block_addr[block]+=1;
                    break;
                case 52:
                    block_addr[block]+=3;
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
                    block_addr[block]+=num;
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
                    block_addr[block]+=num*3;
                    break;
                default:
                    block_addr[block]+=format;
                    break;
            }
        }
        for(i=0;i<=9;i++)
        {
            if(block_name[i]!="\0")
            {
                PRGRAM_BLOCKS<<left<<setw(9)<<setfill(' ')<<block_name[i]<<"  "<<i<<"  "<<right<<setw(4)<<setfill('0')<<hex<< std::uppercase <<sum_addr<<"  "<<setw(4)<<setfill('0')<<hex<< std::uppercase <<block_addr[i]<<endl;
                sum_addr+=block_addr[i];
            }
            else
            {
                break;
            }
        }
        input.close();
        addr_output.close();
        SYMTAB.close();
        PRGRAM_BLOCKS.close();
        cout<<"Successfully create Loc_addr.txt, PRGRAM_BLOCKS.txt, SYMTAB.txt"<<endl;
    }
}
