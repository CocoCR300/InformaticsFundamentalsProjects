// NOTE: Template definitions and implementations can't be put in separate files, it causes
// a linker error, and the "solution" to this, the "export" keyword, is implemented just in
// some compilers, so it's not available yet, maybe won't be available ever.
// More info: https://stackoverflow.com/a/115735

#ifndef COMMON_H
#define COMMON_H

#define INVALID_INPUT_MESSAGE "Entrada inválida, intentelo de nuevo"

#include <functional>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

template <class T>
using floatingPointNumberParseFunction = T(*)(const string&, size_t*);

template <class T>
using inputValidationFunction = function<bool(const T&)>;

template <class T>
using integerNumberParseFunction = T(*)(const string&, size_t*, int);

#pragma region Definitions

namespace
{
    template<class T>
    T userInputLoopInternal(string &inputField, const string &inputRequestMessage, const string &invalidInputMessage,
                            floatingPointNumberParseFunction<T> parseFunction,
                            const inputValidationFunction<T> &inputValidationFunction);

    template<class T>
    T userInputLoopInternal(string &inputField, const string &inputRequestMessage, const string &invalidInputMessage,
                            integerNumberParseFunction<T> parseFunction,
                            const inputValidationFunction <T> &inputValidationFunction);
}

// "userInputLoop" overload that receives a function pointer
template <class T>
T userInputLoop(string& inputField, const string& inputRequestMessage,
                bool (*inputValidationFunction)(T));

// "userInputLoop" overload that receives a std::function
template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   const function<bool(const T&)>& inputValidationFunction);

// "userInputLoop" overload that receives a inputValidationFunction and returns the entered and validated data
template <class T>
T userInputLoop(string& inputField, const string& inputRequestMessage,
                const inputValidationFunction<T>& inputValidationFunction,
                const string& invalidInputMessage = INVALID_INPUT_MESSAGE);

string userInputLoop(const string& inputRequestMessage, const function<bool(const string&)>& inputValidationFunction,
                     const string& invalidInputMessage = INVALID_INPUT_MESSAGE);

#pragma endregion Definitions

#pragma region Implementations

namespace
{
    template<class T>
    T userInputLoopInternal(string &inputField, const string &inputRequestMessage, const string &invalidInputMessage,
                            floatingPointNumberParseFunction<T> parseFunction,
                            const inputValidationFunction<T> &inputValidationFunction)
    {
        volatile bool success = false;
        T result;
        size_t numberOfCharactersParsed;

        while (!success) {
            cout << inputRequestMessage;
            cin >> inputField;

            try {
                result = parseFunction(inputField, &numberOfCharactersParsed);

                success = inputField.length() == numberOfCharactersParsed
                          && inputValidationFunction(result);
            }
            catch (...) {
            }

            if (!success) {
                cout << invalidInputMessage << endl;
            }
        }

        return result;
    }

    template<class T>
    T userInputLoopInternal(string &inputField, const string &inputRequestMessage, const string &invalidInputMessage,
                            integerNumberParseFunction<T> parseFunction,
                            const inputValidationFunction <T> &inputValidationFunction)
    {
        volatile bool success = false;
        T result;
        size_t numberOfCharactersParsed;

        while (!success) {
            cout << inputRequestMessage;
            cin >> inputField;

            try {
                result = parseFunction(inputField, &numberOfCharactersParsed, 10);

                success = inputField.length() == numberOfCharactersParsed
                          && inputValidationFunction(result);
            }
            catch (...) {
            }

            if (!success) {
                cout << invalidInputMessage << endl;
            }
        }

        return result;
    }
}

// "userInputLoop" overload that receives a function pointer
template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   bool (*inputValidationFunction)(const T&))
{
    volatile bool success = false;
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

// "userInputLoop" overload that receives a std::function
template <class T>
void userInputLoop(T& backingField, string& inputField, const string& inputRequestMessage,
                   const function<bool(T)>& inputValidationFunction)
{
    volatile bool success = false;
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

template<>
double userInputLoop<double>(string& inputField, const string& inputRequestMessage,
                             const inputValidationFunction<double>& inputValidationFunction,
                             const string& invalidInputMessage)
{
    return userInputLoopInternal(inputField, inputRequestMessage, invalidInputMessage, stod, inputValidationFunction);
}

template<>
int userInputLoop<int>(string& inputField, const string& inputRequestMessage,
                       const inputValidationFunction<int>& inputValidationFunction,
                       const string& invalidInputMessage)
{
    return userInputLoopInternal(inputField, inputRequestMessage, invalidInputMessage, stoi, inputValidationFunction);
}

template<>
float userInputLoop<float>(string& inputField, const string& inputRequestMessage,
                           const inputValidationFunction<float>& inputValidationFunction,
                           const string& invalidInputMessage)
{
    return userInputLoopInternal(inputField, inputRequestMessage, invalidInputMessage, stof, inputValidationFunction);
}

template<>
short userInputLoop<short>(string& inputField, const string& inputRequestMessage,
                           const inputValidationFunction<short>& inputValidationFunction,
                           const string& invalidInputMessage)
{
    auto shortNumberValidationFunction = [&inputValidationFunction](int input) -> bool
    {
        return inputValidationFunction(input) && input >= numeric_limits<short>::min()
               && input <= numeric_limits<short>::max();
    };

    return userInputLoopInternal<int>(inputField, inputRequestMessage, invalidInputMessage, stoi,
                                      shortNumberValidationFunction);
}

#pragma endregion Implementations

#endif //COMMON_H
