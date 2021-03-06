#include <iostream>
#include "binary_tree.hpp"

int main()
{
    btree <int> b;
    b.insert(10);
   b.insert(5);
   b.insert(20);
 b.insert(22);
 b.insert(21);
 b.insert(3);
 b.insert(15);
 b.insert(27);
 b.insert(7);
 b.insert(25);
 b.insert(1);
 b.insert(8);
 b.insert(26);
  std::cout << "Postorder  : ";
    b.print_postorder();
    std::cout << "Preorder   : ";
    b.print_preorder();
    std::cout << "Inorder    : ";
    b.print_inorder();
    std::cout << "Level order travers : ";
    b.print_level_order();
    std::cout << "Level order travers1 : ";
    b.print_level_order1();
    if (b.search(22)) {
        std::cout << "This item have in tree " << std::endl;
    } else {
        std::cout << "This item have not in tree " << std::endl;
    }
    if (b.search(55)) {
        std::cout << "This item have in tree " << std::endl;
    } else {
        std::cout << "This item have not in tree " << std::endl;
    }
   std::cout << "Inorder    : ";
  b.print_inorder();
    b.remove(22);
   std::cout << "Inorder    : ";
   b.print_inorder();
  std::cout << "Tree height is  : " << b.height() << std::endl;
}

