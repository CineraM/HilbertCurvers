#include "instruction_list.h"
#include <string>
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const InstructionList& il){
/* 
The for loop will iterate thorugh the instruction list.
The switch statement is used to print all possible hilbert_t value,
this is done by attaching them to the ostream
*/
    for(auto it = il.head; it != nullptr; it = it->next){ 
        switch(it->move){
        case FORWARD:
            out << "F" << " ";
            break;
        case TURN_LEFT:
            out << "L" << " ";
            break;
        case TURN_RIGHT:
            out << "R" << " ";
            break;
        case ODD:
            out << "O" << " ";
            break;
        case EVEN:
            out << "E" << " ";
            break;
        }
    }
    return out;
}

void InstructionList::append(hilbert_t ins){

    node_t* new_node = new node_t;   // node to be inserted
    node_t* temp = new node_t;       // temporary node to store the tail
    new_node->move = ins;
    new_node->next = nullptr;

    if(head == nullptr){             // when linked list is empty
        head = new_node;
        tail = new_node; 
    } else {                         // not empty
        temp = tail;                 // set new tail
        temp->next = new_node;
        tail = new_node;  
    }
}

InstructionList::~InstructionList(){
    node_t* cur = new node_t;
    cur = head;

    while(cur != nullptr){          // while loop to iterate thorugh the each node
        node_t* temp = cur->next;   // temp holds the next node in the list
        delete cur;                 // deleting the current
        cur = temp;
    }
}

void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& map){
    node_t* after = nullptr;
    node_t* cur = nullptr; 
    node_t* temp = nullptr;

    // the outer loop iterates thourgh the private member rules from the hilbert cuve class
    for(cur = this->head; cur != nullptr;cur = cur->next)
    {
        after = cur->next;
    // if ODD is found we need to insert the rules from the map replacing ODD node in the procces
        if(cur->move == ODD){   
    // this loop iterates through the map's ODD instructionlist
            for(temp = map.at(ODD)->head; temp != nullptr;
             temp = temp->next, cur = cur->next){   // will increment both temp(map rules) and curr (Hilbert class rules)    
                cur->move = temp->move;             // overwriting the first node, that way we dont need to use "delete"
                if(temp->next == nullptr)
                    break;                          // we break if we are in the last rule to be added
                else
                    cur->next = new node_t;         // else we allocate memory for the next node
            }
            if(after != nullptr)                    // if the next node is not empy we should connect it to current (Hilbert class rules)
                cur->next = after;            
                    
        }
        else if(cur->move == EVEN){                 // same logic for the EVEN map
            for(temp = map.at(EVEN)->head; temp != nullptr;
             temp = temp->next, cur = cur->next){                
                cur->move = temp->move;
                if(temp->next == nullptr)
                    break;
                else
                    cur->next = new node_t;
            }
            if(after != nullptr)
                cur->next = after;                    
        }
    }
}