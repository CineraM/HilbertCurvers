#include "hilbert.h"
#include "math.h"
using namespace std;



HilbertCurve::HilbertCurve(int level, int size)
: turtle(size, size) //turtle needs to be instantiated before HilbertCurve can be constructed
{ 
    
    //Begin with ODD instruction in the rules list
    rules.append(ODD); 

    //map to be passed to substitute fnc
    unordered_map <hilbert_t, const InstructionList*> map;
    
    //Construct odd_rules list with correct sequence of moves 
    // O -> L E F R O F O R F E L
    InstructionList odd_rules;
    odd_rules.append(TURN_LEFT);
    odd_rules.append(EVEN);
    odd_rules.append(FORWARD);
    odd_rules.append(TURN_RIGHT);
    odd_rules.append(ODD);
    odd_rules.append(FORWARD);
    odd_rules.append(ODD);
    odd_rules.append(TURN_RIGHT);
    odd_rules.append(FORWARD);
    odd_rules.append(EVEN);
    odd_rules.append(TURN_LEFT);

    //initialize ODD key with the correct list value(move sequence) in the map
    map[ODD] =  &odd_rules;

    //Construct even_rules list with correct sequence of moves
    //E -> R O F L E F E L F O R 
    InstructionList even_rules;
    even_rules.append(TURN_RIGHT);
    even_rules.append(ODD);
    even_rules.append(FORWARD);
    even_rules.append(TURN_LEFT);
    even_rules.append(EVEN);
    even_rules.append(FORWARD);
    even_rules.append(EVEN);
    even_rules.append(TURN_LEFT);
    even_rules.append(FORWARD);
    even_rules.append(ODD);
    even_rules.append(TURN_RIGHT);

    //initialize EVEN key with the correct list value(move sequence) in the map
    map[EVEN] = &even_rules;
    
    //for every level, perform the substitution
    for(int i = 0; i<level; i++)
    {
        rules.substitute(map);
    }
    
    //for each level divide the size by a factor of 2
    rules.setDistance(size/pow(2, level));
    
    //pass list of instructions to the turtle's follow function 
    turtle.follow(rules);  
}
