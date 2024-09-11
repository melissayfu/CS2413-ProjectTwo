#include <string>
#include <iostream>
using namespace std;

class Chip {
protected:
char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
string id; // Unique identifier for the chip
Chip* input1; // Pointer to the first input chip
Chip* input2; // Pointer to the second input chip (can be NULL)
Chip* output; // Ptr to the output chip (is NULL for output chips)
double inputValue; //for the input chip

public:
double getInputValue() const; // Getter for inputValue

public:
// Constructor
Chip(char type, const string& id);
// Method prototypes
void setInput1(Chip* inputChip); // Sets the first input chip
void setInput2(Chip* inputChip); // second input chip (can be NULL)
void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
void compute(); // Performs the operation based on the chip type
void display() const; // Displays the chip's information
//example: I6, Output = S600 --- for the input Chip
//example: O50, Input 1 = S600 --- for the output Chip
//example: A100, Input 1 = I1, Input 2 = I2, Output = M300
string getId() const; // Returns the chip ID
};

// Derived classes from Chip. Each class will implement the compute and display methods. Implementation by using Copilot.
class AdditionChip : public Chip {
public:
    AdditionChip(const string& id);
    void compute();
    void display();
};

class SubtractionChip : public Chip {
public:
    SubtractionChip(const string& id);
    void compute();
    void display();
};

class MultiplicationChip : public Chip {
public:
    MultiplicationChip(const string& id);
    void compute();
    void display();
};

class NegationChip : public Chip {
public:
    NegationChip(const string& id);
    void compute();
    void display();
};

class OutputChip : public Chip {
public:
    OutputChip(const string& id);
    void compute();
    void display();
};

class InputChip : public Chip {
public:
    InputChip(const string& id);
    void compute();
    void display();
};
// Constructor
Chip::Chip(char type, const string& id) : chipType(type), id(id), input1(nullptr), input2(nullptr), output(nullptr), inputValue(0.0) {}

// Sets the first input chip
void Chip::setInput1(Chip* inputChip) {
    input1 = inputChip;
}

// Sets the second input chip (can be NULL)
void Chip::setInput2(Chip* inputChip) {
    input2 = inputChip;
}

// Sets the output chip (can be NULL)
void Chip::setOutput(Chip* outputChip) {
    output = outputChip;
}

// Returns the chip ID
string Chip::getId() const {
    return id;
}

// AdditionChip methods
AdditionChip::AdditionChip(const string& id) : Chip('A', id) {}

void AdditionChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() + input2->getInputValue();
    }
}

void AdditionChip::display() {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

// SubtractionChip methods
SubtractionChip::SubtractionChip(const string& id) : Chip('S', id) {}

void SubtractionChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() - input2->getInputValue();
    }
}

void SubtractionChip::display() {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

// MultiplicationChip methods
MultiplicationChip::MultiplicationChip(const string& id) : Chip('M', id) {}

void MultiplicationChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() * input2->getInputValue();
    }
}

void MultiplicationChip::display() {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

// NegationChip methods
NegationChip::NegationChip(const string& id) : Chip('N', id) {}

void NegationChip::compute() {
    if (input1) {
        inputValue = -input1->getInputValue();
    }
}

void NegationChip::display() {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

// OutputChip methods
OutputChip::OutputChip(const string& id) : Chip('O', id) {}

void OutputChip::compute() {
    if (input1) {
        inputValue = input1->getInputValue();
    }
}

void OutputChip::display() {
    cout << "I am output chip number " << id << ", and the value I received is " << inputValue << "." << endl;
}

// InputChip methods
InputChip::InputChip(const string& id) : Chip('I', id) {}

void InputChip::compute() {}

void InputChip::display() {
    cout << id << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

int main() {
  int numChips;
Chip** allChips;
int numCommands;
cin >> numChips;
//create an array Chip objects pointers
allChips = new Chip*[numChips];

//each array location is a pointer to a Chip Object
for (int i=0; i < numChips; i++) {
//read the chip ID based on the first letter to determine its type
//create the chip object and initialize it appropriately
//store the chip object in the allChips array
}
for (int i=0; i < numCommands; i++) {
// read from input the links and make the appropriate
//connections. You may need to search the array allChips
//to find the chip that is referred and connect.
// If the first letter is an O, then execute the compute method
// on the object referred.
}
cout << "***** Showing the connections that were established" << endl;
//for each component created call the display () method
return 0;
}