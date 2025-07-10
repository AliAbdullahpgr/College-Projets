#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Donor {
    string name;
    string bloodGroup;
    string contact;
    string address;
    string password;
    string email;
    int age;
    Donor* next;

    Donor(string n, string b, string c, string a, string p, string e, int ag)
        : name(n), bloodGroup(b), contact(c), address(a), password(p), email(e), age(ag), next(nullptr) {}
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Contact: " << contact << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Age: " << age << endl;
    }
};

struct Recipient {
    string name;
    string bloodGroup;
    string contact;
    string address;
    string password;
    string email;
    int units;
    int age;
    Recipient* next;

    Recipient(string n, string b, string c, string a, string p, string e, int u, int ag)
        : name(n), bloodGroup(b), contact(c), address(a), password(p), email(e), units(u), age(ag), next(nullptr) {}
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Contact: " << contact << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Units: " << units << endl;
        cout << "Age: " << age << endl;
    }
};

struct BloodStock {
    string bloodGroup;
    int units;
    BloodStock* next;

    BloodStock(string bg, int u) : bloodGroup(bg), units(u), next(nullptr) {}
};

// Queue implementation for recipients waiting for blood
class RecipientQueue {
    struct Node {
        Recipient* recipient;
        Node* next;

        Node(Recipient* r) : recipient(r), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    RecipientQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Recipient* recipient) {
        Node* newNode = new Node(recipient);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
    }

    Recipient* dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return nullptr;
        }
        Node* temp = front;
        Recipient* recipient = front->recipient;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        return recipient;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "No recipients in the queue.\n";
            return;
        }
        Node* current = front;
        cout << "Recipient Queue:\n";
        while (current) {
            current->recipient->display();
            current = current->next;
        }
    }
};

class BloodDonationSystem {
    Donor* donorsHead;
    Recipient* recipientsHead;
    BloodStock* stockHead;
    RecipientQueue recipientQueue;

public:
    BloodDonationSystem() : donorsHead(nullptr), recipientsHead(nullptr), stockHead(nullptr) {
        initializeStock();
        loadDonorsFromFile();
        loadRecipientsFromFile();
        loadStockFromFile();
    }

    ~BloodDonationSystem() {
        saveDonorsToFile();
        saveRecipientsToFile();
        saveStockToFile();
    }

    void initializeStock() {
        string bloodGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        for (const string& bg : bloodGroups) {
            addBloodStock(bg, 0);
        }
    }

    void addBloodStock(const string& bloodGroup, int units) {
        BloodStock* newStock = new BloodStock(bloodGroup, units);
        if (!stockHead) {
            stockHead = newStock;
        } else {
            BloodStock* current = stockHead;
            while (current->next) current = current->next;
            current->next = newStock;
        }
    }

    void signUp() {
        int userType;
        cout << "1. Donor\n2. Recipient\nChoose account type: ";
        cin >> userType;

        string name, bloodGroup, contact, address, password, email;
        int age;

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        while (!regex_match(name, regex("^[A-Za-z ]+$"))) {
            cout << "Invalid name. Please enter a valid name: ";
            getline(cin, name);
        }

        cout << "Enter Blood Group: ";
        cin >> bloodGroup;
        while (!regex_match(bloodGroup, regex("^(A|B|AB|O)[+-]$"))) {
            cout << "Invalid blood group. Please enter a valid blood group (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
            cin >> bloodGroup;
        }

        cout << "Enter Age: ";
        cin >> age;
        while (age <= 0 || age > 120) {
            cout << "Invalid age. Please enter a valid age: ";
            cin >> age;
        }

        cout << "Enter Contact: ";
        cin >> contact;
        while (!regex_match(contact, regex("^\\+?[0-9]{10,15}$"))) {
            cout << "Invalid contact number. Please enter a valid contact number: ";
            cin >> contact;
        }

        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);

        cout << "Enter Email: ";
        cin >> email;
        while (!regex_match(email, regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}$"))) {
            cout << "Invalid email. Please enter a valid email: ";
            cin >> email;
        }

