#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <queue>

template <typename T>
struct node
{
    T data;
    node* left;
    node* right;
};

template <typename T>
class btree
{
    private:
        node<T> *m_root;
        //help function to insert node
        void insert_help(T data, node<T>* curr_root);

        //help funcion to find given item (without recursion)
        node<T>* find_help(T item, node<T>* curr_root);

        //help funcion to find given item (recursion)
        bool search_help(T item, node<T>* curr_root);

        //this function uded in destructor
        void delete_node(node<T>* root);

        //help function to print tree postorder
        void print_postorder_help(node <T>* curr_root);

        //help function to print tree preorder
        void print_preorder_help(node <T>* curr_root);

        //help function to print tree inorder
        void print_inorder_help(node <T>* curr_root);

        //help function to calculate height of tree
        int height_help(node<T> * curr_root);

        //print tree (given level)
        void print_given_level(node<T>* curr_root, int level);

        //print tree (given level) used queue
        void print_level_order1(node<T>* curr_root);

        //help function to delete node when it is a root of tree
        void remove_root();

        //help function to delete node with given item
        void remove_help(node<T> * curr,T item);

        //this function give node with minimum value
        node<T> * find_min(node<T>* curr_root);

    public:
        btree();
        ~btree();
        void insert(T item);
        node<T>* find(T item);
        bool search(T item);
        void print();
        void print_postorder();
        void print_preorder();
        void print_inorder();
        int height();
        void print_level_order();
        void print_level_order1();
        void remove(T item);
};

#endif

    template <typename T>
btree<T>::btree()
    : m_root(NULL)
{}

    template <typename T>
btree<T>::~btree()
{
    delete_node(m_root);
}

    template <typename T>
void btree<T>::delete_node(node<T> * curr)
{
    if (curr != NULL) {
        delete_node(curr->left);
        delete_node(curr->right);
        delete curr;
    }
}

    template <typename T>
void btree<T>::insert_help(T data,node<T> * curr_root)
{
    if (data < curr_root->data) {
        if (curr_root->left != NULL) {
            insert_help(data,curr_root->left);
        } else {
            curr_root->left = new node<T>;
            curr_root->left->data = data;
            curr_root->left->left = NULL;
            curr_root->left->right = NULL;
        }
    } else {
        if (data >= curr_root->data) {
            if (curr_root->right != NULL) {
                insert_help(data,curr_root->right);
            } else {
                curr_root->right = new node<T>;
                curr_root->right->data = data;
                curr_root->right->left = NULL;
                curr_root->right->right = NULL;
            }
        }
    }
}


    template <typename T>
void btree<T>::insert(T data)
{
    if (m_root != NULL) {
        insert_help(data,m_root);
    } else {
        m_root = new node<T>;
        m_root->data = data;
        m_root->left = NULL;
        m_root->right = NULL;
    }
}

    template <typename T>
bool btree<T>::search_help(T data, node<T> * curr_root)
{
    if (curr_root != NULL) {
        if (data == curr_root->data) {
            return true;
        }
        if (data < curr_root->data) {
            return search_help(data, curr_root->left);
        } else {
            return search_help(data, curr_root->right);
        }
    }
    else return false;
}

    template <typename T>
bool btree<T>::search(T data)
{
    return search_help(data,m_root);
}

    template <typename T>
node<T>* btree<T>::find_help(T data, node<T> * curr_root)
{
    node<T>* tmp = NULL;
    if (curr_root->right != NULL || curr_root->left != NULL) {
        while (curr_root != NULL) {
            if (data < curr_root->data) {
                tmp = curr_root;
                curr_root = curr_root->left;
            } else
                if (data > curr_root->data) {
                    tmp = curr_root;
                    curr_root = curr_root->right;
                }
                else {
                    return tmp ;
                }
        }
    }
    return tmp;
}

    template <typename T>
node<T>* btree<T>::find(T data)
{
    return find_help(data,m_root);
}

    template <typename T>
node<T>* btree<T>::find_min(node<T>* curr_root)
{
    while (curr_root->left != NULL) {
        curr_root = curr_root->left;
    }
    return curr_root;
}


    template <typename T>
void btree<T>::print_inorder_help(node <T> * curr_root)
{
    if (curr_root == NULL) {
        return;
    }
    print_inorder_help(curr_root->left);
    std::cout <<" " << curr_root->data;
    print_inorder_help(curr_root->right);
}

    template <typename T>
void btree<T>::print_inorder()
{
    print_inorder_help(m_root);
    std::cout << std::endl;
}

    template <typename T>
void btree<T>::print_preorder_help(node <T> * curr_root)
{
    if (curr_root == NULL) {
        return;
    }
    std::cout <<" " << curr_root->data;
    print_preorder_help(curr_root->left);
    print_preorder_help(curr_root->right);
}

    template <typename T>
void btree<T>::print_preorder()
{
    print_preorder_help(m_root);
    std::cout << std::endl;
}

    template <typename T>
