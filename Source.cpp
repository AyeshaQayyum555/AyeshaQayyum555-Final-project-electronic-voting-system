#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;
// Text Color Codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define BG_WHITE "\033[47m"

// ---------------- Base User Class ----------------
class User {
protected:
    string username;
    string password;

public:
    User() : username(""), password("") {}
    User(string uname, string pword) : username(uname), password(pword) {}

    virtual bool login(const string& uname, const string& pword) {
        return (username == uname && password == pword);
    }
    virtual string getRole() = 0;
    virtual void displayMenu() = 0;
  virtual ~User() {}
};
class Election {
protected:
    string fileName;
public:
    virtual void createElection() = 0;
    virtual void addCandidate() = 0;
    virtual void viewCandidates() = 0;
    virtual void displayResults() = 0;
    virtual ~Election() {}
};
class NationalElection : public Election {
public:
    NationalElection() { fileName = "national_candidates.txt"; }

    void createElection() override {
        string startDate, endDate;
        ofstream file("election_status.txt", ios::app);
        cout << "Enter Start Date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, startDate);
        cout << "Enter End Date (DD-MM-YYYY): ";
        getline(cin, endDate);
        file << "National Election" << ", " << startDate << ", " << endDate << endl;
        file.close();
        cout << "National Election created successfully!\n";
    }
 void addCandidate() override {
        ofstream file(fileName, ios::app);
        string name, party, role = "", cnic;
        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Party Name: ";
        getline(cin, party);
        cout << "Enter Candidate CNIC: ";
        getline(cin, cnic);
        cout << "Is this candidate running for Prime Minister? (yes/no): ";
        getline(cin, role);
        role = (role == "yes") ? "PM" : "";

        file << name << "," << party << "," << "N/A" << ",0," << role << "," << cnic << "\n";
        file.close();
        cout << "Candidate added successfully!\n";
    }
 void viewCandidates() override {
        ifstream file(fileName);
        if (!file) {
            cout << "Error opening " << fileName << endl;
            return;
        }

        string name, party, region, votesStr, role, cnic, line;
        cout << YELLOW;
        cout << "\n--- National Election Candidates ---\n";
        cout << left << " | " << setw(25) << "Name"
            << " | " << setw(10) << "Party"
            << " | " << setw(10) << "Region"
            << " | " << setw(6) << "Votes"
            << " | " << setw(6) << "Role"
            << " | " << setw(17) << "CNIC"
            << " |\n";
        cout << string(90, '-') << "\n";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            if (name.empty()) name = "N/A";
            if (party.empty()) party = "N/A";
            if (region.empty()) region = "N/A";
            if (votesStr.empty()) votesStr = "0";
            if (role.empty()) role = "N/A";
            if (cnic.empty()) cnic = "N/A";

            cout << left << " | " << setw(25) << name
                << " | " << setw(10) << party
                << " | " << setw(10) << region
                << " | " << setw(6) << votesStr
                << " | " << setw(6) << role
                << " | " << setw(17) << cnic
                << " |\n";
        }
        cout << RESET;
        file.close();
    }
 void displayResults() override {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file: " << fileName << endl;
            return;
        }

        string line, name, party, region, role, cnic, votesStr;
        int votes, highestVotes = -1;
        string winnerName = "", winnerParty = "";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            votes = stoi(votesStr);
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            role.erase(remove_if(role.begin(), role.end(), ::isspace), role.end());

            if (role == "PM" && votes > 30 && votes > highestVotes) {
                highestVotes = votes;
                winnerName = name;
                winnerParty = party;
            }
        }

        if (highestVotes != -1)
            cout << "Prime Minister: " << winnerName << " (" << winnerParty << ") with " << highestVotes << " votes.\n";
        else
            cout << "No eligible PM candidate found.\n";

        file.close();
    }
};
// ---------------- Provincial Election ----------------
class ProvincialElection : public Election {
public:
    ProvincialElection() { fileName = "provincial_candidates.txt"; }

