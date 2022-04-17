// Universidad Nacional de Costa Rica - Sede Liberia
// Evaluación n°2 del curso Fundamentos de informatica (EIF200)
// I ciclo, año 2022
// Oscar Rojas Alvarado
//
// Elabore un programa en C++, que le permita calcular al usuario el monto a pagar por la
// renta de un vehículo.
// Solicite al usuario su nombre completo (con espacios, ver manual).
// Tome en cuenta la siguiente información para calcular el costo de la renta:
// * El alquiler del vehículo tiene un costo por día.
// * A ese costo debe calcularse el monto de impuestos y tarifas que corresponde a un
//   15% de tarifas, y el 13% de impuesto.
// * Añadido al monto anterior, Si el usuario desea adquirir la extra de protección en
//   carretera, puede hacerlo pagando un 5% más sobre el costo del vehículo.
// * También existe la posibilidad que el usuario pague un monto extra por el seguro
//   de responsabilidad civil ante terceros, el cual es un monto fijo de 5000 colones.
// Mostrar al usuario el nombre completo junto con el desglose del pago: días rentados,
// costo del alquiler (por día y por el total de días rentados), tarifas, impuestos, y extras en
// caso de haberlas adquirido (especifique la extra y el monto) y por ultimo despliegue el total.
// Crear la función junto al main, que le permita realizar los cálculos del alquiler. Solicite al
// usuario los datos necesarios, documente el código y aplique buenas prácticas.

#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <windows.h>

using namespace std;

#pragma region Macros
#define CIVIL_LIABILITY_COST 5000
#define FEE_PERCENTAGE 0.15
#define INSURANCE_PERCENTAGE 0.05
#define INVALID_INPUT_MESSAGE "Entrada inválida, intentelo de nuevo"
#define TAX_PERCENTAGE 0.13
#pragma endregion Macros

#pragma region Function declarations
template <class T>
bool higherThanZeroValidator(const T&);

bool yesOrNoInputRequest(char&, const string&, const string& = INVALID_INPUT_MESSAGE);

float calculateCosts(float&, float&, float&, float&, float, short, bool, bool);

template <class T>
T userInputLoop(string&, const string&, const function<bool(const T&)>&, const string& = INVALID_INPUT_MESSAGE);

void calculateCostsAndPrintInformation(const string&, float, short, bool, bool);
#pragma endregion Function declarations

#pragma region userInputLoop specializations
// Solicita al usuario un número que esté entre el rango del tipo "float" y que cumpla con las condiciones de
// "inputValidationFunction". Si un número inválido es ingresado, se le presenta una advertencia al usuario y se
// vuelve a solicitar el número
template<>
float userInputLoop<float>(string& inputField, const string& inputRequestMessage,
                           const function<bool(const float&)>& inputValidationFunction,
                           const string& invalidInputMessage)
{
    volatile bool success = false;
    float result;
    size_t numberOfCharactersParsed;

    while (!success)
    {
        cout << inputRequestMessage;
        cin >> inputField;

        try
        {
            result = stof(inputField, &numberOfCharactersParsed);

            success = inputField.length() == numberOfCharactersParsed
                      && inputValidationFunction(result);
        }
        catch (...)
        {
        }

        if (!success)
        {
            cout << invalidInputMessage << "\n";
        }
    }

    return result;
}

// Solicita al usuario un número que esté entre los rangos del tipo "short" y que cumpla con las condiciones de
// "inputValidationFunction". Si un número inválido es ingresado, se le presenta una advertencia al usuario y se
// vuelve a solicitar el número
template<>
short userInputLoop<short>(string& inputField, const string& inputRequestMessage,
                           const function<bool(const short&)>& inputValidationFunction,
                           const string& invalidInputMessage)
{
    volatile bool success = false;
    int result;
    size_t numberOfCharactersParsed;

    while (!success)
    {
        cout << inputRequestMessage;
        cin >> inputField;

        try
        {
            result = stoi(inputField, &numberOfCharactersParsed);

            success = inputField.length() == numberOfCharactersParsed
                      && result >= numeric_limits<short>::min()
                      && result <= numeric_limits<short>::max()
                      && inputValidationFunction(result);
        }
        catch (...)
        {
        }

        if (!success)
        {
            cout << invalidInputMessage << "\n";
        }
    }

    return result;
}
#pragma endregion userInputLoop specializations

