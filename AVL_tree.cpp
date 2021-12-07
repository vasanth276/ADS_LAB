#include<stdio.h>
#include<stdlib.h>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key, height;
    struct Node *l, *r;
    Node(int data){
        key = data;
        l = r = NULL;
        height = 1;
    };
};

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a: b;
}

Node* newNode(int key)
{
    Node* node = new Node(key);
    return(node);
}

Node *rightRotate(Node *y)
{
    struct Node *x = y->l;
    struct Node *T2 = x->r;
    x->r = y;
    y->l = T2;
    y->height = max(height(y->l), height(y->r))+1;
    x->height = max(height(x->l), height(x->r))+1;
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->r, *T2 = y->l;
    y->l = x;
    x->r = T2;
    x->height = max(height(x->l), height(x->r))+1;
    y->height = max(height(y->l), height(y->r))+1;
    return y;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->l) - height(N->r);
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->l  = insert(node->l, key);
    else if (key > node->key)
        node->r = insert(node->r, key);
    else
        return node;
    node->height = 1 + max(height(node->l),
    height(node->r));
    int balance = getBalance(node);
    if (balance > 1 && key < node->l->key)
        return rightRotate(node);
    if (balance < -1 && key > node->r->key)
        return leftRotate(node);
    if (balance > 1 && key > node->l->key)
    {
        node->l =  leftRotate(node->l);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->r->key)
    {
        node->r = rightRotate(node->r);
        return leftRotate(node);
    }
    return node;
}

Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
    /* loop down to find the leftmost leaf */
    while (current->l != NULL)
        current = current->l;
    return current;

}

Node* deleteNode(Node* base, int key)
{
    if (base == NULL)
        return base;
    if ( key < base->key )
        base->l = deleteNode(base->l, key);
    else if( key > base->key )
        base->r = deleteNode(base->r, key);
    else
    {
        if( (base->l == NULL) || (base->r == NULL) )
        {
            struct Node *temp = base->l ? base->l :
            base->r;
            if (temp == NULL)
            {
                temp = base;
                base = NULL;
            }
            else
                *base = *temp;
            free(temp);
        }
        else
        {
            struct Node* temp = minValueNode(base->r);
            base->key = temp->key;
            base->r = deleteNode(base->r, temp->key);
        }
    }
    if (base == NULL)
        return base;
    base->height = 1 + max(height(base->l),
    height(base->r));
    int balance = getBalance(base);
    if (balance > 1 && getBalance(base->l) >= 0)
        return rightRotate(base);
    if (balance > 1 && getBalance(base->l) < 0)
    {
        base->l =  leftRotate(base->l);
        return rightRotate(base);
    }
    if (balance < -1 && getBalance(base->r) <= 0)
        return leftRotate(base);
    if (balance < -1 && getBalance(base->r) > 0)
    {
        base->r = rightRotate(base->r);
        return leftRotate(base);
    }
    return base;
}

void preOrder(Node *base)
{
    if(base != NULL)
    {
        cout << base->key << " ";
        preOrder(base->l);
        preOrder(base->r);
    }
}

int search(Node* base, int data)
{
    if(base == NULL)
        return 0;
    if(base->key == data)
        return 1;
    else if(data < base->key)
        return search(base->l, data);
    else
        return search(base->r, data);
}

int main()
{
    Node *base = NULL;
    int choice = 0, data;
    cout << "Enter 1 for insertion\n";
    cout << "Enter 2 for deletion\n";
    cout << "Enter 3 to search the tree\n";
    cout << "Enter 4 for printing the tree\n";
    while(choice != -1)
    {
        cout << "Enter your choice : ";
        cin >> choice;
        if(choice == -1)
            break;
        switch(choice)
        {
            case 1: cout << "Enter the value: ";
                    cin >> data;
                    base = insert(base, data);
                    cout << "Inserted\n";
                    break;
            case 2: cout << "Enter the value to delete: ";
                    cin >> data;
                    if(search(base, data) == 1)
                    {
                        base = deleteNode(base, data);
                        cout << "Deleted\n";
                    }
                    else
                        cout << "Element not present in the tree\n";
                    break;
            case 3: cout << "Enter the value to be searched\n";
                    cin >> data;
                    if(search(base, data) == 1)
                        cout << data << " found in the tree\n";
                    else
                        cout << data << " not found in the tree\n";
                    break;
            case 4: preOrder(base);
                    cout << endl;
                    break;
            default: cout << "Invalid Selection\n";
        }
    }
    return 0;
}


