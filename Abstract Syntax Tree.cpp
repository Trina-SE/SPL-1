#include <bits/stdc++.h>
#include "parse.cpp"
using namespace std;

void delete_E_node(node& n)
{
    for (auto it = n.children.begin(); it != n.children.end();)
    {
        if (it->label == "E")
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

void del()
{

    delete_E_node(root);

    cout << "\nParse Tree After Deletion:\n";

    printParseTree(root, 0);
}
