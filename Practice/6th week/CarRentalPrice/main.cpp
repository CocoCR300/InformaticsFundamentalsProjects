#include <windows.h>

#include <common.h>

#pragma region Macros
#define CIVIL_LIABILITY_COST 5000
#define FEE_PERCENTAGE 0.15
#define INSURANCE_PERCENTAGE 0.05
#define TAX_PERCENTAGE 0.13
#pragma endregion Macros

#pragma region Function declarations
template <class T>
bool higherThanZeroValidator(const T&);

bool yesOrNoInputRequest(char&, const string&, const string& = INVALID_INPUT_MESSAGE);

float calculateCosts(float&, float&, float&, float&, float, short, bool, bool);

void calculateCostsAndPrintInformation(const string&, float, short, bool, bool);
#pragma endregion Function declarations

int main()
{
    bool userWantsInsurance, userWantsCivilLiability;
    char option;
    float dailyCost;
    short rentalDays;
    string fullName, userInput;

    SetConsoleOutputCP(CP_UTF8);

    cout << "Ingrese su nombre completo: ";
    getline(cin, fullName);

    dailyCost = userInputLoop<float>(userInput, "Ingrese el costo diario por la renta del vehículo: ", higherThanZeroValidator<float>);

    rentalDays = userInputLoop<short>(userInput, "Ingrese la cantidad de días de renta del vehículo: ", higherThanZeroValidator<short>);

    userWantsInsurance = yesOrNoInputRequest(option,
         "¿Desea adquirir la protección extra en carretera? La misma tiene un costo del 5% sobre el costo del vehiculo (S/n): ");

    userWantsCivilLiability = yesOrNoInputRequest(option,
          "¿Desea adquirir el seguro de responsabilidad civil ante terceros? El mismo tiene un costo fijo de 5000 colones (S/n): ");

    cout.precision(2);
    calculateCostsAndPrintInformation(fullName, dailyCost, rentalDays, userWantsInsurance, userWantsCivilLiability);

    return 0;
}

#pragma region Function definitions
template <class T>
bool higherThanZeroValidator(const T& price)
{
    return price > 0;
}

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