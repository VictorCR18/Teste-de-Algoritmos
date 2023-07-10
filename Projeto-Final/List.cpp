#include <vector>
#include <iostream>
#include <stdexcept>
#include "List.h"

using namespace std;

typedef int Item;

List::List(){
    m_head = new Node();
    m_head->next = m_head;
    m_head->last = m_head;
    m_end = m_head;
    m_head->data = -22;
    m_size = 0;
}

List::~List(){
    if(!empty()){
        Node *deletar = m_head->last;
        Node *correr = deletar->last;
        while(deletar != m_head){
            delete deletar;
            deletar = correr;
            correr = correr->last;
        }
    }
    delete m_head;
    m_size = 0;
}

List::List(const List& lst){
    Node *percorrer = lst.m_head->next;
    while(percorrer != lst.m_head){
        push_back(percorrer->data);
        percorrer = percorrer->next;
    }
    percorrer = nullptr;
    delete percorrer;
}

bool List::empty() const{
    return(m_size == 0);
}

size_t List::size() const{
    return m_size;
}

void List::clear(){
    if(!empty()){
        Node *deletar = m_head->last;
        Node *correr = deletar->last;
        while(deletar != m_head){
            delete deletar;
            deletar = correr;
            correr = correr->last;
        }
        m_head->next = m_head;
        m_head->last = m_head;
        m_end = m_head;
    }
    m_size = 0;
}

Node *List::front(){
    if(!empty()){
        return m_head->next;
    }else{
        throw std::out_of_range("empty list");
    }
    
}

Node *List::back(){
    if(!empty()){
        return m_head->last;
    }else{
        throw std::out_of_range("empty list");
    }
}

void List::push_front(const Item& data){
    //Novo no que vai ser inserido.
    Node *front = new Node;
    front->data = data;
    //Salvar o primeiro elemento para fazer o next.
    Node *primeiro = m_head->next;

    //Circularidade.
    primeiro->last = front;
    m_head->next = front;

    front->next = primeiro;
    front->last = m_head;

    //Circularidade do tail.
    m_end = m_head->last;
    m_end->next = m_head;
    m_end->last = m_head->last->last;
    //Ajuste de Tamanho.
    m_size++;
}

void List::push_back(const Item& data){
    //Novo no que vai ser inserido.
    Node *back = new Node;
    back->data = data;
    
    //Salvar o ultimo elemento para fazer o next.
    Node *ultimo = m_head->last; 
    
    //Circularidade.
    ultimo->next = back;
    m_head->last = back;
    
    back->next = m_head;
    back->last = ultimo;

    // Circularidade com o tail.
    m_end = m_head->last;
    m_end->next = m_head;
    m_end->last = ultimo;

    //Ajustes de tamanho.
    m_size++;
}


void List::pop_front(){
    if(!empty()){
        Node *deletar = m_head->next;
        m_head->next = m_head->next->next;
        m_head->next->last = m_head;
        m_size--;
        delete deletar;
    }
}

void List::pop_back(){
    if(!empty()){
    //Como o ultimo elemento vai ser deletado, teremos que modificar o elemento antes dele
    //para manter a circularidade.
        Node *deletar = m_end;
        Node *antes = m_end->last;

        m_end = antes;
        m_head->last = m_end;
        m_head->last->next = m_head;

        m_end->next = m_head;
    //Verificando se tem um antepenultimo elemento.
        if(m_head->last == m_head ){
            m_end->last = m_head;
        }else{
            m_end->last = m_head->last->last; 
        }
    //Desalocando memória.  
        delete deletar;
        antes = nullptr;
        delete antes;
    //Ajuste de tamanho.
        m_size--;
    }
}

