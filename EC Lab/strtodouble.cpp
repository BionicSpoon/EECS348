#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


double extractNumeric(const string& input) {
    double result = 0;
    bool is_plus_done = false;
    bool is_minus_done = false;
    bool is_decimal_done = false;
    bool is_spacer_reset = false;
    int spacer = 1; // multiply each digit by this and multiply it by 10 each time
    for (int i = input.length() - 1; i >= 0; i--) { // iterate through string from the end
        int digit = input[i];
        if (is_plus_done || is_minus_done) {
            return (double) -999999.99;
        }
        switch (digit) {
            case '0':
                digit = 0;
                result += digit * spacer;
                break;
            case '1':
                digit = 1;
                result += digit * spacer;
                break;
            case '2':
                digit = 2;
                result += digit * spacer;
                break;
            case '3':
                digit = 3;
                result += digit * spacer;
                break;
            case '4':
                digit = 4;
                result += digit * spacer;
                break;
            case '5':
                digit = 5;
                result += digit * spacer;
                break;
            case '6':
                digit = 6;
                result += digit * spacer;
                break;
            case '7':
                digit = 7;
                result += digit * spacer;
                break;
            case '8':
                digit = 8;
                result += digit * spacer;
                break;
            case '9':
                digit = 9;
                result += digit * spacer;
                break;
            case '+':
                if ((is_plus_done) || (is_minus_done)) {
                    return (double) -999999.99;
                }
                is_plus_done = true;
                break;
            case '-':
                if ((is_plus_done) || (is_minus_done)) { // catch the errors
                    return (double) -999999.99;
                }
                else { // no error
                    result *= -1;
                    is_minus_done = true;
                }
                break;
            case '.':
                if (is_decimal_done || is_plus_done || is_minus_done) {
                    return (double) -999999.99;
                }
                // else
                result /= spacer; // divide the result by the spacer and reset it to 1
                spacer = 1;
                is_spacer_reset = true;
                is_decimal_done = true;
                break;
            default:
                return (double) -999999.99;

        }
        // if (digit != '0' || digit != '1' || digit != '2' || digit != '3' || digit != '4' || digit != '5' || digit != '6' || digit != '7' || digit != '8' || digit != '9' || )
        // int spacer = 1; // multiply each digit by this and multiply it by 10 each time
        // result += digit * spacer;
        if (!is_spacer_reset) {
            spacer *= 10;
        }
        else {
            is_spacer_reset = false;
        }
        if (false) {
            return (double) -999999.99;
        }
    }
    return result;
}





int main() {
    string input;
    while (true) {
        cout << "Enter a string (or END to quit): " << endl;
        cin >> input;
        if (input == "END") {
            break;
        }
        double number = extractNumeric(input);
        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        }
        else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}