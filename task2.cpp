#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;

// node class
class Node
{
public:
    long long value;
    Node *next;
    Node *previous;

    // constructor
    Node(long long val = 0) : value(val), next(nullptr), previous(nullptr) {}
};

// a linked list to stor a large number
class LargeNumber
{
public:
    Node *head;
    Node *tail;
    bool isNegative;
    int numLength;
    int headLength;
    int listlength = 0;

    // constructor
    LargeNumber() : head(nullptr), tail(nullptr), isNegative(false) {}

    // helper function to check if the link is empty
    bool isEmpty()
    {
        return this->head == nullptr;
    }

    // Function to clear the linked list
    void clear()
    {
        Node *current = head; // Start from the head
        while (current != nullptr)
        {
            Node *nextNode = current->next; // Store the next node
            delete current;                 // Delete the current node
            current = nextNode;             // Move to the next node
        }
        head = nullptr; // Reset head pointer
        tail = nullptr; // Reset tail pointer
        listlength = 0;
        numLength = 0;
    }
    bool Multiple_of_5()
    {
        // check if the last digit of the number is even or a multiple of 5
        return (this->tail->value % 5 == 0);
    }

    bool isEven()
    {
        // check if the last digit of the number is even
        return (this->tail->value % 2 == 0);
    }

    // helper function to print 0s
    string returnValue(Node *node)
    {

        // if the current node is not the head and the value is 0, print zeros
        if (node->previous != nullptr && node->value == 0)
        {
            return "000000000000000000";
        }
        else
        {
            return to_string(node->value);
        }
    }

    // function to print the entire number
    string toString()
    {
        string result = "";

        if (this->isEmpty())
            result.append("0");

        if (this->isNegative)
            result.append("-");

        Node *current = this->head;

        while (current)
        {
            // printing the value of each node
            result.append(returnValue(current));
            current = current->next;
        }

        // Remove leading zeros from the result
        size_t pos = result.find_first_not_of('0');

        // If all characters are '0', the result should be "0"
        if (pos != string::npos)
        {
            // Keep negative sign if present, otherwise trim leading zeros
            if (this->isNegative)
                result = "-" + result.substr(pos);
            else
                result = result.substr(pos);
        }
        else
        {
            // Handle the case where the number is just 0
            result = "0";
        }

        return result;
    }

    // helper function to check if the number is negative
    bool checkNegative(char first_char)
    {
        // if the fisrt character is the negaive sign
        if (first_char == '-')
        {
            this->isNegative = true;
            return this->isNegative;
        }
        else
        {
            return this->isNegative;
        }
    }

    // helper function to compare nodes of the numbers
    bool isNodeValGreater(Node *node_1, Node *node_2)
    {

        // if both nodes are null, the numbers are equal
        if (node_1 == nullptr && node_2 == nullptr)
        {
            return false;
        }

        // if number 2 has more nodes than number 1
        if (node_1 == nullptr)
        {
            return false;
        }

        // if number 1 has more nodes than number 2
        if (node_2 == nullptr)
        {
            return true;
        }

        // comparing current node values
        if (node_1->value > node_2->value)
        {
            return true;
        }
        else if (node_1->value < node_2->value)
        {
            return false;
        }

        // if current nodes are equal, compare the next nodes recursively
        return isNodeValGreater(node_1->next, node_2->next);
    }

    // function to check if the numbers are equal
    bool isEqual(LargeNumber &b)
    {
        return !(this->isGreater(b) || this->isLess(b));
    }

