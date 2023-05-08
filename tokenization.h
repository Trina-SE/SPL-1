#ifndef TOKENIZATION_H_INCLUDED
#define TOKENIZATION_H_INCLUDED

#include <bits/stdc++.h>
using namespace std;

struct Token{

   string name;
   string type;
   int id;

};

Token code_token [10000];

void token_main();
void removeAllComments(FILE *input_file, FILE *output_file);
bool isNot_key(string str);
bool literal_int(string str);
bool literal_float(string str);
bool literal_bool(string str);
bool type_specifier(string str);
bool ident(string str);
int ifElse_stmt(string str);
bool return_statement(string str);
bool break_statement(string str);


#endif // TOKENIZATION_H_INCLUDED
