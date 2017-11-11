/*
 Project: PostFix Notation
 File Name: postFixCalc.cpp
 Created by Aleksandr Golovin on 10/30/17.
 Copyright © 2017 Aleksandr Golovin. All rights reserved.
 
 Note: Took about 10hrs.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "llStack.hpp"

using namespace std;

//Used for mathmatical operations on elements of stack
void numCalc(const string & sym, LLStack<int> & stack);

int main(int argc, const char * argv[])
{
    string filName;
    char usrInpt;
    
    LLStack<int>calc;
    
    //Loops as long as user what to
    do {
        cout << "Enter File Name: ";
        cin >> filName;
        
        //Creates a input stream and opens it
        ifstream inFile;
        inFile.open(filName);
        
        //Checks if input file is open
        if (inFile.is_open())
        {
            while (!inFile.eof() && inFile.peek() != 10)
            {
                string num;
                
                //Used to ignore spaces
                while (inFile.peek() == 32)
                {
                    inFile.get();
                }
                
                //If not end of file proceed
                if (inFile.peek() != 10)
                {
                    inFile>> num ;
                    
                    //Checks for operator
                    if (num == "+" || num == "-" || num == "*" || num == "/")
                    {
                        //Performs mathematical operations
                        numCalc(num, calc);
                    }
                    else
                    {
                        //Cast-types string to int and push onto stack
                        calc.push(stoi(num));
                    }
                }
            }
            
            //Closes file once done
            inFile.close();
        }
        
        //Checks to see if more than one item on stack
        if (calc.size() >1)
            cout << "FAIL!!!\n";
        
        //Get user input to proceed or not
        cout << "Again? y or n"<<endl<<"Your choice: ";
        
        cin >> usrInpt;
        
    } while (tolower(usrInpt) == 'y');
}

//Performs mathematical operations, throw exception if stack is empty
void numCalc(const string & nwSym, LLStack<int> & stack)
{
    char sym = nwSym[0];
    try
    {
        //Gets top element then pops it off
        int num1 = stack.top();
        stack.pop();
        int num2 = stack.top();
        stack.pop();
        
        int tot;
        switch (sym)
        {
            case '+':
                tot = num2 + num1;
                break;
            case '-':
                tot = num2 - num1;
                break;
            case '*':
                tot = num2 * num1;
                break;
            case '/':
                tot = num2 / num1;
                break;
            default:
                throw std::runtime_error("unknown operator");
        }
        
        //Displays calculation performed
        cout << num2 << sym << num1 << "=" << tot << endl;
        
        //Pushes total after calc. onto stack
        stack.push(tot);
    }
    catch (exception &e)
    {
        cout << "An Expection Occured: " << e.what() << endl;
    }
}

