#include <bits/stdc++.h>
#include "Lexing1.cpp"
#include "ParseTree1.cpp"

using namespace std;

void deleteEnode(node& n)
{
    for (auto it = n.children.begin(); it != n.children.end();)
    {
        if (it->label == "E" || it->label == "()" || it->label == "(" || it->label == ")" || it->label == "{" || it->label == "}" || it->label == ";")
        {
            it = n.children.erase(it);
        }
        else
        {
            deleteEnode(*it);
            ++it;
        }
    }
}

ofstream output3;

void printAbstractSyntaxTree(node n, int depth)
{
    output3 << string(depth, ' ') <<n.label << endl;

    for (node child : n.children)
    {
        printAbstractSyntaxTree(child, depth + 4);

    }
}

int parseTreeNode=0;
int abstractSyntaxTreeNode=0;
vector<Tree>ast;

void printASTDetail(){

    cout<<"No:  Parent\t\tNumber of Childs\t\t\tIs LEAF\t\t\tChilds\n";
    cout<<"-------------------------------------------------------------------------------------------------------------------\n";

    for(int i=0;i<abstractSyntaxTreeNode;i++){

    cout<<i+1<<": "<<ast[i].parent<<"\t\t";

       int coun=0,leaf=0;

      for(int j=0;j<ast[i].child.size();j++){
        coun++;
        if(ast[i].child[j]=="-"){
            leaf=1;
        }
      }

      if(leaf==1){
        cout<<"\t"<<"\tX"<<"\t\t\t\t";
        cout<<"YES\t\t\t\t";
      }
      else{
        cout<<"\t"<<coun<<"\t\t\t\t";
        cout<<"NO\t\t\t\t";
      }

      for(int j=0;j<ast[i].child.size();j++){
        if(ast[i].child[j]=="-"){
             cout<<"NO CHILD";
             break;
        }
        cout<<ast[i].child[j]<<"\n\t\t\t\t\t\t\t\t\t\t\t\t";
      }

      cout<<"\n";
       cout<<"-------------------------------------------------------------------------------------------------------------------\n";
   }
}

void AST(){

  lexed();
  parsing();


   deleteEnode(root);

     for(int i=0;i<indx;i++){
        ast.push_back(tree[i]);
        parseTreeNode++;
     }

     //"E" node delete

     for(int i=0;i<ast.size();i++){
        for(int j=0;j<ast[i].child.size();j++){
            if(ast[i].child[j]=="E"){
                ast.erase(ast.begin()+i);
                i--;
            }
        }
     }

     for(int i=0;i<ast.size();i++){
            if(ast[i].parent=="E"||ast[i].parent=="("||ast[i].parent==")"||ast[i].parent=="{"||ast[i].parent=="}"||ast[i].parent==";"){
                ast.erase(ast.begin()+i);
                i--;
            }
     }

     // Brackets and semicolon

     for(int i=0;i<ast.size();i++){
        for(int j=0;j<ast[i].child.size();j++){

          /*  if(ast[i].child[j]==")" && ast[i].child[j+1]=="{"){
                ast[i].child.erase(ast[i].child.begin() + j);
            }*/

            if(ast[i].child[j]==";"){
                ast[i].child.erase(ast[i].child.begin() + j);
                //cout<<"*"<<j<<"*";
                j--;
            }
            else if(ast[i].child[j]=="()"){
                ast[i].child.erase(ast[i].child.begin() + j);
                //cout<<"*"<<j<<"*";
                j--;
            }
            else if(ast[i].child[j]=="(" || ast[i].child[j]==")"){
                ast[i].child.erase(ast[i].child.begin() + j);
                //cout<<"*"<<j<<"*";
                j--;
            }
            else if(ast[i].child[j]=="{" || ast[i].child[j]=="}"){
                ast[i].child.erase(ast[i].child.begin() + j);
               // cout<<"*"<<j<<"*";
               j--;
            }
        }
     }

     for(int i=0;i<ast.size();i++){
            if(ast[i].child.size()==1){
                 if(ast[i].child[0]==ast[i].parent){
                     ast.erase(ast.begin()+i);

                }
            }
        }

     abstractSyntaxTreeNode=ast.size();

   cout<<"\n\n_______________________\n";
   cout<<"Abstract Syntax Tree:\n";
   cout<<"_______________________\n\n";

     printASTDetail();

/*   cout << "\nAbstract Syntax Tree:\n";
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
   cout<<"__\"Parent\"__\t\t\t  __\"Child\"__\n";
   cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    for(int i=0;i<ast.size();i++){

      cout<<ast[i].parent<<"\t\t\t---->";

      for(int j=0;j<ast[i].child.size();j++){
        cout<<ast[i].child[j]<<"  ";
      }
      cout<<"\n";

    //  cout<<"__________________________________________________________\n";
      //input>>to;
   }
*/
   output3<<"-----------------------------------------------------------------\n";
   output3<<"In a Tree Format:\n";
   output3<<"-----------------------------------------------------------------\n";

    output3.open("AST.txt");

    printAbstractSyntaxTree(root, 0);


}

