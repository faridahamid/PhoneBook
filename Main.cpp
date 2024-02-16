#include <iostream>
#include <string>
using namespace std;
class PhoneBook
{
    string* names;
    string* phones;
    int phoneBookSize;
public:
    void setSize(int size){
        phoneBookSize=size;
        names= new string[size];
        phones=new string[size];
    }
    void copyPB(const PhoneBook& another_phone_num){
        phoneBookSize=another_phone_num.phoneBookSize;
        names=new string [phoneBookSize];
        phones=new string[phoneBookSize];
        for (int i = 0; i < phoneBookSize; i++) {
            names[i] = another_phone_num.names[i];
            phones[i] = another_phone_num.phones[i];
        }

    }
    bool addEntry(string name ,string phone){
        if (phoneBookSize == 0) {
            cout << "Book size isn't set";
            return false;
        }
        string valid_num="";
        while (true){
            cout<<"enter valid number"<<endl;
            cin>>valid_num;

            if (valid_num.size() != 11) {
                cout << "invalid number please enter a valid one ";
                continue;
            }
            bool valid= true;
            for (char f: valid_num) {
                if (!isdigit(f)) {
                    valid=false;
                    break;
                }
            }
            if (valid){
                break;
            }
            else{
                cout<<"invalid number"<<endl;

            }

        }
        for(int i=0;i<phoneBookSize;i++){
            if(names[i]==""&&phones[i]==""){
                names[i]=name;
                phones[i]=valid_num;
                return true;
            }
        }
        return false;
    }
    bool displayEntryAtIndex(int spec_index){
        if(spec_index>phoneBookSize-1 || spec_index<0)
            return false;
        else {
            cout << "name: " << names[spec_index] << endl;
            cout<<"phone: "<<phones[spec_index]<<endl;
            return true;
        }
    }
    void displayEntryAtIndices(int* arr){
        for(int i=0;i<phoneBookSize;i++){
            if(arr[i]==1){
                cout<<"name: "<<names[i]<<endl;
                cout<<"phone: "<<phones[i]<<endl;
            }
        }
    }
    void displayAll(){
        for(int i=0;i<phoneBookSize;i++){
            cout<<"name: "<<names[i]<<","<<"phone: "<<phones[i];
        }
    }
    int* findByName(string wanted_name){
        int *name_match=new int [phoneBookSize];
        for(int i=0;i<phoneBookSize;i++) {
            name_match[i] = 0;
            int name_length = names[i].length();
            int wanted_length=wanted_name.length();
            for  ( int j_name=0;j_name < name_length;j_name++) {
                if (names[i][j_name] == wanted_name[0]) {
                    int temp_name = j_name;
                    int temp_wanted = 0;
                    while (temp_name < name_length && temp_wanted < wanted_length &&
                           names[i][temp_name] == wanted_name[temp_wanted]) {
                        temp_name++;
                        temp_wanted++;
                    }
                    if (temp_wanted == wanted_length) {

                        name_match[i] = 1;
                        break;
                    }
                }


            }

        }
        return name_match;
    }
    string findByPhone(string number){
        for(int i=0;i<phoneBookSize;i++){
            if(number==phones[i])
                return names[i];
        }
        return "";
    }
    bool updateNameAt(string updated_name, int spec_index){
        if(spec_index>phoneBookSize-1 || spec_index<0)
            return false;
        else{
            names[spec_index]=updated_name;
            return true;
        }
    }
    bool updatePhoneAt(string updated_phone, int spec_index){
        if(spec_index>phoneBookSize-1 || spec_index<0)
            return false;
        else{
            phones[spec_index]=updated_phone;
            return true;
        }

    }
    void clear(){
        delete[]names;
        delete[]phones;
        names= nullptr;
        phones= nullptr;
        phoneBookSize=0;
    }
};


bool validateNumber(string &s){
    try{
        stoi(s);
        return true;
    }
    catch (invalid_argument){
        return false;
    }
}

