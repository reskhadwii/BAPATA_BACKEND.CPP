#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include<string>

using namespace std;

class Product{
    private:
        int id;
        string name;
        double price;
        int stock;
        string description;
    public:
        Product(){}

         Product(int pid, string pname, double pprice, int pstock, string pdesc){
            id = pid;
            name = pname;
            price = pprice;
            stock = pstock;
            description = pdesc;
            }

        //ambil data
        int getId() {return id;}
        string getName() {return name;}
        double getPrice() {return price;}
        int getStock() {return stock;}
        string getDescription() {return description;}
        
        //ubah data
        void setId(int pid) {id = pid;}
        void setName(string pname) {name = pname;}
        void setPrice(double pprice) {price = pprice;} 
        void setStock(int pstock) {stock = pstock;}
        void setDescription(string pdesc) {description = pdesc;}
};

#endif