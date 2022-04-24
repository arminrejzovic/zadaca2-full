#include <iostream>
#include "../zadatak 1/ArrayList.h"

class Worker{
private:
    std::string name;
    std::string surname;
    int age;
    int yearsOfExperience;
    std::string phone;
    double wage;

public:
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name_) {
        this->name = name_;
    }

    const std::string &getSurname() const {
        return surname;
    }

    void setSurname(const std::string &surname_) {
        this->surname = surname_;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age_) {
        this->age = age_;
    }

    int getYearsOfExperience() const {
        return yearsOfExperience;
    }

    void setYearsOfExperience(int yearsOfExperience_) {
        this->yearsOfExperience = yearsOfExperience_;
    }

    const std::string &getPhone() const {
        return phone;
    }

    void setPhone(const std::string &phone_) {
        this->phone = phone_;
    }

    double getWage() const {
        return wage;
    }

    void setWage(double wage_){
        this->wage = wage_;
    }

    Worker(const std::string &name, const std::string &surname, int age, int yearsOfExperience, const std::string &phone, double wage) {
        this->name = name;
        this->surname = surname;
        this->age = age;
        this->yearsOfExperience = yearsOfExperience;
        this->phone = phone;
        this->wage = wage;
    }

    Worker(){
        this->name = "";
        this->surname = "";
        this->age = 18;
        this->yearsOfExperience = 1;
        this->phone = "061-123-456";
        this->wage = 500;
    }

    std::string toString(){
        return name + " " + surname + " (" + std::to_string(age) + ")" + " earns " + std::to_string(wage) + " after " +
               std::to_string(yearsOfExperience) + " years of experience";
    }

    void applyBonus(double percentage){
        this->wage = wage + ((wage*percentage)/100.0);
    }

    std::string getFullName() const{
        return name + " " + surname;
    }
};

std::ostream& operator<<(std::ostream& os, const Worker& w)
{
    os << w.getName() + " " + w.getSurname() + " (" + std::to_string(w.getAge()) + ")" + " earns " + std::to_string(w.getWage()) + " after " +
          std::to_string(w.getYearsOfExperience()) + " years of experience"<<std::endl;
    return os;
}

#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

void readWorkersFromFile(ArrayList<Worker>& workers, std::ifstream &stream){
    std::string line;
    while(std::getline(stream,line)){
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream stringstream(line);
        std::string name, surname, ageStr, yearsExperienceStr, phone;

        stringstream>>name>>surname>>ageStr>>yearsExperienceStr>>phone;
        Worker temp = Worker(name, surname, std::stoi(ageStr), std::stoi(yearsExperienceStr), phone, 1000);
        workers.insert(temp);
    }
}

int main() {
    std::ifstream acme{R"(C:\Users\armin\CLionProjects\acme-globex-merger\acme.txt)"};
    std::ifstream globex{R"(C:\Users\armin\CLionProjects\acme-globex-merger\globex.txt)"};
    std::ofstream fout{R"(C:\Users\armin\CLionProjects\acme-globex-merger\corp.txt)"};

    ArrayList<Worker> corpWorkers;

    readWorkersFromFile(corpWorkers, acme);
    readWorkersFromFile(corpWorkers, globex);

    // Sortiranje po godinama
    corpWorkers.sortItems([]( const Worker& lhs, const Worker& rhs ){
        return lhs.getAge() < rhs.getAge();
    });

    corpWorkers.printAll();

    // Penzionisanje starijih od 55
    corpWorkers.removeIf([](const Worker& w) -> bool {
        return w.getAge()>55;
    });

    corpWorkers.printAll();

    // Primjena bonusa za 15 najmlađih i sve sa preko 15 godina iskustva
    for(int i=0; i<corpWorkers.getLength(); i++){
        if(i<15){
            std::cout<<"Applying 10% bonus to " << corpWorkers[i].getFullName()<<std::endl;
            corpWorkers[i].applyBonus(10);
        }
        if(corpWorkers.at(i).getYearsOfExperience() > 15){
            corpWorkers[i].applyBonus(20);
        }
    }

    corpWorkers.printAll();

    // Sortiranje po imenu i prezimenu
    corpWorkers.sortItems([]( const Worker& lhs, const Worker& rhs ){
        return lhs.getFullName() < rhs.getFullName();
    });


    // Ispis svih radnika u fajl
    fout<<"CORP Inc."<<std::endl;
    for(auto w : corpWorkers){
        fout<<w.toString()<<std::endl;
    }

    return 0;
}