void List::insertAt(const Item& data, int index){
    if(index < 0 || index > m_size) {
        throw std::out_of_range("index out of range");
    }
    if(index == 0){
        push_front(data);
        return;
    }
    if(index == m_size){
        push_back(data);
        return;
    }
    int contador = 0;
    Node *correndo = m_head->next;
    while(contador < index-1){
        contador++;
        correndo = correndo->next;
    }
    Node *novo = new Node;
    novo->data = data;
    novo->next = correndo;
    novo->last = correndo->last;
    
    correndo->last->next = novo;
    correndo->last = novo;
    m_size++;
}

Item List::removeAt(int index){
    if(index < 0 || index > m_size - 1){
        throw std::out_of_range("index out of range");
    }
    int contador = 0;
    int guardar = 0;
    if(index == 0){
        guardar = m_head->next->data;
        pop_front();
        contador = index;
    }else{
        Node *correndo = m_head->next->next;
        while(contador <index-1){
            contador++;
            correndo = correndo->next;
    }
        Node *deletar = correndo;
        guardar = correndo->data;
        correndo->last->next = correndo->next;
        correndo->next->last = correndo->last; 

        delete deletar;
        m_size--;
    }
    return guardar;
}

List *List::copy(){
    List *copia = new List;
    if(!empty()){
        Node *percorrer = m_head->next;
        while(percorrer != m_head){
            copia->push_back(percorrer->data);
            percorrer = percorrer->next;
        }
        copia->m_size = m_size;
    }
    return copia;
}

void List::append(Item vec[], int n){
    int i = 0;
    while(i != n){
        push_back(vec[i]);
        i++;
    }
}

void List::BubbleSort(){
    Node *aux_node;
    Item fim = m_size;
    Item cont, i, aux;
    do {
        aux_node = m_head;
        for(i = 0; i < fim; i++) {
            if(aux_node->data > aux_node->next->data) {
                aux = aux_node->data;
                aux_node->data = aux_node->next->data;
                aux_node->next->data = aux;
            }
            aux_node = aux_node->next;
            cont = i;
        }

        fim --;
    }while(cont != i);
}

void List::InsertionSort() {
    Node *aux_node = m_head->next;
    Node *aux_node_2;
    Item i, j;
    Item aux;
    for(i = 1; i <= m_size; i++) {
        aux = aux_node->data;
        aux_node_2 = aux_node;
        for(j = i; (j > 0) && (aux < aux_node_2->last->data); j--) {
            aux_node_2->data = aux_node_2->last->data;
            aux_node_2 = aux_node_2->last;
        }
        aux_node_2->data = aux;
        aux_node = aux_node->next;
    }
}

void List::SelectionSort() {
    Node *aux_node_1 = m_head;
    Node *aux_node_2, *menor;
    Item i, j;
    Item aux;

    for(i = 0; i < m_size ; i++) {
        menor = aux_node_1;
        aux_node_2 = aux_node_1->next;
        for(j = i + 1; j < m_size+1; j++) {
            if(aux_node_2->data < menor->data) {
                menor = aux_node_2;
            }
            aux_node_2 = aux_node_2->next;
        }

        aux = aux_node_1->data;
        aux_node_1->data = menor->data;
        menor->data = aux;
        aux_node_1 = aux_node_1->next;
    }
}

void List::mergeConfiguration() {
    mergeSort(0, size() - 1);
}

void List::mergeSort(Item begin, Item end) {
    if(begin >= end) 
        return;
    
    Item mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);
    merge(begin, mid, end);
}

void List::merge(Item begin, Item mid, Item end) {
    Item left = mid - begin + 1;
    Item right = end - mid;
    Node *aux;

    Item *leftArray = new Item[left];
    Item *rightArray = new Item[right];

    aux = m_head;
    for(int i = 0; i < begin; i++) { aux = aux->next; }

    for(int i = 0; i < left; i++) {
        leftArray[i] = aux->data;
        aux = aux->next;
    }

    aux = m_head;
    for(int i = 0; i <= mid; i++) { aux = aux->next; }

    for(int i = 0; i < right; i++) {
        rightArray[i] = aux->data;
        aux = aux->next;
    }

    Item i = 0, j = 0;
    aux = m_head;
    for(int i = 0; i < begin; i++) { aux = aux->next; }

    while(i < left && j < right) {
        if(leftArray[i] <= rightArray[j]) {
            aux->data = leftArray[i];
            i++;
        } else {
            aux->data = rightArray[j];
            j++;
        }
        aux = aux->next;
    } 

    while(i < left) {
        aux->data = leftArray[i];
        i++;
        aux = aux->next;
    }

    while(j < right) {
        aux->data = rightArray[j];
        j++;
        aux = aux->next;
    }
}

