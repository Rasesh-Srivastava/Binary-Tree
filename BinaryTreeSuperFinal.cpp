#include <iostream>
using namespace std;
template <class t>
class Node
{
public:
    t data;
    Node *left;
    Node *right;
    Node *parent;
    Node(t Data)
    {
        data = Data;
        left = right = parent = NULL;
    }
    Node(t Data, Node *n1, Node *n2)
    {
        data = Data;
        left = n1;
        right = n2;
        if (n1 != NULL)
        {
            n1->parent = this;
        }
        if (n2 != NULL)
        {
            n2->parent = this;
        }
    }
};
template <class T>
class Tree
{
private:
    Node<T> *root;

public:
    Tree(Node<T> *Root) : root(Root) {}
    void preorder(Node<T> *n)
    {
        if (n == NULL)
        {
            return;
        }
        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void inorder(Node<T> *n)
    {
        if (n == NULL)
        {
            return;
        }
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }
    void postorder(Node<T> *n)
    {
        if (n == NULL)
        {
            return;
        }
        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }
};
Node<int> *constructTree(int *pre, int pstart, int pend, int *in, int istart, int iend)
{
    Node<int> *root = new Node<int>(pre[pstart]);
    int index = 0;
    for (int i = istart; i <= iend; i++)
    {
        if (in[i] == pre[pstart])
        {
            index = i;
            break;
        }
    }
    if (pstart <= pend)
    {
        root->left = constructTree(pre, pstart + 1, index - istart + pstart, in, istart, index - 1);
        if (root->left != NULL)
        {
            root->left->parent = root;
        }
        root->right = constructTree(pre, pstart + index - istart + 1, pend, in, index + 1, iend);
        if (root->right != NULL)
        {
            root->right->parent = root;
        }
        return root;
    }
    else
    {
        return NULL;
    }
}
int main()
{
    cout << "Test 1:\n";
    Node<int> *n1 = new Node<int>(69);
    Node<int> *n2 = new Node<int>(24);
    Node<int> *root1 = new Node<int>(29, n1, n2);
    Node<int> *n3 = new Node<int>(22);
    n3->parent = n2;                  //     29
    n2->right = n3;                   //  69     24
    cout << n1->parent->data << endl; //             22
    Tree<int> tree1(root1);           // n1=69, n2=24, n3=22, root1=29
    tree1.postorder(n2);
    cout << endl;
    tree1.postorder(root1);
    cout << endl;
    cout << endl;
    cout << "Test 2:\n";
    Node<int> *a = new Node<int>(2);
    Node<int> *b = new Node<int>(3);
    Node<int> *root2 = new Node<int>(1, a, b);
    Node<int> *c = new Node<int>(4);
    Node<int> *d = new Node<int>(5);
    Node<int> *e = new Node<int>(6); //                 1
    e->parent = b;                   //             2       3
    b->right = e;                    //           4   5   _   6
    c->parent = a;
    d->parent = a;
    a->left = c;
    a->right = d;
    Tree<int> tree2(root2);
    cout << "Pre Order Traversal: ";
    tree2.preorder(root2);
    cout << endl;
    cout << "In Order Traversal: ";
    tree2.inorder(root2);
    cout << endl;
    cout << "Post Order Traversal: ";
    tree2.postorder(root2);
    cout << endl;
    cout << endl;
    cout << "Construction of Binary Tree using given Pre Order and In Order\n\n";
    int n;
    cout << "Enter the Number of nodes in the Binary Tree\n";
    cin >> n;
    int in[n];
    int pre[n];
    cout << "Enter the InOrder Traversal of the tree\n";
    for (int i = 0; i < n; i++)
    {
        cin >> in[i];
    }
    cout << "Enter the PreOrder Traversal of the tree\n";
    for (int i = 0; i < n; i++)
    {
        cin >> pre[i];
    }
    Node<int> *root3 = constructTree(pre, 0, n - 1, in, 0, n - 1);
    Tree<int> tree3(root3);
    cout << "In Order Traversal of the formed Binary Tree: ";
    tree3.inorder(root3);
    cout << endl;
    cout << "Pre Order Traversal of the formed Binary Tree: ";
    tree3.preorder(root3);
    cout << endl;
    return 0;
}