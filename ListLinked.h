#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T>
{

private:
    Node<T> *first = nullptr;
    int n = 0;

public:
    ListLinked() = default;

    ~ListLinked()
    {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
        n = 0;
    }

    T operator[](int pos)
    {
        return this->get(pos);
    }
    friend std::ostream &operator<<(std::ostream &out, const ListLinked<T> &list){
        Node<T> *current = list.first;
        out << "[";
        for (int i = 0; i < list.n; i++)
        {
            out << current->data;
            if (i < list.n - 1)
                out << ", ";
            current = current->next;
        }
        out << "]";
        return out;
    }
};

#endif