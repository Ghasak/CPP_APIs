/**
 * This is the header file CreditCard.h, which contains the  definition of class CreditCard
 *
 */

#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H

#include <string>
#include <iostream>

class CreditCard
{
    public:
        // define your constructor
        CreditCard(const std::string& no, const std::string& nm, int lim, double bal = 0);

                std::string    getNumber()    const { return number ;}
                std::string    getName()      const { return name   ;}
                double         getBalance()   const { return balance;}
                int            getLimit()     const { return limit  ;}

                bool chargelt( double price);
                void makePayment(double payment);


    private:

        std::string number;
        std::string name;
        int         limit;
        double      balance;

};

std::ostream& operator << (std::ostream& out, const CreditCard& c);

#endif
