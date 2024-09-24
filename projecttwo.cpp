#include <string>
#include <iostream>
using namespace std;

class Chip {
protected:
    char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
    string id; // Unique identifier for the chip
    Chip* input1; // Pointer to the first input chip
    Chip* input2; // Pointer to the second input chip (can be NULL)
    Chip* output; // Pointer to the output chip (is NULL for output chips)
    double inputValue; // For the input chip

public:
    Chip* getInput1() const { return input1; }
    Chip* getInput2() const { return input2; }
    Chip* getOutput() const { return output; }

    // Constructor
    Chip(char type, const string& id);

    // Method prototypes
    void setInput1(Chip* inputChip); // Sets the first input chip
    void setInput2(Chip* inputChip); // Sets the second input chip (can be NULL)
    void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
    void compute(); // Performs the operation based on the chip type
    void display() const; // Displays the chip's information
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

// Performs the operation based on the chip type with recursive calls
void Chip::compute() {
    // Base case for input chip 'I', no computation needed, value is directly set.
    if (chipType == 'I') {
        return;
    }

    // Recursively compute input chips before performing the operation
    if (input1) {
        input1->compute(); // Ensure input1 is computed
    }
    if (input2) {
        input2->compute(); // Ensure input2 is computed, if it exists
    }

    // Perform the appropriate operation based on the chip type
    switch (chipType) {
    case 'A': // Addition
        if (input1 && input2) {
            inputValue = input1->getInputValue() + input2->getInputValue();
        }
        break;
    case 'S': // Subtraction
        if (input1 && input2) {
            inputValue = input1->getInputValue() - input2->getInputValue();
        }
        break;
    case 'M': // Multiplication
        if (input1 && input2) {
            inputValue = input1->getInputValue() * input2->getInputValue();
        }
        break;
    case 'N': // Negation
        if (input1) {
            inputValue = -(input1->getInputValue());
        }
        break;
    case 'O': // Output
        if (input1) {
            inputValue = input1->getInputValue();
        }
        break;
    }
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

// Display the chip's information
void Chip::display() const {
    if (chipType == 'O') {
        // Special case for the output chip
        cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << endl;
    }
    else {
        cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL")
            << ", Input 2 = " << (input2 ? input2->getId() : "NULL")
            << ", Output = " << (output ? output->getId() : "NULL") << endl;
    }
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
    Chip** chips = new Chip * [numChips];

    // Create an array of Chip object pointers
    for (int i = 0; i < numChips; i++) {
        string chipId;
        char chipTypeChar;

        // We have to map chip types based on naming convention
        cin >> chipId;
        if (chipId[0] == 'I') {
            chipTypeChar = 'I';
        }
        else if (chipId[0] == 'A') {
            chipTypeChar = 'A';
        }
        else if (chipId[0] == 'M') {
            chipTypeChar = 'M';
        }
        else if (chipId[0] == 'O') {
            chipTypeChar = 'O';
        }
        else {
            chipTypeChar = 'I'; // Default fallback
        }

        chips[i] = new Chip(chipTypeChar, chipId);
    }

    int numCommands;
    cin >> numCommands;
    for (int i = 0; i < numCommands; i++) {
        string command;
        cin >> command;

        if (command == "A") {
            string chip1, chip2;
            cin >> chip1 >> chip2;

            Chip* inputChip = findChipById(chips, numChips, chip1);
            Chip* outputChip = findChipById(chips, numChips, chip2);

            // Set inputs and outputs
            if (!outputChip->getInput1()) {
                outputChip->setInput1(inputChip);
            }
            else {
                outputChip->setInput2(inputChip);
            }
            // Set the output for the input chip if it is an intermediate node
            if (!inputChip->getOutput()) {
                inputChip->setOutput(outputChip); // Establish the connection
            }
        }
        else if (command == "I") {
            string chip1;
            double value;
            cin >> chip1 >> value;
            Chip* inputChip = findChipById(chips, numChips, chip1);
            inputChip->setInputValue(value);
        }
        else if (command == "O") {
            string chipId;
            cin >> chipId;

            Chip* outputChip = findChipById(chips, numChips, chipId);
            if (outputChip) {
                cout << "Computation Starts" << endl;
                outputChip->compute();  // Recursively computes based on chip type
                cout << "The output value from this circuit is " << outputChip->getInputValue() << endl;
            }
            else {
                cout << "Chip " << chipId << " not found." << endl;
            }
        }
        else if (command == "D") {
            string chip1;
            cin >> chip1;
            Chip* outputChip = findChipById(chips, numChips, chip1);
            outputChip->display();
        }
    }

    cout << "***** Showing the connections that were established *****" << endl;
    for (int i = 0; i < numChips; ++i) {
        chips[i]->display();
    }

    // Clean up dynamic memory
    for (int i = 0; i < numChips; ++i) {
        delete chips[i];
    }
    delete[] chips;

    return 0;
}
