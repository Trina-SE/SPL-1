#include<bits/stdc++.h>
using namespace std;

ifstream input;
ofstream output;
string str1="";

struct node
{
    string label;
    vector<node> children;
};

struct Tree{

   string parent;
   vector<string>child;
   int lev;
   //int code;

};

Tree tree [10000];

int indx=0;
int level=0;
int open=0;

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

node parse (string str){

    //cout<<"parse   ";
    tree[indx].lev=level;
    tree[indx].parent="NULL";
    tree[indx].child.push_back("program");

    indx++;
    level++;

  return program(str);

}

node program (string str){

    node newnode = {"program",{}};
    //cout<<"parse-program   ";
    tree[indx].lev=level;
    tree[indx].parent="program";
    tree[indx].child.push_back("decl_list");
    tree[indx].child.push_back("main_func");
    indx++;

    input>>str;
   // cout<<str<<" ";
   str1=str;
        newnode.children.push_back({"decl_list", {}});
        newnode.children.push_back({"main_func", {}});
        int l=level;
        level++;
        newnode.children.push_back(decl_list(str1));
        level=l;

       // level--;
       // level++;

        newnode.children.push_back(main_func(str1));
        level--;

     return newnode;

}

node decl_list(string str){

 // cout<<"parse-decl_list   ";

  node newnode;

  if(str=="4" || str=="81" || str=="82" || str=="83"){

     tree[indx].lev=level;
     tree[indx].parent="decl_list";
     tree[indx].child.push_back("decl_list");
     tree[indx].child.push_back("decl");

      indx++;

      newnode.children.push_back({"decl_list", {}});
      newnode.children.push_back({"decl", {}});
      level++;
      int l=level;
      newnode.children.push_back(decl(str));

       level=l;
       int k = level;

        level++;

      newnode.children.push_back(decl_list(str1));

      level=k;

    }

    else{

     tree[indx].lev=level;
     tree[indx].parent="decl_list";
     tree[indx].child.push_back("E");

     indx++;

     tree[indx].lev=level+1;
     tree[indx].parent="E";
     tree[indx].child.push_back(".........");

     indx++;

     newnode.children.push_back({"E", {}});

     //return newnode;

    }

     return newnode;

}

node decl (string str){

  // cout<<"parse-decl   ";
    node newnode;

    if (str=="4" || str=="81" || str=="82" || str=="83"){

       newnode.children.push_back({"var_decl", {}});

       tree[indx].lev=level;
       tree[indx].parent="decl";
       tree[indx].child.push_back("var_decl");
       indx++;
       int l=level;
       level++;
       newnode.children.push_back(var_decl(str));
       level=l;
    }


    return newnode;

}

node var_decl (string str){

    node newnode;
   // cout<<"parse-var_decl   ";
    string strP=str;
    input>>str;

    if(strP=="81" || strP=="82" || strP=="83"){
            input>>str;
        if(str=="36"){
            tree[indx].lev=level;
            tree[indx].parent="var_decl";
            tree[indx].child.push_back("type_spec IDENT");
            tree[indx].child.push_back(";");
            indx++;
            newnode.children.push_back({"type_spec IDENT", {}});
             newnode.children.push_back({";", {}});
            input>>str;
            str1=str;
            int l=level;
            level++;
            newnode.children.push_back(type_spec(strP));
            level=l;
        }
        else if(str=="41"){
            input>>str;
            input>>str;
            input>>str;
            input>>str;
            tree[indx].lev=level;
            tree[indx].parent="var_decl";
            tree[indx].child.push_back("type_spec IDENT[]");
            tree[indx].child.push_back(";");
            indx++;
            str1=str;
            newnode.children.push_back({"type_spec IDENT[]", {}});
            newnode.children.push_back({";", {}});
            int l=level;
            level++;
            newnode.children.push_back(type_spec(strP));
            level=l;
        }
        else{
            cout<<"SEMICOLON MISSING\n";
        }

    }

    return newnode;

}

