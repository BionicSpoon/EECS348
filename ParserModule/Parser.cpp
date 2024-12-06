// Parser.cpp: A class that takes an input string (or tokenized input),
//             and converts it to Polish/prefix notation to be passed on to the ExpressionTree.

#include <iostream>
#include <string>


class Parser {
    private:
    std::string expression;
    std::string result;

    public:
    Parser(std::string s) { // Constructor: pass the pointer to the string
        expression = s;
    }


    // int convert() {
    //     // "main" function for the parser that controls the conversion
        // std::string operand1; // = "" implied
        // std::string operand2;
        // std::string operation;

    //     int parenthesis_counter = 0;

    //     bool is_operation_done = false;


    //     static int prev = 0; // tracks the current progress in the expression (is not reset to 0)
    //     for (int i = prev; i < expression.size(); i++) { // iterate through the expression from the left from prev (so it can recurse)

    //         char c = expression[i];

    //         // skip any spaces
    //         if (c == ' ') {
    //             continue;
    //         }

    //         // look for highest precendence operator
    //         if (c == '*') {
    //             if (i+1 < expression.size() && expression[i+1] == '*') {
    //                 // the first power from the left has been found, so it is the "root" operator
    //                 // we can take everything before the ** and make it operand1, the other side operand2
    //                 operation = "**";
    //                 operand1 = expression.substr(0, i-1);
    //                 operand2 = expression.substr(i+2); // == expression[i+2:] from Python
    //                 simplify()

    //                 continue;
    //             }
    //         }







    //         if (-1 < (c - '0') < 10) { // if the char is a digit 0-9 (by ascii code)
    //             for (int len = 1; !(-1 < expression[i + len] - '0' < 10); len++) { // until the next char is not a digit 0-9, add them to c
    //                 c += expression[i + len]; // after this, c will have the first digit in the current expression
    //             }
    //             i += c.size() - 1;
    //         }

    //         switch (c) {
    //             // -------------- OPERATORS -------------------
    //             case '+':
    //             case '-':
    //             case '/':
    //             case '%':
    //                 if (operation == "") {
    //                     operation += c;
    //                 }
    //                 else {
    //                     std::cout << "Operator error." << std::endl;
    //                     throw 100; // invalid operator error (define codes later)
    //                 }
    //                 break;

    //             case '*':
    //                 if (operation == "" && i + 1 < expression.size()) {
    //                     // if conditions allow a valid next operand
                        



    //                     if (operation == "" && i + 1 < expression.size() && (expression[i+1] == '*' || (-1 < (expression[i+1] - '0') < 10 || expression[i+1] == ' '))) {
    //                         // if the operation is not yet done, the next index is valid, and the next character is '*' or a digit or a space (not invalid):
    //                         operation = "**";
    //                         i += 1;
    //                     }
    //                     else {
    //                         std::cout << "Operator error after '*'." << std::endl;
    //                         throw 100; // invalid operator error (define codes later)
    //                     }
    //                 }
    //                 // -------------- OPERATORS -------------------
                           
    //         }   

    //     return 0; // for success
    //     }
    // }