int main()
{
    bool userWantsInsurance, userWantsCivilLiability;
    char option;
    float dailyCost;
    short rentalDays;
    string fullName, userInput;

    // Se establece el formato de codificación de caracteres de la consola a UTF8 para que admita caracteres especiales,
    // como las letras tildadas
    SetConsoleOutputCP(CP_UTF8);

    cout << "Ingrese su nombre completo: ";
    getline(cin, fullName);

    dailyCost = userInputLoop<float>(userInput, "Ingrese el costo diario por la renta del vehículo: ",
                                     higherThanZeroValidator<float>);

    rentalDays = userInputLoop<short>(userInput, "Ingrese la cantidad de días de renta del vehículo: ",
                                      higherThanZeroValidator<short>);

    userWantsInsurance = yesOrNoInputRequest(option,
         "¿Desea adquirir la protección extra en carretera? La misma tiene un costo del 5% sobre el costo del vehiculo (S/n): ");

    userWantsCivilLiability = yesOrNoInputRequest(option,
          "¿Desea adquirir el seguro de responsabilidad civil ante terceros? El mismo tiene un costo fijo de 5000 colones (S/n): ");

    cout.precision(2);
    calculateCostsAndPrintInformation(fullName, dailyCost, rentalDays, userWantsInsurance, userWantsCivilLiability);

    return 0;
}

#pragma region Function definitions
// Devuelve un valor booleano indicando si el valor contenido en "amount" es mayor a cero
template <class T>
bool higherThanZeroValidator(const T& amount)
{
    return amount > 0;
}

// Solicita una entrada por teclado de algún caracter y válida si es una letra "S", "N" o el caracter de salto de
// línea "\n", devolviendo un valor booleano verdadero si el caracter es "S" o el salto de línea "\n", o falso, si
// el caracter es "N", para cualquier otro caracter, se vuelve a solicitar otra entrada por teclado
bool yesOrNoInputRequest(char& option, const string& inputRequestMessage, const string& invalidInputMessage)
{
    bool success = false, wasTheLetterNTyped;
    char optionUppercase;

    while (!success)
    {
        cout << inputRequestMessage;
        cin.sync();
        cin.get(option);

        optionUppercase = toupper(option);

        wasTheLetterNTyped = optionUppercase == 'N';

        success = optionUppercase == 'S' || wasTheLetterNTyped || option == '\n';

        if (!success)
        {
            cout << invalidInputMessage << "\n";
        }
    }

    return !wasTheLetterNTyped;
}

// Calcula y devuelve el costo total de la renta, además de almacenar en "costPerRentalDays", "fee", "tax" y
// "insuranceCost" las cantidades correspondientes, con base en los parametros solicitados, usando los valores de las
// macros "FEE_PERCENTAGE", "TAX_PERCENTAGE", "INSURANCE_PERCENTAGE" y "CIVIL_LIABILITY_COST"
float calculateCosts(float& costPerRentalDays, float& fee, float& tax, float& insuranceCost, const float dailyCost,
                     const short rentalDays, const bool userWantsInsurance, const bool userWantsCivilLiability)
{
    float totalCost = 0;

    totalCost += costPerRentalDays = dailyCost * rentalDays;
    totalCost += fee = dailyCost * FEE_PERCENTAGE;
    totalCost += tax = dailyCost * TAX_PERCENTAGE;

    if (userWantsInsurance)
    {
        totalCost += insuranceCost = dailyCost * INSURANCE_PERCENTAGE;
    }

    if (userWantsCivilLiability)
    {
        totalCost += CIVIL_LIABILITY_COST;
    }

    return totalCost;
}

// Llama a la función "calculateCosts" y muestra la información obtenida a través de la consola
void calculateCostsAndPrintInformation(const string& userFullName, const float dailyCost, const short rentalDays,
                                       const bool userWantsInsurance, const bool userWantsCivilLiability)
{
    float costPerRentalDays, fee, insuranceCost, tax, totalCost = calculateCosts(costPerRentalDays, fee, tax,
                                                                                 insuranceCost, dailyCost, rentalDays,
                                                                                 userWantsInsurance,
                                                                                 userWantsCivilLiability);

    cout << fixed << "\nNombre completo: " << userFullName << "\nCantidad de días de renta del vehículo: " << rentalDays
         << "\nCosto diario por renta del vehículo: " << dailyCost << " colones"
         << "\nCosto por el total de días de renta: " << costPerRentalDays << " colones"
         << "\nTarifas: " << fee << " colones"
         << "\nImpuestos: " << tax << " colones"
         << "\n¿El usuario desea adquirir la protección extra en carretera? (";

    if (userWantsInsurance)
    {
        cout << "Sí): " << insuranceCost << " colones adicionales";
    }
    else
    {
        cout << "No): Sin costo adicional";
    }

    cout << "\n¿El usuario desea adquirir el seguro de responsabilidad civil ante terceros? ("
         << (userWantsCivilLiability ? ("Sí): " + to_string(CIVIL_LIABILITY_COST) + " colones adicionales") : "No): Sin costo adicional")
         << "\nCosto total: " << totalCost << endl;
}
#pragma endregion Function definitions