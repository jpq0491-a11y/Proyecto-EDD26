#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <new>

// Singly linked, linear list with a header node.
// The header node stores no useful data: every data node has a previous node,
// so inserting or removing at the beginning works like at any other position.
// Positions are ints: the first element is 0 and -1 means "no position".
template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node() : data(), next(nullptr) {}
        Node(const T& elem, Node* nextNode) : data(elem), next(nextNode) {}
    };

    Node* header;
    int last;

    Node* nodeAt(int pos) const; // nodeAt(-1) returns the header
    void copyFrom(const List<T>& other);

public:
    List();                                  // 1. Default constructor
    List(const List<T>& other);              // 2. Copy constructor
    ~List();                                 // 3. Destructor
    List<T>& operator=(const List<T>& other);// 4. Assignment operator

    bool isEmpty() const;
    bool insert(const T& elem, int pos);
    bool remove(int pos);
    T retrieve(int pos) const;
    int first() const;
    int lastPos() const;
    int previous(int pos) const;
    int next(int pos) const;
    void clear();
    int findData(const T& e) const;

    template <class X>
    friend std::ostream& operator<<(std::ostream& os, const List<X>& l);

    template <class X>
    friend std::istream& operator>>(std::istream& is, List<X>& l);

    void insertSort();
};

// Walk from the header to the node at the given position
template <typename T>
typename List<T>::Node* List<T>::nodeAt(int pos) const {
    Node* current = header;
    for (int i = -1; i < pos; ++i) {
        current = current->next;
    }
    return current;
}

// Append a copy of every node of other (this list must be empty)
template <typename T>
void List<T>::copyFrom(const List<T>& other) {
    Node* tail = header;
    for (Node* current = other.header->next; current != nullptr; current = current->next) {
        tail->next = new Node(current->data, nullptr);
        tail = tail->next;
    }
    last = other.last;
}

// 1. Default constructor
template <typename T>
List<T>::List() : header(new Node()), last(-1) {
}

// 2. Copy constructor
template <typename T>
List<T>::List(const List<T>& other) : header(new Node()), last(-1) {
    copyFrom(other);
}

// 3. Destructor
template <typename T>
List<T>::~List() {
    clear();
    delete header;
}

// 4. Assignment operator
template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) { // Avoid self-assignment
        clear();
        copyFrom(other);
    }
    return *this;
}

// Check if empty
template <typename T>
bool List<T>::isEmpty() const {
    return header->next == nullptr;
}

// Insert element at position
template <typename T>
bool List<T>::insert(const T& elem, int pos) {
    if (pos < 0 || pos > last + 1) {
        return false;
    }
    Node* prev = nodeAt(pos - 1);
    Node* newNode = new (std::nothrow) Node(elem, prev->next);
    if (newNode == nullptr) { // No memory available
        return false;
    }
    prev->next = newNode;
    last++;
    return true;
}

// Remove element at position
template <typename T>
bool List<T>::remove(int pos) {
    if (pos < 0 || pos > last) {
        return false;
    }
    Node* prev = nodeAt(pos - 1);
    Node* target = prev->next;
    prev->next = target->next;
    delete target;
    last--;
    return true;
}

// Retrieve element at position
template <typename T>
T List<T>::retrieve(int pos) const {
    if (pos < 0 || pos > last) {
        return T();
    }
    return nodeAt(pos)->data;
}

// Get first position
template <typename T>
int List<T>::first() const {
    if (isEmpty()) {
        return -1;
    }
    return 0;
}

// Get last position
template <typename T>
int List<T>::lastPos() const {
    return last;
}

// Get previous position
template <typename T>
int List<T>::previous(int pos) const {
    if (pos <= 0 || pos > last) {
        return -1;
    }
    return pos - 1;
}

// Get next position
template <typename T>
int List<T>::next(int pos) const {
    if (pos < 0 || pos >= last) {
        return -1;
    }
    return pos + 1;
}

// Clear the list: frees every data node and keeps the header
template <typename T>
void List<T>::clear() {
    Node* current = header->next;
    while (current != nullptr) {
        Node* following = current->next;
        delete current;
        current = following;
    }
    header->next = nullptr;
    last = -1;
}

// Serialization (Output stream)
template <class X>
std::ostream& operator<<(std::ostream& os, const List<X>& l) {
    for (typename List<X>::Node* current = l.header->next; current != nullptr; current = current->next) {
        os << current->data << std::endl;
    }
    return os;
}

// Deserialization (Input stream)
template <class X>
std::istream& operator>>(std::istream& is, List<X>& l) {
    l.clear();
    X elem;
    while (is >> elem) {
        l.insert(elem, l.lastPos() + 1);
    }
    return is;
}

// Linear Search
template <typename T>
int List<T>::findData(const T& e) const {
    int pos = 0;
    for (Node* current = header->next; current != nullptr; current = current->next) {
        if (current->data == e) {
            return pos; // Element found at position pos
        }
        pos++;
    }
    return -1; // Element not found
}

// Insertion Sort Implementation: relinks the nodes without copying their data
template <typename T>
void List<T>::insertSort() {
    Node* pending = header->next;
    header->next = nullptr;

    while (pending != nullptr) {
        Node* current = pending;
        pending = pending->next;

        Node* prev = header;
        while (prev->next != nullptr && !(current->data < prev->next->data)) {
            prev = prev->next;
        }
        current->next = prev->next;
        prev->next = current;
    }
}

#endif
