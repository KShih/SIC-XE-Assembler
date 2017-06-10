#include<iostream>
 
#include<fstream>
 
#include<string>
 
#include<cstdlib>
 
#include <sstream>
 
 
 
using namespace std;
 
struct reg
 
    {
 
        char r;
 
        char reg_code;
 
    };
 
reg REGTAB[6]=
 
    {
 
        {'A','0'},
 
        {'X','1'},
 
        {'L','2'},
 
        {'B','3'},
 
        {'S','4'},
 
        {'T','5'},
 
    };
 
struct optable
 
    {
 
        char op[8];
 
        unsigned int format;
 
        unsigned int opcode;
 
    };
 
optable OPTAB[32]=
 
    {
 
        {   "ADD",  3,  0x18},
 
        { "CLEAR",  2,  0xB4},
 
        {  "COMP",  3,  0x28},
 
        { "COMPR",  2,  0xA0},
 
        {   "DIV",  3,  0x24},
 
        {     "J",  3,  0x3C},
 
        {   "JEQ",  3,  0x30},
 
        {   "JGT",  3,  0x34},
 
        {   "JLT",  3,  0x38},
 
        {  "JSUB",  3,  0x48},
 
        {   "LDA",  3,  0x00},
 
        {   "LDB",  3,  0x68},
 
        {  "LDCH",  3,  0x50},
 
        {   "LDL",  3,  0x08},
 
        {   "LDT",  3,  0x74},
 
        {   "LDX",  3,  0x04},
 
        {   "LDS",  3,  0x6C},
 
        {   "MUL",  3,  0x20},
 
        {    "RD",  3,  0xD8},
 
        {  "RSUB",  3,  0x4C},
 
        {   "STA",  3,  0x0C},
 
        {   "STB",  3,  0x78},
 
        {  "STCH",  3,  0x54},
 
        {   "STL",  3,  0x14},
 
        {   "STT",  3,  0x84},
 
        {   "STS",  3,  0x7C},
 
        {   "STX",  3,  0x10},
 
        {   "SUB",  3,  0x1C},
 
        {    "TD",  3,  0xE0},
 
        {   "TIX",  3,  0x2C},
 
        {  "TIXR",  2,  0xB8},
 
        {    "WD",  3,  0xDC},
 
    };
 
 
 
string line[1000],code[1000],opcode[1000],symtable[1000],label[1000],objcode[1000]
        ,checkplus[1000];
 
int loc_count = 0;
 
int time =0;
 
void readfile();
 
void writeobj();
 
void cal_immediate();
 
void cal_register();
 
void showobjcode();
 
int main()
 
{
 
    readfile();
 
    writeobj();
 
    showobjcode();
 
}
 
void readfile()
 
{
 
    fstream fi;
 
    fstream fo ;
 
 
 
    fi.open("Loc_addr.txt",ios::in);
 
    fo.open("input.txt",ios::in);
 
 
 
    if(!fi)
 
    {
 
        cout<<"no file"<<endl;
 
    }
 
    else
 
    {
 
        while(!fi.eof())
 
        {
 
            getline(fi,line[++loc_count]);
 
            //cout<<line[loc_count]<<endl;
 
        }
 
    }
 
    loc_count=0;
 
    if(!fo)
 
    {
 
        cout<<"no file"<<endl;
 
    }
 
    else
 
    {
 
        while(!fo.eof())
 
        {
 
            bool check_break =false;
 
            time++;
 
            getline(fo,code[++loc_count]);
 
            for(int i=0;i<code[loc_count].size()&&!check_break;i++)
 
            {
 
                int j=0;
 
//---------------------------symtable-------------------------------------
 
                if(i==0)
 
                {
 
                    if(code[loc_count][i]==' ')
 
                    {
 
                        symtable[time]=" ";
 
                    }
 
                    else if(code[loc_count][i]=='.')
 
                    {
 
                        symtable[time]=".";
 
                        check_break=true;
 
                    }
 
                    else
 
                    {
 
                        string temp="";
 
                        while(code[loc_count][j]!=' ')
 
                        {
 
                            temp+=code[loc_count][j];
 
                            //cout<<code[loc_count][j];
 
                            j++;
 
                        }
 
                        symtable[time]=temp;
 
                        //cout<<temp<<endl;
 
                    }
 
                }
 
                if(check_break)
 
                {
 
                    break;
 
                }
 
//---------------------opcode-------------------------------
 
                int k=j;
 
                while(code[loc_count][k]==' ')
 
                {
 
                    k++;
 
                }
 
                string temp="";
 
                while(code[loc_count][k]!=' ')
 
                {
 
                    temp+=code[loc_count][k];
 
                    k++;
 
                    if(code[loc_count][k]=='\0')
 
                    {
 
                        check_break=true;
 
                        break;
 
                    }
 
                }
 
                opcode[time]=temp;
 
                //cout<<temp<<","<<endl;
 
                if(check_break)
 
                {
 
                    break;
 
                }
 
//-----------------------label---------------------------------
 
                while(code[loc_count][k]==' ')
 
                {
 
                    k++;
 
                }
 
                temp="";
 
                while(code[loc_count][k]!='\0')
 
                {
 
                    temp+=code[loc_count][k];
 
                    k++;
 
                }
 
                label[time]=temp;
 
                //cout<<temp<<endl;
 
                break;
 
            }
 
        }
 
    }
 
    fi.close();
 
    fo.close();
 
};
 