    void createElection() override {
        string startDate, endDate;
        ofstream file("election_status.txt", ios::app);
        cout << "Enter Start Date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, startDate);
        cout << "Enter End Date (DD-MM-YYYY): ";
        getline(cin, endDate);
        file << "Provincial Election" << ", " << startDate << ", " << endDate << endl;
        file.close();
        cout << "Provincial Election created successfully!\n";
    }
  void addCandidate() override {
        ofstream file(fileName, ios::app);
        string name, party, role = "", cnic;
        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Party Name: ";
        getline(cin, party);
        cout << "Enter Candidate CNIC: ";
        getline(cin, cnic);
        cout << "Is this candidate running for MPA? (yes/no): ";
        getline(cin, role);
        role = (role == "yes") ? "MPA" : "";

        file << name << "," << party << "," << "N/A" << ",0," << role << "," << cnic << "\n";
        file.close();
        cout << "Candidate added successfully!\n";
    }
  void viewCandidates() override {
        ifstream file(fileName);
        if (!file) {
            cout << "Error opening " << fileName << endl;
            return;
        }

        string name, party, region, votesStr, role, cnic, line;
        cout << YELLOW;
        cout << "\n--- Provincial Election Candidates ---\n";
        cout << left << " | " << setw(25) << "Name"
            << " | " << setw(10) << "Party"
            << " | " << setw(10) << "Region"
            << " | " << setw(6) << "Votes"
            << " | " << setw(6) << "Role"
            << " | " << setw(17) << "CNIC"
            << " |\n";
        cout << string(90, '-') << "\n";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            if (name.empty()) name = "N/A";
            if (party.empty()) party = "N/A";
            if (region.empty()) region = "N/A";
            if (votesStr.empty()) votesStr = "0";
            if (role.empty()) role = "N/A";
            if (cnic.empty()) cnic = "N/A";

            cout << left << " | " << setw(25) << name
                << " | " << setw(10) << party
                << " | " << setw(10) << region
                << " | " << setw(6) << votesStr
                << " | " << setw(6) << role
                << " | " << setw(17) << cnic
                << " |\n";
        }
        cout << RESET;
        file.close();
    }
 void displayResults() override {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file: " << fileName << endl;
            return;
        }

        string line, name, party, region, role, cnic, votesStr;
        int votes, highestVotes = -1;
        string winnerName = "", winnerParty = "";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            votes = stoi(votesStr);
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            role.erase(remove_if(role.begin(), role.end(), ::isspace), role.end());

            if (role == "MPA" && votes > 30 && votes > highestVotes) {
                highestVotes = votes;
                winnerName = name;
                winnerParty = party;
            }
        }

        if (highestVotes != -1)
            cout << "MPA: " << winnerName << " (" << winnerParty << ") with " << highestVotes << " votes.\n";
        else
            cout << "No eligible MPA candidate found.\n";

        file.close();
    }
};
// ---------------- Local Election ----------------
class LocalElection : public Election {
public:
    LocalElection() { fileName = "local_candidates.txt"; }

    void createElection() override {
        string startDate, endDate;
        ofstream file("election_status.txt", ios::app);
        cout << "Enter Start Date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, startDate);
        cout << "Enter End Date (DD-MM-YYYY): ";
        getline(cin, endDate);
        file << "Local Election" << ", " << startDate << ", " << endDate << endl;
        file.close();
        cout << "Local Election created successfully!\n";
    }
 void addCandidate() override {
        ofstream file(fileName, ios::app);
        string name, party, role = "", cnic;
        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Party Name: ";
        getline(cin, party);
        cout << "Enter Candidate CNIC: ";
        getline(cin, cnic);
        cout << "Is this candidate running for Mayor? (yes/no): ";
        getline(cin, role);
        role = (role == "yes") ? "Mayor" : "";

        file << name << "," << party << "," << "N/A" << ",0," << role << "," << cnic << "\n";
        file.close();
        cout << "Candidate added successfully!\n";
    }

    void viewCandidates() override {
        ifstream file(fileName);
        if (!file) {
            cout << "Error opening " << fileName << endl;
            return;
        }

        string name, party, region, votesStr, role, cnic, line;
        cout << YELLOW;
        cout << "\n--- Local Election Candidates ---\n";
        cout << left << " | " << setw(25) << "Name"
            << " | " << setw(10) << "Party"
            << " | " << setw(10) << "Region"
            << " | " << setw(6) << "Votes"
            << " | " << setw(6) << "Role"
            << " | " << setw(17) << "CNIC"
            << " |\n";
        cout << string(90, '-') << "\n";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            if (name.empty()) name = "N/A";
            if (party.empty()) party = "N/A";
            if (region.empty()) region = "N/A";
            if (votesStr.empty()) votesStr = "0";
            if (role.empty()) role = "N/A";
            if (cnic.empty()) cnic = "N/A";

            cout << left << " | " << setw(25) << name
                << " | " << setw(10) << party
                << " | " << setw(10) << region
                << " | " << setw(6) << votesStr
                << " | " << setw(6) << role
                << " | " << setw(17) << cnic
                << " |\n";
        }
        cout << RESET;
        file.close();
    }
  void displayResults() override {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file: " << fileName << endl;
            return;
        }

        string line, name, party, region, role, cnic, votesStr;
        int votes, highestVotes = -1;
        string winnerName = "", winnerParty = "";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            votes = stoi(votesStr);
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            role.erase(remove_if(role.begin(), role.end(), ::isspace), role.end());

            if (role == "Mayor" && votes > 30 && votes > highestVotes) {
                highestVotes = votes;
                winnerName = name;
                winnerParty = party;
            }
        }

        if (highestVotes != -1)
            cout << "Mayor: " << winnerName << " (" << winnerParty << ") with " << highestVotes << " votes.\n";
        else
            cout << "No eligible Mayor candidate found.\n";

        file.close();
    }
};
class Administrator : public User {
private:
    Election* currentElection = nullptr;

