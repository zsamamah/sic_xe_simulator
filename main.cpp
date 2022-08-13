#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

//global variables
int counter=0,instructions=0;
string start,last;
int A,X,L,PC,SW,B,S,T,F;
char C;
int mc=0;
int mem[30];
int add[30];


/*this func take string represents hexa then convert it to binary*/
string hex_to_binary(string hexa)
{
    string bin;
    for(int i=0; i<hexa.length(); i++)
    {
        switch(hexa[i])
        {
        case '0':
            bin+="0000";
            break;
        case '1':
            bin+="0001";
            break;
        case '2':
            bin+="0010";
            break;
        case '3':
            bin+="0011";
            break;
        case '4':
            bin+="0100";
            break;
        case '5':
            bin+="0011";
            break;
        case '6':
            bin+="0110";
            break;
        case '7':
            bin+="0111";
            break;
        case '8':
            bin+="1000";
            break;
        case '9':
            bin+="1001";
            break;
        case 'A':
        case 'a':
            bin+="1010";
            break;
        case 'B':
        case 'b':
            bin+="1011";
            break;
        case 'C':
        case 'c':
            bin+="1100";
            break;
        case 'D':
        case 'd':
            bin+="1101";
            break;
        case 'E':
        case 'e':
            bin+="1110";
            break;
        case 'F':
        case 'f':
            bin+="1111";
            break;
        default:
            bin+="XXXX";
        }
    }
    return bin;
}


/*this func load start , last and commands */
void loadInput()
{
    ifstream file;
    ofstream output;
    string text;
    int temp;
    file.open("Input.txt");
    output.open("Output.txt");
    //fetch start address
    getline(file,text);
    start = text.substr(6);
    //fetch last address
    getline(file,text);
    last = text.substr(5);

    //fetch instructions
    while(!file.eof())
    {
        file>>text;
        text=hex_to_binary(text);
        output<<text<<endl;
        instructions++;
    }

    file.close();
    output.close();
}

/* this function convert binary to deimal */
int convert(string x) {
  int dec = 0, i = 0, rem;
  int n=stoi(x);
  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}

/* this func convert decimal to hexa */
string decToHexa(int n)
{
    char hexaDeciNum[100];
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
        n = n/16;
    }
    string str;
    for (int j = i - 1; j >= 0; j--)
        str+=hexaDeciNum[j];
    return str;
}

/*this func add to hexa and convert to decimal*/
int add_hex(string x,string y)
{
    string ix,iy;
    int xi=0,yi=0;
    string temp = hex_to_binary(x);
    int c = convert(temp);
    string temp2 = hex_to_binary(y);
    int cx = convert(temp2);
    return c+cx;
}

