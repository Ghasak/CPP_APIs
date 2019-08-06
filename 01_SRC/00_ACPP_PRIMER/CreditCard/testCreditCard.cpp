/**
 * The file CreditCard.cpp, which contains the defintion of out-of-class member
 * for class CreditCard.
 */

#include <vector>
#include "CreditCard.cpp"

using namespace std;

void testCard()
{
    vector<CreditCard*> wallet(10);

    wallet[0] = new CreditCard("5391-0375-9387-5309", "John Bowman", 2500);
    wallet[1] = new CreditCard("5391-0375-9387-1212", "John Bowman", 5000);
    wallet[2] = new CreditCard("5391-0375-9387-4232", "John Bowman", 2322);

    for (int j = 1; j <= 16; j++)
    {
        wallet[0] -> chargelt(double(j));
        wallet[1] -> chargelt(2 *j);
        wallet[2] -> chargelt(double(3 * j));

    }
    cout << *wallet[0] << endl;
    cout << *wallet[1] << endl;
    cout << *wallet[2] << endl;

}

int main()
{
    testCard();
    return EXIT_SUCCESS;
}