void btree<T>::print_postorder_help(node <T> * curr_root)
{
    if (curr_root == NULL) {
        return;
    }
    print_postorder_help(curr_root->left);
    print_postorder_help(curr_root->right);
    std::cout <<" " << curr_root->data;
}

    template <typename T>
void btree<T>::print_postorder()
{
    print_postorder_help(m_root);
    std::cout << std::endl;
}

    template <typename T>
int btree<T>::height_help(node<T> * curr_root)
{
    int h = 0;
    if (curr_root !=  NULL) {
        h++;
        if (height_help(curr_root->left) > height_help(curr_root->right)) {
            h += height_help(curr_root->left);
        } else {
            h += height_help(curr_root->right);
        }
    }
    return h;
}

    template <typename T>
int btree<T>::height()
{
    return height_help(m_root);
}

    template <typename T>
void btree<T>::print_given_level(node<T>* curr_root, int level)
{
    if (curr_root == NULL) {
        return;
    }
    if (level == 1) {
        std::cout << curr_root->data << " ";
    } else if (level > 1) {
        print_given_level(curr_root->left, level - 1);
        print_given_level(curr_root->right, level - 1);
    }
}

    template <typename T>
void btree<T>::print_level_order()
{
    for (int i = 1; i <= height(); ++i) {
        print_given_level(m_root, i);
    }
    std::cout << std::endl;
}

    template <typename T>
void btree<T>::print_level_order1(node<T> * curr_root)
{
    if (curr_root == NULL) {
        return;
    }
    std::queue<node <T> *> q;
    q.push(curr_root);
    while (!q.empty()) {
        node<T> * tmp = q.front();
        std::cout << tmp->data << " ";
        q.pop();
        if (tmp->left != NULL) {
            q.push(tmp->left);
        }
        if (tmp->right != NULL) {
            q.push(tmp->right);
        }
    }
    std::cout << std::endl;
}

    template <typename T>
void btree<T>::print_level_order1()
{
    print_level_order1(m_root);
}

    template <typename T>
void btree<T>::remove_help(node<T> * curr, T item)
{
    node<T> * parent = find(item);
    if (m_root == NULL) {
        std::cout << "is empty";
    } else if (m_root->data == item) {
        remove_root();
    }
    else {
        if (parent->left != NULL && parent->left->left == NULL && parent->left->right == NULL && parent->left->data == item) {
            delete parent->left;
            parent->left = NULL;
        } else if (parent->right != NULL && parent->right->left == NULL && parent->right->right == NULL && parent->right->data == item) {
            delete parent->right;
            parent->right = NULL;
        } else if (parent->right != NULL && parent->right->data == item && (parent->right->left == NULL || parent->right->right == NULL)) {
            if (parent->right->left == NULL && parent->right->right != NULL) {
                node<T> * tmp = parent->right;
                parent->right = parent->right->right;
                delete tmp;
            } else if (parent->right->left != NULL && parent->right->right == NULL) {
                node<T> * tmp = parent->right;
                parent->right = parent->right->left;
                delete tmp;
            }
        } else if (parent->left != NULL && parent->left->data == item && (parent->left->left == NULL || parent->left->right == NULL)) {
            if (parent->left->left == NULL && parent->left->right != NULL) {
                node<T> * tmp = parent->left;
                parent->left = parent->left->right;
                delete tmp;
            } else if (parent->left->left != NULL && parent->left->right == NULL) {
                node<T> * tmp = parent->left;
                parent->left = parent->left->left;
                delete tmp;
            }
        } else {
            if (parent->right->data == item) {
                node<T> * min = find_min(parent->right);
                node<T> * parent1 = find(min->data);
                parent->right->data = min->data;
                if (min->right == NULL) {
                    parent1->left = NULL;
                } else {
                    parent1->left = min->right;
                }
            } else {
                node<T> * min = find_min(parent->left);
                node<T> * parent1 = find(min->data);
                parent->left->data = min->data;
                if (min->right == NULL) {
                    parent1->left = NULL;
                } else {
                    parent1->left = min->right;
                }
            }
        }
    }
}

    template <typename T>
void btree<T>::remove_root()
{
    if (m_root == NULL) {
        std::cout << "The tree is empty" << std::endl;
    } else
        if (m_root->right == NULL && m_root->left == NULL) {
            node<T> * tmp = m_root;
            m_root = NULL;
            delete tmp;
        } else  if (m_root->right == NULL && m_root->left != NULL) {
            node<T> * tmp = m_root;
            m_root = m_root->left;
            delete tmp;
        } else if (m_root->left == NULL && m_root->right != NULL) {
            node<T> * tmp = m_root;
            m_root = m_root->right;
            delete tmp;
        } else  {
            node<T> * min = find_min(m_root->right);
            node<T> * parent = find(min->data);
            m_root->data = min->data;
            if (min->right == NULL) {
                parent->left = NULL;
            } else {
                parent->left = min->right;
            }
        }
}

    template <typename T>
void btree<T>::remove(T item)
{
    remove_help(m_root,item);
}
