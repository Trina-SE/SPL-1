#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string keyword[6]={"for","while","if","else","switch","do"};

bool isNot_key(string str){

    int track=0;

   for(int i=0;i<6;i++){
        if(str==keyword[i]){
            track=1;
            break;
        }
    }

    if(track==0) return true;
    else return false;


}

bool literal_int(string str){

    bool track=false;

    for(int i=0; i<str.size(); i++)
    {
        if(str[i]>='0' && str[i]<='9') track=true;
        else
        {
            track=false;
            break;
        }
    }

    if(track==true) return true;
    else return false;

}

bool literal_float(string str){

    int is_float1=0, is_float2=0;

    for(int i=0; i<str.size(); i++)
    {
        if(str[i]>='0' && str[i]<='9')is_float1=1;
        else if(str[i]=='.') is_float1=1;
        else
        {
            is_float1=0;
            break;
        }
        if(str[i]=='.') is_float2++;
    }

    if(is_float1==1 && is_float2==1) return true;
}

bool literal_bool(string str){

   string boolean[3]={"true","false"};

   for(int i=0;i<2;i++){
    if(str==boolean[i]) return true;
    else return false;
   }
}

bool type_spec(string str){

    if(str=="void" || str=="int" || str=="float" || str=="bool"){
        return true;
    }
}

bool ident(string str){

    bool track=false;

    if(str[0]>='0' && str[0]<='9') return false;

    for(int i=0;i<str.size();i++){

        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z'))
            track=true;
        else if(str[i]>='0' && str[i]<='9')
            track=true;
        else if(str[i]=='_')
            track=true;
        else{
            track=false;
            break;
        }

    if(track==true) return true;
    else return false;

    }

}

int ifElse_stmt(string str){

    if(str=="if") return 13;
    else if(str=="else") return 26;
}

bool return_stmt(string str){

    if(str=="return") return true;
}

bool break_stmt(string str){

    if(str=="break") return true;
}


vector <string> tokens;

