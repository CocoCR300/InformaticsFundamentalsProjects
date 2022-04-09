// Imprimir los números del 1 al 10 de forma descendente. 10, 9 , 8...

#include <iostream>

using namespace std;

int main()
{
    int number = 10;

    while (number)
    {
        cout << number--;

        if (number)
        {
            cout << ", ";
        }
        else
        {
            cout << "." << endl;
        }
    }

    system("pause");

    return 0;
}
