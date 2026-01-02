#ifndef RBT_H
#define RBT_H

#include <cstddef>
#include "allocator.h"
#include "vector.h"
#include <iterator>
#include <algorithm>

namespace ft {
template <typename T>
struct rb_node {
    typedef rb_node* node_ptr;

    node_ptr _parent;
    node_ptr _left;
    node_ptr _right;
    bool _color; // black - false / red - true
    T _value;

    rb_node(node_ptr parent, node_ptr left, node_ptr right, bool color, const T& value): _parent(parent), _left(left), _right(right), _color(color), _value(value) {}
};

template <typename T, typename Compare, typename Allocator>
class rb_tree {
    public:
        typedef T value_type;
        typedef typename rb_node<value_type> node_type;
        typedef node_type* node_ptr;
        typedef std::size_t size_type;
        typedef typename ft::allocator::template rebind<rb_node<value_type> >::other node_allocator;

    private:
        node_ptr _root;
        node_ptr _nil;
        size_type _size;
        Compare _comp;
        node_allocator _node_alloc;

    public:
        rb_tree(const Compare& comp, const Allocator& alloc): _node_alloc(alloc), _comp(comp), _size(0) {
            _nil = _node_alloc.allocate(1);
            _node_alloc.construct(_nil, node_type(NULL, NULL, NULL, false, value_type()));
            _root = _nil;
        }

        rb_tree(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc): _node_alloc(alloc), _comp(comp) {
            _size = 0;
            for(;first!=last ; ++first, ++_size) {
                node_ptr p = _node_alloc.allocate(1);
                _node_alloc.construct(p, *first);
                if(_size==1)
                    _root = p;

                if(first->_left==NULL)
                    _nil = first;
            }
        }

        node_ptr find_node(const value_type& v) const {
            node_ptr search = _root;
            while(true) {
                if(_comp(v, search->_value)) {
                    if(search->_left!=_nil)
                        search = search->_left;
                    else
                        return NULL;
                }
                else if(_comp(search->_value, v)) {
                    if(search->_right!=_nil)
                        search = search->_right;
                    else
                        return NULL;
                }
                else
                    return search;
            }
        }

        node_ptr lower_bound_node(const value_type& v) const {
            node_ptr search = _root;
            node_ptr best = NULL;

            while(search != _nil) {
                if(_comp(search->_value, v))
                    search = search->_right;
                else {
                    best = search;
                    search = search->_left;
                }
            }

            return best;
        }

        node_ptr insert_node(const value_type& v) {
            if(_size==0) {
                node_ptr p = _node_alloc.allocate(1);
                _node_alloc.construct(p, node_type(NULL, _nil, _nil, false, v));

                _root = p;

                ++_size;
                return p;
            }

            node_ptr search = _root;
            bool direction; // false - left / true - right
            while(true) {
                if(_comp(v, search->_value)) {
                    if(search->_left==_nil) {
                        direction = false;
                        break;
                    }
                    else
                        search = search->_left;
                }
                else if(_comp(search->_value, v)) {
                    if(search->_right==_nil) {
                        direction = true;
                        break;
                    }
                    else
                        search = search->_right;
                }
                else
                    return NULL;
            }

            node_ptr n_p = _node_alloc.allocate(1);
            _node_alloc.construct(n_p, node_type(search, _nil, _nil, true, v));
            if(direction)
                search->_right = n_p;
            else
                search->_left = n_p;

            if(search->_color) {
                node_ptr grand = search->_parent;
                node_ptr uncle;
                if(grand->_left==search)
                    uncle = grand->_right;
                else
                    uncle = grand->_left;

                if(uncle->_color) // recoloring
                    recoloring(n_p);
                else // restructuring
                    restructuring(n_p, search, grand);
            }

            ++_size;
            return n_p;
        }

        void recoloring(node_ptr check) {
            node_ptr check_grand = check->_parent->_parent;
            check_grand->_color = true;
            check_grand->_left->_color = false;
            check_grand->_right->_color = false;
            if(check_grand==_root) {
                check_grand->_color = false;
                return;
            }
            else {
                if(check_grand->_parent->_color) {
                    node_ptr grand = check_grand->_parent->_parent;
                    node_ptr uncle;
                    if(grand->_left==check_grand->_parent)
                        uncle = grand->_right;
                    else
                        uncle = grand->_left;
                    
                    if(uncle->_color)
                        recoloring(check_grand);
                    else
                        restructuring(check_grand, check_grand->_parent, grand);

                    return;
                }
                else
                    return;
            }
        }

