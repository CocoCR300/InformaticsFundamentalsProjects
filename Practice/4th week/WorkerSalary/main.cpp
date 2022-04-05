// Un trabajador requiere calcular su sueldo, el cual se obtiene de la siguiente manera:
// * Si trabaja 48 horas o menos se le paga a 2000 por hora trabajada
// * Si trabaja más de 48 horas, se le paga las primeras 48h a 2000 y 3000 por cada hora extra.
// Muestre un mensaje al usuario con la cantidad de horas normales trabajadas, el monto, la
// cantidad de horas extras, el monto y el salario total. Solicite al usuario el total de horas
// trabajadas.

#include <iostream>
#include <windows.h>

#include <common.h>

bool hoursValidator(short hours);

int main()
{
    function hoursValidationFunction(hoursValidator);
    int normalHoursSalary, extraHoursSalary = 0, totalSalary = 0;
    short extraHours = 0, hours;
    string userInput;

    SetConsoleOutputCP(CP_UTF8);

    userInputLoop(hours, userInput, "Ingrese el total de horas laboradas: ", hoursValidationFunction);

    if (hours > 48)
    {
        hours -= extraHours = hours - 48;
        totalSalary += extraHoursSalary = extraHours * 3000;
    }

    totalSalary += normalHoursSalary = hours * 2000;

    cout << "\nHoras normales laboradas: " << hours << "\nMonto obtenido por horas normales: " << normalHoursSalary
         << "\nHoras extra laboradas: " << extraHours << "\nMonto obtenido por horas extra: " << extraHoursSalary
         << "\nSalario total: " << totalSalary << endl;

    system("pause");

    return 0;
}

bool hoursValidator(short hours)
{
    return hours > 0;
}