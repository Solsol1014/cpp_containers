#ifndef RBT_H
#define RBT_H

// namespace ft {
template <typename T>
struct rb_node {
    rb_node* parent;
    rb_node* left;
    rb_node* right;
    bool color;
    T value;
};


// }

#endif