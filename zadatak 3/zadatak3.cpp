#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "../zadatak 1/ArrayList.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

double randBetween(double min, double max){
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

class Person{
private:
    string name;
    string surname;
    int age;

public:
    const string &getName() const {
        return name;
    }

    void setName(const string &name_) {
        this->name = name_;
    }

    const string &getSurname() const {
        return surname;
    }

    void setSurname(const string &surname_) {
        this->surname = surname_;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age_) {
        this->age = age_;
    }

    string getFullName(){
        return name + " " + surname;
    }

    Person(string name, string surname, int age){
        this->name = std::move(name);
        this->surname = std::move(surname);
        this->age = age;
    }

    Person(){
        this->name = "";
        this->surname = "";
        this->age = 0;
    }
};

class Car{
private:
    string model;
    string color;
    int productionYear;

public:
    const string &getModel() const {
        return model;
    }

    void setModel(const string &model_) {
        this->model = model_;
    }

    string getColor() const {
        return color;
    }

    void setColor(string color_) {
        this->color = std::move(color_);
    }

    int getProductionYear() const {
        return productionYear;
    }

    void setProductionYear(int year) {
        this->productionYear = year;
    }

    Car(string model, string color, int productionYear){
        this->model = std::move(model);
        this->color = std::move(color);
        this->productionYear = productionYear;
    }

    Car(){
        this->model = "";
        this->color = "red";
        this->productionYear = 1900;
    }

    string toString(){
        return this->color + " " + this->model + " (" + std::to_string(this->productionYear) + ")";
    }
};

class Driver : public Person {
private:
    int yearsOfExperience;
    Car car;
    double time;

public:
    int getYearsOfExperience() const {
        return yearsOfExperience;
    }

    void setYearsOfExperience(int years) {
        this->yearsOfExperience = years;
    }

    const Car &getCar() const {
        return car;
    }

    void setCar(const Car &car_) {
        this->car = car_;
    }

    double getTime() const {
        return time;
    }

    void setTime(double time_) {
        this->time = time_;
    }

    Driver() : Person(){
        this->yearsOfExperience = 0;
        this->car = Car();
        this->time = 0.0;
    }

    Driver(string name, string surname, int age, int yearsOfExperience, Car car, double time = 0.0) : Person(std::move(name),std::move(surname), age){
        this->yearsOfExperience = yearsOfExperience;
        this->car = std::move(car);
        this->time = time;
    }

    static Driver createDriver(){
        string name, surname, model, color;
        int age, yearManufactured, yearsOfExperience;

        cout<<"Input driver name: ";
        cin>>name;
        cout<<"Input driver surname: ";
        cin>>surname;
        cout<<"Input driver age: ";
        cin>>age;
        cout<<"Input driver years of experience: ";
        cin>>yearsOfExperience;
        //*****************
        cout<<"Input car model: ";
        cin>>model;
        cout<<"Input car manufacturing year: ";
        cin>>yearManufactured;
        cout<<"Input car color: ";
        cin>>color;

        Car car = Car(model, color, yearManufactured);
        Driver driver = Driver(name, surname, age, yearsOfExperience, car);
        return driver;
    }

    string toString(){
        return this->getFullName() + ", aged " + std::to_string(this->getAge()) + ", drives a " + this->car.toString()
               + " and has " + std::to_string(this->yearsOfExperience) + " years of experience.\n";
    }
};

void simulateRace(ArrayList<Driver>& drivers){
    for(auto &driver : drivers){
        double time = randBetween(1,2);
        cout<<time<<endl;
        driver.setTime(time);
    }

    drivers.sortItems([]( const Driver& lhs, const Driver& rhs){
        return lhs.getTime() < rhs.getTime();
    });


    int position = 1;
    cout<<"*********RACE RESULTS*********"<<endl;
    for(const auto& driver : drivers){
        cout<<position<<". "<<driver.getName() + " " + driver.getSurname() + " (" + std::to_string(driver.getTime()) + ")"<<endl;
        position++;
    }
}
/*
int main() {
    ArrayList<Driver> drivers;

    srand( time ( nullptr));

    for (int i=0; i<3; i++){
        cout<<"INPUT DRIVER DETAILS: "<<endl;
        Driver d = Driver::createDriver();
        drivers.insert(d);
    }

    for(auto driver : drivers){
        cout<<driver.toString();
    }

    simulateRace(drivers);

    return 0;
}
*/