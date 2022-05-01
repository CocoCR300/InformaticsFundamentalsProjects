// Universidad Nacional de Costa Rica - Sede Liberia
// Primer proyecto del curso Fundamentos de informatica (EIF200)
// I ciclo
// Fecha: 11/04/2022
// Autores: Aaron Madrigal Arias y Oscar Rojas Alvarado
//
// Conversor de números romanos a decimales y representador de código morse
// Versión 1.0
//
// PROPUESTA #1
// 1 - Recibir por teclado un número romano (del I al MMM)
// 2 - Convertir el número recibido a número en base decimal y mostrar en pantalla el resultado obtenido
// 3 - Convertir el número decimal a clave morse y mostrar en pantalla la secuencia correspondiente de puntos
//     y rayas del código morse.
// 4 - Hacer sonar el resultado obtenido en clave morse.

//
// Copyright 2022 Aaron Madrigal Arias y Oscar Rojas Alvarado
//
// Por la presente se concede permiso, libre de cargos, a cualquier persona que obtenga una copia de este software
// y de los archivos de documentación asociados (el "Software"), a utilizar el Software sin restricción,
// incluyendo sin limitación los derechos a usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar,
// y/o vender copias del Software, y a permitir a las personas a las que se les proporcione el Software a hacer lo
// mismo, sujeto a las siguientes condiciones:
//
// El aviso de copyright anterior y este aviso de permiso se incluirán en todas las copias o partes sustanciales
// del Software.
//
// EL SOFTWARE SE PROPORCIONA "COMO ESTÁ", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA,
// INCLUYENDO PERO NO LIMITADO A GARANTÍAS DE COMERCIALIZACIÓN, IDONEIDAD PARA UN PROPÓSITO
// PARTICULAR E INCUMPLIMIENTO. EN NINGÚN CASO LOS AUTORES O PROPIETARIOS DE LOS DERECHOS
// DE AUTOR SERÁN RESPONSABLES DE NINGUNA RECLAMACIÓN, DAÑOS U OTRAS RESPONSABILIDADES, YA
// SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O CUALQUIER OTRO MOTIVO, DERIVADAS DE, FUERA DE O
// EN CONEXIÓN CON EL SOFTWARE O SU USO U OTRO TIPO DE ACCIONES EN EL SOFTWARE.
//

#include <iostream>
#include <map>
#include <string>
#include <windows.h>

using namespace std;

#pragma region Macros
#define INVALID_INPUT_MESSAGE "Entrada invalida, intentelo de nuevo"
#define PROGRAM_TITLE "==================================================================================" \
                      "\n==== Conversor de numeros romanos a decimales y representador de codigo morse ====" \
                      "\n=================================================================================="
#pragma endregion Macros

#pragma region Constants
const map<char, short> romanNumbersDecimalNumbersEquivalent =
        {
                { 'I', 1 },
                { 'V', 5 },
                { 'X', 10 },
                { 'L', 50 },
                { 'C', 100 },
                { 'D', 500 },
                { 'M', 1000 },
        };

const short morseCodeDotSoundDuration = 250;
const short morseCodeDashSoundDuration = morseCodeDotSoundDuration * 3;
#pragma endregion Constants

#pragma region Function declarations
bool canRomanLettersBeSubtracted(short, short);

bool romanDigitToDecimalNumber(char, short&);

bool romanNumberToDecimalNumber(const string&, short&);

bool yesOrNoInputRequest(const string&, const string& = INVALID_INPUT_MESSAGE);

void subtractOrAdd(bool&, short&, short, short, int&);
#pragma endregion Function declarations

