#include <iostream>
#include <algorithm>

double add(double num1, double num2) {
    return num1 + num2;
}

double subtract(double num1, double num2) {
    return num1 - num2;
}

double multiply(double num1, double num2) {
    return num1 * num2;
}
double divide(double num1, double num2) {
    return num1 / num2;
}

std::string convert_string_to_lowercase(std::string supplied_operation) {
    std::transform(supplied_operation.begin(), supplied_operation.end(), supplied_operation.begin(), ::tolower);
    return supplied_operation;
}

std::string find_operation(std::string supplied_operation) {
    int operations_count = 4;
    std::string lowercase_user_operation = convert_string_to_lowercase(supplied_operation);
    std::string operations[operations_count] = {
        "add",
        "subtract",
        "multiply",
        "divide"
    };
    for (int i = 0; i < operations_count; i++) {
        if (operations[i] == lowercase_user_operation) {
            return operations[i];
        }
    }
    return "NOT FOUND";
}

int main() {
    std::string supplied_operation, operation;
    double first_num, second_num;

    std::cout << "Add, Subtract, Multiply, Divide: ";
    std::getline(std::cin, operation);
    operation = find_operation(operation);

    if (operation == "NOT FOUND") {
        std::cout << "Bad Operation, exiting";
    } else {
        std::cout << operation << " Selected\n" << "Enter First Number: ";
        std::cin >> first_num;

        std::cout << "Enter Second Number: ";
        std::cin >> second_num;


        if (operation == "add") {
            std::cout <<  add(first_num, second_num);
        } else if (operation == "subtract") {
            std::cout << subtract(first_num, second_num);
        } else if (operation == "multiply") {
            std::cout << multiply(first_num, second_num);
        } else if (operation == "divide") {
            std::cout << std::endl << divide(first_num, second_num);
        } else {
            std::cout << "Operation not found, exiting";
        }
    }
}
