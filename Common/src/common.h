#ifndef COMMON_COMMON_H
#define COMMON_COMMON_H

#include <functional>
#include <iostream>
#include <string>

using namespace std;

template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   const function<bool(T)>& inputValidationFunction);

// NOTE: Template definitions and implementations can't be put in separate files, it causes
// a linker error, and the "solution" to this, the "export" keyword, is implemented just in
// some compilers, so it's not available yet, maybe won't be available ever.
// More info: https://stackoverflow.com/a/115735
template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   function<bool(T)>& inputValidationFunction)
{
    bool success = false;
    size_t numberOfCharactersParsed;

    while (!success)
    {
        cout << inputRequestMessage;
        cin >> inputField;

        try
        {
            // NOTE: stof = String TO Float (I think...)
            backingField = stof(inputField, &numberOfCharactersParsed);

            success = inputField.length() == numberOfCharactersParsed
                      && inputValidationFunction(backingField);
        }
        catch (...)
        {
        }

        if (!success)
        {
            cout << "Entrada inválida, intentelo de nuevo" << endl;
        }

    }
}

#endif //COMMON_COMMON_H
