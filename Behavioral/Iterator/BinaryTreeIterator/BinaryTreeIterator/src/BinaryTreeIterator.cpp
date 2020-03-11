#include <string>
#include <iostream>
using namespace std;

template <typename T> struct BinaryTree;

template <typename T>
struct Node
{
    T value = T();
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    explicit Node(const T& value) :
        value{ value }
    {}

    Node(const T& value, Node<T>* const left, Node<T>* const right) :
        value{ value },
        left{ left },
        right{ right }
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }
};

template <typename T>
struct BinaryTree
{
    Node<T>* root = nullptr;

    template <typename U>
    struct BinaryTreeIterator
    {
        Node<U>* current;

        explicit BinaryTreeIterator(Node<U>* const current) :
            current{ current }
        {}

        bool operator!=(const BinaryTreeIterator<U>& other)
        {
            return current != other.current;
        }

        BinaryTreeIterator<U>& operator++()
        {
            if (current->right)
            {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            else
            {
                Node<T>* p = current->parent;
                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };
    typedef BinaryTreeIterator<T> iterator;

    explicit BinaryTree(Node<T>* const root) :
        root{ root }
    {
        root->set_tree(this);
    }

    ~BinaryTree()
    {
        if (root) delete root;
    }

    iterator begin()
    {
        Node<T>* n = root;

        if (n)
            while (n->left)
                n = n->left;

        return iterator{ n };
    }

    iterator end()
    {
        return iterator{ nullptr };
    }
};

int main()
{
    BinaryTree<string> family{
        new Node<string>{ "Me",
            new Node<string>{ "\tMother",
                new Node<string>{ "\t\tMother's mother" },
                new Node<string>{ "\t\tMother's father" }
            },
            new Node<string>{ "\tFather" }
        }
    };

    for (auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << endl;
    }

	return 0;
}