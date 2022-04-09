// Mediante la estructura cíclica for, implementar la tabla del 2.
// Visualizar el resultado de la siguiente manera:
// 2 x 1 = 2
// 2 x 2 = 4
// Utilice una variable contadora para imprimir los números representados de color rojo

#include <iostream>

using namespace std;

void printMultiplicationTable(short);

int main()
{
    printMultiplicationTable(2);

    system("pause");

    return 0;
}

void printMultiplicationTable(short tableNumber)
{
    short result;

    for (short i = 1; i < 11; i++)
    {
        result = i * tableNumber;
        cout << tableNumber << " x " << i << " = " << result << "\n";
    }
}
