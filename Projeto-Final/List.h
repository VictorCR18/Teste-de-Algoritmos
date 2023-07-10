#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>

// Define um tipo de dado chamado Item, nome relativo de variavel int
typedef int Item;

struct Node {
    Item data;
    Node *last;
    Node *next;
     
};


class List{
    private:
    Node *m_head;
    Item m_size;
    Node *m_end;
    
    public:
    List();
    
    List(const List& lst);

    ~List();
    
    bool empty() const;

    size_t size() const;

    void clear();

    Node* front();

    Node* back();

    void push_front(const Item& data);

    void push_back(const Item& data);

    void pop_front();

    void pop_back();

    void insertAt(const Item& data, int index);
    
    Item removeAt(int index);

    List *copy();   
    
    void append(Item vec[], int n);

    void BubbleSort();

    void InsertionSort();

    void SelectionSort();

    void mergeSort(Item begin, Item end);

    void mergeConfiguration();

    void merge(Item begin, Item mid, Item end);

    void quickConfiguration();

    void quickSort(Item begin, Item end);

    Item partition(Item begin, Item end);

    void countingSort();
    
    friend std::ostream& operator<<(std::ostream& out, const List& lst);

    Item& operator[](int index);

    List& operator=(const List& lst);


    
};

#endif