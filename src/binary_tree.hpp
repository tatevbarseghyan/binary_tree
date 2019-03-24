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
        void insert_help(T data, node<T>* curr_root);
        bool find_help(T item, node<T>* curr_root);
        void delete_node(node<T>* root);
        void print_postorder_help(node <T>* curr_root);
        void print_preorder_help(node <T>* curr_root);
        void print_inorder_help(node <T>* curr_root);
        node<T>* remove_help(node <T>* curr_root, T item);
        node<T>* find_min(node<T>* curr_root);
        int height_help(node<T> * curr_root);
        void print_given_level(node<T>* curr_root, int level);
   //     void print_level_order1(node<T>* curr_root);
    public:
        btree();
        ~btree();

        void insert(T item);
        bool find(T item);
        void print();
        void print_postorder();
        void print_preorder();
        void print_inorder();
        node<T>* remove(T item);
        int height();
        void print_level_order();
     //   void print_level_order1();;
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

//template <typename T>
//bool btree<T>::find_help(T data, node<T> * curr_root)
//{
//    if (curr_root != NULL) {
//        if (data == curr_root->data) {
//            return true;
//        }
//        if (data < curr_root->data) {
//            return find_help(data, curr_root->left);
//        } else {
//            return find_help(data, curr_root->right);
//        }
//    }
//    else return false;
//}

    template <typename T>
bool btree<T>::find_help(T data, node<T> * curr_root)
{
    while (curr_root != NULL) {
        if (data < curr_root->data) {
            curr_root = curr_root->left;
        } else
            if (data > curr_root->data) {
                curr_root = curr_root->right;
            }
            else {
                return true;
            }
    }
    return false;
}

    template <typename T>
bool btree<T>::find(T data)
{
    find_help(data,m_root);
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
node<T> * btree<T>::remove_help(node <T> * curr_root, T item)
{
    if (curr_root == NULL) {
        return NULL;
    }
    else if (item < curr_root->data) {
        curr_root->left = remove_help(curr_root->left, item);
    } else if (item > curr_root->data) {
        curr_root->right = remove_help(curr_root->right, item);
    } else if (curr_root->data == item) {
        if (curr_root->left == NULL && curr_root->right == NULL) {
            delete curr_root;
            curr_root = NULL;
        } else if (curr_root->left == NULL) {
            node<T>* tmp = curr_root;
            curr_root = curr_root->right;
            delete tmp;
        } else if (curr_root->right == NULL) {
            node<T>* tmp = curr_root;
            curr_root = curr_root ->left;
            delete tmp;
        } else {
            node<T>* tmp = find_min(curr_root->right);
            curr_root->data = tmp->data;
            curr_root->right = remove_help(curr_root->right,tmp->data);
        }
    }
    return curr_root;
}

    template <typename T>
node<T>* btree<T>::remove(T item)
{
    return remove_help(m_root, item);
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

/*template <typename T>
void btree<T>::print_level_order1(node<T> * curr_root)
{
    if (curr_root == NULL) {
        return;
    }
    std::queue<T> node * q;
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
        std::cout << std::endl;
    }
}*/

/*template <typename T>
void btree<T>::print_level_order1()
{
    print_level_order1(m_root);
}*/

