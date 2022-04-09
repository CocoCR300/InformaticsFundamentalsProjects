// Imprimir un cuadro con base al número de asteriscos digitados por el usuario.
// Limite el número de asteriscos: mayor a 1 y menor a 5

#include <windows.h>

#include <common.h>

bool amountValidator(short);

int main()
{
    function amountValidationFunction(amountValidator);
    short amount;
    string userInput;

    SetConsoleOutputCP(CP_UTF8);

    userInputLoop(amount, userInput, "Digite el número de asteriscos deseados para el cuadrado: ", amountValidationFunction);

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            cout.width(2);
            cout << "*";
        }

        cout << "\n";
    }

    system("pause");

    return 0;
}

bool amountValidator(short amount)
{
    return amount > 1 && amount < 5;
}