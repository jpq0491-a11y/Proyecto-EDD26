#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T, int MAX = 50>
class List {
private:
    T elements[MAX];
    int last;

public:
    List();                                            // 1. Default constructor
    List(const List<T, MAX>& other);                   // 2. Copy constructor
    ~List();                                           // 3. Destructor
    List<T, MAX>& operator=(const List<T, MAX>& other);// 4. Assignment operator

    void initialize();
    bool isEmpty() const;
    bool isFull() const;
    bool insert(const T& elem, int pos);
    bool remove(int pos);
    T retrieve(int pos) const;
    int first() const;
    int lastPos() const;
    int previous(int pos) const;
    int next(int pos) const;
    void clear();
    int findDataA(const T& e) const;
    int findDataB(const T& e) const;

    template <class X, int Y>
    friend std::ostream& operator<<(std::ostream& os, const List<X, Y>& l);

    template <class X, int Y>
    friend std::istream& operator>>(std::istream& is, List<X, Y>& l);

    void insertSort();
    void shellSort();
};

// 1. Default constructor
template <typename T, int MAX>
List<T, MAX>::List() {
    initialize();
}

// 2. Copy constructor
template <typename T, int MAX>
List<T, MAX>::List(const List<T, MAX>& other) {
    this->last = other.last;
    for (int i = 0; i <= other.last; ++i) {
        this->elements[i] = other.elements[i];
    }
}

// 3. Destructor
template <typename T, int MAX>
List<T, MAX>::~List() {
}

// 4. Assignment operator
template <typename T, int MAX>
List<T, MAX>& List<T, MAX>::operator=(const List<T, MAX>& other) {
    if (this != &other) { // Avoid self-assignment
        this->last = other.last;
        for (int i = 0; i <= other.last; ++i) {
            this->elements[i] = other.elements[i];
        }
    }
    return *this;
}

// Initialize
template <typename T, int MAX>
void List<T, MAX>::initialize() {
    last = -1;
}

// Check if empty
template <typename T, int MAX>
bool List<T, MAX>::isEmpty() const {
    return last == -1;
}

// Check if full
template <typename T, int MAX>
bool List<T, MAX>::isFull() const {
    return last == MAX - 1;
}

// Insert element at position
template <typename T, int MAX>
bool List<T, MAX>::insert(const T& elem, int pos) {
    if (isFull() || pos < 0 || pos > last + 1) {
        return false;
    }
    for (int i = last; i >= pos; --i) {
        elements[i + 1] = elements[i];
    }
    elements[pos] = elem;
    last++;
    return true;
}

// Remove element at position
template <typename T, int MAX>
bool List<T, MAX>::remove(int pos) {
    if (isEmpty() || pos < 0 || pos > last) {
        return false;
    }
    for (int i = pos; i < last; ++i) {
        elements[i] = elements[i + 1];
    }
    last--;
    return true;
}

// Retrieve element at position
template <typename T, int MAX>
T List<T, MAX>::retrieve(int pos) const {
    if (pos < 0 || pos > last) {
        return T();
    }
    return elements[pos];
}

// Get first position
template <typename T, int MAX>
int List<T, MAX>::first() const {
    if (isEmpty()) {
        return -1;
    }
    return 0;
}

// Get last position
template <typename T, int MAX>
int List<T, MAX>::lastPos() const {
    return last;
}

// Get previous position
template <typename T, int MAX>
int List<T, MAX>::previous(int pos) const {
    if (pos <= 0 || pos > last) {
        return -1;
    }
    return pos - 1;
}

// Get next position
template <typename T, int MAX>
int List<T, MAX>::next(int pos) const {
    if (pos < 0 || pos >= last) {
        return -1;
    }
    return pos + 1;
}

// Clear the list
template <typename T, int MAX>
void List<T, MAX>::clear() {
    last = -1;
}

// Serialization (Output stream)
template <class X, int Y>
std::ostream& operator<<(std::ostream& os, const List<X, Y>& l) {
    int i = 0;
    while (i <= l.last) {
        os << l.elements[i] << std::endl;
        i++;
    }
    return os;
}

// Deserialization (Input stream)
template <class X, int Y>
std::istream& operator>>(std::istream& is, List<X, Y>& l) {
    l.clear();
    X elem;
    while (is >> elem && !l.isFull()) {
        l.insert(elem, l.lastPos() + 1);
    }
    return is;
}

// Linear Search
template <class T, int MAX>
int List<T, MAX>::findDataA(const T& e) const {
    for (int i = 0; i <= last; ++i) {
        if (elements[i] == e) {
            return i; // Element found at index i
        }
    }
    return -1; // Element not found
}

// Binary Search
template <typename T, int MAX>
int List<T, MAX>::findDataB(const T& e) const {
    if (isEmpty()) {
        return -1;
    }
    int i = 0; // Lower bound
    int j = last; // Upper bound
    while (i <= j) {
        int m = i + (j - i) / 2; // Midpoint

        if (elements[m] == e) {
            return m; // Element found at index m
        }

        if (e < elements[m]) {
            j = m - 1; // Target is in the left sublist
        } else {
            i = m + 1; // Target is in the right sublist
        }
    }
    return -1; // Element not found
}

// ShellSort Implementation
template <typename T, int MAX>
void List<T, MAX>::shellSort() {
    if (isEmpty()) {
        return;
    }

    float factor = 0.5;
    int dif = (last + 1) * factor;

    while (dif > 0) {
        int i = dif;

        while (i <= last) {
            int j = i;

            while (j >= dif && elements[j - dif] > elements[j]) {

                T temp = elements[j - dif];
                elements[j - dif] = elements[j];
                elements[j] = temp;

                j = j - dif;
            }
            i = i + 1;
        }
        dif = dif * factor;
    }
}
// Insertion Sort Implementation
template <typename T, int MAX>
void List<T, MAX>::insertSort() {
    if (isEmpty()) {
        return;
    }

    int i = 1;
    while (i <= last) {
        T aux = elements[i];
        int j = i;

        while (j > 0 && aux < elements[j - 1]) {
            elements[j] = elements[j - 1];
            j = j - 1;
        }

        if (i != j) {
            elements[j] = aux;
        }

        i = i + 1;
    }
}

#endif
