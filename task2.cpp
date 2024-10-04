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

    //helper function to print 0s
    void printValue(Node* node){
        
        //if the current node is not the head and the value is 0, print zeros
        if(node->previous != nullptr && node->value == 0){
            cout << "000000000000000000";
        }
        else{
            cout << node->value;
        }
    }

    //function to print the entire number
    void print() {
        if (isNegative) {
            //print negative sign if negative
            cout << "-"; 
        }
        Node* current = head;

        while (current) {
            //printing the value of each node
            printValue(current);
            current = current->next; 
        }
    cout << endl;
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

    //helper function to compare nodes of the numbers
    bool isNodeValGreater(Node* node_1, Node* node_2){
        
        //if both nodes are null, the numbers are equal
        if (node_1 == nullptr && node_2 == nullptr) {
            return false; 
        }

        //if number 2 has more nodes than number 1
        if (node_1 == nullptr) {
            return false; 
        }

        //if number 1 has more nodes than number 2
        if (node_2 == nullptr) {
            return true; 
        }

        // comparing current node values
        if (node_1->value > node_2->value) {
            return true;
        } 
        else if (node_1->value < node_2->value) {
        return false; 
        }

        //if current nodes are equal, compare the next nodes recursively
        return isNodeValGreater(node_1->next, node_2->next);
    }


    //helper function to check which number is bigger
    bool isGreater(LargeNumber &b){
        //if the length of the first number is greater than the second number's length
        if(numLength > b.numLength){
            return true;
        }
        //if the length of the first number is less than the second number's length
        else if(numLength < b.numLength){
            return false;
        }
        //if the length of the first number is equal to the second number's length
        else{
            //getting the heads of each list
            Node* current_1 = head;
            Node* current_2 = b.head;

            //calling function which compares the nodes
            return isNodeValGreater(current_1, current_2);                
        }
    }
    
    //helper function to calculate the number of digits in the fist node
    int numHeadDigits(){
        return numLength%18;
    }

    //helper function to check if borrow is required in subtraction
    bool borrowRequired(Node* node_1, Node* node_2){
        //checking if we will need to borrow
        if (node_1 != nullptr && node_2 != nullptr){
            //if the current node value is less than the node value in the second list
            if(node_1->value < node_2->value){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
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
        }

        while (str != "") {
            //storing the lenght of the number
            numLength = str.length();

            //taking the last 18 digits
            string last_18_digits= getLast_18_Digits(str);

            // convert string to long long
            long long num = stoll(last_18_digits);

            //adding the node to the start of the list
            addNode(num);
        }
    
    }


    //function to add two large numbers in the form of lists
    //this will return a linked list which will be the sum
    LargeNumber add(LargeNumber &b){
        //creating a new list object to store the result
        LargeNumber result;

        //creating two pointers to traverse the two linked lists
        Node * node_1 = tail;
        Node * node_2 = b.tail;

        //to track the carry
        bool carry = false;

        do{
                //taking the sum of the current node values
                long long sum = (node_1!= nullptr? node_1->value : 0) + (node_2!= nullptr? node_2->value : 0);


                //moving to the next nodes
                if(node_1 != nullptr)node_1 = (node_1->previous != nullptr) ? node_1->previous : nullptr;
                if(node_2 != nullptr)node_2 = (node_2->previous != nullptr) ? node_2->previous : nullptr;

                //if the sum is greater than 18 digits
                if(sum > 999999999999999999){
                    //taking the carry
                    carry = true;
                    sum = sum - 1000000000000000000;
                }

                //adding the node to the start of the result list
                result.addNode(sum);

                //if there is a carry
                if(carry && node_1!= nullptr){
                    node_1->value++;
                    carry = false;
                }

        }while(node_1 != nullptr || node_2 != nullptr ||carry);

         return result;
    }

    
    //function to subtact two large numbers in the form of lists
    LargeNumber subtract(LargeNumber &b){
          //creating a new list object to store the result
        LargeNumber result;

        //defining two nodes
        Node * node_1;
        Node * node_2;

        //checking which number is larger
        if(isGreater(b)){
            //this number is larger than than the number b
            node_1 = tail;
            node_2 = b.tail;
        }
        else{
            //the bigger number is set to node 1
            node_2 = tail;
            node_1 = b.tail;
            
            //the result will be negative
            result.isNegative = true;
        }

        do{

                //checking if we will need to borrow
                if (borrowRequired(node_1, node_2)){
                    //if the previous node is not null
                    if (node_1->previous) {
                        //reduce the previous node's value and add the carry
                        node_1->previous->value--;  
                        node_1->value += 1000000000000000000;
                    }
                }
                
                //taking the sum of the current node values
                long long difference = (node_1!= nullptr? node_1->value : 0) - (node_2!= nullptr? node_2->value : 0);


                //moving to the next nodes
                if(node_1 != nullptr)node_1 = (node_1->previous != nullptr) ? node_1->previous : nullptr;
                if(node_2 != nullptr)node_2 = (node_2->previous != nullptr) ? node_2->previous : nullptr;
 
                //adding the node to the result list
                result.addNode(difference);


        }while(node_1 != nullptr || node_2 != nullptr);

         return result;

    }
    
};



//main function 
int main(){
    //creating a list object
    LargeNumber list;
    LargeNumber list_b;
     //storing a string into the linked list
    list.storeString("10000000000000000000");
    list.print();

    cout<<endl;

    list_b.storeString("123456789123456789001");
    list_b.print();

    LargeNumber res = list.subtract(list_b);
    res.print();
    if(list.isGreater(list_b)){
        cout<<"\nlist is greater than list_b\n";
    }
    else{
        cout<<"noo\n";
    }



    return 0;
}
