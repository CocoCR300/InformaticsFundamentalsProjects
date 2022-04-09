// En una empresa existen tres áreas: Producción, Recursos Humanos y Administración.
// El presupuesto anual se reparte conforme a la siguiente distribución:
// * Producción 40%
// * Recursos Humanos 35%
// * Administración 25%
// Obtener la cantidad de dinero a recibir cada área, para cualquier monto presupuestado

#include <windows.h>

#include <common.h>

bool amountValidator(float amount);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    float annualBudget;
    function amountValidationFunction(amountValidator);
    string userInput;

    userInputLoop(annualBudget, userInput, "Ingrese el presupuesto anual: ", amountValidationFunction);

    if (annualBudget == 0)
    {
        cout << "¡¡No hay presupuesto para repartir!!" << endl;
    }
    else
    {
        cout.precision(2);
        cout << fixed << "\nDistribución del presupuesto anual a cada área"
             << "\nProducción (40%): " << annualBudget * 40 / 100
             << "\nRecursos Humanos (35%): " << annualBudget * 35 / 100
             << "\nAdministración (25%): " << annualBudget * 25 / 100 << endl;
    }

    system("pause");

    return 0;
}

bool amountValidator(float amount)
{
    return amount >= 0;
}