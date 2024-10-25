#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <chrono>
#include <random>

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
    Operation choice{};
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
    using namespace std::chrono_literals;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distKilo(1, 1000);
    std::uniform_int_distribution<std::mt19937::result_type> distCent(1, 100);
    std::uniform_int_distribution<std::mt19937::result_type> distDeci(1, 10);

    std::cout << "Answer as many questions as possible in 60 seconds!" << '\n';
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    int i{};
    while (std::chrono::high_resolution_clock::now() - start < 60s)
    {
        int a{};
        int b{};
        int answer{};

        switch (operation)
        {
        case Operation::addition:
        case Operation::subtraction:
            a = static_cast<int>(distKilo(rng));
            do
            {
                b = static_cast<int>(distKilo(rng));
            }
            while (b > a);
            if (operation == Operation::addition)
            {
                answer = a + b;
            } else
            {
                answer = a - b;
            }
            break;
        case Operation::multiplication:
            a = static_cast<int>(distDeci(rng));
            b = static_cast<int>(distDeci(rng));
            answer = a * b;
            break;
        case Operation::division:
            do
            {
                a = static_cast<int>(distKilo(rng));
                do
                {
                    b = static_cast<int>(distCent(rng));
                }
                while (a % b != 0);
            }
            while (a == b || b == 1);
            answer = a / b;
            break;
        default:
            std::cout << "Error! Aborting." << '\n';
            return;
        }

        while (true)
        {
            std::cout << "  ";
            if (a < 100) std::cout << " ";
            if (a < 10) std::cout << " ";
            std::cout << a << '\n';
            switch (operation)
            {
            case Operation::addition:
                std::cout << "+ ";
                break;
            case Operation::subtraction:
                std::cout << "- ";
                break;
            case Operation::multiplication:
                std::cout << "* ";
                break;
            case Operation::division:
                std::cout << "/ ";
                break;
            }
            if (b < 100) std::cout << " ";
            if (b < 10) std::cout << " ";
            std::cout << b << '\n';
            std::cout << "------" << '\n';

            int attempt{};
            std::cin >> attempt;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (attempt != answer)
            {
                std::cout << "Try again!" << '\n';
            } else
            {
                i++;
                break;
            }
        }
    }

    std::cout << "You got " << i << " question(s) correct!" << '\n';
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        }
        else if (currentOperation == Operation::quit)
        {
            break;
        }
        else
        {
            play(currentOperation);
        }
    }
}
