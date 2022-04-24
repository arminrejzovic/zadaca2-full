#include <iostream>
#include <cmath>
#include <sstream>
#include "../zadatak 1/ArrayList.h"

class Polynomial{
private:
    ArrayList<int> coefficients;

    static int ddx(int power, int coefficient){
        if(power == 0) {
            return 0;
        }
        if(power == 1) {
            return coefficient;
        }
        return power*coefficient;
    }

    static std::string stringifyExpression(int degree, int coefficient){
        std::stringstream ss;
        if(degree==0){
            ss<<coefficient;
            return ss.str();
        }

        if(coefficient != 1){
            ss<<coefficient;
        }
        ss<<"x";
        if(degree != 1){
            ss<<"^"<<degree;
        }

        return ss.str();
    }

public:

    Polynomial() = default;

    explicit Polynomial(ArrayList<int> coefficients_){
        for(auto coeff: coefficients_){
            coefficients.insert(coeff);
        }
    }

    Polynomial(std::initializer_list<int> coefficients_){
        for(auto coeff : coefficients_){
            coefficients.insert(coeff);
        }
    }

    Polynomial add(Polynomial& other){
        Polynomial result(coefficients);
        if(coefficients.getLength() > other.coefficients.getLength()){
            for(int i=0; i<other.coefficients.getLength(); i++){
                result.coefficients[i] += other.coefficients[i];
            }
        }
        else{
            for(int i=0; i<coefficients.getLength(); i++){
                result.coefficients[i] += other.coefficients[i];
            }
            for(int i=coefficients.getLength(); i<other.coefficients.getLength(); i++){
                result.coefficients.insert(other.coefficients[i]);
            }
        }
        return result;
    }

    Polynomial subtract(Polynomial& other){
        Polynomial result(coefficients);
        if(coefficients.getLength() > other.coefficients.getLength()){
            for(int i=0; i<other.coefficients.getLength(); i++){
                result.coefficients[i] -= other.coefficients[i];
            }
        }
        else{
            for(int i=0; i<coefficients.getLength(); i++){
                result.coefficients[i] -= other.coefficients[i];
            }
            for(int i=coefficients.getLength(); i<other.coefficients.getLength(); i++){
                result.coefficients.insert(other.coefficients[i]);
            }
        }
        return result;
    }

    ArrayList<int> getCoefficients(){
        return coefficients;
    }

    Polynomial derivative(){
        ArrayList<int> newCoeffs;
        for(int i=1; i<coefficients.getLength(); i++){
            newCoeffs.insert(ddx(i,coefficients[i]));
        }
        //Polynomial(newCoeffs);
        return *this;
    }

    Polynomial multiply(Polynomial& other){
        Polynomial result;
        for(int i=0; i<coefficients.getLength(); i++){
            Polynomial current;
            for(int k=0; k<i; k++){
                current.addCoefficient(0);
            }
            for(auto coeff : other.coefficients){
                current.addCoefficient(coefficients[i]*coeff);
            }
            result.add(current);
        }
        return result;
    }

    void addCoefficient(int degree, int coefficient){
        coefficients.insertAt(degree, coefficient);
    }

    void addCoefficient(int coefficient){
        coefficients.insert(coefficient);
    }

    double operator() (double x){
        double result=0;
        for(int i=0; i<coefficients.getLength(); i++){
            result += coefficients[i] * std::pow(x,i);
        }
        return result;
    }

    void print(){
        std::stringstream ss;
        for(int i=0; i<coefficients.getLength(); i++){
            if(coefficients[i] == 0){
                continue;
            }
            ss << stringifyExpression(i, coefficients[i]);
            if(i<coefficients.getLength()-1){
                ss<<" + ";
            }
        }
        std::cout<<ss.str()<<std::endl;
    }

    void printHighestFirst(){
        std::stringstream ss;
        for(int i=coefficients.getLength()-1; i>0; i--){
            if(coefficients[i] == 0){
                continue;
            }
            ss << stringifyExpression(i, coefficients[i]);
            if(i>0){
                ss<<" + ";
            }
        }
        if(coefficients.first() != 0){
            ss<<coefficients.first();
        } else{
            ss.seekp(-3, std::ios_base::end);
            ss<<"   ";
        }
        std::cout<<ss.str()<<std::endl;
    }
};

/*
void testAdding(Polynomial p1, Polynomial p2){
    std::cout<<"***************** ADDITION *****************"<<std::endl;
    std::cout<<"Before addition: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();

    std::cout<<"After addition: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();
    p1.add(p2).printHighestFirst();
}

void testSubtract(Polynomial p1, Polynomial p2){
    std::cout<<"***************** SUBTRACTION *****************"<<std::endl;
    std::cout<<"Before subtraction: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();

    Polynomial p3 = p1.subtract(p2);

    std::cout<<"After subtraction: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();
    p3.printHighestFirst();
}

void testMultiply(Polynomial p1, Polynomial p2){
    std::cout<<"***************** MULTIPLICATION *****************"<<std::endl;
    std::cout<<"Before multiplication: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();

    Polynomial p3 = p1.multiply(p2);

    std::cout<<"After multiplication: "<<std::endl;
    p1.printHighestFirst();
    p2.printHighestFirst();
    p3.printHighestFirst();
}

void testBracesOperator(Polynomial p, double x){
    std::cout<<"***************** P(x) *****************"<<std::endl;
    p.printHighestFirst();
    std::cout<<"P("<<x<<") = " << p(x)<<std::endl;
}

void testDerivative(Polynomial p){
    std::cout<<"***************** DERIVATIVE *****************"<<std::endl;
    std::cout<<"y = "; p.printHighestFirst();
    std::cout<<"y' = "; p.derivative().printHighestFirst();
}


int main() {
    Polynomial p1{1,5,0,1};
    Polynomial p2{0,2,5};

    testAdding(p1, p2);
    testSubtract(p1,p2);
    testSubtract(p2, p2);
    testBracesOperator(p1, 4);
    testDerivative(p1);

    return 0;
}
*/