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
    Chip* getInput1() const { return input1; }

public:
    // Constructor
    Chip(char type, const string& id);

    // Method prototypes
    void setInput1(Chip* inputChip); // Sets the first input chip
    void setInput2(Chip* inputChip); // Sets the second input chip (can be NULL)
    void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
    virtual void compute() = 0; // Performs the operation based on the chip type
    virtual void display() const = 0; // Displays the chip's information
    string getId() const; // Returns the chip ID
    char getType() const; // Returns the chip type
    double getInputValue() const; // Getter for inputValue
    void setInputValue(double value); // Setter for inputValue
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
double Chip::getInputValue() const {
    return inputValue;
}

// Setter for inputValue
void Chip::setInputValue(double value) {
    inputValue = value;
}

// Derived classes
class AdditionChip : public Chip {
public:
    AdditionChip(const string& id);
    void compute();
    void display() const;
};

AdditionChip::AdditionChip(const string& id) : Chip('A', id) {}

void AdditionChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() + input2->getInputValue();
    }
}

void AdditionChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

class SubtractionChip : public Chip {
public:
    SubtractionChip(const string& id);
    void compute();
    void display() const;
};

SubtractionChip::SubtractionChip(const string& id) : Chip('S', id) {}

void SubtractionChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() - input2->getInputValue();
    }
}

void SubtractionChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

class MultiplicationChip : public Chip {
public:
    MultiplicationChip(const string& id);
    void compute();
    void display() const;
};

MultiplicationChip::MultiplicationChip(const string& id) : Chip('M', id) {}

void MultiplicationChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() * input2->getInputValue();
    }
}

void MultiplicationChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

class NegationChip : public Chip {
public:
    NegationChip(const string& id);
    void compute();
    void display() const;
};

NegationChip::NegationChip(const string& id) : Chip('N', id) {}

void NegationChip::compute() {
    if (input1) {
        inputValue = -input1->getInputValue();
    }
}

void NegationChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

class DivisionChip : public Chip {
public:
    DivisionChip(const string& id);
    void compute();
    void display() const;
};

DivisionChip::DivisionChip(const string& id) : Chip('D', id) {}

void DivisionChip::compute() {
    if (input1 && input2) {
        inputValue = input1->getInputValue() / input2->getInputValue();
    }
}

void DivisionChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << ", Input 2 = " << (input2 ? input2->getId() : "NULL") << ", Output = " << (output ? output->getId() : "NULL") << endl;
}

class OutputChip : public Chip {
public:
    OutputChip(const string& id);
    void compute();
    void display() const;
};

OutputChip::OutputChip(const string& id) : Chip('O', id) {}

void OutputChip::compute() {
    if (input1) {
        inputValue = input1->getInputValue();
    }
}

void OutputChip::display() const {
    cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << endl;
}

class InputChip : public Chip {
public:
    InputChip(const string& id);
    void compute();
    void display() const;
};

InputChip::InputChip(const string& id) : Chip('I', id) {}

void InputChip::compute() {}

void InputChip::display() const {
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
        } else if (chipId[0] == 'D') {
            chips[i] = new DivisionChip(chipId);
        } else if (chipId[0] == 'O') {
            chips[i] = new OutputChip(chipId);
        } else if (chipId[0] == 'I') {
            chips[i] = new InputChip(chipId);
        }
    }

    int numCommands;
    cin >> numCommands;
    for (int i = 0; i < numCommands; i++) {
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
            cout << "Computation Starts" << endl;
            for (int j = 0; j < numChips; ++j) {
                chips[j]->compute();
            }
            for (int j = 0; j < numChips; ++j) {
                if (chips[j]->getType() == 'O') {
                    cout << "The output value from this circuit is " << chips[j]->getInputValue() << endl;
                }
            }
        } else if (command == "D") {
            Chip* outputChip = findChipById(chips, numChips, chip1);
            outputChip->display();
        }
    }

    cout << "***** Showing the connections that were established" << endl;
    for (int i = 0; i < numChips; ++i) {
        chips[i]->display();
    }

    return 0;
}