int main()
{
    bool isNumberMoreThan3000 = false, isRomanNumberValid = false, userWantsAnotherGo = false;
    short decimalNumber;
    string romanNumber;

    cout << PROGRAM_TITLE;

    while (!isRomanNumberValid || isNumberMoreThan3000 || userWantsAnotherGo)
    {
        cout << "\nDigite el numero romano (maximo MMM = 3000): ";
        cin >> romanNumber;

        for (char &letter : romanNumber)
        {
            letter = toupper(letter);
        }

        isRomanNumberValid = romanNumberToDecimalNumber(romanNumber, decimalNumber);
        isNumberMoreThan3000 = decimalNumber > 3000;

        if (isNumberMoreThan3000)
        {
            cout << "El numero ingresado es mayor a 3000. Intentelo de nuevo.\n";
        }
        else if (!isRomanNumberValid)
        {
            cout << romanNumber << " no es un numero romano. Intentelo de nuevo.\n";
        }
        // Comprobación necesaria para evitar la ejecución de este código en caso de que se fuerce el cierre
        // del programa con Ctrl+C
        else if (!romanNumber.empty())
        {
            cout << "\nEl numero romano " << romanNumber << " tiene como equivalente decimal al numero "
                 << decimalNumber << "\n";

            string fullMorseCode;

            while (decimalNumber > 0)
            {
                // Se insertan 5 guiones al inicio de la cadena de texto por cada dígito en el número decimal, esto así,
                // ya que la siguiente operación con la que se obtiene cada dígito del número decimal, lo hace de
                // derecha a izquierda
                fullMorseCode.insert(0, "-----");

                // Se obtiene cada dígito del número contenido en "decimalNumber"
                short digit = decimalNumber % 10;
                decimalNumber /= 10;

                // Se genera el código morse del dígito obtenido
                // Si el dígito es menor que 6, los puntos se insertan al principio de la secuencia, en forma ascendente
                // respecto a la cantidad de puntos. Caso contrario, los puntos se ingresan al final de la secuencia,
                // y en forma descendente respecto a su cantidad
                bool isDigitLessThanSix = digit < 6;
                short i = 0, dotsToPut = (isDigitLessThanSix ? digit : 10 - digit);

                while (dotsToPut > 0)
                {
                    if (isDigitLessThanSix)
                    {
                        fullMorseCode[i] = '.';
                    }
                    else
                    {
                        fullMorseCode[4 - i] = '.';
                    }

                    i++;
                    dotsToPut--;
                }
            }

            cout << "Se reproducira la representacion sonora y escrita en codigo morse del numero decimal obtenido en: ";
            Sleep(1000);

            for (int i = 5; i > 0; i--)
            {
                cout << i << "..";
                Sleep(1000);
            }

            cout << "\n";

            int soundCount = 0;

            for (char sound : fullMorseCode)
            {
                cout << sound;

                Beep(600, (sound == '-' ? morseCodeDashSoundDuration : morseCodeDotSoundDuration));

                soundCount++;
                if (soundCount == 5)
                {
                    cout << " ";
                    soundCount = 0;
                }
            }

            userWantsAnotherGo = yesOrNoInputRequest("\n\n¿Desea convertir otro numero romano a decimal? (S/n): ");

            if (userWantsAnotherGo)
            {
                system("cls");
                cout << PROGRAM_TITLE;
            }
        }
    }

    cout << "\nSaliendo del programa..." << endl;
    system("pause");

    return 0;
}

#pragma region Function definitions
// Busca una posible resta entre los valores decimales de dos números romanos y devuelve un valor booleano
// indicando si existe alguna o no
bool canRomanLettersBeSubtracted(const short subtractor, const short subtracting)
{
    return (subtractor == 1 && (subtracting == 5 || subtracting == 10)) ||
           (subtractor == 10 && (subtracting == 50 || subtracting == 100)) ||
           (subtractor == 100 && (subtracting == 500 || subtracting == 1000));
}

// Trata de convertir un único dígito romano a su equivalente número decimal y devuelve un valor booleano que indica si
// la conversión fue exitosa, además de guardar el resultado en "resultingDecimalNumber"
bool romanDigitToDecimalNumber(const char romanDigit, short& resultingDecimalNumber)
{
    auto iterator = romanNumbersDecimalNumbersEquivalent.find(romanDigit);
    bool found = iterator != romanNumbersDecimalNumbersEquivalent.end();

    if (found)
    {
        resultingDecimalNumber = iterator->second;
    }

    return found;
}