    // Utility to clean up memory
    void clearElection() {
        if (currentElection != nullptr) {
            delete currentElection;
            currentElection = nullptr;
        }
    }
// Factory method to instantiate the right election type
    void selectElectionType() {
        int choice;
        cout << "\nSelect Election Type:\n";
        cout << "1. National Election\n";
        cout << "2. Provincial Election\n";
        cout << "3. Local Election\n";
        cout << "Choice: ";
        cin >> choice;

        clearElection(); // Ensure no memory leaks

        switch (choice) {
        case 1: currentElection = new NationalElection(); 
            break;
        case 2: currentElection = new ProvincialElection(); 
            break;
        case 3: currentElection = new LocalElection(); 
            break;
        default:
            cout << "Invalid choice. Defaulting to National Election.\n";
            currentElection = new NationalElection();
            break;
        }
    }
public:
    string getRole() override { return "Administrator"; }
    void displayMenu() override {

        cout << BG_WHITE << GREEN;
        cout << "----------------------------------\n";
        cout << "|        Admin Menu              |\n";
        cout << "----------------------------------\n";
        cout << "| 1. Register Voter              |\n";
        cout << "| 2. Create Election             |\n";
        cout << "| 3. Add Candidates              |\n";
        cout << "| 4. View Candidates             |\n";
        cout << "| 5. View Voters                 |\n";
        cout << "| 6. View Results                |\n";
        cout << "| 7. Exit                        |\n";
        cout << "----------------------------------" << RESET << endl;
    }
    void createElectionMenu() {
        int electionChoice;
        system("CLS");
        cout << BG_WHITE << GREEN;
        cout << "----------------------------------\n";
        cout << "|      Create Election           |\n";
        cout << "----------------------------------\n";
        cout << "| 1. National Election           |\n";
        cout << "| 2. Provincial Election         |\n";
        cout << "| 3. Local Election              |\n";
        cout << "| 4. Exit                        |\n";
        cout << "----------------------------------\n";
        cout << RESET;
        cout << "Enter your choice: ";
        cin >> electionChoice;
        cin.ignore();
        if (electionChoice == 1)
            createElection("election_status.txt", "National Election");
        else if (electionChoice == 2)
            createElection("election_status.txt", "Provincial Election");
        else if (electionChoice == 3)
            createElection("election_status.txt", "Local Election");
        else
            cout << "Invalid choice!\n";
    }
    void createElection(const string& fileName, const string& title) {
        ofstream file(fileName, ios::app);
        string startDate, endDate;
        cout << "Enter Start Date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, startDate);
        cout << "Enter End Date (DD-MM-YYYY): ";
        getline(cin, endDate);

        file << title << ", " << startDate << ", " << endDate << endl;
        file.close();
        cout << title << " created successfully!\n";
    }
    void addCandidate(const string& fileName) {
        ofstream file(fileName, ios::app);
        string name, party, region = "", role = "", cnic;

        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Party Name: ";
        getline(cin, party);
        cout << "Enter Candidate CNIC: "; //  CNIC Add Kiya
        getline(cin, cnic);

        if (fileName == "local_candidates.txt") {
            cout << "Enter City: ";
            getline(cin, region);
        }
        else if (fileName == "provincial_candidates.txt") {
            cout << "Enter Province: ";
            getline(cin, region);
            cout << "Is this candidate running for Chief Minister? (yes/no): ";
            getline(cin, role);
            role = (role == "yes") ? "CM" : "";
        }
        else if (fileName == "national_candidates.txt") {
            cout << "Is this candidate running for Prime Minister? (yes/no): ";
            getline(cin, role);
            role = (role == "yes") ? "PM" : "";
        }

        file << name << "," << party << "," << region << ",0," << role << "," << cnic << "\n"; //  CNIC Store Kiya
        file.close();
        cout << "Candidate added successfully!\n";
    }
    void addCandidateMenu() {
        int addChoice;
        cout << BG_WHITE << GREEN;
        cout << "----------------------------------\n";
        cout << "|       Add Candidate            |\n";
        cout << "----------------------------------\n";
        cout << "| 1. National Election           |\n";
        cout << "| 2. Provincial Election         |\n";
        cout << "| 3. Local Election              |\n";
        cout << "| 4. Exit                        |\n";
        cout << "----------------------------------\n";
        cout << RESET;
        cout << "Enter your choice: ";
        cin >> addChoice;
        cin.ignore();
        if (addChoice == 1)
            addCandidate("national_candidates.txt");
        else if (addChoice == 2)
            addCandidate("provincial_candidates.txt");
        else if (addChoice == 3)
            addCandidate("local_candidates.txt");
        else
            cout << "Invalid choice!\n";
    }
    void viewCandidates(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening " << filename << endl;
            return;
        }

        string name, party, region, votesStr, role, cnic;
        cout << YELLOW;
        cout << "\n--- Candidates from file: " << filename << " ---\n";
        cout << left << " | " << setw(25) << "Name"
            << " | " << setw(10) << "Party"
            << " | " << setw(10) << "Region"
            << " | " << setw(6) << "Votes"
            << " | " << setw(6) << "Role"
            << " | " << setw(17) << "CNIC"
            << " |\n";
        cout << string(90, '-') << "\n";

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            // Handle missing fields gracefully
            if (name.empty()) name = "N/A";
            if (party.empty()) party = "N/A";
            if (region.empty()) region = "N/A";
            if (votesStr.empty()) votesStr = "0";
            if (role.empty()) role = "N/A";
            if (cnic.empty()) cnic = "N/A";

