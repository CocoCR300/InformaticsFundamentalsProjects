// Crear un menú enciclado mediante el switch/case con las opciones:
// 1. Realizar compra
// 2. Salir
// La opción Realizar compra debe solicitar al usuario, el precio de los artículos, luego calcular y
// mostrar el total a pagar y la cantidad de artículos comprados.

#include <windows.h>

#include <common.h>

bool optionValidator(short);

bool priceValidator(short);

void printMenu();

int main()
{
    function optionValidationFunction(optionValidator), priceValidationFunction(priceValidator);
    short option = 0, price = -1, totalPrice = 0;
    string userInput;

    SetConsoleOutputCP(CP_UTF8);

    while(option != 2)
    {
        printMenu();
        userInputLoop(option, userInput, "Opción: ", optionValidationFunction);

        if (option == 1)
        {
            short itemsCount = 0;

            cout << "Ingrese el precio de los articulos a comprar, sepárelos presionando la tecla ENTER."
                    " Para concluir, ingrese cero";

            while (price != 0)
            {
                userInputLoop(price, userInput, "\nArticulo n° " + to_string(itemsCount) + ": ", priceValidationFunction);
                totalPrice += price;

                if (price != 0)
                {
                    itemsCount++;
                }
            }

            cout << "\nCantidad de articulos: " << itemsCount << "\nTotal: " << totalPrice << "\n\n";
        }
    }

    cout << "¡¡Gracias por su preferencia!!" << endl;

    system("pause");

    return 0;
}

bool optionValidator(short option)
{
    return option == 1 || option == 2;
}

bool priceValidator(short price)
{
    return price > -1;
}

void printMenu()
{
    cout << "=========== Menú ===========\n" << "1. Realizar compra\n2. Salir\n\n";
}
