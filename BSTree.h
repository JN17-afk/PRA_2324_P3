#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class BSNode {
public:
    T elem;
    BSNode<T>* left;
    BSNode<T>* right;

    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
        : elem(elem), left(left), right(right) {}

    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;
        return out;
    }
};

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado.");
        }
        if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw std::runtime_error("Elemento ya existe.");
        }
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    T max(BSNode<T>* n) const {
        while (n->right != nullptr) {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left_child = n->left;
            delete n;
            nelem--;
            return left_child;
        }
        n->right = remove_max(n->right);
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Elemento no encontrado.");
        }
        if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            if (n->left == nullptr) {
                BSNode<T>* right_child = n->right;
                delete n;
                nelem--;
                return right_child;
            } else if (n->right == nullptr) {
                BSNode<T>* left_child = n->left;
                delete n;
                nelem--;
                return left_child;
            } else {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            }
        }
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        BSNode<T>* node = search(root, e);
        return node->elem;
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
    }

    void remove(T e) {
        root = remove(root, e);
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif
