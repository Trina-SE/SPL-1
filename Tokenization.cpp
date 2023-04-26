#include <bits/stdc++.h>
using namespace std;

struct token{

    string name;
    string type;
    int id;
};

token tok[1000];

void removeAllComments(FILE *input_file, FILE *output_file) {

    char c, next_c;

    while ((c = fgetc(input_file)) != EOF) {
        if (c == '/') {
            next_c = fgetc(input_file);
            if (next_c == '/') {
                while ((c = fgetc(input_file)) != EOF && c != '\n') {}
                if (c == '\n') {
                    fputc(c, output_file);
                }
            } else if (next_c == '*') {
                while ((c = fgetc(input_file)) != EOF) {
                    if (c == '*') {
                        next_c = fgetc(input_file);
                        if (next_c == '/') {
                            break;
                        } else {
                            ungetc(next_c, input_file);
                        }
                    }
                }
            } else {
                fputc(c, output_file);
                fputc(next_c, output_file);
            }
        } else {
            fputc(c, output_file);
        }
    }
}

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


int main() {

    FILE *input_file, *output_file;
    char input_filename[10000], output_filename[10000];

    input_file = fopen("input.txt", "r");

    if (input_file == NULL) {
        printf(" Error: Could not open input file.\n");
        return 1;
    }

    output_file = fopen("sourceCode.txt", "w");

    if (output_file == NULL) {
        printf("Error: Could not open output file.\n");
        return 1;
    }

    removeAllComments(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    printf("Comment removal complete.\n");

    string str="";
    ifstream input;
    ofstream output;

    char ch;
    int token=0;

    input.open("sourceCode.txt");
    output.open("Token.txt");

    if(input.is_open()){

        cout<<"File is Opened which contains C source code\n";

        char prev_char='@';
        input.get(ch);

        while(true){
            if(ch=='\n' || ch==' ' || ch=='\t'){

                if(type_spec(str)==true){

                    tok[token].name=str;
                    tok[token].type="type_spec";
                    tok[token].id=5;
                    str="";
                    token++;
                    input.get(ch);
                    break;
                }

                if(str[0]=='#' && str[str.size()-1]=='>'){

                    tok[token].name=str;
                    tok[token].type="Header";
                    tok[token].id=1;
                    token++;
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

                    tok[token].name=str;
                    tok[token].type="type_spec";
                    tok[token].id=5;

                str="";
                token++;
            }

            else if(str=="while"){

                tok[token].name=str;
                tok[token].type="while_stmt";
                tok[token].id=10;
                str="";
                token++;
            }
            else if(str=="for"){

                    tok[token].name=str;
                    tok[token].type="for_stmt";
                    tok[token].id=15;
                str="";
                token++;
            }
            else if(str=="void"){

                    tok[token].name=str;
                    tok[token].type="type_spec";
                    tok[token].id=4;
                str="";
                token++;
            }
            else if(break_stmt(str)==true){

                    tok[token].name=str;
                    tok[token].type="break_stmt";
                    tok[token].id=20;

                str="";
                token++;
               }
            else if(ifElse_stmt(str)==13){

                    tok[token].name=str;
                    tok[token].type="if_stmt";
                    tok[token].id=22;

                str="";
                token++;
            }
            else if(ifElse_stmt(str)==26){

                    tok[token].name=str;
                    tok[token].type="if_stmt";
                    tok[token].id=23;

                str="";
                token++;
            }
            else if(literal_int(str)==true){

                    tok[token].name=str;
                    tok[token].type="INT_LIT";
                    tok[token].id=3;
                str="";
                token++;
               }
            else if(literal_bool(str)==true){

                    tok[token].name=str;
                    tok[token].type="BOOL_LIT";
                    tok[token].id=6;
                str="";
                token++;
               }
            else if(literal_float(str)==true){

                    tok[token].name=str;
                    tok[token].type="FLOAT_LIT";
                    tok[token].id=2;
                str="";
                token++;
               }
            else if(return_stmt(str)==true){

                    tok[token].name=str;
                    tok[token].type="RETURN";
                    tok[token].id=30;

                str="";
                token++;
               }
            else if(ident(str)==true){

                    tok[token].name=str;
                    tok[token].type="IDENT";
                    tok[token].id=28;
                str="";
                token++;
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

                    tok[token].name=str;
                    tok[token].type="STRING_LIT";
                    tok[token].id=7;
            }
            if(ch==';'){

                    tok[token].name=";";
                    tok[token].type="SEMICOLON";
                    tok[token].id=36;
                str="";
                token++;

            }
            if(ch==','){

                    tok[token].name=",";
                    tok[token].type="COMA";
                    tok[token].id=35;
                str="";
                token++;
            }
            if(ch=='('){

                    tok[token].name="(";
                    tok[token].type="F_BRAC_O";
                    tok[token].id=37;
                str="";
                token++;
            }
            if(ch==')'){

                    tok[token].name=")";
                    tok[token].type="F_BRAC_C";
                    tok[token].id=38;
                str="";
                token++;
            }
            if(ch=='{'){
                    tok[token].name="{";
                    tok[token].type="S_BRAC_O";
                    tok[token].id=39;
                str="";
                token++;
            }
            if(ch=='}'){
                    tok[token].name="}";
                    tok[token].type="S_BRAC_C";
                    tok[token].id=40;
                str="";
                token++;
            }
            if(ch=='['){
                    tok[token].name="[";
                    tok[token].type="T_BRAC_O";
                    tok[token].id=41;
                str="";
                token++;
            }
            if(ch==']'){
                    tok[token].name="]";
                    tok[token].type="T_BRAC_C";
                    tok[token].id=42;
                str="";
                token++;
            }

            if(ch=='+'){
                    tok[token].name="+";
                    tok[token].type="ADDITION";
                    tok[token].id=46;
                str="";
                token++;
            }
            if(ch=='-'){
                    tok[token].name="-";
                    tok[token].type="SUBTRACTION";
                    tok[token].id=47;
                str="";
                token++;
            }

            if(ch=='<'){
                    tok[token].name="<";
                    tok[token].type="LESSER";
                    tok[token].id=49;
                str="";
                token++;
            }
            if(ch=='>'){
                    tok[token].name=">";
                    tok[token].type="GREATER";
                    tok[token].id=48;
                str="";
                token++;
            }
            if(ch=='!'){
                    tok[token].name="!";
                    tok[token].type="NOT";
                    tok[token].id=53;
                str="";
                token++;
            }
        }
             else str=str+ch;

        prev_char=ch;
        input.get(ch);

        if(isNot_key(str)==true && ch=='('){
                    tok[token].name=str;
                    tok[token].type="func";
                    tok[token].id=61;
                str="";
                token++;
           }

        else if(prev_char=='=' && ch=='='){
                    tok[token].name="==";
                    tok[token].type="EQUAL";
                    tok[token].id=51;
                str="";
                token++;
           }
        else if(prev_char=='!' && ch=='='){
                    tok[token].name="!=";
                    tok[token].type="NOT_EQUAL";
                    tok[token].id=52;
                str="";
                token++;
           }
        else if(prev_char=='>' && ch=='='){
                    tok[token].name=">=";
                    tok[token].type="GREATER_EQUAL";
                    tok[token].id=45;
                str="";
                token++;
           }
        else if(prev_char=='<' && ch=='='){
                    tok[token].name="<=";
                    tok[token].type="LESS_EQUAL";
                    tok[token].id=44;
                str="";
                token++;
           }
        else if(prev_char=='=' && ch!='=' && tok[token-1].name!="==" && tok[token-1].type!="ASSIGNMENT"){
                    tok[token].name="=";
                    tok[token].type="ASSIGNMENT";
                    tok[token].id=70;
                str="";
                token++;
           }
        }
   }
    else{
    cout<<"Input File is not opened\n";
   }

   cout<<"Number of Tokens: "<<token-1<<"\n";
   cout<<"Tokenization is done successfully\n";

   input.close();

   output<<"NO: "<<"  Token"<<"\t\t\t\t"<<"Token_Type"<<"\t\t\t"<<"Token_ID"<<"\n";
   output<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   output<<1<<". "<<tok[0].name<<"\t\t\t"<<tok[0].type<<"\t\t\t\t"<<tok[0].id<<"\n";

   for(int i=1;i<token;i++){

        if(tok[i].name=="int" && tok[i+1].name=="main"){
            output<<i+1<<". "<<"int main"<<"\t\t\t\t\t"<<"main_func"<<"\t\t\t\t"<<"9"<<"\n";
            i++;
            continue;
        }

        output<<i<<". "<<tok[i].name<<"\t\t\t\t\t"<<tok[i].type<<"\t\t\t\t"<<tok[i].id<<"\n";

   }

   return 0;


}
