#include<bits/stdc++.h>
using namespace std;

struct node
{
    string label;
    vector<node> children;
};

struct Tree{

   string parent;
   vector<string>child;
   int lev;

};

Tree tree [10000];

void parsing ();
void printParseTree(node newnode, int depth);
node parse (string str);
node program (string str);
node decl_list(string str);
node decl (string str);
node var_decl(string str);
node type_spec(string str);
node main_func(string str);
node stmt_list(string str);
node stmt (string str);
node st_list (string str);
node st (string str);
node compound_stmt(string str);
node local_decls(string str);
node local_decl(string str);
node if_stmt (string str);
node for_stmt (string str);
node for_expr(string str);
node while_stmt (string str);
node print (string str);
node expr_stmt(string str);
node expr (string str);
node break_stmt (string str);
node return_stmt (string str);
