//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "mystack.h"
 
using namespace std; //standard

void evaluateExpression(ifstream& inpF, ofstream& outF, //takes reference in ifstream, reference ofstream, reference stackType of double, a reference bool type 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack, //takes reference ofstream, stackType reference in double and a char reference type and a reference bool type
                  char& ch, bool& isExpOk);
void discardExp(ifstream& in, ofstream& out, char& ch); // takes ifstream reference, ofstream reference, and ref char
void printResult(ofstream& outF, stackType<double>& stack, //takes ref ofstream and another stackType as a double and another reference bool type
                 bool isExpOk);

int main()
{
    bool expressionOk;//bool of true or false
    char ch; //create a char to be used in the functions
    stackType<double> stack(100); //allocate space to be used in the functions
    ifstream infile; //input stream file
    ofstream outfile; // output stream file
  
    infile.open("RpnData.txt"); //opens a to input a file named RpnData.txt

    if (!infile)//if the file is not inputted
    {
        cout << "Cannot open the input file. " //output these strings
             << "Program terminates!" << endl;
        return 1; //means program is returning an error
    }
     
    outfile.open("RpnOutput.txt"); // creates a output file named RpnOutput.txt

    outfile << fixed << showpoint; // sets the outfile to a certain significant figure as well as
    //allows the outfile to automatically remove the point in the decimal with leading 0's or no zeros at all
    outfile << setprecision(2); //set the precision or in other words similar to significant figures to 2 numbers

    infile >> ch; //read the documents character by character
    while (infile)//while infile is true as in while the file is still open and 
    {
        stack.initializeStack();//initialize the stack
        expressionOk = true; // set the expresison as ok
        outfile << ch; //out put those chars to the outfile

        evaluateExpression(infile, outfile, stack, ch, //calls the function evaluateExpression
                           expressionOk);
        printResult(outfile, stack, expressionOk);//print the results 
        infile >> ch; //begin processing the next expression after printing
    } //end while 

    infile.close();//close infile so no memory leaks
    outfile.close();//close outfile so no memory leaks

    return 0;//ends this function off well

} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)//function to evaluate expressions
{
    double num;//declared to use in function

    while (ch != '=')//while the ch being input is not = do the while loop
    {
        switch (ch)//switch between the given character's depending on the specific char landed on
        {
        case '#': //if ch is a number
            inpF >> num; // input that number
            outF << num << " ";// put the ch in the file with a space after
            if (!stack.isFullStack()) //while the stack is not full, the stack being 100 spots
                stack.push(num);//push to the top of the stack
            else // if stack is full then
            {
                cout << "Stack overflow. " //output these 2 strings
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;// break if you've push an item on the stack
        default: //default is the case in which it is anything else other than the given case of #
            evaluateOpr(outF, stack, ch, isExpOk); //it will automatically evaluate the operator still
        }//end switch

        if (isExpOk) //if there is no error
        {
            inpF >> ch;//inputfile the char
            outF << ch;//output file the char

            if (ch != '#')//if its not a number then it's assumed to be a space
                outF << " ";// add a space in the outfile
        }
        else //pretty much if isExpOk is not okay 
            discardExp(inpF, outF, ch);//discard the given operator
    } //end while (!= '=')
} //end evaluateExpression


void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk) //evaluate operator, instead of expression its an operator that's being considered for all your + - * /
{
    double op1, op2;

    if (stack.isEmptyStack())//if the stack is an empty stack by this point 
    {
        out << " (Not enough operands)" //if the stack is empty by the time you get to this evaluateOpr there are not enough operands
        isExpOk = false;// set isexpOK to false
    }
    else//if the stack being empty is false, and the stack is full, now you can start checking the operators
    {
        op2 = stack.top();//op2 at the top f the stack
        stack.pop(); //pop the top of the stack

        if (stack.isEmptyStack())//another check if the stack is empty by this point
        {
            out << " (Not enough operands)";//then there is not enough operators
            isExpOk = false;//set isExpOk to false
        }
        else//other wise
        {
            op1 = stack.top();//set the second op1 as element on the top of the stack
            stack.pop();//pop the top of the stack

            switch (ch)//switch the operator cases between + - * /
            {
            case '+':
                stack.push(op1 + op2);//add the op1 and op2 taken from the stack
                break; //then break from switch
            case '-': 
                stack.push(op1 - op2);//subtract the op2 from op1 from the stack
                break;//then break from switch
            case '*': 
                stack.push(op1 * op2);//multiply op1 and op2 together and add on the stack
                break;//then break from switch
            case '/': 
                if (op2 != 0)//as long as the denominator isn't 0 continue to add on the stack
                    stack.push(op1 / op2);//divide op1 by op2
                else//if it is equal to 0
                {
                    out << " (Division by 0)";//output string bad division
                    isExpOk = false; //set isExpOk to false
                }
                break;//then break from switch
            default:  //if it is anything other than the listen above operators
                out << " (Illegal operator)";//automatically assumed not to be a operator for numbers
                isExpOk = false;//set isExpOk to false
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


void discardExp(ifstream& in, ofstream& out, char& ch)//function to discard the bad expressions
{
    while (ch != '=')//while the char is not equal to =
    {
        in.get(ch);//get that char from the infile
        out << ch;//outfile the char to discard it
    }
} //end discardExp

void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)//printing the reuslt of given stack
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())//if the stack is not empty continue
        {
            result = stack.top();//the result is the top of the stack
            stack.pop();//pop the top of the stack

            if (stack.isEmptyStack())//if the stack is empty
                outF << result << endl;//output the result as empty
            else//possible exceptions to the if statment
                outF << " (Error: Too many operands)" << endl;//put in outfile if the stack is full
        } //end if
        else
            outF << " (Error in the expression)" << endl;//put in outfile an issue with the error
    }
    else
        outF << " (Error in the expression)" << endl;//put error in expression

    outF << "_________________________________" //output a blank line 
         << endl << endl;// skip 2 lines
} //end printResult

