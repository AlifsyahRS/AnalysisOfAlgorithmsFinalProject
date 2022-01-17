#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

bool isNumber(const string& s)
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) 
            return false;
    }
    return true;
}


class PhoneDirectory {
    private:
        string nameList[30000];
        string phoneNumList[30000]; // Up to 30000 values. Program crashes when array size is too high
        int N = 0;
        int choice = -1;
    public:
        void run(){
            /*
            for(int i = 0; i < 25000; i++){ // Adding some dummy contacts to test runtime
                nameList[i] = "test";
                phoneNumList[i] = "123";
                N++;  
            }
            
            nameList[N] = "yo";
            phoneNumList[N] = "456";
            N++;
            */
            while (choice != 0){
                cout << "\nPhone Directory" << endl;
                cout << "Please select one of the following choices" << endl;
                cout << "1. Add a new contact" << endl;
                cout << "2. Search for contact" << endl;
                cout << "3. Delete a contact" << endl;
                cout << "4. Show all contacts" << endl;
                cout << "0. Exit program" << endl;
                cin >> choice;
                if (choice == 1){
                    string name;
                    string phoneNum;
                    cout << "\nInput the name for your contact: ";
                    cin >> name;
                    cout << "\nInput the phone number of your contact: ";
                    cin >> phoneNum;
                    if(searchContact(name) != -1000){
                        cout << "Contact with that name already exists" << endl;
                    } else if (isNumber(phoneNum) == false) {
                        cout << "Invalid input on phone number" << endl;
                    } else {
                        addContact(name, phoneNum);
                    }
                    
                } else if (choice == 2){                 
                    if (N == 0){
                        cout << "\nYou currently have no contacts. Why not add some?" << endl;
                    } else {
                        string name;
                        cout << "\nInput the name of the contact you would like to find: ";
                        cin >> name;
                        int searchResult = searchContact(name);
                        if (searchResult == -1000){
                            cout << "\nContact not found" << endl;
                        } else {
                            cout << nameList[searchResult] << "(" << phoneNumList[searchResult] << ")" << endl;
                        }
                    }
                } else if (choice == 3){
                    if (N == 0){
                        cout << "\nYou currently have no contacts. Why not add some?" << endl;
                    } else {
                        string name;
                        cout << "\nInput the name of the contact you would like to delete: ";
                        cin >> name;
                        int searchResult = searchContact(name);
                        if (deleteContact(name) == 0){
                            cout << "\nContact not found" << endl;
                        } else {
                            cout << "\nContact successfully deleted." << endl;
                        }
                    }
                } else if (choice == 4){
                    shellSort();
                    for(int i = 0; i < N; i++){
                        cout << nameList[i] << "(" << phoneNumList[i] << ")" << endl;
                    }
                }
            }
        }

        void addContact (string name, string phoneNum){
            auto start = steady_clock::now();
            nameList[N] = name;
            phoneNumList[N] = phoneNum;
            cout << "Contact successfully added" << endl;
            auto end = steady_clock::now();
            double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
            cout << "Amount of time for insertion: " << elapsedTime << " nanoseconds." << endl;
            N++;
        }

        int searchContact(string name){
            auto start = steady_clock::now();
            shellSort();
            // For searching, we will use binary search
            int left = 0;
            int right = N-1;
            int mid;
            bool found = false;


            while (left<=right && !found){
                mid =  (left+right) / 2;
                if (name == nameList[mid]){
                    auto end = steady_clock::now();
                    double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
                    cout << "Amount of time for search: " << elapsedTime << " nanoseconds." << endl;
                    return mid; // Returns index of the successful search

                }
                
                if (name > nameList[mid]){
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            auto end = steady_clock::now();
            double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
            cout << "Amount of time for search: " << elapsedTime << " nanoseconds." << endl;
            return -1000; // Default number to indicate that search has failed
        }

        int deleteContact(string name){ // Returns int to indicate success or failure. 1 = success, 0 = failure
            auto start = steady_clock::now();
            int searchResult = searchContact(name);
            if (searchResult == -1000){
                return 0;
            } else {
                for(int j = searchResult; j<N; j++){
                    nameList[j] = nameList[j+1];
                    phoneNumList[j] = phoneNumList[j+1];
                }
                N--;
                auto end = steady_clock::now();
                double elapsedTime = double(duration_cast<nanoseconds>(end-start).count());
                cout << "Amount of time for delete: " << elapsedTime << " nanoseconds." << endl;
                return 1;
            }
        }
        
        void shellSort(){ // Source: https://www.geeksforgeeks.org/shellsort/
            for (int gap = N/2; gap > 0 ; gap /= 2){ // Sort still a WIP
                for (int i = gap; i < N; i++){
                    auto temp = nameList[i];
                    auto tempPhoneNum = phoneNumList[i];
                    int j;
                    for(j = i; j >= gap && nameList[j-gap] > temp; j -= gap){
                        nameList[j] = nameList[j-gap];
                        phoneNumList[j] = phoneNumList[j-gap];
                    }
                    nameList[j] = temp;
                    phoneNumList[j] = tempPhoneNum;
                    // Has a time complexity of O(N^2). Gap might need to be adjusted
                }
            }

        }
    
};

int main(){
    PhoneDirectory phoneDir;
    phoneDir.run();
    return 0;
}
