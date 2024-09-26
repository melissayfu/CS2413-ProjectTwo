#include <string>
#include <iostream>
using namespace std;

/*
    Changes Made:
        - Corrected the display logic to show "None" for missing inputs.
        - Fixed the computation logic for all operations.
        - Handled recursive computation of chips to ensure proper ordering.
*/

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
    case 'D': // Division
        if (input1 && input2 && input2->getInputValue() != 0) {
            inputValue = input1->getInputValue() / input2->getInputValue();
        }
        else if (input2->getInputValue() == 0) {
            cout << "Error: Division by zero in chip " << id << endl;
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
        cout << id << ", Input 1 = " << (input1 ? input1->getId() : "NULL") << endl;
    }
    else {
        cout << id;

        if (input1) {
            cout << ", Input 1 = " << input1->getId();
        }

        if (input2) {
            cout << ", Input 2 = " << input2->getId();
        }
        else if (chipType != 'I' && chipType != 'O') {
            cout << ", Input 2 = None";  // Show 'None' for chips that only use 1 input
        }

        if (output) {
            cout << ", Output = " << output->getId();
        }

        cout << endl;
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
        else if (chipId[0] == 'S') {
            chipTypeChar = 'S';
        }
        else if (chipId[0] == 'N') {
            chipTypeChar = 'N';
        }
        else if (chipId[0] == 'O') {
            chipTypeChar = 'O';
        }
        else if (chipId[0] == 'D') {
            chipTypeChar = 'D'; // Division chip
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

    cout << "***** Showing the connections that were established" << endl;
    // Display input chips first
    for (int i = 0; i < numChips; ++i) {
        if (chips[i]->getType() == 'I') {
            chips[i]->display();
        }
    }
    // Display operation chips next
    for (int i = 0; i < numChips; ++i) {
        if (chips[i]->getType() != 'I' && chips[i]->getType() != 'O') {
            chips[i]->display();
        }
    }
    // Display output chip last
    for (int i = 0; i < numChips; ++i) {
        if (chips[i]->getType() == 'O') {
            chips[i]->display();
        }
    }

    // Clean up dynamic memory
    for (int i = 0; i < numChips; ++i) {
        delete chips[i];
    }
    delete[] chips;

    return 0;
}


/*
    LLM and GitHub Copilot Usage Documentation:
    -------------------------------------------

    Prompts and Suggestions:
    1. "Generate a constructor for the Chip class"
       - Copilot helped generate the constructor for the Chip class with initialization of the chipType, id, and input/output values. This was particularly useful for setting up the basic structure of the class.
       
    2. "How can I implement the compute function for an arithmetic chip?"
       - Copilot provided a useful starting point for implementing the recursive compute method, where it suggested calling compute() on the input chips before performing the main operation. This allowed me to handle circuits with multiple layers of connected chips.

    3. "Display the chip information"
       - Copilot suggested adding a display() function, which prints the connections between the chips. This made it easier to debug and understand the established connections between different chip types.

    4. "Set the input chips and establish connections"
       - I asked Copilot for help in establishing input-output relationships between chips. It provided a suggestion that helped set the first and second input chips properly, ensuring no overwrites happen during the connection phase.

    Rationale:
    - I used these suggestions because they provided a well-structured starting point for my methods and allowed me to focus on refining the logic specific to chip behavior.
    - The `compute()` method suggestion, for example, gave a recursive approach, which allowed me to handle the logic of circuits with dependencies on other chips.

    Incremental Development:
    - Initially, I generated the class skeleton using Copilot, defining attributes and method prototypes. 
    - Then, I incrementally implemented individual methods like `setInput1()`, `setInput2()`, and `compute()` while ensuring each part integrated well with the rest of the code.
    - I also asked Copilot for suggestions on memory management (delete operations) to avoid memory leaks, and it helped generate a deletion loop at the end of the main function.

    Debugging and Testing Plan:
    ---------------------------
    Specific Tests:
    - I tested the `compute()` function with different circuits, such as an addition chip connected to two input chips and a negation chip connected to a multiplication chip.
    - I created test cases to check that setting the input values for the chips results in the correct final computation. For example, testing input values of 3 and 4 for an addition chip correctly returned 7.

    Issues and Resolutions:
    - Issue 1: Handling of chips without second inputs (e.g., negation chip) was initially incorrect. The compute function did not account for chips with only one input. I resolved this by adding conditional checks before accessing `input2`.
    - Issue 2: Incorrect mapping of chip types due to edge cases where chip IDs didn’t start with standard letters like 'A' or 'M'. I resolved this by implementing more precise type mappings based on specific chip naming conventions.

    Verification:
    - I verified the correctness of the program by running a set of test cases with various combinations of addition, negation, and multiplication chips.
    - Each chip's connection was verified using the `display()` function, and the output values from the computation were checked against expected results.

    Future Improvements:
    - I could further improve the debugging process by adding more detailed output logs during the recursive compute phase, helping to trace the exact flow of data through each chip.
*/





