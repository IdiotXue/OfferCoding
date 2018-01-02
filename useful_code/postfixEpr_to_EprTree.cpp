#include <iostream>
#include <stack>
#include <string>
using namespace std;

//test.in: a b + c d e + * *

struct BinaryNode
{
    string elem;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode(const string &value) : elem(value), left(nullptr), right(nullptr) {}
};

bool IsOperator(const string &opr)
{
    if (opr == "+" || opr == "-" || opr == "*" || opr == "/")
        return true;
    return false;
}

void InOrder(BinaryNode *pNode)
{
    if (pNode == nullptr)
        return;
    if (!(pNode->left == nullptr && pNode->right == nullptr))
        cout << " ( ";
    InOrder(pNode->left);
    cout << pNode->elem << " ";
    InOrder(pNode->right);
    if (!(pNode->left == nullptr && pNode->right == nullptr))
        cout << " ) ";
}

int main(int argc, char *argv[])
{
    string input;
    stack<BinaryNode *> nodeStack;
    while (cin >> input)
    {
        BinaryNode *pNode = new BinaryNode(input);
        if (IsOperator(input))
        {
            pNode->right = nodeStack.top();
            nodeStack.pop();
            pNode->left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(pNode);
        }
        else
        {
            nodeStack.push(pNode);
        }
    }
    InOrder(nodeStack.top());
    cout << endl;
    return 0;
}
