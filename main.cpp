#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cctype>

class PostFixEvaluator {
private:
    std::string postfix; // To hold the postfix expression
    double result; // To hold the result of evaluation

    // Helper function to perform arithmetic operations
    double applyOperation(double operand1, double operand2, char op) {
        switch (op) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/': 
                if (operand2 == 0) throw std::invalid_argument("Division by zero");
                return operand1 / operand2;
            default:
                throw std::invalid_argument("Invalid operator");
        }
    }

public:
    // Constructors
    PostFixEvaluator() : postfix(""), result(0) {}
    PostFixEvaluator(std::string postfixExpr) : postfix(postfixExpr), result(0) {}

    // Method to evaluate postfix expression
    void evaluate() {
        std::stack<double> stack;
        std::istringstream ss(postfix);  // To handle the space-separated tokens
        std::string token;

        while (ss >> token) {
            // Skip semicolons or any invalid characters
            if (token == ";") {
                continue;
            }

            // If the token is a number, push it to the stack
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
                stack.push(std::stod(token));  // Support negative numbers
            }
            // If the token is an operator, pop two operands and apply the operation
            else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (stack.size() < 2) throw std::invalid_argument("Insufficient operands");

                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = applyOperation(operand1, operand2, token[0]);
                stack.push(result);
            } 
            else {
                throw std::invalid_argument("Invalid character in expression");
            }
        }

        if (stack.size() != 1) throw std::invalid_argument("Malformed expression");

        result = stack.top();
    }

    // Getter for result
    double getResult() {
        return result;
    }

    // Setter for postfix expression
    void setPostfix(std::string postfixExpr) {
        postfix = postfixExpr;
    }
};

int main() {
    // Read test data from "RPNData.txt"
    std::ifstream file("RPNData.txt");
    std::string line;
    while (std::getline(file, line)) {
        try {
            std::cout << "\nEvaluating postfix expression: " << line << std::endl;
            PostFixEvaluator evaluator(line);
            evaluator.evaluate();
            std::cout << "Result: " << evaluator.getResult() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}