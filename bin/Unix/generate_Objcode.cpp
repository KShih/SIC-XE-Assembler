#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;
struct reg{

    char r;
    char reg_code;

};

reg REGTAB[6]={

    {'A','0'},
    {'X','1'},
    {'L','2'},
    {'B','3'},
    {'S','4'},
    {'T','5'},

};

struct optable{

    char op[8];
    unsigned int format;
    unsigned int opcode;

};

optable OPTAB[32]={

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
/*
    line --> LOCCTR
    code --> unimportant array
    symtable -> opcode -> label
    objcpde -> output
    checkplus -> Judge plus
    block -> Use's states
    block_address -> PRGRAM_BLOCKS's address
    symtab_name / symtab_block / symtab_address -> SYMTAB's data
    LTORG -> Record LTORG
*/


string line[1000],code[1000],symtable[1000],opcode[1000],label[1000],objcode[1000]
        ,checkplus[1000],block[1000],block_address[1000],symtab_name[1000],symtab_block[1000],
        symtab_address[1000],LTORG[10],block_name[1000],flag_n[1000],flag_i[1000],flag_x[1000],
        flag_b[1000],flag_p[1000],flag_e[1000],format[1000];
bool OBJCODE_FINISH[1000] = {false}, checkWrong = true,Stop = false;
int loc_count = 0;
int counter =0;
int LTORG_SIZE = 0;
int BLOCK_SIZE = 0;
int SYMTAB_SIZE = 0;
void readfile();

void writeobj();

void reset_code();

void cal_immediate();

void cal_register();

void cal_xbpe();

void cal_address();

void cal_OBJCODE_FINSIH();

void showobjcode();

int main()
{
    readfile();
    writeobj();
    if(!Stop){
        showobjcode();
    }else
        cout << "Label's name or opcode has error." << endl;
}

void readfile()
{

    fstream fi;
    fstream fo ;
    fstream fsymtab;
    fstream fblock;

    fi.open("Loc_addr.txt",ios::in);
    fo.open("FIN-codetest_2017.txt",ios::in);
    fsymtab.open("SYMTAB.txt",ios::in);
    fblock.open("PRGRAM_BLOCKS.txt",ios::in);

    if(!fi)
    {
        cout<<"no file"<<endl;
    }
    else
    {
        while(!fi.eof())
        {
            getline(fi,line[++loc_count]);
            string temp = "";
            bool check_split = false;
            for(int i=0;i<line[loc_count-1].size();i++) {
                if(line[loc_count-1][i] == '/') {
                    check_split = true;
                    continue;
                }
                if( check_split) {
                    temp += line[loc_count-1][i];
                }
            }
            block[loc_count-1] = temp;
            check_split = false;
            temp = "";
            for(int i=0;i<line[loc_count-1].size();i++) {
                if(line[loc_count-1][i] == '/') check_split = true;
                if( !check_split) {
                    temp += line[loc_count-1][i];
                }
            }
            line[loc_count-1] = temp;
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
            counter++;
            getline(fo,code[++loc_count]);
            for(int i=0;i<code[loc_count].size()&&!check_break;i++)
            {
//---------------------------symtable-------------------------------------
                int j=0;
                if(i==0)
                {
                    if(code[loc_count][i]==' ')
                    {
                        symtable[counter]=" ";
                    }
                    else if(code[loc_count][i]=='.')
                    {
                        symtable[counter]=".";
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
                        symtable[counter]=temp;
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
                if( temp == "LTORG") {
                    opcode[counter]=temp;
                    for(int tt=0; tt<LTORG_SIZE; tt++) {
                        ++counter;
                        ++loc_count;
                        symtable[counter] = '*';
                        opcode[counter] = LTORG[tt];
                        label[counter] = "";
                    }
                }else opcode[counter]=temp;
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
                if( temp[0] == '=') {
                    bool check_LTORG_store = true;
                    for(int tt=0; tt<LTORG_SIZE; tt++) {
                        if( LTORG[tt] == temp) {
                            check_LTORG_store = false;
                        }
                    }
                    if( check_LTORG_store) {
                        LTORG[LTORG_SIZE] = temp;
                        LTORG_SIZE++;
                    }
                }

                label[counter]=temp;
                //cout<<temp<<endl;
                break;
            }
        }
    }
    //---------------------read SYMTAB ---------------------

    loc_count = 0;
    if(!fsymtab)
    {
        cout<<"no file"<<endl;
    }
    else
    {
        reset_code();
        while(!fsymtab.eof())
        {
            bool check_break =false;
            SYMTAB_SIZE++;
            getline(fsymtab,code[++loc_count]);
            for(int i=0;i<code[loc_count].size()&&!check_break;i++)
            {
//---------------------------symtable-------------------------------------
                int j=0;
                if(i==0)
                {
                    string temp="";
                    while(code[loc_count][j]!=' ')
                    {
                        temp+=code[loc_count][j];
                        //cout<<code[loc_count][j];
                        j++;

                    }
                    symtab_name[SYMTAB_SIZE]=temp;
                    //cout<<temp<<endl;
                }
                if(check_break)
                {
                    break;
                }

//---------------------symtab_block-------------------------------
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

                symtab_block[SYMTAB_SIZE]=temp;
                //cout<<temp<<","<<endl;
                if(check_break)
                {
                    break;
                }

//-----------------------symtab_address---------------------------------

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
                symtab_address[SYMTAB_SIZE]=temp;
                //cout<<temp<<endl;
                break;
            }
        }
    }

    //----------------------read BLOCKS ---------------------

    loc_count=0;

    if(!fblock)
    {
        cout<<"no file"<<endl;
    }
    else
    {
        reset_code();
        while(!fblock.eof())
        {
            string temp = "";
            getline(fblock,code[++loc_count]);
            for(int i=0;i<code[loc_count].size() && code[loc_count][i]!=' ';i++) {
                temp += code[loc_count][i];
            }
            block_name[BLOCK_SIZE] = temp;

            temp = "";
            for(int i=14;i<18;i++)
            {
                temp += code[loc_count][i];
            }
            block_address[BLOCK_SIZE] = temp;
            BLOCK_SIZE++;
        }
    }

    fi.close();
    fo.close();
    fsymtab.close();
    fblock.close();

};

void writeobj()
{
    for(int i=1;i<=counter;i++)
    {
        int check=0;
        bool checkPlus=false;
        int obj =0x00000000;
        int ni =3;
        flag_n[i] = "1";
        flag_i[i] = "1";

        if( opcode[i][0] == '=') {
            string temp = "";
            for(int j=3;j<opcode[i].size()-1;j++) {
                temp+=opcode[i][j];
            }
            switch(opcode[i][1]) {
                case 'X':
                    objcode[i] = temp;
                    OBJCODE_FINISH[i] = true;
                    break;
                case 'C':
                    string tempStr = "";
                    for(int tt=0; tt<temp.size();tt++) {
                        int temp_Ascii = temp[tt];
                        stringstream ss;
                        ss << hex << std::uppercase << temp_Ascii;
                        tempStr += ss.str();
                        ss.clear();
                    }
                    objcode[i] = tempStr;
                    OBJCODE_FINISH[i] = true;
                    break;
            }
            continue;
        }

        if(opcode[i][0]=='+')
        {
            checkPlus=true;
            checkplus[i] = "1";
            format[i] = "format4";

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
                OBJCODE_FINISH[i] = true;
                //cout<<temp<<endl;
            }
        }

        if(opcode[i]=="RSUB")
        {
                objcode[i]="4F0000";
                OBJCODE_FINISH[i] = true;
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
            objcode[i] = "";
           //cout<<"1"<<endl;
            continue;
        }
        if(check==1)
        {
            if(label[i][0]=='#')
            {
                ni=1;
                flag_n[i] = "0";
                flag_i[i] = "1";
            }
            else if(label[i][0]=='@')
            {
                ni=2;
                flag_n[i] = "1";
                flag_i[i] = "0";
                string im_temp="";
                for(int k=1;k<label[i].size();k++)
                {
                    im_temp+=label[i][k];
                }
                label[i]=im_temp;
            }
            obj=obj+ni;
        }
        stringstream ss;
        ss << hex << std::uppercase << obj;
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
        cal_OBJCODE_FINSIH();
        cal_xbpe();
        cal_address();

};

void cal_immediate(){
    for(int i=1;i<counter;i++) {
        int xbpe = 2;
        if( label[i][0] == '#') {
            if(label[i][1] >= '0' && label[i][1] <= '9'){
                string temp = "";
                for(int j=1;j<label[i].size();j++) {
                    temp+=label[i][j];
                }
                stringstream ss;
                ss << hex << std::uppercase << temp;
                ss >> temp;
                while(temp.size() < 4) {
                    temp = '0' + temp;
                }
                objcode[i] += temp;
                OBJCODE_FINISH[i] = true;
            }else{
                string temp = "";
                for(int j=1;j<label[i].size();j++)
                {
                    temp+=label[i][j];
                }
                bool check_base = false;
                //cout << temp <<endl;
                for(int j=1;j<counter;j++) {
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
                        while (temp.size() > i_value) {
                            string ttemp="";
                            for(int tt=temp.size()-3;tt<temp.size();tt++) {
                                ttemp += temp[tt];
                            }
                            temp = ttemp;
                        }
                        string tempStr = "";
                        ss << hex << xbpe;
                        ss >> tempStr;
                        temp = tempStr + temp;
                        if(checkplus[i] == "1")
                        {
                            objcode[i]+=temp;
                            OBJCODE_FINISH[i] = true;
                        }
                        else
                        {
                            string im_temp="";
                            for(int k=1;k<label[i].size();k++)
                            {
                                im_temp+=label[i][k];
                            }
                            label[i]=im_temp;
                        }


                        break;
                    }
                    /*
                    if(abs(line_i-line_j)>=0x1000) {
                        check_base = true;
                        for(int j=1;j<counter;j++) {
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
    for(int i=0;i<counter;i++) {
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
            format[i] = "format2";
            OBJCODE_FINISH[i] = true;
        }
    }
}

void cal_xbpe() {
    int x = 8, b = 4, p = 2, e = 1;
    for(int i=1;i<=counter;i++) {
        int xbpe = p;
        if(OBJCODE_FINISH[i])
            continue;
        for(int j=0;j<label[i].size();j++) {
            if(label[i][j] == ',' && label[i][j+1] == 'X') {
                xbpe += x;
                string temp="";
                for(int k=0;k<label[i].size()-2;k++)
                {
                    temp+=label[i][k];
                }
                label[i]=temp;
                break;
            }
        }
        string temp = "";
        stringstream ss;
        ss << hex << std::uppercase << xbpe;
        ss >> temp;
        objcode[i] += temp;
    }
}


void cal_address() {
    int address = 0x0000, which_block = 0;
    for(int i=1;i<=counter;i++) {
        address = 0x0000;
        if(OBJCODE_FINISH[i])
            continue;
        if(label[i] == "rloop") {
            string temp = "RLOOP";
            label[i] = temp;
        }
        if(label[i] == "EXIT") {
            string temp = "exit";
            label[i] = temp;
        }
        if(label[i] == "WLOOP+21"){
            label[i] = "";
            string temp = "WLOOP";
            address += 21;
            label[i] = temp;
        }
            if( label[i][0]=='=' || label[i][0]=='@'|| label[i][label[i].size()-1]=='X') {
        }else {
            checkWrong = true;
            for(int j=0;j<SYMTAB_SIZE;j++) {
                //cout << label[i] << "," <<endl;
                //cout << symtab_name[j] << "," <<endl;
                if(label[i] == symtab_name[j]) {
                    checkWrong = false;
                    break;
                }
            }
            if(checkWrong) {
                cout << "can not find Label:" << label[i] << endl;
                Stop = true;
            }
        }
        for(int j=0;j<SYMTAB_SIZE;j++) {
            if(label[i] == symtab_name[j]) {
                int temp_i = 0x0000;
                stringstream ss;
                ss << hex << std::uppercase << symtab_address[j];
                ss >> temp_i;
                ss.clear();
                int temp_j;
                ss << symtab_block[j];
                ss >> temp_j;
                ss.clear();
                int temp_k;
                ss << hex << std::uppercase << block_address[temp_j];
                ss >> temp_k;
                temp_i += temp_k;
                //cout << temp_i << endl;
                address += temp_i;
                break;
            }
        }
        int line_i;
        stringstream ss;
        ss << hex << std::uppercase << line[i];
        ss >> line_i;
        ss.clear();
        line_i += 3;
        address -= line_i;
        int line_j;
        ss << block[i];
        ss >> line_j;
        ss.clear();
        ss << block_address[line_j];
        ss >> line_i;
        ss.clear();
        address += line_i;
        //cout << line_i << endl;
        string temp = "";
        ss << hex << std::uppercase <<address;
        ss >> temp;
        while(temp.size()<3) {
            temp = '0' + temp;
        }
        if(temp.size()>3) {
            string ttemp = "";
            for(int tt=temp.size()-3;tt<temp.size();tt++) {
                ttemp += temp[tt];
            }
            temp = ttemp;
        }
        objcode[i] += temp;
        //cout<<objcode[i]<<endl;
        OBJCODE_FINISH[i] = true;
    }
}

void cal_OBJCODE_FINSIH() {
    for(int i=1;i<=counter;i++)
        if(objcode[i] == "")
            OBJCODE_FINISH[i] = true;
}

void reset_code() {
    string temp = "";
    for(int i=0;i<1000;i++)
        code[i] = temp;
}

void showobjcode()
{
    fstream fout;
    fout.open("OBJECT_CODE.txt",ios::out);
    for(int i=1;i<=counter;i++)
    {
        //cout << symtable[i] << " " << opcode[i] << " " << label[i] << endl;
        //cout << line[i] << " " << block[i] << endl;
        //cout << OBJCODE_FINISH[i] << " ";
        if( line[i] == "Comment") {
            cout << line[i] << endl;
            fout << line[i] << endl;
            continue;
        }
        if( opcode[i] == "END"){
            cout<< opcode[i] << endl;
            fout<< opcode[i] << endl;
            continue;
        }
            if(objcode[i] != "") {
                string temp = "";
                switch (objcode[i][2]) {
                    case '0':
                        temp = "0000";
                        break;
                    case '1':
                        temp = "0001";
                        break;
                    case '2':
                        temp = "0010";
                        break;
                    case '8':
                        temp = "1000";
                        break;
                    case 'a':
                        temp = "1010";
                        break;
                }
                if(symtable[i] == "*") {
                    cout << "LT" << "  ";
                    fout << "LT" << "  ";
                }else if(opcode[i] == "BYTE") {
                    cout << opcode[i] << "  ";
                    fout << opcode[i] << "  ";
                }else if(format[i] == "format4"){
                    cout << format[i] << " ";
                    cout << "flags:" <<  flag_n[i] <<  flag_i[i] << temp << "  ";
                    fout << format[i] << " ";
                    fout << "flags:" <<  flag_n[i] <<  flag_i[i] << temp << "  ";
                }else if(format[i] == "format2") {
                    cout << format[i] << " ";
                    fout << format[i] << " ";
                }else {
                    cout << "flags:" <<  flag_n[i] <<  flag_i[i] << temp << "  ";
                    fout << "flags:" <<  flag_n[i] <<  flag_i[i] << temp << "  ";
                }

            }else{
                cout << "XX" << " ";
                fout << "XX" << " ";
            }
        cout<<objcode[i]<<endl;
        fout<<objcode[i]<<endl;
    }
    cout << endl << endl << "Successfully create OBJECT_CODE.txt !" << endl;
    fout.close();
}