        cout << "Create Password: ";
        cin >> password;
        while (!regex_match(password, regex("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$"))) {
            cout << "Invalid password. Password must be at least 8 characters long and contain at least one letter and one number: ";
            cin >> password;
        }

        if (userType == 1) {
            Donor* newDonor = new Donor(name, bloodGroup, contact, address, password, email, age);
            if (!donorsHead) {
                donorsHead = newDonor;
            } else {
                Donor* current = donorsHead;
                while (current->next) current = current->next;
                current->next = newDonor;
            }
            cout << "Donor account created successfully!\n";
        } else if (userType == 2) {
            int units;
            cout << "Enter Units Needed (for recipients): ";
            cin >> units;
            while(units <= 0 || units > 3) {
            cout << "Invalid input. Enter units between 1 and 3: ";
            cin >> units;
        }

            Recipient* newRecipient = new Recipient(name, bloodGroup, contact, address, password, email, units, age);
            if (!recipientsHead) {
                recipientsHead = newRecipient;
            } else {
                Recipient* current = recipientsHead;
                while (current->next) current = current->next;
                current->next = newRecipient;
            }
            recipientQueue.enqueue(newRecipient);
            cout << "Recipient account created successfully!\n";
        } else {
            cout << "Invalid account type.\n";
        }
    }

    void processQueue() {
        cout << "Processing recipient queue:\n";
        while (!recipientQueue.isEmpty()) {
            Recipient* recipient = recipientQueue.dequeue();
            if (!recipient) continue;

            BloodStock* stock = stockHead;
            bool isMatched = false;

            while (stock) {
                if (stock->bloodGroup == recipient->bloodGroup) {
                    if (stock->units >= recipient->units) {
                        stock->units -= recipient->units;
                        cout << "Blood provided to recipient:\n";
                        recipient->display();
                        isMatched = true;
                    } else {
                        cout << "Insufficient blood stock for recipient:\n";
                        recipient->display();
                    }
                    break;
                }
                stock = stock->next;
            }

            if (!isMatched) {
                cout << "No matching blood group found for recipient:\n";
                recipient->display();
            }
        }
    }

    void displayStock() {
        cout << "Current Blood Stock:\n";
        BloodStock* current = stockHead;
        while (current) {
            cout << "Blood Group: " << current->bloodGroup << ", Units: " << current->units << endl;
            current = current->next;
        }
    }

    void loadDonorsFromFile() {
        ifstream file("donors.txt");
        if (!file) return;

        string name, bloodGroup, contact, address, password, email;
        int age;
        while (file >> name >> bloodGroup >> contact >> address >> password >> email >> age) {
            Donor* newDonor = new Donor(name, bloodGroup, contact, address, password, email, age);
            if (!donorsHead) {
                donorsHead = newDonor;
            } else {
                Donor* current = donorsHead;
                while (current->next) current = current->next;
                current->next = newDonor;
            }
        }
        file.close();
    }

    void saveDonorsToFile() {
        ofstream file("donors.txt");
        Donor* current = donorsHead;
        while (current) {
            file << current->name << " " << current->bloodGroup << " " << current->contact << " "
                 << current->address << " " << current->password << " " << current->email << " "
                 << current->age << endl;
            current = current->next;
        }
        file.close();
    }

    void loadRecipientsFromFile() {
        ifstream file("recipients.txt");
        if (!file) return;

        string name, bloodGroup, contact, address, password, email;
        int units, age;
        while (file >> name >> bloodGroup >> contact >> address >> password >> email >> units >> age) {
            Recipient* newRecipient = new Recipient(name, bloodGroup, contact, address, password, email, units, age);
            if (!recipientsHead) {
                recipientsHead = newRecipient;
            } else {
                Recipient* current = recipientsHead;
                while (current->next) current = current->next;
                current->next = newRecipient;
            }
            recipientQueue.enqueue(newRecipient);
        }
        file.close();
    }

    void saveRecipientsToFile() {
        ofstream file("recipients.txt");
        Recipient* current = recipientsHead;
        while (current) {
            file << current->name << " " << current->bloodGroup << " " << current->contact << " "
                 << current->address << " " << current->password << " " << current->email << " "
                 << current->units << " " << current->age << endl;
            current = current->next;
        }
        file.close();
    }

    void loadStockFromFile() {
        ifstream file("stock.txt");
        if (!file) return;

        string bloodGroup;
        int units;
        while (file >> bloodGroup >> units) {
            BloodStock* stock = stockHead;
            while (stock) {
                if (stock->bloodGroup == bloodGroup) {
                    stock->units = units;
                    break;
                }
                stock = stock->next;
            }
        }
        file.close();
    }

    void saveStockToFile() {
        ofstream file("stock.txt");
        BloodStock* current = stockHead;
        while (current) {
            file << current->bloodGroup << " " << current->units << endl;
            current = current->next;
        }
        file.close();
    }
    void signIn() {
    int userType;
    cout << "1. Donor\n2. Recipient\n3. Admin\nChoose account type: ";
    cin >> userType;

    string email, password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    if (userType == 1) {
        // Donor Sign In
        Donor* current = donorsHead;
        while (current) {
            if (current->email == email && current->password == password) {
                cout << "Welcome, " << current->name << "!\n";
                donorMenu(current);
                return;
            }
            current = current->next;
        }
        cout << "Invalid email or password for donor.\n";
    } else if (userType == 2) {
        // Recipient Sign In
        Recipient* current = recipientsHead;
        while (current) {
            if (current->email == email && current->password == password) {
                cout << "Welcome, " << current->name << "!\n";
                recipientMenu(current);
                return;
            }
            current = current->next;
        }
        cout << "Invalid email or password for recipient.\n";
    } else if (userType == 3) {
        // Admin Sign In
        if (email == "admin@admin.com" && password == "admin123") {
            cout << "Welcome, Admin!\n";
            adminMenu();
        } else {
            cout << "Invalid email or password for admin.\n";
        }
    } else {
        cout << "Invalid account type.\n";
    }
}

