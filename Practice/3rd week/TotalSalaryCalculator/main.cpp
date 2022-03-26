#include <functional>
#include <iostream>
#include <string>

using namespace std;

bool saleValidator(float input);

template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   function<bool(T)>& inputValidationFunction);

int main()
{
    // In C++, lambdas are structured like this: [capture](parameter list) -> return type { body }
    function baseSalaryValidationFunction([](float input) -> bool { return input > 0; });
    function saleValidationFunction(saleValidator);
    int numberOfSalesEntered = 1;
    float baseSalary = 0, commission, enteredSaleAmount = -1, salesTotal = 0;
    string userInput;

    userInputLoop(baseSalary, userInput, "Ingrese su sueldo base: ", baseSalaryValidationFunction);

    cout << "\nIngrese los montos de las ventas que realizo durante este mes, separe cada uno en una nueva linea "
            "pulsando la tecla 'Enter'.\nPara terminar de ingresar los valores, digite el numero cero y pulse "
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
            "\nComision del 15% por el total de las ventas: " << commission <<
            "\nSalario total (Sueldo base + comision por ventas): " << baseSalary + commission << endl;

    system("pause");
    return 0;
}

bool saleValidator(float input)
{
    return input >= 0;
}

template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   function<bool(T)>& inputValidationFunction)
{
    bool success = false;
    size_t numberOfCharactersParsed;

    while (!success)
    {
        cout << inputRequestMessage;
        cin >> inputField;

        try
        {
            // NOTE: stof = String TO Float (I think...)
            backingField = stof(inputField, &numberOfCharactersParsed);

            success = inputField.length() == numberOfCharactersParsed
                      && inputValidationFunction(backingField);
        }
        catch (...)
        {
        }

        if (!success)
        {
            cout << "Entrada invalida, intentelo de nuevo" << endl;
        }
    }
}