#include <windows.h>

#include <common.h>

#define FEE_PERCENTAGE 0.15
#define TAX_PERCENTAGE 0.13
#define INSURANCE_PERCENTAGE 0.05
#define CIVIL_LIABILITY_COST 5000

template <class T>
bool higherThanZeroValidator(const T&);

bool yesOrNoInputRequest(char&, const string&, function<bool(const char&)>&);

float calculateTotalCost(float&, float&, float&, float&, float, short, bool, bool);

int main()
{
    bool userWantsInsurance, userWantsCivilLiability;
    char option;
    float costPerRentalDays, dailyCost, fee, insuranceCost, tax, totalPrice;
    function yesOrNoSelectionFunction([](const char& input) -> bool { return toupper(input) == 'S' || input == '\n'; });
    short rentalDays;
    string fullName, userInput;

    SetConsoleOutputCP(CP_UTF8);

    cout << "Ingrese su nombre completo: ";
    getline(cin, fullName, '\n');

    dailyCost = userInputLoop<float>(userInput, "Ingrese el costo diario por la renta del vehículo: ", higherThanZeroValidator<float>);

    rentalDays = userInputLoop<short>(userInput, "Ingrese la cantidad de días de renta del vehículo: ", higherThanZeroValidator<short>);

    userWantsInsurance = yesOrNoInputRequest(option,
         "¿Desea adquirir la protección extra en carretera? La misma tiene un costo del 5% sobre el costo del vehiculo (S/n): ",
         yesOrNoSelectionFunction);

    userWantsCivilLiability = yesOrNoInputRequest(option,
          "¿Desea adquirir el seguro de responsabilidad civil ante terceros? El mismo tiene un costo fijo de 5000 colones (S/n): ",
          yesOrNoSelectionFunction);

    totalPrice = calculateTotalCost(costPerRentalDays, fee, tax, insuranceCost, dailyCost, rentalDays, userWantsInsurance,
                                    userWantsCivilLiability);

    cout.precision(2);
    cout << fixed << "\nNombre completo: " << fullName << "\nCantidad de días de renta del vehículo: " << rentalDays
         << "\nCosto diario por alquiler del vehículo: " << dailyCost << " colones"
         << "\nCosto por el total de días de renta: " << costPerRentalDays << "colones"
         << "\nTarifas: " << fee << "colones"
         << "\nImpuestos: " << tax << "colones"
         <<"\n¿El usuario desea adquirir la protección extra en carretera? (";

    if (userWantsInsurance)
    {
        cout << "Sí): " << insuranceCost << " colones adicionales";
    }
    else
    {
        cout << "No): Sin costo adicional";
    }

    cout << "\n¿El usuario desea adquirir el seguro de responsabilidad civil ante terceros? ("
         << (userWantsCivilLiability ? ("Sí): " + to_string(CIVIL_LIABILITY_COST) + " colones adicionales") : "No): Sin costo adicional");

    cout << "\nCosto total: " << totalPrice << endl;

    return 0;
}

template <class T>
bool higherThanZeroValidator(const T& price)
{
    return price > 0;
}

bool yesOrNoInputRequest(char& option, const string& inputRequestMessage,
                         function<bool(const char&)>& inputSelectionFunction)
{
    cout << "¿Desea adquirir la protección extra en carretera? La misma tiene un costo del 5% sobre el costo del vehiculo (S/n): ";
    cin.sync();
    cin.get(option);

    return inputSelectionFunction(option);
}

float calculateTotalCost(float& costPerRentalDays, float& fee, float& tax, float& insuranceCost, float dailyCost, short rentalDays,
                         bool userWantsInsurance, bool userWantsCivilLiability)
{
    float totalCost = 0;

    totalCost += costPerRentalDays = dailyCost * (float)rentalDays;
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