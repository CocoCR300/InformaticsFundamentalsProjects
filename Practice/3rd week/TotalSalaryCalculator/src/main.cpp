#include <functional>
#include <iostream>
#include <string>
#include <windows.h>

#include "common.h"

using namespace std;

bool saleValidator(float input);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // In C++, lambdas are structured like this: [capture](parameter list) -> return type { body }
    function baseSalaryValidationFunction([](float input) -> bool { return input > 0; });
    function saleValidationFunction(saleValidator);
    int numberOfSalesEntered = 1;
    float baseSalary = 0, commission, enteredSaleAmount = -1, salesTotal = 0;
    string userInput;

    userInputLoop(baseSalary, userInput, "Ingrese su sueldo base: ", baseSalaryValidationFunction);

    cout << "\nIngrese los montos de las ventas que realizó durante este mes, separe cada uno en una nueva línea "
            "pulsando la tecla 'Enter'.\nPara terminar de ingresar los valores, digite el número cero y pulse "
            "la tecla 'Enter'" << endl;

    while (enteredSaleAmount != 0)
    {
        string message = "Venta ";
        message += to_string(numberOfSalesEntered) + ": ";

        userInputLoop(enteredSaleAmount, userInput, message, saleValidationFunction);

        if (enteredSaleAmount != 0)
        {
            numberOfSalesEntered++;
            salesTotal += enteredSaleAmount;
        }
    }

    commission = salesTotal * 15 / 100;

    cout.precision(2);
    cout << fixed << "\nTotal de las ventas realizadas este mes: " << salesTotal <<
                     "\nComisión del 15% por el total de las ventas: " << commission <<
                     "\nSalario total (Sueldo base + comisión por ventas): " << baseSalary + commission << endl;

    system("pause");
    return 0;
}

bool saleValidator(float input)
{
    return input >= 0;
}