// Trata de convertir un número romano a su equivalente número decimal y devuelve un valor booleano que indica si la
// conversión fue exitosa, además de guardar el resultado en "resultingDecimalNumber"
// Presenta la diferencia con la función "romanDigitToDecimalNumber", la cual convierte un único dígito romano a su
// equivalente número decimal
bool romanNumberToDecimalNumber(const string& romanNumber, short& resultingDecimalNumber)
{
    resultingDecimalNumber = 0;

    if (romanNumber.length() == 1)
    {
        return romanDigitToDecimalNumber(romanNumber[0], resultingDecimalNumber);
    }

    bool canCurrentSubtractNext, hasNext, isCurrentLessThanNext, shouldCurrentSubtractNext;
    char currentRomanLetter, nextRomanLetter;
    short currentNumber, nextNumber;

    for (int i = 0; i < romanNumber.length(); i++)
    {
        hasNext = i + 1 < romanNumber.length();
        currentRomanLetter = romanNumber[i];

        if (!romanDigitToDecimalNumber(currentRomanLetter, currentNumber))
        {
            return false;
        }

        if (hasNext)
        {
            nextRomanLetter = romanNumber[i + 1];

            if (!romanDigitToDecimalNumber(nextRomanLetter, nextNumber))
            {
                return false;
            }

            isCurrentLessThanNext = currentNumber < nextNumber;
            canCurrentSubtractNext = canRomanLettersBeSubtracted(currentNumber, nextNumber);

            // Si el dígito de la izquierda es menor al de la derecha y no existe una resta posible entre ellos en los
            // números romanos, significa que el número ingresado es inválido, entonces, no es necesario continuar
            if (isCurrentLessThanNext && !canCurrentSubtractNext)
            {
                return false;
            }

            shouldCurrentSubtractNext = isCurrentLessThanNext && canCurrentSubtractNext;
        }

        subtractOrAdd(shouldCurrentSubtractNext, resultingDecimalNumber, currentNumber, nextNumber, i);
    }

    return true;
}

// Solicita una entrada por teclado de algún caracter y válida si es una letra "S", "N"
// (ya sean mayúsculas o minúsculas) o el caracter de salto de línea "\n", devolviendo un valor booleano verdadero si
// el caracter es "S" o el salto de línea "\n", o falso, si el caracter es "N", para cualquier otro caracter, se vuelve
// a solicitar otra entrada por teclado
bool yesOrNoInputRequest(const string& inputRequestMessage, const string& invalidInputMessage)
{
    bool success = false, wasTheLetterNTyped;
    char option;

    while (!success)
    {
        cout << inputRequestMessage;
        cin.ignore();
        cin.get(option);

        option = toupper(option);

        wasTheLetterNTyped = option == 'N';

        success = option == 'S' || wasTheLetterNTyped || option == '\n';

        if (!success)
        {
            cout << invalidInputMessage << "\n";
        }
    }

    return !wasTheLetterNTyped;
}

// Función de ayuda para la función "romanNumberToDecimalNumber", que suma a "decimalNumber" la resta de
// "nextRomanDigit" y "currentRomanDigit" o, "currentRomanDigit", basado en el valor de "shouldCurrentSubtractNext",
// además de devolver esta última variable mencionada a su valor original (false) en caso de que no lo tuviese
void subtractOrAdd(bool& shouldCurrentSubtractNext, short& decimalNumber, const short currentRomanDigit,
                   const short nextRomanDigit, int& index)
{
    if (shouldCurrentSubtractNext)
    {
        decimalNumber += nextRomanDigit - currentRomanDigit;
        index++;
        shouldCurrentSubtractNext = false;
    }
    else
    {
        decimalNumber += currentRomanDigit;
    }
}
#pragma endregion Function definitions