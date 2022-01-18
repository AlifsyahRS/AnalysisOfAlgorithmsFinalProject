#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Class to store contact
// details
class node {
    string name;
    long int tel;
    int id;
  
public:
    node()
    {
        tel = 0;
        id = 0;
    }
    friend class hashing;
};
  
class hashing {

    node data[30001];
    string n;
    long int t;
    int i, index;
  
public:
    hashing()
    {
        i = 0;
        t = 0;
        /*
        for (int iden = 0; iden < 1000; iden++){ // Entering dummy contacts to measure runtime.
            index = iden % 1001;        
            for (int j = 0; j < 1001; j++) {
                if (data[index].id == 0) {
                    data[index].id = iden;
                    data[index].name = "test";
                    data[index].tel = 123;
                    break;
                }
                else
                    index
                        = (index + 1) % 1001;
            }
        }
        index = 1000 % 25001;
        for (int j = 0; j < 1001; j++) {
            if (data[index].id == 0) {
                data[index].id = 25000;
                data[index].name = "yo"; // Target value for search
                data[index].tel = 456;
                break;
            }
            else
                index
                    = (index + 1) % 25001;
        }
        */
    }
    
  
    void createcontact(int size) // Function to add contact
    {

        cout << "\nInput ID for your contact : ";
        cin >> i;
        cout << "\nInput name for your contact: ";
        cin >> n ;   
        cout << "\nInput number for your contact: ";
        cin >> t;

        auto start = steady_clock::now(); // Runtime measured using steady_clock()
        index = i % size;
        for (int j = 0; j < size; j++) {
            if (data[index].id == 0) {
                data[index].id = i;
                data[index].name = n;
                data[index].tel = t;
                break;
            }
            else
                index
                    = (index + 1) % size;
        }
        auto end = steady_clock::now();
        double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
        cout << "Amount of time for insert: " << elapsedTime << " nanoseconds." << endl; // Runtime broadcasted here.
    }
  
    void searchcontact(int size) // Function to search contacts
    {

        int index1, key, flag = 0;
        
        cout << "\nInput id of the contact you would like to find: ";
        cin >> key;

        auto start = steady_clock::now();
        index1 = key % size;
  
        for (int a = 0; a < size; a++) {
            if (data[index1].id == key) {
                flag = 1;
                cout << "\nContact found:" <<endl;
                cout << "\n\t"
                     << data[index1].id
                     << " \t"
                     << data[index1].name
                     << " \t"
                     << data[index1].tel;
                break;
            }
            else
                index1
                    = (index1 + 1) % size;
        }
        if (flag == 0)
            cout << "\nContact not found" << endl;
        auto end = steady_clock::now();
        double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
        cout << "\nAmount of time for search: " << elapsedTime << " nanoseconds." << endl;
    }
  
    void deletecontact(int size) // Function to delete contacts
    {
        int index1, key, flag = 0;
        
        cout << "\nInput the ID of the contact you would like to delete: ";
        cin >> key;

        auto start = steady_clock::now();
        index1 = key % size;

        for (int a = 0; a < size; a++) {
            if (data[index1].id
                == key) {
                flag = 1;
                data[index1].id = 0;
                data[index1].name = " ";
                data[index1].tel = 0;
                cout << "\nContact Succesfully deleted." << endl;
                break;
            }
            else
                index1
                    = (index1 + 1) % size;
        }
        if (flag == 0)
            cout << "\nContact not found" << endl;
        auto end = steady_clock::now();
        double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
        cout << "Amount of time for deletion: " << elapsedTime << " nanoseconds." << endl;        
    }
  
   
    void displaycontact(int size) // Show contacts
    {
        cout << "Contact list: " << endl;
        for (int a = 0; a < size; a++) {
            if (data[a].id != 0) {
                cout << "\n\t"
                     << data[a].id
                     << " \t"
                     << data[a].name
                     << " \t"
                     << data[a].tel;
            }
        }
    }
};
  
int main()
{
    int size;
    hashing s;
    size = 1001;
    char choice;
    
    do
	{
		cout << "\nPhone Directory" << endl; // Showing options
        cout << "Please select one of the following choices" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Search for contact" << endl;
        cout << "3. Delete a contact" << endl;
        cout << "4. Show all contacts" << endl;
        cout << "0. Exit program" << endl;
		cin >> choice;
		cin.get();
		
		choice = toupper(choice);

		switch(choice)
		{
			case '1':	s.createcontact(size);	break;
			case '2':	s.searchcontact(size);	break;
			case '3':	s.deletecontact(size);;	break;
			case '4':	s.displaycontact(size);	break;
		}
	} while (choice != '0' && choice != 'q'); // Program exits if 0 or q is typed

    return 0;
}
