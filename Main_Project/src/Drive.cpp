#include <bits/stdc++.h>
#include "AbstractSyntaxTree1.cpp"

using namespace std;

int main(){

       AST();

    cout<<"\n";
    cout<<"Calculation:\n";
    cout<<"`````````````````````````````````````````````````\n";

    cout<<"PARSE TREE          : "<<"  Total Number of NODES: "<<parseTreeNode;
    cout<<"\tAllocated Memory: "<<(parseTreeNode*128)<<" bytes\n";
    cout<<"ABSTRACT SYNTAX TREE: "<<"  Total Number of NODES: "<<abstractSyntaxTreeNode;
    cout<<"\tAllocated Memory: "<<(abstractSyntaxTreeNode*128)<<" bytes\n\n";
    double comp=(parseTreeNode-abstractSyntaxTreeNode)/1.0;
    comp=comp/parseTreeNode;
    comp=comp*100;
    cout<<"Compression Percentage: "<<comp<<" %\n";

}