            cout << left << " | " << setw(25) << name
                << " | " << setw(10) << party
                << " | " << setw(10) << region
                << " | " << setw(6) << votesStr
                << " | " << setw(6) << role
                << " | " << setw(17) << cnic
                << " |\n";
        }
        cout << RESET;

        file.close();
    }
    void viewCandidatesMenu() {
        int viewChoice;
        cout << BG_WHITE << GREEN;
        cout << "----------------------------------\n";
        cout << "|      View Candidates           |\n";
        cout << "----------------------------------\n";
        cout << "| 1. National Election           |\n";
        cout << "| 2. Provincial Election         |\n";
        cout << "| 3. Local Election              |\n";
        cout << "| 4. Exit                        |\n";
        cout << "----------------------------------\n";
        cout << RESET;
        cout << "Enter your choice: ";
        cin >> viewChoice;
        cin.ignore();
        if (viewChoice == 1)
            viewCandidates("national_candidates.txt");
        else if (viewChoice == 2)
            viewCandidates("provincial_candidates.txt");
        else if (viewChoice == 3)
            viewCandidates("local_candidates.txt");
        else
            cout << "Invalid choice!\n";
    }
    void displayGeneralWinner(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line, name, party, region, role, cnic;
        int votes, highestVotes = -1;
        string winnerName = "", winnerParty = "";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            ss >> votes;
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            if (votes > highestVotes) {
                highestVotes = votes;
                winnerName = name;
                winnerParty = party;
            }
        }

        if (highestVotes != -1)
            cout << "Winner: " << winnerName << " (" << winnerParty << ") with " << highestVotes << " votes.\n";
        else
            cout << "No candidates found.\n";

        file.close();
    }
    void displayEligibleWinner(const string& filename, const string& roleTag) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line, name, party, region, role, cnic, votesStr;
        int votes, highestVotes = -1;
        string winnerName = "", winnerParty = "";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, party, ',');
            getline(ss, region, ',');
            getline(ss, votesStr, ',');
            votes = stoi(votesStr);
            getline(ss, role, ',');
            getline(ss, cnic, ',');

            // Remove whitespace from role
            role.erase(remove_if(role.begin(), role.end(), ::isspace), role.end());

            if (role == roleTag && votes > 30 && votes > highestVotes) {
                highestVotes = votes;
                winnerName = name;
                winnerParty = party;
            }
        }

        if (highestVotes != -1)
            cout << "Selected " << roleTag << ": " << winnerName << " (" << winnerParty << ") with " << highestVotes << " votes.\n";
        else
            cout << "No eligible candidate found for " << roleTag << ".\n";

        file.close();
    }
    void viewResults() {
        cout << "\n--- Election Results ---\n";

        cout << "\nLocal Election Results:\n";
        displayGeneralWinner("local_candidates.txt");

        cout << "\nProvincial Election Results (CM Selection):\n";
        displayEligibleWinner("provincial_candidates.txt", "CM");

        cout << "\nNational Election Results (PM Selection):\n";
        displayEligibleWinner("national_candidates.txt", "PM");
    }
    void viewVoters() {
        system("CLS");

        ifstream file("voters.txt");
        if (!file) {
            cout << "Error opening voters.txt\n";
            return;
        }

        string line;
        cout << "\n------------------- Registered Voters -----------------------\n";
        cout << left << " | " << setw(20) << "Name"
            << " | " << setw(20) << "CNIC"
            << " | " << setw(10) << "Age" << " |\n";
        cout << "-------------------------------------------------------------\n";

        while (getline(file, line)) {
            stringstream ss(line);
            string name, cnic, ageStr;
            int age;
            getline(ss, name, ',');
            getline(ss, cnic, ',');
            getline(ss, ageStr, ',');
            age = stoi(ageStr);

            cout << " | " << setw(20) << name << " | " << setw(20) << cnic
                << " | " << setw(10) << age << " |\n";
        }

        file.close();
    }
    void registerVoter() {
        ofstream file("voters.txt", ios::app);
        string name, cnic;
        int age;

        cout << "Enter Voter Name: ";
      /*  cin.ignore();*/
        getline(cin, name);

        cout << "Enter Voter CNIC (without dashes): ";
        getline(cin, cnic);

        cout << "Enter Voter Age: ";
        cin >> age;

        if (age >= 18) {
            file << name << "," << cnic << "," << age << "\n";
            cout << "Voter registered successfully!\n";
        }
        else {
            cout << "Voter must be at least 18 years old to register.\n";
        }

        file.close();
    }
    void adminMenu() {
        int choice;
        do {
            cout << "----------------------------------\n";
            cout << "|        Admin Menu              |\n";
            cout << "----------------------------------\n";
            cout << "| 1. Register Voter              |\n";
            cout << "| 2. Create Election             |\n";
            cout << "| 3. Add Candidates              |\n";
            cout << "| 4. View Candidates             |\n";
            cout << "| 5. View Voters                 |\n";
            cout << "| 6. View Results                |\n";
            cout << "| 7. Exit                        |\n";
            cout << "----------------------------------" << RESET << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                registerVoter(); // your pre-existing voter registration logic
                break;

            case 2: // Create Election
                selectElectionType();
                if (currentElection)
                    currentElection->createElection();
                break;

            case 3: // Add Candidates
                if (!currentElection) selectElectionType();
                if (currentElection)
                    currentElection->addCandidate();
                break;

            case 4: // View Candidates
                if (!currentElection) selectElectionType();
                if (currentElection)
                    currentElection->viewCandidates();
                break;

            case 5: // View Voters
                viewVoters(); // your existing implementation
                break;

            case 6: // View Results
                if (!currentElection) selectElectionType();
                if (currentElection)
                    currentElection->displayResults();
                break;

            case 7:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
            }
        } while (choice != 7);

        clearElection(); // cleanup before exit
    }
};
    