        void restructuring(node_ptr n, node_ptr p, node_ptr g) {
            node_ptr small, mid, big;
            node_ptr t0, t1, t2, t3;

            if(g->_left==p) {
                if(p->_left==n) {
                    mid = p; small = n; big = g;
                    t0 = n->_left; t1 = n->_right; t2 = p->_right; t3 = g->_right;
                }
                else {
                    mid = n; small = p; big = g;
                    t0 = p->_left; t1 = n->_left; t2 = n->_right; t3 = g->_right;
                }
            }
            else {
                if(p->_left==n) {
                    mid = n; small = g; big = p;
                    t0 = g->_left; t1 = n->_left; t2 = n->_right; t3 = p->_right;
                }
                else {
                    mid = p; small = g; big = n;
                    t0 = g->_left; t1 = p->_left; t2 = n->_left; t3 = n->_right;
                }
            }

            mid->_parent = g->_parent;
            if(mid->_parent==NULL)
                _root = mid;
            else {
                if(mid->_parent->_left==g)
                    mid->_parent->_left = mid;
                else
                    mid->_parent->_right = mid;
            }
            mid->_left = small;
            mid->_right = big;
            small->_parent = mid;
            big->_parent = mid;

            small->_left = t0;
            if(t0 != _nil) t0->_parent = small;

            small->_right = t1;
            if(t1 != _nil) t1->_parent = small;

            big->_left = t2;
            if(t2 != _nil) t2->_parent = big;

            big->_right = t3;
            if(t3 != _nil) t3->_parent = big;

            mid->_color = false;
            small->_color = true;
            big->_color = true;

            return;
        }

        void erase_node(node_ptr p) {
            bool deleted_color;
            node_ptr real_del;
            node_ptr real_del_p;

            if(p->_left==_nil || p->_right==_nil) {
                deleted_color = p->_color;
                if(p->_left==_nil && p->_right==_nil) { // 자식 0
                    if(p==_root) {
                        real_del_p = _nil;
                        _root = _nil;
                    }
                    else {
                        if(p->_parent->_left==p)
                            p->_parent->_left = _nil;
                        else
                            p->_parent->_right = _nil;
                        
                        real_del_p = p->_parent;
                    }

                    real_del = _nil;
                    _node_alloc.destroy(p);
                    _node_alloc.deallocate(p, 1);
                }
                else { // 자식 1
                    if(p->_left==_nil)
                     real_del = p->_right;
                    else
                     real_del = p->_left;

                    if(p==_root)
                        _root = real_del;
                    else {
                        if(p->_parent->_left==p)
                            p->_parent->_left = real_del;
                        else
                            p->_parent->_right = real_del;
                    }
                    real_del->_parent = p->_parent;
                    real_del_p = real_del->_parent;

                    _node_alloc.destroy(p);
                    _node_alloc.deallocate(p, 1);
                }
            }
            else { // 자식 2
                node_ptr successor = p->_right;
                while(successor->_left!=_nil)
                    successor = successor->_left;

                deleted_color = successor->_color;
                p->_value = successor->_value;

                real_del = _nil;
                real_del_p = successor->_parent;
                if(successor==p->_right)
                    p->_right = _nil;
                else
                    real_del_p->_left = _nil;

                
                
                _node_alloc.destroy(successor);
                _node_alloc.deallocate(successor, 1);
            }
        }

        node_ptr minimum(node_ptr x) const {

        }

        node_ptr maximum(node_ptr x) const {

        }

        node_ptr begin_node() const {

        }

        node_ptr end_node() const {

        }

        size_type size() const {
            return _size;
        }
};

template <typename T>
class rb_tree_iterator {
    public:
        typedef T value_type;
        typedef typename value_type& reference;
        typedef typename value_type* pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        typedef typename rb_node<value_type> node_type;
        typedef typename node_type* node_ptr;

    private:
        node_ptr _node;
        node_ptr _nil;

    public:
        rb_tree_iterator() : _node(NULL), _nil(NULL) {}
        rb_tree_iterator(node_ptr n, node_ptr nil) : _node(n), _nil(nil) {}

        reference operator*() const {return _node->value;}

        pointer operator->() const {return &_node->value;}

        rb_tree_iterator& operator++() {

        }

        rb_tree_iterator operator++(int n) {

        }

        rb_tree_iterator& operator--() {

        }

        rb_tree_iterator operator--(int n) {

        }

        bool operator==(const rb_tree_iterator& other) const {return _node==other._node;}
        bool operator!=(const rb_tree_iterator& other) const {return _node!=other._node;}

        node_ptr base() const {return _node;}
};

}

#endif