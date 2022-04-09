#include <cmath>
#include <windows.h>

#include <common.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    function selectionValidationFunction([](short input) -> bool { return input == 0 || input == 1; });
    short selection = -1;
    string selectionAsString;
    cout << "Elija una figura para calcular su area:\n0. Cuadrado\n1. Rectangulo\n" << endl;

    while (selection != 0 && selection != 1)
    {
        userInputLoop(selection, selectionAsString, "", selectionValidationFunction);
    }

    if (selection == 0)
    {
        float side;

        cout << "Ingrese la medida del lado: ";
        cin >> side;

        cout << "\nEl area del cuadrado es de: " << pow(side, 2) << endl;
    }
    else
    {
        float length, width;

        cout << "Ingrese la medida del largo: ";
        cin >> length;

        cout << "\nIngrese la medida del ancho: ";
        cin >> width;

        cout << "\nEl area del rectangulo es de: " << length * width << endl;
    }

    system("pause");
    return 0;
}
