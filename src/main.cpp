#include <algorithm>
#include <iostream>
#include <string>

enum class Operation
{
    none,
    addition,
    subtraction,
    multiplication,
    division,
    quit,
};

std::ostream& operator<<(std::ostream& os, const Operation& op)
{
    switch (op)
    {
        case Operation::none:
            os << "none";
            break;
        case Operation::addition:
            os << "addition";
            break;
        case Operation::subtraction:
            os << "subtraction";
            break;
        case Operation::multiplication:
            os << "multiplication";
            break;
        case Operation::division:
            os << "division";
            break;
        case Operation::quit:
            os << "quit";
            break;
    }
    return os;
}

Operation selectOperation()
{
    Operation choice {};
    std::string input;
    while (choice == Operation::none)
    {
        std::cout << "Select an operation (a)ddition, (s)ubtraction, (m)ultiplication, (d)ivision, or (q)uit: " << '\n';
        std::cin >> input;
        if (input.empty()) continue;
        switch (input[0])
        {
            case 'a':
                choice = Operation::addition;
                break;
            case 's':
                choice = Operation::subtraction;
                break;
            case 'm':
                choice = Operation::multiplication;
                break;
            case 'd':
                choice = Operation::division;
                break;
            case 'q':
                return Operation::quit;
            default:
                std::cout << "Invalid input! Please try again!\n";
                break;
        }
    }
    return choice;
}

void play(Operation operation)
{

}

int main()
{
    Operation currentOperation{Operation::none};
    std::string input{};
    while (true)
    {
        if (currentOperation == Operation::none)
        {
            currentOperation = selectOperation();
            if (currentOperation == Operation::quit)
            {
                break;
            }
        }
        std::cout << "Currently practicing: " << currentOperation << ".\n";
        while (true)
        {
            std::cout << "Select\n" << "1) Change mode\n" << "2) Start timer\n" << "3) Quit\n";
            std::getline(std::cin, input);
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "q" || input == "quit" || input == "3")
            {
                currentOperation = Operation::quit;
                break;
            }
            if (input == "1")
            {
                currentOperation = Operation::none;
                break;
            }
            if (input == "2")
            {
                break;
            }
            std::cout << "Invalid input! Please try again!\n";
        }
        if (currentOperation == Operation::none)
        {
            continue;
        } else if (currentOperation == Operation::quit)
        {
            break;
        } else
        {
            play(currentOperation);
        }
    }
}