void display() {
    cout << RED;
    cout << R"(
  __             _  _                            _     _             _      _                     
 /      \            |  \|  \                         
|  $$$$$$\ ___      | $$ \$$ ___    __        | $$   | $$    | $$             $$ ___    __  
| $$  | $$|       \ | $$|  \|       \  /      \       | $$   | $$ /      \|   $$ \  |  \|       \  /      \ 
| $$  | $$| $$$$$$$\| $$| $$| $$$$$$$\|  $$$$$$\       \$$\ /  $$|  $$$$$$\\$$$$$$  | $$| $$$$$$$\|  $$$$$$\
| $$  | $$| $$  | $$| $$| $$| $$  | $$| $$    $$        \$$\  $$ | $$  | $$ | $$ __ | $$| $$  | $$| $$  | $$
| $$  | $$| $$  | $$| $$| $$| $$  | $$| $$$$$$$$         \$$ $$  | $$    $$ | $$|  \| $$| $$  | $$| $$  | $$
 \$$    $$| $$  | $$| $$| $$| $$  | $$ \$$     \          \$$$    \$$    $$  \$$  $$| $$| $$  | $$ \$$    $$
  \$$$$$$  \$$   \$$ \$$ \$$ \$$   \$$  \$$$$$$$           \$      \$$$$$$    \$$$$  \$$ \$$   \$$ _\$$$$$$$
                                                                                                  |  \__| $$
                                                                                                   \$$    $$
                                                                                                    \$$$$$$ 
                               _       _                      _        _                                
                              |  \     /  \                    |  \      |  \                               
                              | $$\   /  $$  __    ___ |   __   \$$ ___    __             
                              | $$$\ /  $$$ |      \  /       \| $$    \ |  \|       \  /      \            
                              | $$$$\  $$$$  \$$$$$$\|  $$$$$$$| $$$$$$$\| $$| $$$$$$$\|  $$$$$$\           
                              | $$\$$ $$ $$ /      $$| $$      | $$  | $$| $$| $$  | $$| $$    $$           
                              | $$ \$$$| $$|  $$$$$$$| $$      | $$  | $$| $$| $$  | $$| $$$$$$$$           
                              | $$  \$ | $$ \$$    $$ \$$     \| $$  | $$| $$| $$  | $$ \$$     \           
                               \$$      \$$  \$$$$$$$  \$$$$$$$ \$$   \$$ \$$ \$$   \$$  \$$$$$$$           
                                                                                                            
                                                                                                            
                                                                                                            

             )" << endl;
    cout << RESET;
}
// ---------------- Voter Class --------------
    class Voter : public User {
    private:
        string cnic;
        bool authenticated = false;
        bool hasVotedLocal = false;
        bool hasVotedProvincial = false;
        bool hasVotedNational = false;
        bool hasVotedMPA = false;
        bool hasVotedMNA = false;
        bool isEligibleVoter(const string& fileName, const string& cnicToCheck) {
            ifstream file(fileName);
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, party, region, votesStr, roleTag, cnic;
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                getline(ss, votesStr, ',');
                getline(ss, roleTag, ',');
                getline(ss, cnic, ',');

                if (cnic == cnicToCheck) {
                    int votes = stoi(votesStr);
                    return votes > 30;
                }
            }
            return false;
        }
        bool hasAlreadyVoted() {
            ifstream file("voted.txt");
            string line, voterCnic;
            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, voterCnic, ',');
                if (voterCnic == this->cnic) {
                    return true;
                }
            }
            return false;
        }
      
 public:
        Voter() : User("", "") {}
        Voter(string c) {
            cnic = c;
        }
        string getRole() override { return "Voter"; }
        void displayMenu() override {
            int choice;
            do {
                cout << "\n--- Voter Menu ---\n";
                cout << "1. View Elections\n";
                cout << "2. Cast Vote\n";
                cout << "3. Check Vote Status\n";
                cout << "4. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1:
                    viewElections();
                    break;
                case 2:
                    if (!authenticated) {
                        cout << "Enter your CNIC: ";
                        getline(cin, cnic);
                        if (authenticateVoter()) {
                            cout << "Authentication successful.\n";
                            authenticated = true;
                        }
                        else {
                            cout << "Authentication failed. CNIC not found.\n";
                            break;
                        }
                    }
                    castVote();
                    break;
                case 3:
                    if (!authenticated) {
                        cout << "Enter your CNIC: ";
                        getline(cin, cnic);
                        if (authenticateVoter()) {
                            authenticated = true;
                        }
                        else {
                            cout << "Authentication failed. CNIC not found.\n";
                            break;
                        }
                    }
                    checkVoteStatus();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid option.\n";
                }

            } while (choice != 4);
        }

        bool authenticateVoter() {
            ifstream file("voters.txt");
            string line, voterName, voterCnic, voterAge;

            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, voterName, ',');
                getline(ss, voterCnic, ',');
                getline(ss, voterAge, ',');

                if (voterCnic == this->cnic) {
                    return true;
                }
            }
            return false;
        }

        void castVote() {
            int choice;
            cout << "\n1. Vote as Citizen\n2. Vote as MPA\n3. Vote as MNA\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                if (!hasAlreadyVoted()) {
                    voteCitizen(); // markAsVoted() is already inside voteCitizen()
                }
                else {
                    cout << "You have already voted as a citizen. Cannot vote again.\n";
                }
                break;
            case 2:
                voteMPA();
                break;
            case 3:
                voteMNA();
                break;
            default:
                cout << "Invalid choice.\n";
            }
        }

        void viewElections() {
            ifstream file("election_status.txt");
            string line;
            cout << "\n--- Available Elections ---\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        void checkVoteStatus() {
            ifstream file("voted.txt");
            string line, voterCnic;
            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, voterCnic, ',');
                if (voterCnic == this->cnic) {
                    cout << "You have already voted.\n";
                    file.close();
                    return;
                }
            }
            cout << "You have not voted yet.\n";
        }

    private:
        void voteCitizen() {
            // Check if already voted as citizen
            ifstream votedFile("voted.txt");
            string line;
            while (getline(votedFile, line)) {
                if (line == cnic) {
                    cout << "You have already voted as a citizen.\n";
                    votedFile.close();
                    return;
                }
            }
            votedFile.close();
            while (!(hasVotedLocal && hasVotedProvincial && hasVotedNational)) {
                cout << "\nVote for:\n1. Local Election\n2. Provincial Election\n3. National Election\n";
                int choice;
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1:
                    if (!hasVotedLocal) {
                        vote("local_candidates.txt");
                        hasVotedLocal = true;
                    }
                    else {
                        cout << "You have already voted in Local Election.\n";
                    }
                    break;
                case 2:
                    if (!hasVotedProvincial) {
                        vote("provincial_candidates.txt");
                        hasVotedProvincial = true;
                    }
                    else {
                        cout << "You have already voted in Provincial Election.\n";
                    }
                    break;
                case 3:
                    if (!hasVotedNational) {
                        vote("national_candidates.txt");
                        hasVotedNational = true;
                    }
                    else {
                        cout << "You have already voted in National Election.\n";
                    }
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            }
            cout << "You have successfully voted in all elections as a citizen!\n";
            ofstream file("voted.txt", ios::app);
            file << cnic << endl;
            file.close();
            updateCandidatesEligibility();
        }

        void updateCandidatesEligibility() {
            checkAndUpdateEligibility("provincial_candidates.txt", "MPA");
            checkAndUpdateEligibility("national_candidates.txt", "MNA");
        }

        void checkAndUpdateEligibility(const string& fileName, const string& role) {
            ifstream file(fileName);
            string line, name, party, region, cnic;
            int votes;
            bool eligible = false;

            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                ss >> votes;
                getline(ss, cnic, ',');

                if (votes > 30) {
                    eligible = true;
                    cout << name << " is eligible for " << role << ".\n";
                }
            }
            file.close();

            if (!eligible) {
                cout << "No candidates eligible for " << role << " based on vote count.\n";
            }
        }
        void voteMPA() {
            string voterCnic;
            cout << "Enter your CNIC to verify MPA eligibility: ";
            getline(cin, voterCnic);

            if (isEligibleVoter("provincial_candidates.txt", voterCnic)) {
                if (!hasVotedMPA) {
                    voteEligible("provincial_candidates.txt", 30, "CM");
                    hasVotedMPA = true;
                }
                else {
                    cout << "You have already voted as MPA.\n";
                }
            }
            else {
                cout << "You are not eligible to vote as MPA (need more than 30 votes).\n";
            }
        }
        void voteMNA() {
            string voterCnic;
            cout << "Enter your CNIC to verify MNA eligibility: ";
            getline(cin, voterCnic);

            if (isEligibleVoter("national_candidates.txt", voterCnic)) {
                if (!hasVotedMNA) {
                    voteEligible("national_candidates.txt", 30, "PM");
                    hasVotedMNA = true;
                }
                else {
                    cout << "You have already voted as MNA.\n";
                }
            }
            else {
                cout << "You are not eligible to vote as MNA (need more than 30 votes).\n";
            }
        }
        void vote(const string& fileName, const string& role = "") {
            ifstream file(fileName);
            string line;
            string candidates[100];
            int total = 0;

            cout << "\n--- Candidates ---\n";
            while (getline(file, line) && total < 100) {
                stringstream ss(line);
                string name, party, region, votes, candidateRole;
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                getline(ss, votes, ',');
                getline(ss, candidateRole, ',');

                if (role.empty() || candidateRole == role) {
                    cout << total + 1 << ". " << name << " (" << party << ")\n";
                    candidates[total++] = name;
                }
            }
            file.close();
            if (total == 0) {
                cout << "No candidates available for voting.\n";
                return;
            }

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice < 1 || choice > total) {
                cout << "Invalid choice.\n";
                return;
            }

            updateVotes(fileName, candidates[choice - 1]);
            cout << "Vote casted successfully for " << candidates[choice - 1] << ".\n";
        }

        void voteEligible(const string& fileName, int minVotes, const string& role) {
            ifstream file(fileName);
            string lines[100];
            int totalLines = 0;

            while (getline(file, lines[totalLines]) && totalLines < 100) {
                totalLines++;
            }
            file.close();

            string eligible[100];
            int count = 0;

            cout << "\n--- Eligible Candidates for " << role << " ---\n";
            for (int i = 0; i < totalLines; ++i) {
                stringstream ss(lines[i]);
                string name, party, region, votesStr, roleTag, cnic;
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                getline(ss, votesStr, ',');
                getline(ss, roleTag, ',');
                getline(ss, cnic, ',');

                int votes = stoi(votesStr);
                if (votes >= minVotes && roleTag == role) {
                    eligible[count] = name;
                    cout << count + 1 << ". " << name << " (" << party << ")\n";
                    count++;
                }
            }

            if (count == 0) {
                cout << "No eligible candidates available for voting.\n";
                return;
            }

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice < 1 || choice > count) {
                cout << "Invalid choice.\n";
                return;
            }

            string selected = eligible[choice - 1];

            ofstream outFile(fileName);
            for (int i = 0; i < totalLines; ++i) {
                stringstream ss(lines[i]);
                string name, party, region, votesStr, roleTag, cnic;
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                getline(ss, votesStr, ',');
                getline(ss, roleTag, ',');
                getline(ss, cnic, ',');

                int votes = stoi(votesStr);
                if (name == selected) {
                    votes++;
                }

                outFile << name << "," << party << "," << region << "," << votes << "," << roleTag << "," << cnic << "\n";
            }
            outFile.close();

            cout << "Vote casted successfully for " << selected << " as " << role << ".\n";
        }
        void updateVotes(const string& fileName, const string& candidateName) {
            ifstream file(fileName);
            string lines[100];
            int count = 0;

            while (getline(file, lines[count]) && count < 100) {
                count++;
            }
            file.close();

            ofstream outFile(fileName);
            for (int i = 0; i < count; ++i) {
                stringstream ss(lines[i]);
                string name, party, region, votesStr, roleTag, cnic;
                getline(ss, name, ',');
                getline(ss, party, ',');
                getline(ss, region, ',');
                getline(ss, votesStr, ',');
                getline(ss, roleTag, ',');
                getline(ss, cnic, ',');

                int votes = stoi(votesStr);
                if (name == candidateName) {
                    votes++;
                }

                outFile << name << "," << party << "," << region << "," << votes << "," << roleTag << "," << cnic << "\n";
            }
            outFile.close();
        }
    };
    class Candidate {
    private:
        string* name;
        string* party;
        string* city;
        int voteCount;
        static int totalCandidates; // Static variable

    public:
        // Constructor
        Candidate(string candidateName = "", string candidateParty = "", string candidateCity = "", int votes = 0) {
            name = new string(candidateName);
            party = new string(candidateParty);
            city = new string(candidateCity);
            voteCount = votes;
            totalCandidates++;
        }
        // Destructor
        ~Candidate() {
            delete name;
            delete party;
            delete city;
            totalCandidates--;
        }
        // Copy Constructor (deep copy)
        Candidate(const Candidate& other) {
            name = new string(*other.name);
            party = new string(*other.party);
            city = new string(*other.city);
            voteCount = other.voteCount;
            totalCandidates++;
        }
        // Setters
        void setName(const string& candidateName) {
            *name = candidateName;
        }
        void setParty(const string& candidateParty) {
            *party = candidateParty;
        }
        void setCity(const string& candidateCity) {
            *city = candidateCity;
        }
        void setVoteCount(int votes) {
            voteCount = votes;
        }
        // Getters
        string getName() const {
            return *name;
        }

        string getParty() const {
            return *party;
        }

        string getCity() const {
            return *city;
        }

        int getVoteCount() const {
            return voteCount;
        }

        // Function to increment vote
        void incrementVotes() {
            voteCount++;
        }

        // Display candidate data
        void display() const {
            cout << "Candidate: " << *name
                << " | Party: " << *party
                << " | City: " << *city
                << " | Votes: " << voteCount << endl;
        }

        // Function to get candidate info based on the name
        void getCandidateInfo() {
            string searchName;
            cout << "Enter candidate name: ";
            getline(cin, searchName);

            // Normalize input: remove leading/trailing spaces
            searchName.erase(0, searchName.find_first_not_of(" \t\r\n"));
            searchName.erase(searchName.find_last_not_of(" \t\r\n") + 1);

            ifstream file("local_candidates.txt");
            if (!file) {
                cout << "Error: Unable to open file.\n";
                return;
            }

            string line;
            bool found = false;

            while (getline(file, line)) {
                stringstream ss(line);
                string fileName, fileParty, fileCity, votesStr;

                getline(ss, fileName, ',');
                getline(ss, fileParty, ',');
                getline(ss, fileCity, ',');
                getline(ss, votesStr);

                // Trim fileName
                fileName.erase(0, fileName.find_first_not_of(" \t\r\n"));
                fileName.erase(fileName.find_last_not_of(" \t\r\n") + 1);

                if (fileName == searchName) {
                    *name = fileName;
                    *party = fileParty;
                    *city = fileCity;
                    voteCount = stoi(votesStr);

                    display(); // show name, party, city, votes
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Candidate not found.\n";
            }

            file.close();
        }
        // Friend function for stream insertion
        friend ostream& operator<<(ostream& out, const Candidate& c);
        // Friend function for stream extraction
        friend istream& operator>>(istream& in, Candidate& c);
        // Static function to get total candidates
        static int getTotalCandidates() {
            return totalCandidates;
        }
    };

    // Static member initialization
    int Candidate::totalCandidates = 0;

    // Stream insertion
    ostream& operator<<(ostream& out, const Candidate& c) {
        out << "Candidate: " << *c.name
            << " | Party: " << *c.party
            << " | City: " << *c.city
            << " | Votes: " << c.voteCount;
        return out;
    }

    // Stream extraction
    istream& operator>>(istream& in, Candidate& c) {
        cout << "Enter candidate name: ";
        getline(in, *c.name);
        cout << "Enter party: ";
        getline(in, *c.party);
        cout << "Enter city: ";
        getline(in, *c.city);
        cout << "Enter vote count: ";
        in >> c.voteCount;
        in.ignore(); // clear newline
        return in;
    }

    int main(){
        display();  // Optional startup banner

        int mainChoice;

        while (true) {
            cout << BG_WHITE << GREEN;
            cout << "----------------------------------\n";
            cout << "|        Main Menu               |\n";
            cout << "----------------------------------\n";
            cout << "| 1. Admin                       |\n";
            cout << "| 2. Voter                       |\n";
            cout << "| 3. Candidate                   |\n";
            cout << "| 4. Exit                        |\n";
            cout << "----------------------------------" << RESET << endl;

            cout << "Enter your choice: ";

            if (!(cin >> mainChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << " Invalid input! Please enter a valid number.\n";
                continue;
            }

            cin.ignore(); // Clear newline

            switch (mainChoice) {
            case 1: {
                string password;
                cout << "Enter Admin Password: ";
                getline(cin, password);

                if (password == "SE2425") {
                    Administrator admin;
                    int adminChoice;

                    do {
                        admin.displayMenu();
                        cout << "Enter your choice: ";
                        if (!(cin >> adminChoice)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << " Invalid input! Please enter a valid number.\n";
                            continue;
                        }
                        cin.ignore();
                        system("CLS");

                        switch (adminChoice) {
                        case 1:
                            admin.registerVoter();
                            break;
                        case 2:
                            admin.createElectionMenu();
                            break;
                        case 3:
                            admin.addCandidateMenu();
                            break;
                        case 4:
                            admin.viewCandidatesMenu();
                            break;
                        case 5:
                            admin.viewVoters();
                            break;
                        case 6:
                            admin.viewResults();
                            break;
                        case 7:
                            cout << "Exiting Admin Menu...\n";
                            break;
                        default:
                            cout << " Invalid choice. Please try again.\n";
                        }
                    } while (adminChoice != 7);
                }
                else {
                    cout << " Incorrect password.\n";
                }
                break;
            }

            case 2: {
                string cnic;
                cout << "Enter CNIC (e.g., 12345-6789012-3): ";
                getline(cin, cnic);

                Voter voter(cnic);
                if (!voter.authenticateVoter()) {
                    cout << "Invalid CNIC. Access denied.\n";
                    break;
                }

                int voterChoice;
                do {
                    voter.displayMenu();
                    cout << "Enter your choice: ";
                    if (!(cin >> voterChoice)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a valid number.\n";
                        continue;
                    }
                    cin.ignore();

                    switch (voterChoice) {
                    case 1:
                        voter.viewElections();
                        break;
                    case 2:
                        voter.castVote();
                        break;
                    case 3:
                        voter.checkVoteStatus();
                        break;
                    case 4:
                        cout << "Exiting Voter Menu...\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (voterChoice != 4);
                break;
            }

            case 3: {
                Candidate candidate;
                int candidateChoice;

                do {
                    cout << BG_WHITE << GREEN;
                    cout << "----------------------------------\n";
                    cout << "|      Candidate Menu            |\n";
                    cout << "----------------------------------\n";
                    cout << "| 1. View Candidate Info         |\n";
                    cout << "| 2. Increment Vote Count        |\n";
                    cout << "| 3. Exit                        |\n";
                    cout << "----------------------------------\n" << RESET;

                    cout << "Enter your choice: ";
                    if (!(cin >> candidateChoice)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Please enter a valid number.\n";
                        continue;
                    }
                    cin.ignore();

                    switch (candidateChoice) {
                    case 1:
                        candidate.getCandidateInfo();
                        break;
                    case 2:
                        candidate.incrementVotes();
                        cout << "Votes incremented successfully.\n";
                        break;
                    case 3:
                        cout << "Exiting Candidate Menu...\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (candidateChoice != 3);
                break;
            }

            case 4:
                cout << YELLOW;
                cout << "==============================================\n";
                cout << "                                              \n";
                cout << " THANKYOU FOR USING OUR ONLINE VOTING MACHINE \n";
                cout << "                                              \n";
                cout << "                GROUP MEMBERS                 \n";
                cout << "                2024-SE-2                     \n";
                cout << "                2024-SE-4                     \n";
                cout << "                2024-SE-25                    \n";
                cout << "                                              \n";
                cout << "==============================================\n";
                cout << "Exiting program. Goodbye!\n";
                cout << RESET;
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        return 0;
    }
    