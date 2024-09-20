#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "StreamTree.h"

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    Node<T>* root;

    Node<T>* removeNode(Node<T>* node, const T& data);
    T minValue(Node<T>* node);
    void printInOrderHelper(Node<T>* node) const;
    void toStreamInOrderHelper(Node<T>* node, Stream<T>& stream) const;

public:
    BinaryTree() : root(nullptr) {}

    void insert(const T& data);
    bool contains(const T& data) const;
    void remove(const T& data);
    void printInOrder() const;
    Stream<T> toStreamInOrder() const;
};

template <typename T>
void BinaryTree<T>::insert(const T& data) {
    Node<T>* newNode = new Node<T>(data);

    if (root == nullptr) {
        root = newNode;
    } else {
        Node<T>* current = root;
        Node<T>* parent = nullptr;

        while (true) {
            parent = current;

            if (data < current->data) {
                current = current->left;

                if (current == nullptr) {
                    parent->left = newNode;
                    return;
                }
            } else {
                current = current->right;

                if (current == nullptr) {
                    parent->right = newNode;
                    return;
                }
            }
        }
    }
}

template <typename T>
bool BinaryTree<T>::contains(const T& data) const {
    Node<T>* current = root;

    while (current != nullptr) {
        if (data == current->data) {
            return true;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

template <typename T>
void BinaryTree<T>::remove(const T& data) {
    root = removeNode(root, data);
}

template <typename T>
Node<T>* BinaryTree<T>::removeNode(Node<T>* node, const T& data) {
    if (node == nullptr) {
        return node;
    }

    if (data < node->data) {
        node->left = removeNode(node->left, data);
    } else if (data > node->data) {
        node->right = removeNode(node->right, data);
    } else {
        if (node->left == nullptr) {
            Node<T>* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        }

        Node<T>* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = removeNode(node->right, temp->data);
    }

    return node;
}

template <typename T>
T BinaryTree<T>::minValue(Node<T>* node) {
    T minv = node->data;
    while (node->left != nullptr) {
        minv = node->left->data;
        node = node->left;
    }
    return minv;
}


template <typename T>
Stream<T> BinaryTree<T>::toStreamInOrder() const {
    Stream<T> stream;
    toStreamInOrderHelper(root, stream);
    return stream;
}

template <typename T>
void BinaryTree<T>::toStreamInOrderHelper(Node<T>* node, Stream<T>& stream) const {
    if (node != nullptr) {
        toStreamInOrderHelper(node->left, stream);
        stream.add(node->data);
        toStreamInOrderHelper(node->right, stream);
    }
}

#endif // BINARY_TREE_H