    // function to chcek if the number is less than the 2nd
    bool isLess(LargeNumber &b)
    {
        // comparing lengths
        if (this->listlength < b.listlength)
        {
            return true;
        }
        else if (this->listlength > b.listlength)
        {
            return false;
        }

        // compare digit by digit if lengths are the same
        Node *current = this->head;
        Node *otherCurrent = b.head;

        // while loop runs until we get a nullptr
        while (current != nullptr && otherCurrent != nullptr)
        {
            // if the current value is smaller that the secodn value
            if (current->value < otherCurrent->value)
            {
                return true;
            }
            else if (current->value > otherCurrent->value)
            {
                return false;
            }

            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        // If all digits are the same, return false (they are equal)
        return false;
    }

    // helper function to check which number is bigger
    bool isGreater(LargeNumber &b)
    {
        // comparing the lengths to see which one is larger
        if (this->listlength > b.listlength)
        {
            return true;
        }
        else if (this->listlength < b.listlength)
        {
            return false;
        }

        // storing node values of both lists
        Node *current = this->head;
        Node *otherCurrent = b.head;

        // while loop runs until we get a nullptr
        while (current != nullptr && otherCurrent != nullptr)
        {
            // if the current value is bigger that the secodn value
            if (current->value > otherCurrent->value)
            {
                return true;
            }
            // if the current value is smaller than the secodn value
            else if (current->value < otherCurrent->value)
            {
                return false;
            }

            // move to the next nodes
            current = current->next;
            otherCurrent = otherCurrent->next;
        }

        // if all digits are same rerutn false
        return false;
    }

    // helper function to calculate the number of digits in the fist node
    int numHeadDigits()
    {
        return this->numLength % 18;
    }

    // helper function to check if borrow is required in subtraction
    bool borrowRequired(Node *node_1, Node *node_2)
    {
        // checking if we will need to borrow
        if (node_1 != nullptr && node_2 != nullptr)
        {
            // if the current node value is less than the node value in the second list
            if (node_1->value < node_2->value)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    // helper function to return a string of 18 digits
    string getLast_18_Digits(string &str)
    {
        string result;
        int stringLength = str.length();

        // if the string length is less or equalthan 18
        if (stringLength <= 18)
        {
            // storing the result
            result = str;
            str = "";

            // setting the head node's lenght
            this->headLength = stringLength;
        }
        else
        {
            // if the string length is more than 18
            // taking the last 18 digits
            result = str.substr(stringLength - 18, 18);

            // removing the last 18 digits from the orginal string
            str = str.substr(0, stringLength - 18);
        }

        return result;
    }

    // function to add a node to the start of the list
    void addNode(long long val)
    {
        // creating a new node
        Node *newNode = new Node(val);

        // if the list is empty, make the new node as head and tail
        if (this->isEmpty())
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            // updating the linked list
            newNode->next = this->head;
            this->head->previous = newNode;
            this->head = newNode;
        }
        listlength++;
    }

    // fucntion to add a node at the end of the list
    void addNodeAtEnd(long long val)
    {
        // creating a new node
        Node *newNode = new Node(val);

        // if the list is empty, make the new node as head and tail
        if (this->isEmpty())
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            // updating the linked list
            newNode->previous = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
        listlength++;
    }

    // function to store a string into the linked list
    void storeString(string str)
    {
        // if the string is empty
        if (str.empty())
            return;

        // checking if the number is negative
        char first = str[0];
        if (this->checkNegative(first))
        {
            // removing the negative sign
            str = str.substr(1);
        }
        this->numLength = str.length();

        while (!str.empty())
        {
            // storing the lenght of the number

            // taking the last 18 digits
            string last_18_digits = getLast_18_Digits(str);

            // convert string to long long
            long long num = stoll(last_18_digits);

            // adding the node to the start of the list
            this->addNode(num);
        }
    }

    // function to add two large numbers in the form of lists
    // this will return a linked list which will be the sum
    LargeNumber Addition(LargeNumber &b)
    {
        // creating a new list object to store the result
        LargeNumber result;

        // creating two pointers to traverse the two linked lists
        Node *node_1 = this->tail;
        Node *node_2 = b.tail;

        // to track the carry
        bool carry = false;

        do
        {
            // taking the sum of the current node values
            long long sum = (node_1 != nullptr ? node_1->value : 0) + (node_2 != nullptr ? node_2->value : 0);

            // moving to the next nodes
            if (node_1 != nullptr)
                node_1 = (node_1->previous != nullptr) ? node_1->previous : nullptr;
            if (node_2 != nullptr)
                node_2 = (node_2->previous != nullptr) ? node_2->previous : nullptr;

            // if the sum is greater than 18 digits
            if (sum > 999999999999999999)
            {
                // taking the carry
                carry = true;
                sum = sum - 1000000000000000000;
            }

            // adding the node to the start of the result list
            result.addNode(sum);

            // if there is a carry
            if (carry && node_1 != nullptr)
            {
                node_1->value++;
                carry = false;
            }

        } while (node_1 != nullptr || node_2 != nullptr || carry);

        return result;
    }

    // function to subtact two large numbers in the form of lists
    LargeNumber Subtraction(LargeNumber &b)
    {
        // creating a new list object to store the result
        LargeNumber result;

        // defining two nodes
        Node *node_1;
        Node *node_2;

        // checking which number is larger
        if (this->isGreater(b))
        {
            // this number is larger than than the number b
            node_1 = this->tail;
            node_2 = b.tail;
        }
        else if (this->isEqual(b))
        {
            // the numbers are equal
            return result;
        }
        else
        {
            // the bigger number is set to node 1
            node_2 = this->tail;
            node_1 = b.tail;

            // the result will be negative
            result.isNegative = true;
        }

        do
        {

            // checking if we will need to borrow
            if (borrowRequired(node_1, node_2))
            {
                // if the previous node is not null
                if (node_1->previous)
                {
                    // reduce the previous node's value and add the carry
                    node_1->previous->value--;
                    node_1->value += 1000000000000000000;
                }
            }

            // taking the sum of the current node values
            long long difference = (node_1 != nullptr ? node_1->value : 0) - (node_2 != nullptr ? node_2->value : 0);

            // moving to the next nodes
            if (node_1 != nullptr)
                node_1 = (node_1->previous != nullptr) ? node_1->previous : nullptr;
            if (node_2 != nullptr)
                node_2 = (node_2->previous != nullptr) ? node_2->previous : nullptr;

            // adding the node to the result list
            result.addNode(difference);

        } while (node_1 != nullptr || node_2 != nullptr);

        return result;
    }

    // function to multiply 2 large numbers
    LargeNumber Multiplication(LargeNumber &b)
    {
        // initializing a large number to store the result
        LargeNumber result;

        // if any number is null the answer will b 0
        if (this->isEmpty() || b.isEmpty())
        {
            result.addNode(0);
            return result;
        }

        // vector to stoer partial sums
        vector<LargeNumber> partial_sums;

        // to keep track of the shift count, used when we add the partial sums
        int shift_count = 0;

        // the end digits of the first number
        Node *node_1 = this->tail;

        while (node_1 != nullptr)
        {
            // temporary variable to store the partial sum
            LargeNumber temp;

            Node *node_2 = b.tail;

            // 128 bit to keep track of the carry, 128 used to avoid overlflow
            __uint128_t carry = 0;

            // adding 0s to account for the shift
            for (int i = 0; i < shift_count; ++i)
            {
                temp.addNode(0);
            }

            // each node of the first number will be mutiplied wiht all the nodes of number 2
            while (node_2 != nullptr)
            {
                // multiplying the current nodes and storing it ina 128 variable to avoid overflow
                __uint128_t product = (__uint128_t)node_1->value * (__uint128_t)node_2->value + carry;

                // adding the last 1 digits of the product into the temp list
                temp.addNode((long long)(product % 1000000000000000000));

                // calculating the carry, whcih are the digits before the last 18 digists
                carry = product / 1000000000000000000;

                // move to the next node
                node_2 = node_2->previous;
            }

            if (carry > 0)
            {
                temp.addNode((long long)carry);
            }

            // storing the partial sum into the vector
            partial_sums.push_back(temp);

            // moving to the next node
            node_1 = node_1->previous;

            // increasing the shift
            shift_count++;
        }

        // adding all of the partial sums
        result = partial_sums[0];

        for (size_t i = 1; i < partial_sums.size(); ++i)
        {
            result = result.Addition(partial_sums[i]);
        }

        return result;
    }

    // function to divide two large numberspair<LargeNumber, LargeNumber> Division(LargeNumber &divisor) {
    //  Initializing a large number to store the quotient and the remainder

    // function to increaese or decrease value of the dividend accoriding to the divisor
  // matches the number of digits in divisor to an initial segment of the dividend string
    LargeNumber MatchDigits(LargeNumber &divisor, std::string &strDividend) {
        std::string temp = "";
        int divisorLen = divisor.numLength;
        LargeNumber newDividend;

        // construct the initial dividend segment to match divisor length
        for (int i = 0; i < divisorLen && !strDividend.empty(); i++) {
            temp += strDividend[0];
            strDividend = strDividend.substr(1);
        }

        newDividend.storeString(temp);
        return newDividend;
    }

    // appends the next digit of the string dividend to the LargeNumber dividend
    LargeNumber AddDigit(LargeNumber &dividend, std::string &strDividend) {
        std::string temp = dividend.toString();
        if (!strDividend.empty()) {
            // append the next digit to the current dividend
            temp += strDividend[0];
            strDividend = strDividend.substr(1); // remove the appended digit from the string dividend
        }

        // update dividend with new value
        LargeNumber newDividend;
        newDividend.storeString(temp);
        return newDividend;
    }

    // performs division of *this number by the divisor using repeated subtraction
    std::pair<LargeNumber, LargeNumber> Division(LargeNumber &divisor) {
        LargeNumber quotient, remainder;

        // handle division by zero error
        if (divisor.isEmpty()) {
            throw std::runtime_error("Division by zero is not supported");
        }

        // if dividend is zero, the quotient is also zero
        if (this->isEmpty()) {
            return std::make_pair(quotient, remainder);
        }

        // copy dividend as a string to process individual digits
        std::string currentNodeValue = this->toString();
        LargeNumber dividend;

        // match initial digits in dividend to the divisor length
        dividend = MatchDigits(divisor, currentNodeValue);

        // initialize string to store quotient
        std::string quotientStr;

        while (!currentNodeValue.empty()) {
            // if current dividend is less than divisor, append zero to quotient
            if (dividend.isLess(divisor)) {
                quotientStr += "0";
                // add next digit to dividend
                currentNodeValue += currentNodeValue[0];
                currentNodeValue.erase(currentNodeValue.begin()); // remove digit from dividend string
                dividend = AddDigit(dividend, currentNodeValue);
            } else {
                int count = 0;
                // repeatedly subtract divisor from dividend
                while (dividend.isGreater(divisor) || dividend.isEqual(divisor)) {
                    dividend = dividend.Subtraction(divisor);
                    count++;
                }
                // append the count to the quotient
                quotientStr += std::to_string(count);

                // add next digit to dividend if available
                if (!currentNodeValue.empty()) {
                    dividend = AddDigit(dividend, currentNodeValue);
                    currentNodeValue.erase(currentNodeValue.begin());
                }
            }
        }

        // store computed quotient
        quotient.storeString(quotientStr);
        remainder = dividend; // final state of dividend is the remainder
        return std::make_pair(quotient, remainder);
    }

  // Function for modular exponentiation
    long long modularExponentiation(long long base, long long exponent, long long mod) {
        long long result = 1;
        base = base % mod;

        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = (result * base) % mod;
            }
            exponent = exponent >> 1; // equivalent to exponent / 2
            base = (base * base) % mod;
        }
        return result;
    }