void List::quickConfiguration() {
    quickSort(0, size() - 1);
}

void List::quickSort(Item begin, Item end) {
    if(begin >= end)
        return;

    Item p = partition(begin, end);

    quickSort(begin, p - 1);
    quickSort(p + 1, end);
}

Item List::partition(Item begin, Item end) {
    Node *aux = m_head, *aux_2 = m_head;
    Item sw, i, j, count = 0, pivot, auxValue;

    for(i = 0; i < begin; i++) 
        aux = aux->next;
    
    pivot = aux->data;
    aux = aux->next;

    for(i = begin + 1; i <= end; i++) {
        if(aux->data <= pivot)
            count++;
        aux = aux->next;
    }

    aux = m_head;
    auxValue = begin + count;
    for(i = 0; i < begin; i++) 
        aux = aux->next;
    
    for(i = 0; i < auxValue; i++)
        aux_2 = aux_2->next;
    
    sw = aux->data;
    aux->data = aux_2->data;
    aux_2->data = sw;

    aux = m_head;
    aux_2 = m_head;
    for(i = 0; i < begin; i++)
        aux = aux->next;
    
    for(i = 0; i < end; i++)
        aux_2 = aux_2->next;
    
    i = begin;
    j = end;
    while(i < auxValue && j > auxValue) {
        while(aux->data <= pivot) {
            aux = aux->next;
            i++;
        }

        while(aux_2->data > pivot){
            aux_2 = aux_2->last;
            j--;
        }

        if(i < auxValue && j > auxValue) {
            sw = aux->data;
            aux->data = aux_2->data;
            aux_2->data = sw;
            aux = aux->next;
            i++;
            aux_2 = aux_2->last;
            j--;
        }
    }

    return auxValue;
}

void List::countingSort() {
    Node *aux = m_head;
    Item max = aux->data;
    while(aux->next != m_head) {
        if(max < aux->data) { max = aux->data; }
        aux = aux->next;
    }
    
    Item *sec_vec = new Item[max+1];
    for(int i = 0; i <= max; i++) {
        sec_vec[i] = 0;
    }

    aux = m_head;
    sec_vec[aux->data]++;
    aux = aux->next;
    while(aux != m_head) {
        sec_vec[aux->data]++;
        aux = aux->next;
    }

    aux = m_head;
    for(int j = 0; j <= max; j++) {
        for(int k = sec_vec[j]; k > 0; k--) {
            aux->data = j;
            aux = aux->next;
        }
    }

    sec_vec = nullptr;
    delete sec_vec;
}

std::ostream& operator<<(std::ostream& out, const List& lst){
    out << "[ ";
    if(!lst.empty()){
        Node *percorrer = lst.m_head->next;
        while(percorrer != lst.m_head){
            out << percorrer->data << " ";
            percorrer = percorrer->next;
        }
    }
    return out << "]";
}

Item& List::operator[](int index){
    if(index < 0 || index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    int contador = 0;
    Node *correndo = m_head->next;
    while(contador < index) {
        contador++;
        correndo = correndo->next;
    }
    return correndo->data;
}

//Ajustar.
List& List::operator=(const List& lst){
    clear();
    Node *correndo = lst.m_head->next;

    while(correndo != lst.m_head){
        push_back(correndo->data);
    } 
    return *this;
}