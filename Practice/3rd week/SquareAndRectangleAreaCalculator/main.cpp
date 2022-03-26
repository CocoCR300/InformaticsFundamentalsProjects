#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    short selection = -1;

    cout << "Elija una figura para calcular su area:\n0. Cuadrado\n1. Rectangulo\n" << endl;

    while (selection != 0 && selection != 1)
    {
        cin >> selection;

        if (selection != 0 && selection != 1)
        {
            cout << "Opcion invalida, intentelo de nuevo: ";
        }
    }

    if (selection == 0)
    {
        float side;

        cout << "Ingrese la medida del lado: ";
        cin >> side;

        cout << "\nEl area del cuadrado es de: " << pow(side, 2);
    }
    else
    {
        float length, width;

        cout << "Ingrese la medida del largo: ";
        cin >> length;

        cout << "\nIngrese la medida del ancho: ";
        cin >> width;

        cout << "\nEl area del rectangulo es de: " << length * width;
    }

    system("pause");
    return 0;
}
