#include <iostream>
#include <string>
using namespace std;

// Global process number variable
int processNumber = 1;

//creating a class for nodes
class node{
    public:
    int process_id;
    string name;
    int execution_time;
    int remaining_time;

    node* next;
    node* previous;

    //constructor for the node
    node(string p_name, int Time){
        process_id = processNumber++;
        name = p_name;
        execution_time = Time;
        remaining_time = Time;
        next = nullptr;
        previous = nullptr;
    }

    //fucntion to check if process has been executed
    bool isExecuted(){
       return  remaining_time <=0;
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



     //function to print initial processes
     void ListInitialProcesses(){
        if(!isEmpty()){
            //setting the temporary node to the head
            node* temp = first;

            cout<<"Initial Processes: [" ;
            do{
                //printing each node
                if(temp == first->previous){
                    cout<< "(" << temp->name << "," << temp->execution_time << ")]\n";
                    break;
                }
                else{
                    cout<< "(" << temp->name << "," << temp->execution_time << "), ";
                }   

                temp = temp->next;
                
            }while(temp != first);
        }
        else{
             cout<<"List is empty" <<endl;
         }
    }      

    //function to print the processes as they are being executed
    void ListExecutingProcesses(int cycle, int cycleNumber){
        if(!isEmpty()){
            //setting the temporary node to the head
            node* temp = first;


            cout << "Cycle " << cycleNumber << ": ";

            do {
                //updating the time remaining
                temp->remaining_time -= cycle;

                //printing the status of the current process
                cout << temp->name << " (Remaining: ";
                
                //check if the process is completed or still executing
                if (temp->remaining_time <= 0) {
                    cout << "Completes";
                } else {
                    cout << temp->remaining_time;
                }
                
                //check if we are at the last process
                if(temp == first->previous){
                    cout << ")";
                }
                else{
                    cout << "), ";
                }

                //move to the next node
                temp = temp->next;

            } while (temp != first);
            
            cout << endl;
        } else {
            cout << "No processes in the list." << endl;
        }
    }


     //fucntion to add a new process
     void addProcess(string name, int time){
        addTask(time, name);
        cout << "New process arrives: "<< name << " (Remaining: "<< time << ")" << endl;
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

                        delete temp;
                        first = nullptr;
                        return;
                    }
                    //if the node is not the first node
                    else if(temp == first){
                        //updating the links of the previous and next nodes
                        first->previous->next = first->next;
                        first->next->previous = first->previous;
                        first = first->next;
                    }       
                    else{
                        //updating the links of the previous and next nodes
                        temp->previous->next = temp->next;
                        temp->next->previous = temp->previous;
                    }

                    node* toDelete = temp;
                    temp = temp->next;
                    delete toDelete;
                    length--;
                 }
                 else{
                    temp = temp->next;
                }
            }while(temp!= first && length>0);  

        }
    }

    void ExecuteProcesses(int cycle){

        int counter = 1; 

        //printing the initaial prcoces.
        ListInitialProcesses();
        cout<<"CPU Time per Process per cycle: " << cycle << endl;

        //while loop runs until all processes are completed
        while (!isEmpty()) {
            if(counter == 3){
                 //adding a new process after the 2nd cycle
                 addProcess("P4",9);
             }
             
            //printing the executing processes
            ListExecutingProcesses(cycle,counter); 


             //deleting all completed processes
             deleteAllCompletedProcesses();
             counter ++;
        }
        cout << "All processes have been completed." << endl;
        
    } 

};

// Main function to test the ArrayList class
int main() {
    CLL CPUProcesses;

    // Add initial processes
    CPUProcesses.addTask(10, "P1");
    CPUProcesses.addTask(5, "P2");
    CPUProcesses.addTask(8, "P3");

    // Execute processes with 3 units of time per cycle
    CPUProcesses.ExecuteProcesses(3);

    
    return 0;
}