    // Function to check if the LargeNumber is prime
    bool isPrime(int k) {
        // Edge cases
        if (listlength == 0 || (listlength == 1 && head->value < 2)) return false; // 0 and 1 are not prime
        if (head->value == 2 || head->value == 3) return true; // 2 and 3 are prime
        if (head->value % 2 == 0) return false; // exclude even numbers

        // Write n - 1 as d * 2^r
        LargeNumber n = *this; // Store the current number
        LargeNumber d;
        d.addNode(n.tail->value - 1);
        int r = 0;

        LargeNumber n1;
        LargeNumber n2;
        n1.storeString("0");
        n2.storeString("2");
        // Find d and r
        while (d.isLess(n1)) { // Check if d is even
            d = d.Subtraction(n2);
            r++;
        }

        // Witness loop
        for (int i = 0; i < k; i++) {
            // Pick a random base a in [2, n-2]
            long long a = 2 + rand() % (n.head->value - 3);
            
            // Compute x = a^d % n
            long long x = modularExponentiation(a, d.head->value, n.head->value);

            if (x == 1 || x == n.head->value - 1) continue;

            bool found = false;
            for (int j = 0; j < r - 1; j++) {
                x = modularExponentiation(x, 2, n.head->value);
                if (x == n.head->value - 1) {
                    found = true;
                    break;
                }
            }
            if (!found) return false; // n is composite
        }
        return true; // n is probably prime
    }
};

int main() {
 // Create LargeNumber instances for testing
    LargeNumber num1;
    LargeNumber num2;

    // Storing numbers as strings
    num1.storeString("811111111111111111111111111111111111111111111111111111");
    num2.storeString("123456789012345678901234567890");

    // Output the numbers
    cout << "Number 1: " << num1.toString() << endl;
    cout << "Number 2: " << num2.toString() << endl;

    // Addition
    LargeNumber sum = num1.Addition(num2);
    cout << "Addition: " << sum.toString() << endl;

    // Subtraction
    LargeNumber difference = num1.Subtraction(num2);
    cout << "Subtraction: " << difference.toString() << endl;

    // Multiplication
    LargeNumber product = num1.Multiplication(num2);
    cout << "Multiplication: " << product.toString() << endl;

    // Division
    pair<LargeNumber, LargeNumber> divisionResult = num1.Division(num2);
    cout << "Division Quotient: " << divisionResult.first.toString() << endl;
    cout << "Division Remainder: " << divisionResult.second.toString() << endl;

    // Check if num1 is prime
    if (num1.isPrime(10)) {
        cout << "Number 1 is probably prime." << endl;
    } else {
        cout << "Number 1 is composite." << endl;
    }

    return 0;
}


