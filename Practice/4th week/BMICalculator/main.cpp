#include <cmath>
#include <iostream>
#include <windows.h>

#include <common.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    float height, weight, bmi;
    function weightValidationFunction([](float input) -> bool { return input > 0 && input < 1000; });
    function heightValidationFunction([](float input) -> bool { return input > 0 && input <= 3; });
    string inputField, message;

    userInputLoop(height, inputField, "Ingrese su altura (en metros): ", weightValidationFunction);
    userInputLoop(weight, inputField, "Ingrese su peso (en kilogramos): ", weightValidationFunction);

    bmi = weight / (pow(height, 2));

    if (bmi < 18.5)
    {
        message = "Infrapeso";
    }
    else if (bmi < 25)
    {
        message = "Peso normal";
    }
    else if (bmi < 30)
    {
        message = "Sobrepeso";
    }
    else if (bmi < 40)
    {
        message = "Obesidad";
    }
    else
    {
        message = "Obesidad mórbida";
    }

    cout.precision(2);
    cout << "Su IMC es de " << bmi << " y entra en la clasificación de: " << message << endl;
    system("pause");

    return 0;
}
