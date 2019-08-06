
/**
 * The file CreditCard.cpp, which contains the defintion of out-of-class memeber functions
 * for class CreditCard
 */

#include "CreditCard.h"

using namespace std;

CreditCard::CreditCard(const string& no, const string& nm, int lim, double bal)
{
    number  = no;
    name    = nm;
    balance = bal;
    limit   = lim;

}

bool CreditCard::chargelt(double price)
{
    if (price + balance > double (limit))
        return false;

    balance += price;
        return true;

}

void CreditCard::makePayment(double payment)
{
    balance -= payment ;

}

ostream& operator << (ostream& out, const CreditCard& c)
{
    out << "Number  = "    << c.getNumber() << endl;
    out << "Name    = "    << c.getName() << endl;
    out << "Balance = "    << c.getBalance() << endl;
    out << "Limit   = "    << c.getLimit() << endl;


    return out;
}