node type_spec(string str){

     node newnode;
    // cout<<"parse-type_spec   ";
     if(str=="81"){
            tree[indx].lev=level;
            tree[indx].parent="type_spec";
            tree[indx].child.push_back("INT");
            indx++;

            tree[indx].lev=level+1;
            tree[indx].parent="INT";
            tree[indx].child.push_back(".........");
             indx++;

             tree[indx].lev=level+1;
            tree[indx].parent="IDENT";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent=";";
            tree[indx].child.push_back(".........");
             indx++;
            newnode.children.push_back({"INT", {}});
     }
     else if(str=="82"){
            tree[indx].lev=level;
            tree[indx].parent="type_spec";
            tree[indx].child.push_back("FLOAT");
            indx++;
            tree[indx].lev=level+1;
            tree[indx].parent="FLOAT";
            tree[indx].child.push_back(".........");
             indx++;

             tree[indx].lev=level+1;
            tree[indx].parent="IDENT";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent=";";
            tree[indx].child.push_back(".........");
             indx++;
            newnode.children.push_back({"FLOAT", {}});
     }
     else if(str=="83"){
            tree[indx].lev=level;
            tree[indx].parent="type_spec";
            tree[indx].child.push_back("BOOL");
            indx++;
            tree[indx].lev=level+1;
            tree[indx].parent="BOOL";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent="IDENT";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent=";";
            tree[indx].child.push_back(".........");
             indx++;
            newnode.children.push_back({"BOOL", {}});
     }
   /*  else{
            tree[indx].lev=level;
            tree[indx].parent="type_spec";
            tree[indx].child.push_back("NULL");
            indx++;
            newnode.children.push_back({"NULL", {}});
     }*/

     return newnode;

}

node main_func(string str){

    node newnode;
    // cout<<"parse-main_func  ";
      tree[indx].lev=level;
      tree[indx].parent="main_func";
      tree[indx].child.push_back("int main ()");
     // tree[indx].child.push_back("main");
     // tree[indx].child.push_back("()");
      input>>str;
      input>>str;
      input>>str;//{
      open++;
      input>>str;

      str1=str;

      newnode.children.push_back({"int main ()", {}});
     // newnode.children.push_back({"main", {}});
    //  newnode.children.push_back({"()", {}});

        if(str=="81" || str=="82" || str=="83"){
            newnode.children.push_back({"compound_stmt", {}});
            tree[indx].child.push_back("compound_stmt");
            indx++;
            tree[indx].lev=level+1;
      tree[indx].parent="int main ()";
      tree[indx].child.push_back("..........");
      indx++;
            int l=level;
            level++;
            newnode.children.push_back(compound_stmt(str1));
            level=l;
        }
        else{
            tree[indx].child.push_back("{");
            newnode.children.push_back({"{", {}});
            tree[indx].child.push_back("stmt_list");
            tree[indx].child.push_back("}");
            indx++;
            tree[indx].lev=level+1;
            tree[indx].parent="{";
            tree[indx].child.push_back(".........");
             indx++;
            int l=level;
            level++;
            newnode.children.push_back(stmt_list(str1));
            level=l;
            tree[indx].lev=level+1;
            tree[indx].parent="}";
            tree[indx].child.push_back(".........");
             indx++;
            newnode.children.push_back({"}", {}});
        }

      return newnode;
}

node compound_stmt(string str){

     node newnode;
 // cout<<"parse-compound  ";
     tree[indx].lev=level;
     tree[indx].parent="compound_stmt";
          tree[indx].child.push_back("{");
     tree[indx].child.push_back("local_decls");
         tree[indx].child.push_back("stmt_list");
     tree[indx].child.push_back("}");

     indx++;

            tree[indx].lev=level+1;
            tree[indx].parent="{";
            tree[indx].child.push_back(".........");
             indx++;

      newnode.children.push_back({"{", {}});
      newnode.children.push_back({"local_decls", {}});
      int l=level;
      level++;
      newnode.children.push_back(local_decls(str));
      level=l;
      //input>>str1;
      //cout<<":"<<str1<<"::"<<str;
      newnode.children.push_back({"stmt_list", {}});

      /*if(str=="40"){
      open--;
      tree[indx].lev=2;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("E");
      indx++;
      newnode.children.push_back({"E", {}});

    }*/

      l=level;
      level++;
      newnode.children.push_back(stmt_list(str1));
      level=l;
            tree[indx].lev=level+1;
            tree[indx].parent="}";
            tree[indx].child.push_back(".........");
             indx++;

      newnode.children.push_back({"}", {}});

     return newnode;
}