/* Command Class */
class Command
{
private:
    int size;
    int format;
    string hexCode;
    string opcode;
    string r1;
    string r2;
    string n;
    string i;
    string x;
    string b;
    string p;
    string e;
    string address;
    int t_add;
public:
    //setters
    void setSize(int val)
    {
        size=val;
    }
    void setFormat(int val)
    {
        if(val==8)
            format=1;
        else if(val==16)
            format=2;
        else if(val==24)
            format=3;
        else if(val==32)
            format=4;
        else
            cout<<"\n Error Format !! \n";
    }
    void setHexCode(string val)
    {
        hexCode=val;
    }
    void setOp(string val)
    {
        if(format==1 || format==2)
            opcode=val.substr(0,8);
        else if(format==3 || format==4)
            opcode=val.substr(0,6);
        else
            cout<<"\n Error Opcode !! \n";
    }
    void setR1(string val)
    {
        if(format==2)
            r1=val.substr(7,4);
    }
    void setR2(string val)
    {
        if(format==2)
            r2=val.substr(11,4);
    }
    void setN(string val)
    {
        if(format==3 || format==4)
            n=val[6];
    }
    void setI(string val)
    {
        if(format==3 || format==4)
            i=val[7];
    }
    void setX(string val)
    {
        if(format==3 || format==4)
            x=val[8];
    }
    void setB(string val)
    {
        if(format==3 || format==4)
            b=val[9];
    }
    void setP(string val)
    {
        if(format==3 || format==4)
            p=val[10];
    }
    void setE(string val)
    {
        if(format==3 || format==4)
            e=val[11];
    }
    void setAddress(string val)
    {
        if(format==3)
            address=val.substr(12,12);
        else if(format==4)
            address=val.substr(12,20);
    }
    //set target address
    void setTAdd()
    {
        string st1,st2,st3;
        int t1,t2,t3;
        if(format==3 || format==4)
        {

            if(getN()=="1" && getI()=="1")
            {
                if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="0")
                {
                    st1=hex_to_binary(getAddress());
                    t1 = convert(x);
                    t_add=t1;
                }
                else if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="1"){
                    st1=hex_to_binary(getAddress());
                    t1 = convert(x);
                    t_add=t1;
                }
                else if(getX()=="0" && getB()=="0" && getP()=="1" && getE()=="0"){
                    t1 = convert(address);
                    st1 = hex_to_binary(start);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }
                else if(getX()=="0" && getB()=="1" && getP()=="0" && getE()=="0"){
                        t1 = convert(address);
                    st1 = hex_to_binary(last);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }
            }
            else if(getN()=="0" && getI()=="0"){
                t1=add_hex(start,last);
                t2=convert(address);
                t_add=t1+t2+stoi(getE());
            }
            else if(getN()=="1" && getI()=="0")
            {
                if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="0")
                    t_add = convert(address);
                else if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="1")
                    t_add = convert(address);

                else if(getX()=="0" && getB()=="0" && getP()=="1" && getE()=="0"){
                        t1 = convert(address);
                    st1 = hex_to_binary(start);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }
                else if(getX()=="0" && getB()=="1" && getP()=="0" && getE()=="0"){
                    t1 = convert(address);
                    st1 = hex_to_binary(last);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }
            }
            else if(getN()=="0" && getI()=="1")
            {
                if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="0")
                    t_add = convert(address);
                else if(getX()=="0" && getB()=="0" && getP()=="0" && getE()=="1")
                    t_add = convert(address);

                else if(getX()=="0" && getB()=="0" && getP()=="1" && getE()=="0"){
                    t1 = convert(address);
                    st1 = hex_to_binary(start);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }

                else if(getX()=="0" && getB()=="1" && getP()=="0" && getE()=="0"){
                    t1 = convert(address);
                    st1 = hex_to_binary(last);
                    t2 = convert(st1);
                    t_add=t1+t2;
                }
            }
        }
    }

    //getters
    int getSize()
    {
        return size;
    }
    int getFormat()
    {
        return format;
    }
    string getHexCode()
    {
        return hexCode;
    }
    string getOp()
    {
        return opcode;
    }
    string getR1()
    {
        return r1;
    }
    string getR2()
    {
        return r2;
    }
    string getN()
    {
        return n;
    }
    string getI()
    {
        return i;
    }
    string getX()
    {
        return x;
    }
    string getB()
    {
        return b;
    }
    string getP()
    {
        return p;
    }
    string getE()
    {
        return e;
    }
    string getAddress()
    {
        return address;
    }
    int getTAdd()
    {
        return t_add;
    }

    /*execute command and update registers*/
    void execute()
    {
        if(format==3 || format==4)
        {
            if(opcode=="000000")//LDA
                A=getTAdd();
            else if (opcode=="011010")//LDB
                B=getTAdd();
            else if (opcode=="000010")//LDL
                L=getTAdd();
            else if (opcode=="011011")//LDS
                S=getTAdd();
            else if (opcode=="011101")//LDT
                T=getTAdd();
            else if (opcode=="000001")//LDX
                X=getTAdd();
            else if (opcode=="000110")//ADD
                A+=getTAdd();
            else if (opcode=="001010")//COMP
            {
                if(A==getTAdd())
                    C='=';
                else if(A>getTAdd())
                    C='>';
                else if (A<getTAdd())
                    C='<';
            }
            else if (opcode=="000011")//STA
            {
                mem[mc]=A;
                add[mc]=getTAdd();
            }
}}
};


/* this function decode commands */
void decode(Command arr[])
{
    ifstream output;
    output.open("Output.txt");
    string command;
    for(int i=0; i<instructions; i++)
    {
        output>>command;
        arr[counter].setSize(command.length());
        arr[counter].setFormat(command.length());
        arr[counter].setHexCode(command);
        arr[counter].setOp(command);
        arr[counter].setR1(command);
        arr[counter].setR2(command);
        arr[counter].setN(command);
        arr[counter].setI(command);
        arr[counter].setX(command);
        arr[counter].setB(command);
        arr[counter].setP(command);
        arr[counter].setE(command);
        arr[counter].setAddress(command);
        arr[counter].setTAdd();
        arr[counter++].execute();
//        cout<<command<<" "<<counter<<endl;
    }
    output.close();
}

/* this function create output file (Output.txt) */
void upload()
{
    ofstream opt;
    opt.open("Output.txt");
    opt<<"A= "<<A
        <<"\nX= "<<X
        <<"\nL= "<<L
        <<"\nPC= "<<PC
        <<"\nSW= "<<SW
        <<"\nB= "<<B
        <<"\nS= "<<S
        <<"\nT= "<<T
        <<"\nF= "<<F
        <<"\nC="<<C<<endl;
    opt<<"** NOTE ** ALL VALUES IN DECIMAL \n";
    opt.close();

}

int main()
{
    //fetch input file
    loadInput();

    //define commands
    Command commands[instructions];

    //decode each instruction to object
    decode(commands);

    //create output file
    upload();

    cout<<"Go To Output.txt :)"<<endl;

    return 0;
}