void writeobj()
 
{
 
    for(int i=1;i<time;i++)
 
    {
 
        int check=0;
 
        bool checkPlus=false;
 
        int obj =0x00000000;
 
        int ni =3;
 
        if(opcode[i][0]=='+')
 
        {
            checkPlus=true;
            checkplus[i] = "1";
 
            string temp="";
 
            for(int j=1;j<opcode[i].size();j++)
 
            {
 
                temp+=opcode[i][j];
 
            }
 
                opcode[i]=temp;
 
        }
 
        if(opcode[i]=="BYTE")
 
        {
 
            string temp="";
 
            if(label[i][0]=='X')
 
            {
 
                for(int j=2;j<label[i].size()-1;j++)
 
                {
 
                    temp+=label[i][j];
 
                }
 
                objcode[i]=temp;
 
                //cout<<temp<<endl;
 
            }
 
        }
 
        if(opcode[i]=="RSUB")
 
        {
 
                objcode[i]="4F0000";
 
                continue;
 
                //cout<<temp<<endl;
 
        }
 
       for(int k=0;k<32;k++)
 
        {
 
            if(opcode[i]==OPTAB[k].op)
 
            {
 
                obj=OPTAB[k].opcode;
 
                if(OPTAB[k].format==2)
 
                {
 
                   check=2;
 
                }
 
                else
 
                {
 
                    check=1;
 
                }
 
                break;
 
                //cout<<obj<<endl;
 
            }
 
        }
 
        if(check==0)
 
        {
 
            objcode[i]==" ";
 
           //cout<<"1"<<endl;
 
            continue;
 
        }
 
        if(check==1)
 
        {
 
            if(label[i][0]=='#')
 
            {
 
                ni=1;
 
            }
 
            else if(label[i][0]=='@')
 
            {
 
                ni=2;
 
            }
 
            obj=obj+ni;
 
        }
        stringstream ss;
        ss << hex << obj;
        ss >> objcode[i];
        if (objcode[i].size() == 1) {
            string temp = "0";
            temp += objcode[i];
            objcode[i] = temp;
        }
        ss.str("");
        ss.clear();
        //cout<<hex<<obj<<endl;
 
    }
 
    cal_immediate();
    cal_register();
 
};
 
void cal_immediate(){
    for(int i=1;i<time;i++) {
        int xbpe = 2;
        if( label[i][0] == '#') {
            if(label[i][1] >= '0' && label[i][1] <= '9'){
                string temp = "";
                for(int j=1;j<label[i].size();j++) {
                    temp+=label[i][j];
                }
                stringstream ss;
                ss << hex << temp;
                ss >> temp;
                while(temp.size() < 4) {
                    temp = '0' + temp;
                }
                objcode[i] += temp;
            }else{
                string temp = "";
                for(int j=1;j<label[i].size();j++)
 
                {
 
                    temp+=label[i][j];
 
                }
                bool check_base = false;
                //cout << temp <<endl;
                for(int j=1;j<time;j++) {
                    int line_i, line_j;
                    stringstream ss;
                    ss << hex << line[i];
                    ss >> line_i;
                    ss.clear();
                    ss << hex << line[j];
                    ss >> line_j;
                    ss.clear();
                    if( symtable[j] == temp) {
                        temp = "";
                        temp = line[j];
                        int i_value = 0;
                        //cout << symtable[j] << endl;
                        if(checkplus[i] == "1") {
                            xbpe = 1;
                            i_value = 5;
                        }else i_value = 3;
                        while (temp.size() < i_value) {
                            temp = '0' + temp;
                        }
                        string tempStr = "";
                        ss << hex << xbpe;
                        ss >> tempStr;
                        temp = tempStr + temp;
                        objcode[i]+=temp;
                        break;
                    }
                    /*
                    if(abs(line_i-line_j)>=0x1000) {
                        check_base = true;
                        for(int j=1;j<time;j++) {
                            //cout << opcode[j] << " " << label[j] << endl;
                            if(opcode[j] == "BASE" && label[j] == temp) {
 
                                break;
                            }
                        }
                        break;
                    }
                    */
                    /*
                    if(temp == symtable[j]) {
                        string temp1 = line[j];
                        int line_len = line[j].size();
                        if( checkplus[i] == "1") {
                            while(temp1.size()<4) {
                                temp1 = '0' + temp1;
                            }
                            cout << temp1 << endl;
                        }
                    }
                    */
                }
            }
        }
    }
}
 
void cal_register() {
    for(int i=0;i<time;i++) {
        if(opcode[i][opcode[i].size()-1] == 'R') {
            if(label[i].size()>1) {
                for(int j=0;j<6;j++) {
                    if(label[i][0] == REGTAB[j].r) {
                        objcode[i] += REGTAB[j].reg_code;
                    }
                }
                for(int j=0;j<6;j++) {
                    if(label[i][2] == REGTAB[j].r) {
                        objcode[i] += REGTAB[j].reg_code;
                    }
                }
            }else{
                for(int j=0;j<6;j++) {
                    if(label[i][0] == REGTAB[j].r) {
                        objcode[i] += REGTAB[j].reg_code;
                        objcode[i] += '0';
                    }
                }
            }
        }
    }
}
 
void showobjcode()
 
{
 
    for(int i=1;i<time;i++)
 
    {
 
        cout<<hex<<objcode[i]<<endl;
 
    }
}
