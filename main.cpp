#include <iostream>
#include <algorithm>
#include <stack>
#include <stdlib.h>
#include <vector>
#include <string>
#include <cctype>
#include <string.h>
#include <math.h>
#include <locale>
#include "WTNumber.h"
using namespace std;

void printWelcomeInfo()
{
    puts("-----------------------------------------------------------------------------------------------------");
    puts("Welcome to use this calculator!");
    puts("This calculator can do the four fundamental operations of arithmetic and is better than the first one");
    puts("if you want to exit, please input 'q'");
    puts("input expression to start your calculating!");
    puts("-----------------------------------------------------------------------------------------------------");
}

// check if the input is valid
bool checkValid(string expression)
{

    if ((expression[0] >= 65 && expression[0] <= 90) || (expression[0] >= 97 && expression[0] <= 122))
    {

        if (expression[1] != '=')
        {
            return false;
        }

        if (!((expression[2] >= 48 && expression[2] <= 57) || expression[2] == 43 || expression[2] == 45))
        {
            return false;
        }

        for (int i = 3; i < expression.length(); i++)
        {
            if (!(expression[i] >= 48 && expression[i] <= 57))
            {
                return false;
            }
        }
        return true;
    }
    else
    {

        int openingParenthesis = 0;
        int closingParenthesis = 0;
        for (int i = 0; i < expression.length(); i++)
        {
            if (!(expression[i] >= 40 && expression[i] <= 57 && expression[i] != 44))
            {
                return false;
            }
            if (expression[i] == 40)
            {
                openingParenthesis++;
            }
            if (expression[i] == 41)
            {
                closingParenthesis++;
            }
        }
        if (openingParenthesis != closingParenthesis)
        {
            return false;
        }
    }
    return true;
}

bool ifContainLetter(string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if ((expression[i] >= 65 && expression[i] <= 90) || (expression[i] >= 97 && expression[i] <= 122))
        {
            return true;
        }
    }
    return false;
}

bool ifCalculate(string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == 42 || expression[i] == 43 || expression[i] == 45 || expression[i] == 47)
        {
            return true;
        }
    }
    return false;
}

// Change the '-' for numbers less than zero to '0'
string pretreatment(string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == 45)
        {
            if (i == 0)
            {
                expression = expression.replace(0, 1, "0");
            }
            else if (expression[i - 1] == 40)
            {
                expression = expression.replace(i, 1, "0");
            }
        }
    }
    return expression;
}

// calculate the priority of the operator
int priorityCalculation(char o)
{
    if (o == '+' || o == '-')
    {
        return 1;
    }
    if (o == '*' || o == '/')
    {
        return 2;
    }
    return 0;
}

// transform the expression to the Reverse Polish notation form
vector<string> transformToRPN(string expression)
{
    stack<char> op;
    vector<string> RPN;
    for (int i = 0; i < expression.length(); i++)
    {
        string s;
        if (expression[i] == '(')
        {
            op.push(expression[i]);
        }
        if (expression[i] == ')')
        {
            while (op.top() != '(')
            {
                s = op.top();
                RPN.push_back(s);
                op.pop();
                s = "";
            }
            op.pop();
        }
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            if (op.empty() || op.top() == '(')
            {
                op.push(expression[i]);
            }
            else
            {
                while (!op.empty() && priorityCalculation(op.top()) >= priorityCalculation(expression[i]))
                {
                    s = op.top();
                    RPN.push_back(s);
                    op.pop();
                    s = "";
                }
                op.push(expression[i]);
            }
        }
        if ((expression[i] >= '0' && expression[i] <= '9'))
        {
            s += expression[i];
            while ((i + 1 < expression.size() && expression[i + 1] >= '0' && expression[i + 1] <= '9') || expression[i + 1] == '.')
            {
                s += expression[i + 1];
                i++;
            }
            RPN.push_back(s);
        }
    }
    while (!op.empty())
    {
        string s;
        s = op.top();
        RPN.push_back(s);
        op.pop();
        s = "";
    }
    return RPN;
}

string calculate(vector<string> RPN)
{
    stack<string> res;
    for (int i = 0; i < RPN.size(); i++)
    {
        string s;
        s = RPN[i];
        if (s[0] >= 48 && s[0] <= 57)
        {
            res.push(s);
        }
        else if (s[0] == 43)
        {
            CWTNumber num1(res.top().c_str());
            res.pop();
            CWTNumber num2(res.top().c_str());
            res.pop();
            string resultOfAdd = (num1 + num2).ToString();
            res.push(resultOfAdd);
        }
        else if (s[0] == 45)
        {
            CWTNumber num1(res.top().c_str());
            res.pop();
            CWTNumber num2(res.top().c_str());
            res.pop();
            string resultOfMinus = (num2 - num1).ToString();
            res.push(resultOfMinus);
        }
        else if (s[0] == 42)
        {
            CWTNumber num1(res.top().c_str());
            res.pop();
            CWTNumber num2(res.top().c_str());
            res.pop();
            string resultOfTime = (num1 * num2).ToString();
            res.push(resultOfTime);
        }
        else if (s[0] == 47)
        {
            CWTNumber num1(res.top().c_str());
            res.pop();
            CWTNumber num2(res.top().c_str());
            res.pop();
            string resultOfDivide = (num2 / num1).ToString();
            res.push(resultOfDivide);
        }
    }
    return res.top();
}

int main()
{

    printWelcomeInfo();
    string expression;
    vector<string> letter;
    vector<string> num;
    while (getline(cin, expression))
    {
        if (expression == "q")
        {
            puts("Thanks for using!");
            break;
        }
        else if (ifContainLetter(expression))
        {
            if (!ifCalculate(expression))
            {
                if (!checkValid(expression))
                {
                    puts("The input is not valid,please check your input!");
                }
                else
                {
                    string tem1;
                    string tem2(1, expression[0]);
                    for (int i = 2; i < expression.length(); i++)
                    {
                        tem1 += expression[i];
                    }
                    letter.push_back(tem2);
                    num.push_back(tem1);
                }
            }
            else
            {
                for (int i = 0; i < num.size(); i++)
                {
                    expression = expression.replace(expression.find(letter[i]), num[i].size(), num[i]);
                }
                letter.clear();
                num.clear();
                expression = pretreatment(expression);
                vector<string> RPN1 = transformToRPN(expression);
                cout << calculate(RPN1) << endl;
            }
        }

        else if (!checkValid(expression))
        {
            puts("The input is not valid,please check your input!");
        }
        else
        {
            expression = pretreatment(expression);
            vector<string> RPN2 = transformToRPN(expression);
            cout << calculate(RPN2) << endl;
        }
    }

    return 0;
}