node stmt (string str){

    node newnode;

   // cout<<"parse-stmt   ";

    if(str=="22"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("if_stmt");
      indx++;
      newnode.children.push_back({"if_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(if_stmt(str));
      level=l;

    }
    else if(str=="81" || str=="82" || str=="83"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("var_decl");
      indx++;
      newnode.children.push_back({"var_decl", {}});
      int l=level;
      level++;
      newnode.children.push_back(var_decl(str));
      level=l;

   }

    else if(str=="10"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("while_stmt");
      indx++;
      newnode.children.push_back({"while_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(while_stmt(str));
      level=l;

    }

    else if(str=="30"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("return_stmt");
      indx++;
      newnode.children.push_back({"return_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(return_stmt(str));
      level=l;

    }

    else if(str=="15"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("for_stmt");
      indx++;
      newnode.children.push_back({"for_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(for_stmt(str));
      level=l;

    }

    else if(str=="20"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("break_stmt");
      indx++;
      newnode.children.push_back({"break_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(break_stmt(str));
      level=l;

    }

    else if(str=="61"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("print");
      indx++;
      newnode.children.push_back({"print", {}});
      int l=level;
      level++;
      newnode.children.push_back(print(str));
      level=l;

    }

  /*  else if(str=="40"){
      open--;
      tree[indx].lev=2;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("E");
      indx++;
      newnode.children.push_back({"E", {}});

    }*/

    else if(str=="28"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("expr_stmt");
      indx++;
      newnode.children.push_back({"expr_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(expr_stmt(str));
      level=l;

    }

    return newnode;
}

node stmt_list(string str){

    node newnode;
    //cout<<"parse-stmt_list   ";
    if(str=="end"){

     tree[indx].lev=level;
     tree[indx].parent="stmt_list";
     tree[indx].child.push_back("E");

     indx++;

     tree[indx].lev=level+1;
            tree[indx].parent="E";
            tree[indx].child.push_back(".........");
             indx++;


     newnode.children.push_back({"E", {}});

    }
    else if(str=="40"){
        open--;
        input>>str;
        str1=str;
        stmt_list(str);
    }

    else{

     tree[indx].lev=level;
     tree[indx].parent="stmt_list";
     tree[indx].child.push_back("stmt_list");
     tree[indx].child.push_back("stmt");

      indx++;

      newnode.children.push_back({"stmt_list", {}});
      newnode.children.push_back({"stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(stmt(str));
      level=l;
      int k=level;
      level++;
      newnode.children.push_back(stmt_list(str1));
      level=k;

    }

     return newnode;
}

node local_decls(string str){

    node newnode;

   // cout<<"parse-local_decls   ";

    if(str=="4" || str=="81" || str=="82" || str=="83"){

     tree[indx].lev=level;
     tree[indx].parent="local_decls";
     tree[indx].child.push_back("local_decls");
     tree[indx].child.push_back("local_decl");

      indx++;

      newnode.children.push_back({"local_decls", {}});
      newnode.children.push_back({"local_decl", {}});
      int l=level;
      level++;

      newnode.children.push_back(local_decl(str));

      level=l;
      int k=level;
      level++;

      /* if(str1=="40"){
      open--;
      tree[indx].lev=2;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("E");
      indx++;
      newnode.children.push_back({"E", {}});

    }*/

      newnode.children.push_back(local_decls(str1));

      level=k;

    }

    else{

     tree[indx].lev=level;
     tree[indx].parent="local_decls";
     tree[indx].child.push_back("E");

     indx++;

     tree[indx].lev=level+1;
            tree[indx].parent="E";
            tree[indx].child.push_back(".........");
             indx++;


     newnode.children.push_back({"E", {}});

     //return newnode;

    }

     return newnode;
}

node local_decl (string str){

   //cout<<"parse-local_decl   ";

    node newnode;

    string strP=str;
    input>>str;

    if(strP=="81" || strP=="82" || strP=="83"){
            input>>str;
        if(str=="36"){
            tree[indx].lev=level;
            tree[indx].parent="local_decl";
            tree[indx].child.push_back("type_spec IDENT");
            tree[indx].child.push_back(";");
            indx++;
            newnode.children.push_back({"type_spec IDENT", {}});
             newnode.children.push_back({";", {}});
            input>>str;
            str1=str;
            int l=level;
            level++;
            newnode.children.push_back(type_spec(strP));
            level=l;
        }
        else if(str=="41"){
            input>>str;
            input>>str;
            input>>str;
            input>>str;
            tree[indx].lev=level;
            tree[indx].parent="var_decl";
            tree[indx].child.push_back("type_spec IDENT[]");
            tree[indx].child.push_back(";");
            indx++;
            str1=str;
            newnode.children.push_back({"type_spec IDENT[]", {}});
             newnode.children.push_back({";", {}});
            int l=level;
            level++;
            newnode.children.push_back(type_spec(strP));
            level=l;
        }
        else{
            cout<<"Input code is not following the Context Free Grammar!\n";
        }

    }

    return newnode;
}

node if_stmt (string str){

    node newnode;
  // cout<<"parse-if   ";
    tree[indx].lev=level;
    tree[indx].parent="if_stmt";

        newnode.children.push_back({"IF", {}});
        tree[indx].child.push_back("IF");

        newnode.children.push_back({"(", {}});
        tree[indx].child.push_back("(");

        newnode.children.push_back({"expr", {}});
        tree[indx].child.push_back("expr");
        tree[indx].child.push_back(")");
            tree[indx].child.push_back("{");
        tree[indx].child.push_back("st_list");
        tree[indx].child.push_back("}");
          indx++;
          tree[indx].lev=level+1;
            tree[indx].parent="IF";
            tree[indx].child.push_back(".........");
             indx++;
            tree[indx].lev=level+1;
            tree[indx].parent="(";
            tree[indx].child.push_back(".........");
             indx++;



    input>>str;
    input>>str;
    str1=str;

   /* int k=level;
     level++;
     newnode.children.push_back(st_list(str1));
     level=k;*/

    int l=level;
    level++;
    newnode.children.push_back(expr(str1));
    level=l;
    tree[indx].lev=level+1;
            tree[indx].parent=")";
            tree[indx].child.push_back(".........");
             indx++;
    tree[indx].lev=level+1;
            tree[indx].parent="{";
            tree[indx].child.push_back(".........");
             indx++;

    newnode.children.push_back({")", {}});
    newnode.children.push_back({"{", {}});
    open++;
    input>>str;
    str1=str;
    newnode.children.push_back({"st_list", {}});
    l=level;
    level++;
    newnode.children.push_back(st_list(str1));
    level=l;

    tree[indx].lev=level+1;
            tree[indx].parent="}";
            tree[indx].child.push_back(".........");
             indx++;

    newnode.children.push_back({"}", {}});

  return newnode;

}


node st_list (string str){

    node newnode;

   // cout<<"parse-st_list   ";

    if(str=="40"){

        open--;

        input>>str;
        str1=str;

       // cout<<str1<<"\n";

        tree[indx].lev=level;
        tree[indx].parent="st_list";
        tree[indx].child.push_back("E");

        indx++;
        tree[indx].lev=level+1;
            tree[indx].parent="E";
            tree[indx].child.push_back(".........");
             indx++;


       newnode.children.push_back({"E", {}});

       }

    else{

     tree[indx].lev=level;
     tree[indx].parent="st_list";
     tree[indx].child.push_back("st_list");
     tree[indx].child.push_back("st");

      indx++;

      newnode.children.push_back({"st_list", {}});
      newnode.children.push_back({"st", {}});
      int l=level;
      level++;
      newnode.children.push_back(st(str));
      level=l;
     // cout<<"::"<<str1;
     int k=level;
     level++;
     newnode.children.push_back(st_list(str1));
     level=k;

    }

     return newnode;

}

node st (string str){

    node newnode;

 // cout<<"parse-st   ";

    if(str=="22"){

      tree[indx].lev=level;
      tree[indx].parent="st";
      tree[indx].child.push_back("if_stmt");
      indx++;
      newnode.children.push_back({"if_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(if_stmt(str));
      level=l;

    }

    else if(str=="81" || str=="82" || str=="83"){

      tree[indx].lev=level;
      tree[indx].parent="stmt";
      tree[indx].child.push_back("var_decl");
      indx++;
      newnode.children.push_back({"var_decl", {}});
      int l=level;
      level++;
      newnode.children.push_back(var_decl(str));
      level=l;

   }
    else if(str=="28"){

      tree[indx].lev=level;
      tree[indx].parent="st";
      tree[indx].child.push_back("expr_stmt");
      indx++;
      newnode.children.push_back({"expr_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(expr_stmt(str));
      level=l;

    }
    else if(str=="61"){

      tree[indx].lev=level;
      tree[indx].parent="st";
      tree[indx].child.push_back("print");
      indx++;
      newnode.children.push_back({"print", {}});
      int l=level;
      level++;
      newnode.children.push_back(print(str));
      level=l;

    }
    else if(str=="20"){

      tree[indx].lev=level;
      tree[indx].parent="st";
      tree[indx].child.push_back("break_stmt");
      indx++;
      newnode.children.push_back({"break_stmt", {}});
      int l=level;
      level++;
      newnode.children.push_back(break_stmt(str));
      level=l;

    }

    return newnode;

}
node print (string str){

    //cout<<"parse-(print)   ";

     node newnode;

      tree[indx].lev=level;
      tree[indx].parent="print";
      tree[indx].child.push_back("printf");
      newnode.children.push_back({"printf", {}});
      tree[indx].child.push_back("(");
      newnode.children.push_back({"(", {}});
      tree[indx].child.push_back("STRING_LIT");
      newnode.children.push_back({"STRING_LIT", {}});
      tree[indx].child.push_back(")");
      newnode.children.push_back({")", {}});
      tree[indx].child.push_back(";");
      newnode.children.push_back({";", {}});

      indx++;

            tree[indx].lev=level+1;
            tree[indx].parent="printf";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent="(";
            tree[indx].child.push_back(".........");
             indx++;
            tree[indx].lev=level+1;
            tree[indx].parent="STRING_LIT";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent=")";
            tree[indx].child.push_back(".........");
             indx++;
             tree[indx].lev=level+1;
            tree[indx].parent=";";
            tree[indx].child.push_back(".........");
             indx++;

      input>>str;
      input>>str;
      input>>str;
      input>>str;//';'
      //cout<<str;
      input>>str;

    str1=str;

    return newnode;
}
node break_stmt (string str){

    //cout<<"parse-Break   ";

    input>>str; //';'

    node newnode;

       tree[indx].lev=level;
       tree[indx].parent="break_stmt";
       tree[indx].child.push_back("BREAK");
          newnode.children.push_back({"BREAK", {}});
       tree[indx].child.push_back(";");
          newnode.children.push_back({";", {}});

    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="BREAK";
    tree[indx].child.push_back(".........");
             indx++;
    tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;

    input>>str;
    //cout<<str;
    str1=str;
    return newnode;

}
node return_stmt (string str){

    //cout<<"parse-Return   ";

    input>>str;

    node newnode;

    if(str=="36"){

       tree[indx].lev=level;
       tree[indx].parent="return_stmt";
       tree[indx].child.push_back("RETURN");
          newnode.children.push_back({"RETURN", {}});
       tree[indx].child.push_back(";");
          newnode.children.push_back({";", {}});
          indx++;

        tree[indx].lev=level+1;
    tree[indx].parent="RETURN";
    tree[indx].child.push_back(".........");
             indx++;
    tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;

    }
    else if(str=="3"){

       tree[indx].lev=level;
       tree[indx].parent="return_stmt";
       tree[indx].child.push_back("RETURN");
          newnode.children.push_back({"RETURN", {}});
       tree[indx].child.push_back("expr");
          newnode.children.push_back({"expr", {}});
       tree[indx].child.push_back(";");
          newnode.children.push_back({";", {}});

          indx++;

          tree[indx].lev=level+1;
    tree[indx].parent="RETURN";
    tree[indx].child.push_back(".........");
             indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;

    tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;

          input>>str; //';'

    }

    input>>str;
    str1=str;
    return newnode;
}
node while_stmt (string str){

   node newnode;
   //cout<<"parse-while   ";
    tree[indx].lev=level;
    tree[indx].parent="while_stmt";

        tree[indx].child.push_back("WHILE");
        tree[indx].child.push_back("(");
        tree[indx].child.push_back("expr");
        tree[indx].child.push_back(")");
        tree[indx].child.push_back("{");
        tree[indx].child.push_back("st_list");
        tree[indx].child.push_back("}");
        indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="WHILE";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="(";
    tree[indx].child.push_back(".........");
    indx++;

    newnode.children.push_back({"WHILE", {}});
    input>>str;
    newnode.children.push_back({"(", {}});
    input>>str;
    str1=str;
    newnode.children.push_back({"expr", {}});
    int l=level;
    level++;
    newnode.children.push_back(expr(str));
    level=l;
    tree[indx].lev=level+1;
    tree[indx].parent=")";
    tree[indx].child.push_back(".........");
    indx++;
        tree[indx].lev=level+1;
        tree[indx].parent="{";
        tree[indx].child.push_back(".........");
    indx++;
    newnode.children.push_back({")", {}});
    newnode.children.push_back({"{", {}});
    newnode.children.push_back({"st_list", {}});
    //str=str1;
        open++;
        input>>str;
        str1=str;
    //cout<<"[[[["<<str;
    int k=level;
    level++;
    newnode.children.push_back(st_list(str1));
    level=k;
     tree[indx].lev=level+1;
    tree[indx].parent="}";
    tree[indx].child.push_back(".........");
    indx++;
    newnode.children.push_back({"}", {}});

    return newnode;

}

node for_stmt (string str){

    node newnode;
   // cout<<"parse-for   ";
    tree[indx].lev=level;
    tree[indx].parent="for_stmt";

        tree[indx].child.push_back("FOR");
        newnode.children.push_back({"FOR", {}});

        tree[indx].child.push_back("(");
           newnode.children.push_back({"(", {}});
           //cout<<indx;

    tree[indx].child.push_back("for_expr");
    newnode.children.push_back({"for_expr", {}});

    newnode.children.push_back({";", {}});
    tree[indx].child.push_back(";");
        tree[indx].child.push_back("for_expr");
        tree[indx].child.push_back(";");
            tree[indx].child.push_back("for_expr");
             //tree[indx].child.push_back(";");

    tree[indx].child.push_back(")");
    tree[indx].child.push_back("{");

        tree[indx].child.push_back("st_list");
        tree[indx].child.push_back("}");

        indx++;
        tree[indx].lev=level+1;
    tree[indx].parent="FOR";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="(";
    tree[indx].child.push_back(".........");
    indx++;

    input>>str; //'('
    //newnode.children.push_back({"(", {}});
    input>>str;
    str1=str;
    int l=level;
    level++;
    newnode.children.push_back(for_expr(str));
    level=l;
    tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;

    newnode.children.push_back({"for_expr", {}});
    newnode.children.push_back({";", {}});
    l=level;
    level++;
    newnode.children.push_back(for_expr(str1));
    level=l;
     tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;
    newnode.children.push_back({"for_expr", {}});
    newnode.children.push_back({";", {}});
    l=level;
    newnode.children.push_back(for_expr(str1));
    level=l;

    //cout<<level;
    tree[indx].lev=level+1;
    tree[indx].parent=")";
    tree[indx].child.push_back(".........");
    indx++;

    newnode.children.push_back({")", {}});
    newnode.children.push_back({"{", {}});
    tree[indx].lev=level+1;
    tree[indx].parent="{";
    tree[indx].child.push_back(".........");
    indx++;
    open++;
    newnode.children.push_back({"st_list", {}});

    input>>str;
    //cout<<str<<"\n";
    str1=str;
    l=level;
    level++;
    newnode.children.push_back(st_list(str1));
    level=l;

    tree[indx].lev=level+1;
    tree[indx].parent="}";
    tree[indx].child.push_back(".........");
    indx++;

    newnode.children.push_back({"}", {}});

    return newnode;

}

node for_expr(string str){

      node newnode;
  //cout<<"parse-for_expr   ";

      tree[indx].lev=level;
      tree[indx].parent="for_expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
      int l=level;
      level++;
      newnode.children.push_back(expr(str));
      level=l;
      //indx++;
      return newnode;
}

node expr_stmt(string str){

  //cout<<"parse-expr_stmt   ";

      node newnode;

      tree[indx].lev=level;
      tree[indx].parent="expr_stmt";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back(";");
      indx++;
    int l=level;
    level++;
    newnode.children.push_back(expr(str));
    level=l;
    tree[indx].lev=level+1;
    tree[indx].parent=";";
    tree[indx].child.push_back(".........");
    indx++;
    newnode.children.push_back({";", {}});

      return newnode;

}

node expr (string str){

  //cout<<"parse-expr   ";

   input>>str;

   node newnode;

   str1=str;

   if(str=="48"){

      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back(">");
      newnode.children.push_back({">", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
      tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent=">";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
      //input>>str;
   }
   else if(str=="49"){
      //cout<<str;
      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back("<");
      newnode.children.push_back({"<", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
        tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="<";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
   }
   else if(str=="51"){

      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back("==");
      newnode.children.push_back({"==", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
         tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="==";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
      //input>>str;
   }
   else if(str=="52"){

      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back("!=");
      newnode.children.push_back({"!=", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
      tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="!=";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
   }
   else if(str=="50"){

        input>>str;

    if(str=="3" || str=="2" || str=="6"){

      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("IDENT");
      newnode.children.push_back({"IDENT", {}});
      tree[indx].child.push_back("=");
      newnode.children.push_back({"=", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
      tree[indx].lev=level+1;
    tree[indx].parent="IDENT";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="=";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
    }
    else if(str=="28"){
        input>>str;
      //  cout<<str;
     if(str=="46"){

      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back("+");
      newnode.children.push_back({"+", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
      tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="+";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
    }

    else if(str=="47"){
      //cout<<str;
      tree[indx].lev=level;
      tree[indx].parent="expr";
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      tree[indx].child.push_back("-");
      newnode.children.push_back({"-", {}});
      tree[indx].child.push_back("expr");
      newnode.children.push_back({"expr", {}});
      indx++;
          tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="-";
    tree[indx].child.push_back(".........");
    indx++;
    tree[indx].lev=level+1;
    tree[indx].parent="expr";
    tree[indx].child.push_back(".........");
    indx++;
      input>>str;
      input>>str;
      input>>str;
    }

  }

   }

   str1=str;

   //cout<<"++"<<str1<<"++";

   return newnode;

}

void printParseTree(node n, int depth)
{
    output << string(depth, ' ') <<n.label << endl;

    for (node child : n.children)
    {
        printParseTree(child, depth + 4);

    }
}

node root;

/*void printTreeDetail(){

    cout<<"---------------------------------------------------------------------\n";
    cout<<"No:  Parent\t\tNumber of Childs\tChilds\t\tIs LEAF\t";
    cout<<"---------------------------------------------------------------------\n";

    for(int i=0;i<indx;i++){

    cout<<i+1<<"  "<<tree[i].parent<<"\t\t";

      for(int j=0;j<tree[i].child.size();j++){
        cout<<tree[i].child[j]<<"  ";
      }
      cout<<"\n";
      //input>>to;
   }




}*/

void parsing(){

   input.open("Tok.txt");
   output.open("parseTree.txt");

   //node root;

        input>>str1;

       // cout<<"parse0   ";

        root=parse(str1);

      cout<<"Parse Tree is Successfully Created!\n";

      // cout<<open<<"\n";

      if(open==0){
        cout<<"Brackets are balanced!\n\n";
      }

   //printParseTree(root, 0);

   input.close();

   cout<<"Parse Tree:\n";
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
   cout<<"__\"Parent\"__\t\t\t  __\"Child\"__\n";
   cout<<"-----------------------------------------------------------------\n";

   for(int i=0;i<indx;i++){

    cout<<tree[i].parent<<"\t\t\t\t-->";

      for(int j=0;j<tree[i].child.size();j++){
        cout<<tree[i].child[j]<<"  ";
      }
      cout<<"\n";
      //input>>to;
   }

   output<<"-----------------------------------------------------------------\n";
   output<<"In a Tree Format:\n";
   output<<"-----------------------------------------------------------------\n";
   printParseTree(root, 0);

}

