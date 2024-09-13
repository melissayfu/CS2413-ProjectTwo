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
// Constructor
Chip(char type, const string& id);

// Method prototypes
void setInput1(Chip* inputChip); // Sets the first input chip
void setInput2(Chip* inputChip); // second input chip (can be NULL)
Chip* getInput1() const { return input1; }
Chip* getInput2() const { return input2; }
void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
void compute(); // Performs the operation based on the chip type
void display() const; // Displays the chip's information
//example: I6, Output = S600 --- for the input Chip
//example: O50, Input 1 = S600 --- for the output Chip
//example: A100, Input 1 = I1, Input 2 = I2, Output = M300
string getId() const; // Returns the chip ID
char getType() const; // Returns the chip type
double getInputValue() const; // Getter for inputValue
void setInputValue(double value); // Setter for inputValue
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

// Returns the chip type
char Chip::getType() const {
    return chipType;
}

// Getter for inputValue
double Chip::getInputValue() const{
    return inputValue;
}

// Setter for inputValue
void Chip::setInputValue(double value) {
    inputValue = value;
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

// Function to find a chip by its ID
Chip* findChipById(Chip** chips, int numChips, const string& chipId) {
    for (int i = 0; i < numChips; i++) {
        if (chips[i]->getId() == chipId) {
            return chips[i];
        }
    }
    return nullptr;
}

int main() {
    int numChips;
    cin >> numChips;
    Chip** chips = new Chip*[numChips];

    // Create an array of Chip object pointers
    for (int i = 0; i < numChips; i++) {
        string chipId;
        cin >> chipId;
        if (chipId[0] == 'A') {
            chips[i] = new AdditionChip(chipId);
        } else if (chipId[0] == 'S') {
            chips[i] = new SubtractionChip(chipId);
        } else if (chipId[0] == 'M') {
            chips[i] = new MultiplicationChip(chipId);
        } else if (chipId[0] == 'N') {
            chips[i] = new NegationChip(chipId);
        } else if (chipId[0] == 'O') {
            chips[i] = new OutputChip(chipId);
        } else if (chipId[0] == 'I') {
            chips[i] = new InputChip(chipId);
        }
    }

    int numCommands;
    cin >> numCommands;
    for (int i = 0; i < numCommands; i++) {
        // read from input the links and make the appropriate
        // connections. You may need to search the array allChips
        // to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
        string command, chip1, chip2;
        cin >> command >> chip1 >> chip2;
        if (command == "A") {
            Chip* inputChip = findChipById(chips, numChips, chip1);
            Chip* outputChip = findChipById(chips, numChips, chip2);
            if (!outputChip->getInput1()) {
                outputChip->setInput1(inputChip);
            } else {
                outputChip->setInput2(inputChip);
            }
        } else if (command == "I") {
            double value;
            cin >> value;
            Chip* inputChip = findChipById(chips, numChips, chip1);
            inputChip->setInputValue(value);
        } else if (command == "C") {
            for (int j = 0; j < numChips; ++j) {
                chips[j]->compute();
            }
        } else if (command == "D") {
            Chip* outputChip = findChipById(chips, numChips, chip1);
            outputChip->display();
        }
    }
    cout << "***** Showing the connections that were established" << endl;
    for (int i = 0; i < numChips; ++i) {
        chips[i]->display();  // for each component created call the display () method
    }

    // Clean up
    for (int i = 0; i < numChips; ++i) {
        delete chips[i];
    }
    delete[] chips;

    return 0;

}