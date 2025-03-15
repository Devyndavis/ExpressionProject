#ifndef POSTFIX_EVALUATOR_H
#define POSTFIX_EVALUATOR_H

#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>

class PostFixEvaluator {
private:
    std::string postfix; // To hold the postfix expression
    double result; // To hold the result of evaluation

    // Helper function to perform arithmetic operations
    double applyOperation(double operand1, double operand2, char op);

public:
    // Constructors
    PostFixEvaluator();
    PostFixEvaluator(std::string postfixExpr);

    // Method to evaluate postfix expression
    void evaluate();

    // Getter for result
    double getResult();

    // Setter for postfix expression
    void setPostfix(std::string postfixExpr);
};

#endif