int main() {
    PhoneBook my_phone_book;
    int size;
    cout << "Enter the size of the phone book";
    cin >> size;
    my_phone_book.setSize(size);
    for (int i = 0; i < size; i++) {
        string name,phone;
        cout<<"enter name "<<i+1<<":"<<endl;
        cin.ignore();
        getline(cin,name);
        my_phone_book.addEntry(name,phone);

    }
    string schoice;
    int choice;
    while (choice != 8) {
        cout << endl<<"1-Display all phone book" << endl << "2- search for entry /entries by name" << endl
             << "3-search for entry/entries by phone" << endl << "4-find an entry by index " << endl
             << "5-update name by index " << endl << "6- update phone by index " << endl
             << "7-copy phone book to another and displays enteres of  the new one  " << endl << "8-exit" << endl
             << "choice" << endl;
        cin >> schoice;
        if(validateNumber(schoice)){
            choice = stoi(schoice);
        }
        else{
            continue;
        }
        switch (choice) {
            case 1: {
                my_phone_book.displayAll();
                break;
            }
            case 2: {
                string search_for_name;
                cout << "enter the name you want to search for ";
                cin.ignore();
                getline(cin,search_for_name);
                int *result=my_phone_book.findByName(search_for_name);
                bool found= false;
                for (int i=0;i<size;i++){
                    cout<<"result of search"<<i+1<<":"<<result[i]<<endl;
                    if (result[i]==1){
                        my_phone_book.displayEntryAtIndex(i);
                        found=true;
                    }

                }
                if(!found ){
                    cout<<"not matching entries found for the name"<<search_for_name<<endl;
                }
                break;
            }
            case 3: {
                string search_for_phone;
                cout << "enter the number you want to search for ";
                cin >> search_for_phone;
                string name_found = my_phone_book.findByPhone(search_for_phone);
                if (name_found!="") {
                    cout << "name found for number" << search_for_phone << ":" << name_found << endl;
                } else {
                    cout << "number not found";
                }
                break;
            }
            case 4: {
                int index_to_be_found;
                while (true) {
                    cout << "Enter the index to find: ";
                    cin >> schoice;
                    if (validateNumber(schoice)) {
                        index_to_be_found = stoi(schoice);
                        if (index_to_be_found >= 0 && index_to_be_found < size) {
                            my_phone_book.displayEntryAtIndex(index_to_be_found);
                            break;
                        } else {
                            cout << "Invalid index. enter a valid index." << endl;
                        }
                    } else {
                        cout << "Invalid input enter a valid  index." << endl;
                    }
                }
                break;
            }
            case 5: {
                int index_to_be_updated;
                while (true) {
                    cout << "Enter index to update name: ";
                    cin >> schoice;
                    if (validateNumber(schoice)) {
                        index_to_be_updated = stoi(schoice);
                        if (index_to_be_updated >= 0 && index_to_be_updated < size) {
                            string new_name;
                            cout << "Enter new name: ";
                            cin.ignore();
                            getline(cin, new_name);
                            bool updated=my_phone_book.updateNameAt(new_name,index_to_be_updated);
                            if(updated){
                                cout<<" name updated"<<endl;
                            }
                            my_phone_book.updateNameAt(new_name, index_to_be_updated);
                            my_phone_book.displayAll();
                            break;
                        } else {
                            cout << "Invalid index enter a valid index." << endl;
                        }
                    } else {
                        cout << "Invalid input enter a valid  index." << endl;
                    }
                }
                break;
            }
            case 6: {
                int index_to_be_updated;
                while (true) {
                    cout << "Enter index to update phone: ";
                    cin >> schoice;
                    if (validateNumber(schoice)) {
                        index_to_be_updated = stoi(schoice);
                        if (index_to_be_updated >= 0 && index_to_be_updated < size) {
                            string new_num;
                            bool valid_number= false;
                            while(!valid_number){
                                cout << "Enter new number: ";
                                cin >> new_num;
                                if (new_num.size()==11) {
                                    valid_number = true;
                                    for (char c: new_num) {
                                        if (!isdigit(c)) {
                                            valid_number = false;
                                            break;
                                        }
                                    }

                                }
                                if(!valid_number){
                                    cout<<"invalid number"<<endl;

                                }

                            }
                            bool updated=my_phone_book.updatePhoneAt(new_num,index_to_be_updated);
                            if(updated){
                                cout<<" phone num updated:"<<endl;
                            }
                            my_phone_book.updatePhoneAt(new_num, index_to_be_updated);
                            my_phone_book.displayAll();
                            break;
                        } else {
                            cout << "Invalid index enter a valid index." << endl;
                        }
                    } else {
                        cout << "Invalid input enter a valid  index." << endl;
                    }
                }
                break;
            }
            case 7: {
                PhoneBook newPhoneBook;
                newPhoneBook.copyPB(my_phone_book);
                cout << "copied:" << endl;
                newPhoneBook.displayAll();
                break;
            }
            case 8:
                cout << "Exiting the program" << endl;
                break;
            default: {
                cout << "Invalid choice enter a valid choice." << endl;
            }
        }
    }

    my_phone_book.clear();
    return 0;
}






