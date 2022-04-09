#include <windows.h>

#include <common.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    function catAgeValidationFunction([](int input) -> bool { return input > 0; });
    int catAge;
    string inputField, message;

    userInputLoop(catAge, inputField, "Ingrese la edad de su gato: ", catAgeValidationFunction);

    switch (catAge)
    {
        case 1:
            message = "requiere la vacuna contra la Rabia";
            break;
        case 3:
            message = "requiere la vacuna contra la Panleucopenia";
            break;
        case 5:
            message = "requiere la vacuna contra la Rinotraqueítis";
            break;
        case 7:
            message = "requiere la vacuna contra la Calicivirosis";
            break;
        case 10:
            message = "requiere la vacuna contra la Peritonitis infecciosa";
            break;
        default:
            message = "no requiere ninguna vacuna";
    }

    cout << "Su gato "<< message << endl;
    system("pause");

    return 0;
}