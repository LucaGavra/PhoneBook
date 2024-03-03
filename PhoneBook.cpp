#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact() {}

    Contact(const string& name, const string& phone, const string& email)
        : name(name), phone(phone), email(email) {}

    string getName() const {
        return name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getPhone() const {
        return phone;
    }

    void setPhone(const string& phone) {
        this->phone = phone;
    }

    string getEmail() const {
        return email;
    }

    void setEmail(const string& email) {
        this->email = email;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << contact.name << "\t" << contact.phone << "\t" << contact.email;
        return os;
    }
};

class PhoneBook {
private:
    vector<Contact> contacts;

public:
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
        cout << "Contact added successfully" << endl;
        updateContactsFile();
    }

    void updateContact(const string& query, const Contact& updatedContact) {
        for (Contact& contact : contacts) {
            if (contact.getName() == query || contact.getPhone() == query) {
                contact = updatedContact;
                cout << "Contact updated successfully" << endl;
                updateContactsFile();
                return;
            }
        }
        cout << "Error: contact not found" << endl;
    }

    void deleteContact(const string& query) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->getName() == query || it->getPhone() == query) {
                contacts.erase(it);
                cout << "Contact deleted successfully" << endl;
                updateContactsFile();
                return;
            }
        }
        cout << "Error: contact not found" << endl;
    }

    vector<Contact> viewContacts() const {
        return contacts;
    }

    void searchContacts(const string& query) const {
        if (contacts.empty()) {
            cout << "Phone book is empty" << endl;
            return;
        }
        cout << "Name\tPhone\tEmail" << endl;
        for (const Contact& contact : contacts) {
            if (contact.getName() == query || contact.getPhone() == query) {
                cout << contact << endl;
            }
        }
    }

    void readContactsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, phone, email;
            if (iss >> name >> phone >> email) {
                contacts.emplace_back(name, phone, email);
            }
        }

        file.close();
        cout << "Contacts loaded from file successfully" << endl;
    }

    void updateContactsFile() const {
    ofstream file("contacts.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    for (const Contact& contact : contacts) {
        file << contact.getName() << " " << contact.getPhone() << " " << contact.getEmail() << endl;
    }

    file.close();
    cout << "Contacts saved to file successfully" << endl;
}
};


int main() {
    PhoneBook phoneBook;
    phoneBook.readContactsFromFile("contacts.txt");

    int option;

    do {
        cout << "\nPhone Book Menu" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Update Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. View Contacts" << endl;
        cout << "5. Search Contacts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case 1: {
                string name, phone, email;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phone;
                cout << "Enter email address: ";
                cin >> email;
                phoneBook.addContact(Contact(name, phone, email));
                break;
            }
            case 2: {
                if (phoneBook.viewContacts().empty()) {
                    cout << "Phone book is empty" << endl;
                    break;
                }
                string query;
                cout << "Enter name or phone number to update: ";
                cin >> query;
                string updatedName, updatedPhone, updatedEmail;
                cout << "Enter updated name: ";
                cin >> updatedName;
                cout << "Enter updated phone number: ";
                cin >> updatedPhone;
                cout << "Enter updated email address: ";
                cin >> updatedEmail;
                phoneBook.updateContact(query, Contact(updatedName, updatedPhone, updatedEmail));
                break;
            }
            case 3: {
                if (phoneBook.viewContacts().empty()) {
                    cout << "Phone book is empty" << endl;
                    break;
                }
                string query;
                cout << "Enter name or phone number to delete: ";
                cin >> query;
                phoneBook.deleteContact(query);
                break;
            }
            case 4: {
                vector<Contact> contacts = phoneBook.viewContacts();
                if (contacts.empty()) {
                    cout << "Phone book is empty" << endl;
                    break;
                }
                cout << "Name\tPhone\tEmail" << endl;
                for (const Contact& contact : contacts) {
                    cout << contact << endl;
                }
                break;
            }
            case 5: {
                if (phoneBook.viewContacts().empty()) {
                    cout << "Phone book is empty" << endl;
                    break;
                }
                string query;
                cout << "Enter name or phone number to search: ";
                cin >> query;
                phoneBook.searchContacts(query);
                break;
            }
            case 6:
                cout << "Goodbye" << endl;
                break;
            default:
                cout << "Error: invalid option" << endl;
                break;
        }
    } while (option != 6);

    return 0;
}
