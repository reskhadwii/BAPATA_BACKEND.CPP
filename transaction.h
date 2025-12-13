#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction{
    private: 
        int id;
        string username;
        double totalAmount;
        string itemsDetail;
        string paymentMethod;
        string status;
    public:
        Transaction(){}
            Transaction(int tid, string tuser, double ttotal, string titems, string tpay, string tstat){
                id = tid;
                username = tuser;
                totalAmount = ttotal;
                itemsDetail = titems;
                paymentMethod = tpay;
                status = tstat;
            }

            int getId(){return id;}
            string getUsername(){return username;}
            double getTotal(){return totalAmount;}
            string getItemsDetail(){return itemsDetail;}
            string getPaymentMethod(){return paymentMethod;}
            string getStatus(){return status;}

            void setStatus(string newStatus){status = newStatus;}
};

#endif