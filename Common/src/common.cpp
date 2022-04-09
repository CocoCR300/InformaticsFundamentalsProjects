#include "common.h"

string userInputLoop(const string& inputRequestMessage, const char& delimiter, const function<bool(const string&)>& inputValidationFunction,
                     const string& invalidInputMessage)
{
    bool success = false;
    string inputField;

    while (!success)
    {
        cout << inputRequestMessage;
        getline(cin, inputField, delimiter);

        success = inputValidationFunction(inputField);

        if (!success)
        {
            cout << invalidInputMessage << endl;
        }
    }

    return inputField;
}