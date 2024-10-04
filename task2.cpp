#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


//node class
class Node {
public:
    long long value; 
    Node* next;
    Node* previous;

    //constructor
    Node(long long val = 0) : value(val), next(nullptr), previous(nullptr){}
};


//a linked list to stor a large number
class LargeNumber{
public:
    Node* head;
    Node* tail;
    bool isNegative;
    int numLength;
    int headLength;
    int listlength = 0;

    //constructor
    LargeNumber() : head(nullptr), tail(nullptr), isNegative(false) {}

    //helper function to check if the link is empty
    bool isEmpty(){
        return head == nullptr;
    }

    //function to print the entire number
    void print() {
        if (isNegative) {
            cout << "-"; // Print negative sign if the number is negative
        }
        Node* current = head;

        while (current) {
            cout << current->value; // Print the value of each node
            current = current->next; // Move to the next node
        }
    cout << endl; // New line after printing the number
}

    //helper function to check if the number is negative
    bool checkNegative(char first_char){
        //if the fisrt character is the negaive sign
        if(first_char == '-'){
            isNegative = true;
            return isNegative;
        }
        else{
            return isNegative;
        }
    }

    
    //helper function to calculate the number of digits in the fist node
    int numHeadDigits(){
        return numLength%18;
    }

    //helper function to return a string of 18 digits
    string getLast_18_Digits(string &str){
        string result;
        int stringLength = str.length();

        //if the string length is less or equalthan 18
        if (stringLength <= 18){
            //storing the result
            result = str;
            str = "";

            //setting the head node's lenght
            headLength = stringLength ;
        }
        else{
            //if the string length is more than 18
            //taking the last 18 digits
            result = str.substr(stringLength - 18, 18);

            //removing the last 18 digits from the orginal string
            str = str.substr(0, stringLength - 18);
        }

        return result;
    }


    //function to add a node to the start of the list
    void addNode(long long val){
        //creating a new node
        Node* newNode = new Node(val);
        
        //if the list is empty, make the new node as head and tail
        if(isEmpty()){
            head = newNode;
            tail = newNode;
        }
        else{
            //updating the linked list
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        listlength++; 
    }


    //function to store a string into the linked list
    void storeString(string str){
        //if the string is empty
        if (str.empty()) return;

        //checking if the number is negative
        char first = str[0];
        if(checkNegative(first)){
            //removing the negative sign
            str = str.substr(1);

           //storing the lenght of the number
            numLength = str.length();
        }

        while (str != "") {
            //taking the last 18 digits
            string last_18_digits= getLast_18_Digits(str);

            // convert string to long long
            long long num = std::stoll(last_18_digits);

            //adding the node to the start of the list
            addNode(num);
        }
        
        
        



    }
};



//main function 
int main(){
    //creating a list object
    LargeNumber list;
     //storing a string into the linked list
    list.storeString("-123456789012345678901234567890");
    list.print();



    return 0;
}
