#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct contactbook 
{
    map<string, vector<pair<string, string>>> contacts; 
    vector<string> favorites;

    void addcontact(const string& name) 
    {
        if (contacts.count(name)) 
        {
            cout << "contact already exist\n";
        } else 
        {
            contacts[name] = {};
            cout << "contact added .\n";
        }
    }

    void removecontact(const string& name) 
    {
        if (contacts.erase(name)) 
        {
            favorites.erase(remove(favorites.begin(), favorites.end(), name), favorites.end());
            cout << "contact removed .\n";
        } else 
        {
            cout << "contact didn't remove\n";
        }
    }

    void editcontat(const string& oldName, const string& newName) 
    {
        auto it = contacts.find(oldName);
        if (it != contacts.end()) 
        {
            contacts[newName] = move(it->second);
            contacts.erase(it);
            replace(favorites.begin(), favorites.end(), oldName, newName);
            cout << "contact renamed\n";
        } else 
        {
            cout << "contact not found\n";
        }
    }

    void addphonenumber(const string& name, const string& type, const string& number) 
    {
        if (contacts.count(name)) 
        {
            contacts[name].emplace_back(type, number);
            cout << "phone number added\n";
        } 
        else 
        {
            cout << "contact not found\n";
        }
    }

    void removephonenumber(const string& name, const string& number) 
    {
        if (contacts.count(name)) 
        {
            auto& phoneNumbers = contacts[name];
            auto it = remove_if(phoneNumbers.begin(), phoneNumbers.end(),
                [&](const pair<string, string>& p) { return p.second == number; });
            if (it != phoneNumbers.end()) 
            {
                phoneNumbers.erase(it, phoneNumbers.end());
                cout << "phone number removed.\n";
            } 
            else 
            {
                cout << "phone number not found\n";
            }
        } 
        else 
        {
            cout << "contact not found\n";
        }
    }

    void displayphonenumbers(const string& name) const 
    {
        auto it = contacts.find(name);
        if (it != contacts.end()) 
        {
            cout << "contat numbers " << name << " :\n";
            for (const auto& [type, number] : it->second) 
            {
                cout << type << " : " << number << '\n';
            }
        } 
        else 
        {
            cout << "contact not found.\n";
        }
    }

    void addtofavorites(const string& name) 
    {
        if (contacts.count(name) && find(favorites.begin(), favorites.end(), name) == favorites.end()) 
        {
            favorites.push_back(name);
            cout << "contact added to favorits\n";
        } 
        else 
        {
            cout << "contact not found or already exist in favorites\n";
        }
    }

    void removefromfavorites(const string& name) 
    {
        auto it = remove(favorites.begin(), favorites.end(), name);
        if (it != favorites.end()) 
        {
            favorites.erase(it, favorites.end());
            cout << "contact removed from favorites\n";
        } 
        else 
        {
            cout << "contact doesn't exist in favorites\n";
        }
    }

    void displayfavorites() const 
    {
        cout << "favorite list : \n";
        for (const auto& name : favorites) 
        {
            cout << name << '\n';
        }
    }

    void showallcontacts() const 
    {
        cout << "\ncontact list : \n";
        for (const auto& [name, _] : contacts) 
        {
            cout << name << '\n';
        }
    }

    void searchcontact(const string& query) const 
    {
        cout << "search result : \"" << query << "\":\n";
        for (const auto& [name, _] : contacts) 
        {
            if (name.find(query) == 0) 
            {
                cout << name << '\n';
            }
        }
    }
};

int main() 
{
    contactbook book;
    int choice;

    do 
    {
        cout << "\nphone listn\n\n";
        cout << "1.add contact\n";
        cout << "2. remove contact\n";
        cout << "3. edit contact\n";
        cout << "4. add phone number\n";
        cout << "5. remove phone number\n";
        cout << "6. display numbers\n";
        cout << "7. add to favorites\n";
        cout << "8. remove from favorites\n";
        cout << "9. show favoritws\n";
        cout << "10. show all contacts\n";
        cout << "11. search contact\n";
        cout << "0. exit\n";
        cout << "choice : ";
        cin >> choice;

        string name, type, number, newName;

        switch (choice) 
        {
        case 1:
            cout << "contact name : ";
            cin >> name;
            book.addcontact(name);
            break;
        case 2:
            cout << "contact name : ";
            cin >> name;
            book.removecontact(name);
            break;
        case 3:
            cout << "current name : ";
            cin >> name;
            cout << "new name : ";
            cin >> newName;
            book.editcontat(name, newName);
            break;
        case 4:
            cout << "contact name : ";
            cin >> name;
            cout << "phone number type ";
            cin >> type;
            cout << "phone number : ";
            cin >> number;
            book.addphonenumber(name, type, number);
            break;
        case 5:
            cout << "contact name : ";
            cin >> name;
            cout << "phone number ";
            cin >> number;
            book.removephonenumber(name, number);
            break;
        case 6:
            cout << "contact name : ";
            cin >> name;
            book.displayphonenumbers(name);
            break;
        case 7:
            cout << "contact name : ";
            cin >> name;
            book.addtofavorites(name);
            break;
        case 8:
            cout << "contact name: ";
            cin >> name;
            book.removefromfavorites(name);
            break;
        case 9:
            book.displayfavorites();
            break;
        case 10:
            book.showallcontacts();
            break;
        case 11:
            cout << "search : ";
            cin >> name;
            book.searchcontact(name);
            break;
        case 0:
            cout << "exit...\n";
            break;
        default:
            cout << "invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