int main(){

    string str="";
    ifstream input;
    ofstream output;

    char ch;
    int token=0;

    input.open("C_sourceCode.txt");
    output.open("Token.txt");

    if(input.is_open()){

        cout<<"Input file is Opened\n";
        char prev_char='@';
        input.get(ch);

        while(true){
            if(ch=='\n' || ch==' ' || ch=='\t'){

                if(type_spec(str)==true){

                    output<<str<<" -->type_spec\n";
                    str="";
                    token++;
                    tokens.push_back("type_spec");
                    input.get(ch);
                    break;
                }

                if(str[0]=='#' && str[str.size()-1]=='>'){
                    output<<str<<" -->Header_file\n";
                    token++;
                    tokens.push_back("Header_file");
                }
                str="";
            }

            else{

                if(ch=='#'){
                    str+=(char)35;
                }
                else{
                    str+=ch;
                }
            }
            input.get(ch);
          }

        while(!input.eof()){

        if(ch==',' || ch==';' || ch==' ' || ch=='=' || ch=='\n' || ch=='\t' || ch=='('|| ch==')' || ch=='{'|| ch=='}'|| ch=='"'|| ch==']'|| ch=='['|| ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| ch=='%'|| ch=='!'|| ch=='<'|| ch=='>'){

            if(type_spec(str)==true){
                output<<str<<" -->type_spec\n";
                str="";
                token++;
                tokens.push_back("type_spec");
            }
            else if(str=="while"){
                output<<str<<"-->WHILE_LOOP\n";
                str="";
                token++;
                tokens.push_back("while_stmt");
            }
            else if(str=="for"){
                output<<str<<"-->FOR_LOOP\n";
                str="";
                token++;
                tokens.push_back("for_loop");
            }
            else if(str=="void"){
                output<<str<<" -->VOID\n";
                str="";
                token++;
                tokens.push_back("VOID");
            }
            else if(break_stmt(str)==true){
                output<<str<<"-->BREAK\n";
                str="";
                token++;
                tokens.push_back("break_stmt");
               }
            else if(ifElse_stmt(str)==13){
                output<<str<<"-->IF\n";
                str="";
                token++;
                tokens.push_back("if_stmt");
            }
            else if(ifElse_stmt(str)==26){
                output<<str<<"-->ELSE\n";
                str="";
                token++;
                tokens.push_back("else_stmt");
            }
            else if(literal_int(str)==true){
                output<<str<<"-->INT_LIT\n";
                str="";
                token++;
                tokens.push_back("INT_LIT");
               }
            else if(literal_bool(str)==true){
                output<<str<<"-->BOOL_LIT\n";
                str="";
                token++;
                tokens.push_back("BOOL_LIT");
               }
            else if(literal_float(str)==true){
                output<<str<<"-->FLOAT_LIT\n";
                str="";
                token++;
                tokens.push_back("FLOAT_LIT");
               }
            else if(return_stmt(str)==true){
                output<<str<<"-->RETURN\n";
                str="";
                token++;
                tokens.push_back("return_stmt");
               }
            else if(ident(str)==true){
                output<<str<<"-->IDENT\n";
                str="";
                token++;
                tokens.push_back("IDENT");
               }
            if(ch=='"'){

                str+='"';
                prev_char=ch;
                input.get(ch);
                  while(ch!='"'){
                    str=str+ch;
                    prev_char=ch;
                    input.get(ch);
                  }
                output<<str<<ch<<"-->STRING_LIT\n";
            }
            if(ch==';'){
                output<<ch<<"-->SEMICOLON\n";
                str="";
                token++;
                tokens.push_back(";");

            }
            if(ch==','){
                output<<ch<<"-->COMA\n";
                str="";
                token++;
                tokens.push_back(",");
              //  prev_char=str.size()-1;
            }
            if(ch=='('){
                output<<ch<<"-->FIRST_BRACKET_OPEN\n";
                str="";
                token++;
                tokens.push_back("(");
              //  prev_char=str.size()-1;
            }
            if(ch==')'){
                output<<ch<<"-->FIRST_BRACKET_CLOSE\n";
                str="";
                token++;
                tokens.push_back(")");
              //  prev_char=str.size()-1;
            }
            if(ch=='{'){
                output<<ch<<"-->SECOND_BRACKET_OPEN\n";
                str="";
                token++;
                tokens.push_back("{");
               // prev_char=str.size()-1;
            }
            if(ch=='}'){
                output<<ch<<"-->SECOND_BRACKET_CLOSE\n";
                str="";
                token++;
                tokens.push_back("}");
               // prev_char=str.size()-1;
            }
            if(ch=='['){
                output<<ch<<"-->THIRD_BRACKET_OPEN\n";
                str="";
                token++;
                tokens.push_back("[");
               // prev_char=str.size()-1;
            }
            if(ch==']'){
                output<<ch<<"-->THIRD_BRACKET_CLOSE\n";
                str="";
                token++;
                tokens.push_back("]");
               // prev_char=str.size()-1;
            }
            if(ch=='*'){
                output<<ch<<"-->MULTIPLICATION\n";
                str="";
                token++;
                tokens.push_back("*");
              //  prev_char=str.size()-1;
            }
            if(ch=='+'){
                output<<"("<<ch<<")"<<"-->ADDITION\n";
                str="";
                token++;
                tokens.push_back("+");
               // prev_char=str.size()-1;
            }
            if(ch=='-'){
                output<<"("<<ch<<")"<<"-->SUBTRACTION\n";
                str="";
                token++;
                tokens.push_back("-");
               // prev_char=str.size()-1;
            }
            if(ch=='/'){
                output<<ch<<"-->DIVISION\n";
                str="";
                token++;
                tokens.push_back("/");
              //  prev_char=str.size()-1;
            }
            if(ch=='%'){
                output<<ch<<"-->MODULUS\n";
                str="";
                token++;
                tokens.push_back("%");
               // prev_char=str.size()-1;
            }
            if(ch=='<'){
                output<<"("<<ch<<")"<<"-->LESSER\n";
                str="";
                token++;
                tokens.push_back("<");
               // prev_char=str.size()-1;
            }
            if(ch=='>'){
                output<<"("<<ch<<")"<<"-->GREATER\n";
                str="";
                token++;
                tokens.push_back(">");
              //  prev_char=str.size()-1;
            }
            if(ch=='!'){
                output<<ch<<"-->NOT\n";
                str="";
                token++;
                tokens.push_back("!");
              //  prev_char=str.size()-1;
            }
        }
             else str=str+ch;

        prev_char=ch;
        input.get(ch);

        if(isNot_key(str)==true && ch=='('){
            output<<str<<"-->FUNCTION\n";
            str="";
            token++;
            tokens.push_back("func");
           }

        else if(prev_char=='/' && ch=='/'){
                str+="/";
                prev_char=ch;
                input.get(ch);
                 while(ch!='\n'){
                    str+=ch;
                    prev_char=ch;
                    input.get(ch);
                }
               str="";
            }

        else if(prev_char=='=' && ch=='='){
            output<<prev_char<<ch<<"-->EQUAL\n";
            str="";
            token++;
            tokens.push_back("==");
           }
        else if(prev_char=='!' && ch=='='){
            output<<prev_char<<ch<<"-->NOT_EQUAL\n";
            str="";
            token++;
            tokens.push_back("!=");
           }
        else if(prev_char=='>' && ch=='='){
            output<<prev_char<<ch<<"-->GREATER_EQUAL\n";
            str="";
            token++;
            tokens.push_back(">=");
           }
        else if(prev_char=='<' && ch=='='){
            output<<prev_char<<ch<<"-->LESS_EQUAL\n";
            str="";
            token++;
            tokens.push_back("<=");
           }
        else if(prev_char=='=' && ch!='=' && tokens[token-1]!="==" && tokens[token-1]!="ASSIGN"){
            output<<"="<<"-->ASSIGNMENT\n";
            str="";
            token++;
            tokens.push_back("ASSIGN");
           }
        }
   }
    else{
    cout<<"Input File is not opened\n";
   }

   cout<<"Number of Tokens: "<<token<<"\n";
   cout<<"Tokenization is done successfully\n";

   input.close();
   output.close();

   return 0;

}