    std::string simplify(std::string expression) {
        // recursive. needs to return the prefix version of the expression split at the highest precendence operation.
        for (int i = 0; i < expression.size(); i++) { // remove all spaces (this is clunky, should be done earlier in the process)
            char c = expression[i];
            if (c == ' ') {
                expression.erase(i);
                i -= 1;
            }
        }

        if (expression == "") {
            return "";
        }

        if (expression.size() == 1) {
            if (-1 < expression[0] - '0' && expression[0] - '0' < 10) {
                return expression;
            }
            else {
                std::cout << expression << "will throw an error" << std::endl;
                throw 101;
            }
        }

        // // matching parenthesis (eliminate and call again)
        // if (expression[0] == '(' && expression[expression.size()-1] == ')') {
        //     std::string inner = simplify(expression.substr(1, size(expression) - 2));
        //     expression.replace(1, size(inner), inner);
        // }

        // solve parenthesis by calling simplify() on the inside and placing this result back into expression
        if (expression[0] == '(') {
            int i;
            for (i = 1; expression[i] != ')'; i++); // count i up to ')'
            std::string inner = simplify(expression.substr(1, size(expression) - 2));
            expression.replace(1, inner.size(), inner);
        }

        // starts with + or - (add to call on inner expression)
        if (expression[0] == '+' || expression[0] == '-') {
            return simplify(expression[0] + expression.substr(1));
        }



        std::string operand1; // = "" implied
        std::string operand2;
        std::string operation;

        for (int i = 0; i < expression.size(); i++) { // iterate through the expression from the left from prev (so it can recurse)

            char c = expression[i];

            // skip any spaces
            if (c == ' ') {
                continue;
            }

            // // Identify parenthesis
            // int parenthesis_counter = 0;
            // if (c == '(') {
            //     parenthesis_counter += 1;
            // }
            // if (c == ')') {
            //     parenthesis_counter -= 1;
            // }

            // look for highest precendence operator
            // ----------------- ** -----------------
            if (c == '*') {
                if (i+1 < expression.size() && expression[i+1] == '*') {
                    // the first power from the left has been found, so it is the "root" operator
                    // we can take everything before the ** and make it operand1, the other side operand2
                    operation = "**";
                    operand1 = simplify(expression.substr(0, i-1));
                    operand2 = simplify(expression.substr(i+2)); // == expression[i+2:] from Python
                    return combine_subexpressions(operand1, operation, operand2);
                }
            }

            // Is there a way for me to do this (convert to prefix) without doing all this? It's kind of pointless to convert to prefix from this granular form just for it to be resimplified later 
            // ----------------- *, /, % -----------------
            if (c == '*' || c == '/' || c == '%') { // * must be for multiplication now
                operation = c;
                operand1 = simplify(expression.substr(0, i-1));
                operand2 = simplify(expression.substr(i+1)); // == expression[i+1:] from Python
                return combine_subexpressions(operand1, operation, operand2);
            }

            // ----------------- +, - -----------------
            if (c == '+' || c == '-') { // pos/neg already handled
                operation = c;
                operand1 = simplify(expression.substr(0, i-1));
                operand2 = simplify(expression.substr(i+1)); // == expression[i+1:] from Python
                return combine_subexpressions(operand1, operation, operand2);
            }

            // else if (-1 < (c - '0') < 10) {// is a digit 0-9
            //     for (int len = 1; !(-1 < expression[i + len] - '0' < 10); len++) { // until the next char is not a digit 0-9, add them to c
            //         c += expression[i + len]; // after this, c will have the first digit in the current expression
            //     }
            }
        // if there are no operators in the current expression, extract the first number
        // maybe it should only be a num left if the rest of the code is good enough?? try return expression;
        // std::string num = "";
        // for (int i = 0; i < expression.size(); i++) {
        //     if (-1 < expression[i] - '0' < 10) {
        //         num += expression[i];
        //     }
        //     else { // there are unbalanced parens or bad stuff after the num
        //         throw 100;
        //     }
        // }
        // return num;
        // }
        return expression;
    }




    std::string combine_subexpressions(std::string operand1, std::string operation, std::string operand2) {
        // returns the combined prefix expression of two operands and an operator (they can be any size)
        return operation + ' ' + operand1 + ' ' + operand2; // this should work for combining any 2 prefix expressions with an operator
    }

    // std::string add_spaces();

};




int main() {
    // another temporary main inlcuded only for testing purposes
    Parser parser("1+2*3");
    std::cout << R"(combine_subexpressions("1", "+", "- 3 5"))" << " -> " << parser.combine_subexpressions("1", "+", "- 3 5") << std::endl;
    // parser.convert();
    std::string testcase1 = "(1*2)**3";
    std::string testcase2 = "1**2+3";
    std::string testcase3 = "-1";
    std::string testcase4 = "(1))";
    std::string testcase5 = "+5";
    std::cout << testcase1 << " -> " << parser.simplify(testcase1) << std::endl;
    std::cout << testcase2 << " -> " << parser.simplify(testcase2) << std::endl;
    std::cout << testcase3 << " -> " << parser.simplify(testcase3) << std::endl;
    std::cout << testcase4 << " -> " << parser.simplify(testcase4) << std::endl;
    std::cout << testcase5 << " -> " << parser.simplify(testcase5) << std::endl;



    return 0;
}