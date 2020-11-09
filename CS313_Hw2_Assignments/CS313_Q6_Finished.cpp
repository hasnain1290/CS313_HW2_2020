#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class Stack
{
    public:
    int top;
    unsigned limit;
    char* array;
};

int IsFull(Stack* stack)//IsFull checks if stack is equal to the stack limit and if it then it is full
{ 
    return stack->top == stack->limit - 1; 
}

int isEmpty(Stack* stack)
{ 
    return stack->top == -1; //isEmpty checks if the stack is set to -1 and if it is then it is empty
}

Stack* startStack(unsigned limit) // function to create the stack intialized as 0
{
    Stack* stack = new Stack();//initalizes stack
    stack->limit = limit;
    stack->top = -1;//set first stack equal to -1, with this you can chec, if stack is full
    stack->array = new char[(stack->limit * sizeof(char))];
    return stack;
}

void push(Stack* stack, char item)
{
    if (IsFull(stack)) return; //if stack is full return
    stack->array[++stack->top] = item;//while stack is not full push an item on top of the stack and increase by 1
}

char pop(Stack* stack) //pop an element off the top of the stack
{
    if (isEmpty(stack)) return -1;//if Empty

    return stack->array[stack->top--];//decrease top each iteration
}

void strswitch(string cn)//stack function that reverses string
{
    stack <char> stackz;
    for (int i=0; i<cn.length(); i++){
        if (cn[i] != ' ')//if the string at the spot of cn[i] is != to a space then
        stackz.push(cn[i]);//push the string onto the stack
        else{
            while (stackz.empty() == false) {//while the stackz is empty is false
                cout << stackz.top(); //cout the top of the stack
                stackz.pop();//then pop that char
            }
            cout << " ";//cout space each time the while loop stops
        }
    }
    while (stackz.empty() == false){
        cout << stackz.top();
        stackz.pop();
    }
}

int main()
{
    ifstream infile;
    infile.open("YouDontJokeAboutChuckNorrisChuckNorrisJokeYou.txt");

    if (infile.fail()){
        cout<< "This file does not exist, try another file";
    }
    else{
        string str;
        while(getline(infile,str)){//while there are still lines in the file is true, continue, once this is false the loop ends itself
            cout << str << endl;// cout string before it is switched
            strswitch(str);
            cout << endl;
        }
        infile.close();//close infile so no memory leaks
    }
    return 0;
}
