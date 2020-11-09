#include <iostream>
#include <stack>
using namespace std;

bool operand(char ch){

    return isdigit(ch);//isdigit checks if character is a decimal digit

}

double evalPrefix(string x){
    stack<double> stack; //call the stack from #include stack

    for(int i = x.size() - 1;i>=0;i--){

        if(operand(x[i])) stack.push(x[i]-'0'); //ensure the string that is input from the main
        //is converted into a number
        
    else{
        double op1;
        double op2;

        op1 = stack.top();//take op1 as the elemen on top of stack
        stack.pop();//pop off that top element
        
        op2 = stack.top();//take next element as op2 
        stack.pop();//pop off that top element

        switch(x[i]){//check for which case applies
            case '+': stack.push(op1+op2);//if + applies add op1 and op2 and push to the stack
            break;//break switch
            case '-': stack.push(op1-op2);//if - applies minus op1 and op2 and push to the stack
            break;//break switch
            case '*': stack.push(op1*op2);//if * applies multiply op1 and op2 and push to the stack
            break;//break switch
            case '/'://if / applies rules slightly different, if it is dividing by 0 then throw exception, otherwise divide op1 by op2
            if(op2 == 0){
                cout << "Illegal division by 0";
            }
            else{
                stack.push(op1/op2);//push result of op1/op2 to stack
            }
            break;
        }
    }
    }
    return stack.top();
}

int main(){
    string prefix = "****23*52+42+34+23";
    string prefix2 = "+++++23+32*43*53*54";
    
    string prefix3 = "//+34*45*66";
    string prefix4 = "/30";
    
 cout <<"Prefix turns into " << evalPrefix(prefix) << endl;
 cout <<"Prefix2 turns into " << evalPrefix(prefix2) << endl;

 cout <<"Prefix4 turns into " << evalPrefix(prefix3) << endl;
 cout <<"Prefix3 turns into " << evalPrefix(prefix4) << endl;



    return 0;
}