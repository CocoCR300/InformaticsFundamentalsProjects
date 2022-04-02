//Un estudiante desea conocer su promedio final en el curso, dicho promedio se
//compone de los siguientes porcentajes:
//45% del promedio de sus tres notas de exámenes parciales, cada examen parcial tiene el
//mismo porcentaje.
//30% de la nota del examen final.
//25% de la nota del proyecto final.
//Solicite las notas al usuario y calcule los respectivos porcentajes, para dar la solución. Si el
//promedio es mayor o igual a 70 despliegue un mensaje que diga: Estudiante aprobado, en
//caso contrario un mensaje que diga: estudiante reprobado.

#include <iostream>
#include <windows.h>

#include <common.h>

bool gradeValidator(float grade);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    float average = 0;
    float finalTestGrade, finalProjectGrade, finalTestPercentage, finalProjectPercentage;
    float partialTestGrades[3];
    float partialTestPercentages[3];
    function gradeValidationFunction(gradeValidator);
    int i;
    string userInput;

    cout << "Ingrese las notas obtenidas en los tres examenes parciales" << endl;

    for (i = 0; i < 3; i++)
    {
        string message = "Nota del examen parcial n° " + std::to_string(i + 1) + ":";
        userInputLoop(partialTestGrades[i], userInput, message, gradeValidationFunction);
    }

    userInputLoop(finalTestGrade, userInput, "Ingrese la nota obtenida en el examen final: ", gradeValidationFunction);
    userInputLoop(finalProjectGrade, userInput, "Ingrese la nota obtenida en el proyecto final: ", gradeValidationFunction);

    cout << "=================================================="
            "\nPorcentaje obtenido en los tres examenes parciales (Porcentaje máximo c/u: 15%)";

    for (i = 0; i < 3; i++)
    {
        average += partialTestPercentages[i] = partialTestGrades[i] * 15 / 100;
        cout << "\nExamen parcial n° " << i + 1 << ": " << partialTestPercentages[i];
    }

    cout << "\nSuma de los tres promedios de los examenes parciales (Porcentaje máximo: 45%): " << average;

    average += finalTestPercentage = finalProjectGrade * 30 / 100;
    average += finalProjectPercentage = finalProjectGrade * 25 / 100;

    cout.precision(2);
    cout << fixed << "\nPorcentaje obtenido en el examen final (Porcentaje máximo: 30%): " << finalTestPercentage
         << "\nPorcentaje obtenido en el proyecto final (Porcentaje máximo 25%): " << finalProjectPercentage
         << "\n\nPromedio final: " << average
         << "\nSegún su promedio final, usted está en la condición de: " << (average >= 70 ? "Aprobado" : "Reprobado")
         << "\n==================================================" << endl;

    system("pause");

    return 0;
}

bool gradeValidator(float grade)
{
    return grade >= 0 && grade <= 100;
}