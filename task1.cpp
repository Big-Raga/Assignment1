#include <iostream>
#include <string>
using namespace std;

//creating a class for nodes
class node{
    public:
    static  int processNumber;
    int process_id;
    string name;
    int execution_time;
    int remaining_time;

    node* next;
    node* previous;

    //constructor for the node
    node(string p_name, int execution_time){
        process_id = processNumber++;
        name = p_name;
        execution_time = execution_time;
        remaining_time = execution_time;
        next = nullptr;
        previous = nullptr;
    }

    //fucntion to check if process has been executed
    bool isExecuted(){
        remaining_time <=0;
    }    

};

//creating a class for a linked list
class CLL{
    public:
    node* first;
    int length;

   //constructor
    CLL(){
        first = nullptr;
        length = 0;
    }

    //fucntion to return if the list is empty
    bool isEmpty(){
        return first == nullptr;
    }
    

    //function to check if a new process has arrived
    void checkArrival(int size){
        int difference = length - size;

        //if the previous lenght is less than the actual length than a new process has arrived
        if(size < length){
            //starting with the last process
            node* temp = first->previous;

            //iterates through each newly arrived process
            for (int i = 0; i < difference; i++) {
                cout<<"New process arrives: " << temp->name <<" (Remaining: " << temp->execution_time << ")"<<endl;
            }
        
        }

    }


     //function to print  the processes
     void ListOutAllProcesses(){
        if(!isEmpty()){
            //setting the temporary node to the head
            node* temp = first;

            do{
                //printing the data of each node
                cout<< "Process ID: "<< temp->process_id <<"\nName: "<< temp->name <<"\nExecution Time: "<< temp->execution_time
                 <<"\nRemaining Time: "<< temp->remaining_time <<endl <<endl;

                //updating the temporary node to the next node
                temp = temp->next;
                
            }while (temp != first);
            
            cout<<endl;
        }
        else{
             cout<<"List is empty" <<endl;
            }
    }
     

     //function to print initial processes
     void ListInitialProcesses(){
        if(!isEmpty()){
            //setting the temporary node to the head
            node* temp = first;

            cout<<"Initial Processes: [" ;
            do{
                //printing each node
                if(temp == first->next){
                    cout<< "(" << temp->name << "," << temp->execution_time << ")]\n\n";
                    break;
                }
                else{
                    cout<< "(" << temp->name << "," << temp->execution_time << "), ";
                }   
                
            }while(true);
        }
        else{
             cout<<"List is empty" <<endl;
         }
    }      


    //function to add nodes to the list
    void addTask(int time, string name){
        //creating a new tast
        node* newTask = new node(name, time);
        
        //if the list is empty, make the new node as the first and last node
        if(isEmpty()){
            first = newTask;
            newTask->next = newTask;
            newTask->previous = newTask;
        }
        else{
            //if the list is not empty, add the new task after the last task
            node* temp = first->previous;

            //updating the links of the new task and the last task
            temp->next = newTask;
            newTask->previous = temp;
            newTask->next = first;
            first->previous = newTask;
        }    

        length++;
    }   


    //fucntion to remove all completed processes
    void deleteAllCompletedProcesses(){
        //if the list is not empty
        if(!isEmpty()){
            //setting the temporary node to the head
            node* temp = first;            
            
            //looping through the list until we reach the head
            do{
                //if the process has been executed
                if(temp->isExecuted()){
                    //if the node is the first and last node
                    if(temp == first && temp == first->next){
                        first->next = nullptr;
                        first->previous = nullptr;

                        delete temp;
                        temp = nullptr;
                        first = nullptr;
                    }
                    //if the node is not the first node
                    else if(temp!= first){
                        //updating the links of the previous and next nodes
                        temp->previous->next = temp->next;
                        temp->next->previous = temp->previous;
                    }       
                 }
            }while(temp!= first);

        }
    }

    void ExecuteProcesses(int cycle){


    }

    

    

    

};

// Main function to test the ArrayList class
int main() {
    CLL CPUProcesses;

    
    return 0;
}
