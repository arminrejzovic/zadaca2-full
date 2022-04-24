//
// Created by armin on 09.04.2022.
//

#ifndef ZADACA2_ARRAYLIST_H
#define ZADACA2_ARRAYLIST_H

#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>

template<typename T>
class ArrayList{
private:
    int length{};
    int capacity{};
    T* items;

    //resize
    void expandArray(){
        T* newArr = new T[capacity+10];
        capacity += 10;
        for(int i=0; i<length; i++){
            newArr[i] = items[i];
        }
        delete[] items;
        items = newArr;
    }

public:
    ArrayList(){
        this->items = new T[10];
        this->length = 0;
        this->capacity = 10;
    }

    explicit ArrayList(int initialSize){
        if(initialSize < 0) throw std::invalid_argument( "Illegal initial size!" );
        this->items = new T[initialSize];
        this->length = 0;
        this->capacity = initialSize;
    }

    ArrayList(std::initializer_list<T> initializerList){
        items = new T[initializerList.size()];
        length = initializerList.length;
        for(int i=0; i<initializerList.size(); i++){
            items[i] = initializerList[i];
        }
    }

    ArrayList(ArrayList &other){
        items = new T[other.length];
        length = other.length;
        for(int i=0; i<other.length; i++){
            items[i] = other.items[i];
        }
    }

    ArrayList &operator=(ArrayList const &other){

    }

    ~ArrayList() {
        delete[] items;
    }

    //size
    int getLength() const{
        return length;
    }

    int getCapacity() const{
        return capacity;
    }

    //push_back
    void insert(T x){
        if(length == capacity){
            expandArray();
        }
        items[length] = x;
        length++;
    }

    void insertAt(int index, T x){
        if(index > length-1 || index < 0){
            throw std::invalid_argument( "Index out of bounds" );
        }
        items[index] = x;
    }

    //pop_back
    void removeLast(){
        if(isEmpty()){
            return;
        }

        length--;
    }

    void remove(int index){
        if(isEmpty()){
            return;
        }
        if(index > length-1 || index < 0){
            throw std::invalid_argument( "Index out of bounds" );
        }
        for(int i=index; i<length; i++){
            items[i] = items[i+1];
        }
        length--;
    }

    void removeRange(int startIndex, int endIndex){
        if(startIndex < 0 || endIndex > length-1 || startIndex > endIndex){
            throw std::invalid_argument( "Invalid range provided" );
        }
        int range = endIndex - startIndex + 1;
        for(int i=startIndex; i<length; i++){
            if(i+range < length){
                items[i] = items[i+range];
            }
        }
        length -= range;
    }


    void clear(){
        delete items;
        length = 0;
    }

    //empty
    bool isEmpty() const{
        return length == 0;
    }

    T& at(int index){
        if(isEmpty()) throw std::invalid_argument("Array is empty");
        if(index > length-1 || index < 0){
            throw std::invalid_argument("Index out of bounds");
        }
        return items[index];
    }

    void printAll(){
        if (this->length > 0){
            std::cout<<"[";
            for (int i=0; i<length; i++){
                std::cout<<items[i]<<", ";
            }
            std::cout<<"\b\b]"<<std::endl;
            return;
        }
        else{
            std::cout<<"[]"<<std::endl;
        }
    }

    T &operator[](int index) {
        if(isEmpty() || index < 0){
            throw std::invalid_argument("Index out of bounds");
        }
        if(index > length-1){
            expandArray();
        }
        return items[index];
    }

    void sortItems(){
        std::sort(items, items + length);
    }

    void sortItems(std::function<bool(T, T)> comparison){
        std::sort(items, items+length, comparison);
    }

    //front
    T first(){
        if (isEmpty()) throw std::invalid_argument("Is empty");
        return items[0];
    }

    T last(){
        if (isEmpty()) throw std::invalid_argument("Is empty");
        return items[length-1];
    }

    T firstN(int n){
        if (isEmpty()){
            throw std::invalid_argument("Array is empty!");
        }
        if(n>length){
            throw std::invalid_argument("Invalid number, the array has less items than specified");
        }

        T* arr = new T[n];
        for(int i=0; i<n; i++){
            arr[i] = items[i];
        }
        return arr;
    }

    void forEach(const std::function<T(T)>& function) const{
        for(int i=0; i<length; i++){
            items[i] = function(items[i]);
        }
    }

    //Ovo zanemari
    T* begin(){
        return items;
    }

    //Ovo zanemari
    T* end(){
        return items+length;
    }

    void removeIf(std::function<bool(T)> condition){
        for(int i=length-1; i>=0; i--){
            if(condition(items[i])){
                remove(i);
            }
        }
    }

};


#endif //ZADACA2_ARRAYLIST_H