void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Display Blood Stock\n";
        cout << "2. Process Recipient Queue\n";
        cout << "3. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayStock();
                break;
            case 2:
                processQueue();
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void donorMenu(Donor* donor) {
    int choice;
    do {
        cout << "\n--- Donor Menu ---\n";
        cout << "1. Donate Blood\n";
        cout << "2. View Profile\n";
        cout << "3. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                donateBlood(donor);
                break;
            case 2:
                donor->display();
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void donateBlood(Donor* donor) {
     unsigned int units;
    cout << "Enter units to donate: ";
    cin >> units;
    while(units > 3 || units <= 0){
    cout << "Invalid input. Enter units between 1 and 3: ";
    cin >> units;
    }

    BloodStock* current = stockHead;
    while (current) {
        if (current->bloodGroup == donor->bloodGroup) {
            current->units += units;
            cout << "Thank you for donating " << units << " units of " << donor->bloodGroup << " blood!\n";
            return;
        }
        current = current->next;
    }
    cout << "Error: Unable to update blood stock.\n";
}

void recipientMenu(Recipient* recipient) {
    int choice;
    do {
        cout << "\n--- Recipient Menu ---\n";
        cout << "1. Request Blood\n";
        cout << "2. View Profile\n";
        cout << "3. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                requestBlood(recipient);
                break;
            case 2:
                recipient->display();
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void requestBlood(Recipient* recipient) {
    recipientQueue.enqueue(recipient);
    cout << "Your request for " << recipient->units << " units of " << recipient->bloodGroup << " blood has been added to the queue.\n";
}

};
int main() {
    BloodDonationSystem system;

    int choice;
    do {
        cout << "\n--- Blood Donation Management System ---\n";
        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                system.signUp();
                break;
            case 2:
                system.signIn();
                break;
            case 3:
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
