#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

class InfixToPostfixConverter {
private:
    std::string infix;  // stores infix expression
    std::string postfix;  // stores postfix expression

public:
    // Constructor with infix string
    InfixToPostfixConverter(const std::string &infix_expr = "") {
        infix = infix_expr;
        postfix = "";
    }

    // Method to evaluate precedence of operators
    int precedence(char op) {
        if(op == '+' || op == '-') {
            return 1;
        } else if(op == '*' || op == '/') {
            return 2;
        } else {
            return 0;
        }
    }

    // Method to check if character is an operand
    bool isOperand(char c) {
        return std::isalnum(c);
    }

    // Method to convert infix to postfix
    void convert() {
        std::stack<char> s;
        postfix = "";

        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];

            // If operand, add it to the result
            if (isOperand(c)) {
                postfix += c;
            }
            // If '(', push it to the stack
            else if (c == '(') {
                s.push(c);
            }
            // If ')', pop until '(' is encountered
            else if (c == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                if (!s.empty() && s.top() == '(') {
                    s.pop();  // pop '('
                }
            }
            // If operator, handle precedence
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(c);
            }
            // Invalid character handling
            else {
                throw std::invalid_argument("Malformed expression: invalid character.");
            }
        }

        // Pop remaining operators from the stack
        while (!s.empty()) {
            if (s.top() == '(') {
                throw std::invalid_argument("Malformed expression: unmatched '('.");
            }
            postfix += s.top();
            s.pop();
        }
    }

    // Setter for infix expression
    void setInfix(const std::string &infix_expr) {
        infix = infix_expr;
    }

    // Getter for postfix expression
    std::string getPostfix() const {
        return postfix;
    }

    // Getter for infix expression
    std::string getInfix() const {
        return infix;
    }
};

int main() {
    try {
        // Test cases
        std::string expressions[] = {
            "A+B", "A+B*C", "(A+B)*C", "A*B+C/D", "(A+B)*(C-D)", 
            "A+B*C-D/E", "A*(B+C)/D", "(A+B*C)/(D-E)", "A+(B-C)*D", 
            "A+B*(C-D)/E"
        };

        for (const std::string &expr : expressions) {
            InfixToPostfixConverter converter(expr);
            converter.convert();
            std::cout << "Infix: " << expr << " => Postfix: " << converter.getPostfix() << std::endl;
        }

        // Testing malformed expression
        std::string malformed_expr = "A+B*";
        InfixToPostfixConverter malformed_converter(malformed_expr);
        malformed_converter.convert();  // This should throw an exception
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}