// Universidad Nacional de Costa Rica - Sede Liberia
// Primer proyecto del curso Fundamentos de informatica (EIF200)
//
// PROPUESTA #1
// 1 - Recibir por teclado un número romano (del I al MMM)
// 2 - Convertir el número recibido a número en base decimal y mostrar en pantalla el resultado obtenido
// 3 - Convertir el número decimal a clave morse y mostrar en pantalla la secuencia correspondiente de puntos
//     y rayas del código morse.
// 4 - Hacer sonar el resultado obtenido en clave morse.

#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

const map<short, string> numbersMorseCodeRepresentation =
{
    { 1, ".----" },
    { 2, "..---" },
    { 3, "...--" },
    { 4, "....-" },
    { 5, "....." },
    { 6, "-...." },
    { 7, "--..." },
    { 8, "---.." },
    { 9, "----." },
    { 0, "-----" },
};

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

const short asteriskSoundDuration = 250;
const short dashSoundDuration = asteriskSoundDuration * 3;

constexpr bool canRomanLettersBeSubtracted(const short&, const short&);

bool romanDigitToDecimalNumber(const char&, short&);

bool romanNumberToDecimalNumber(const string&, short&);

void subtractOrAdd(bool, short&, const short&, const short&, int&);

void test()
{
    short decimalNumber = 0;
    string romanNumbers[] = { "XVIII", "MDCXII", "MMMX", "IX", "VCX", "I" };

    for (const string& romanNumber : romanNumbers)
    {
        if (romanNumberToDecimalNumber(romanNumber, decimalNumber))
        {
            cout << romanNumber << " is " << decimalNumber << "\n";
        }
        else
        {
            cout << "Número romano inválido: " << romanNumber << "\n";
        }

        decimalNumber = 0;
    }
}

int main()
{
    short decimalNumber = 0;
    string romanNumber;

    SetConsoleOutputCP(CP_UTF8);

    cout << "Digite el numero romano (máximo MMM = 3000):\n";
    cin >> romanNumber;

    if (romanNumberToDecimalNumber(romanNumber, decimalNumber) && decimalNumber < 3001)
    {
        vector<short> numbers;

        cout << "\nEl número romano " << romanNumber << " tiene como equivalente en base decimal al número "
             << decimalNumber << "\n";

        while (decimalNumber > 0)
        {
            short digit = decimalNumber % 10;
            decimalNumber /= 10;

            numbers.insert(numbers.begin(), digit);
        }

        cout << "Se reproducirá la representación sonora y escrita en código Morse del número decimal obtenido en: ";
        Sleep(1000);

        for (int i = 5; i > 0; i--)
        {
            cout << i << "..";
            Sleep(1000);
        }

        cout << "\n";

        for (short digit : numbers)
        {
            string soundSequence = numbersMorseCodeRepresentation.at(digit);

            for (char sound : soundSequence)
            {
                cout << sound;
                Beep(600, (sound == '-' ? dashSoundDuration : asteriskSoundDuration));

//                if (sound == '-')
//                {
//                    cout << '-';
//                    Beep(600, dashSoundDuration);
//                }
//                else
//                {
//                    cout << '.';
//                    Beep(600, asteriskSoundDuration);
//                }
            }

            cout << " ";
        }
    }
    else
    {
        cout << "Número romano inválido: " << romanNumber << "\n";
    }

    cout << endl;
//    test();

    return 0;
}

// Busca una posible resta entre los valores decimales de dos números romanos y devuelve un valor booleano
// indicando si existe alguna o no
constexpr bool canRomanLettersBeSubtracted(const short& subtractor, const short& subtracting)
{
    switch (subtractor)
    {
        case 1:
            return subtracting == 5 || subtracting == 10;
        case 10:
            return subtracting == 50 || subtracting == 100;
        case 100:
            return subtracting == 500 || subtracting == 1000;
        default:
            return false;
    }
}

// Convierte un número romano a su equivalente decimal, a diferencia de la función "romanDigitToDecimalNumber" que
// convierte un único dígito romano a su equivalente número decimal
bool romanNumberToDecimalNumber(const string& romanNumber, short& resultingDecimalNumber)
{
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

// Convierte un único dígito romano a su equivalente número decimal
bool romanDigitToDecimalNumber(const char& romanDigit, short& decimalNumber)
{
    auto iterator = romanNumbersDecimalNumbersEquivalent.find(romanDigit);
    bool found = iterator != romanNumbersDecimalNumbersEquivalent.end();

    if (found)
    {
        decimalNumber = iterator->second;
    }

    return found;
}

// Función de ayuda para la función "romanNumberToDecimalNumber" que suma a "decimalNumber" la resta de
// "nextRomanDigit" y "currentRomanDigit" o, "currentRomanDigit", basado en el valor de "shouldCurrentSubtractNext"
void subtractOrAdd(bool shouldCurrentSubtractNext, short &decimalNumber, const short &currentRomanDigit,
                   const short &nextRomanDigit, int &index)
{
    if (shouldCurrentSubtractNext)
    {
        decimalNumber += nextRomanDigit - currentRomanDigit;
        index++;
    }
    else
    {
        decimalNumber += currentRomanDigit;
    }
}