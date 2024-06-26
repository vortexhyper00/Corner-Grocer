/*
* Source.cpp
* 
* Date: 6/13/24
* Author: Andrew Galipeau
*/

#include <iostream>
#include <set>
#include <fstream>
#include "GroceryItem.h"

using namespace std;

// Displays the menu options
void mainMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Print item frequency list" << endl;
    cout << "3. Print item frequency histogram" << endl;
    cout << "4. Exit" << endl;
}

// Backup data to frequency.txt
void outputFile(set<GroceryItem>& items) {
    ofstream outputFile("frequency.txt");
    if (!outputFile.is_open()) {
        cout << "Error, failed to open file" << endl;
        return;
    }
    for (const GroceryItem& groceryItem : items) {
        outputFile << groceryItem.getName() << " " << groceryItem.getQuantity() << endl;
    }
    outputFile.close();
    cout << "Info backed up to frequency.txt" << endl;
}

// Displays frequency list with how many times an item is repeated
void printFrequencyList(set<GroceryItem>& items, int itemsAdded, int itemsUpdated) {
    cout << "Items added = " << itemsAdded << endl;
    cout << "Items updated = " << itemsUpdated << endl;

    int count = 1;
    for (const GroceryItem& groceryItem : items) {
        cout << count << " " << groceryItem.getName() << " " << groceryItem.getQuantity() << endl;
        count++;
    }
}

// Displays frequency histogram with '*' instead of number
void printFrequencyHistogram(set<GroceryItem>& items, int itemsAdded, int itemsUpdated) {
    cout << "Items added = " << itemsAdded << endl;
    cout << "Items updated = " << itemsUpdated << endl;

    int count = 1;
    for (const GroceryItem& groceryItem : items) {
        cout << count << " " << groceryItem.getName() << " ";
        for (int i = 0; i < groceryItem.getQuantity(); ++i) {
            cout << "*";
        }
        cout << endl;
        count++;
    }
}

// Gets the quantity of each item in the inventory file
int getItemQuantity(set<GroceryItem>& items, const string& itemName) {
    for (const GroceryItem& groceryItem : items) {
        if (groceryItem.getName() == itemName) {
            return groceryItem.getQuantity();
        }
    }
    return 0;
}

int main() {
    mainMenu();
    // Declaring a set
    set<GroceryItem> items;

    // Opens the txt file
    ifstream inputFile("inventory.txt");
    if (!inputFile.is_open()) {
        cout << "Error, file not found" << endl;
        return 1;
    }

    string item;

    // Used for displaying the amount of different items
    int itemsAdded = 0;

    // Used for displaying how many items were found to be duplicates
    int itemsUpdated = 0;

    while (inputFile >> item) {
        bool found = false;

        for (auto existingItem = items.begin(); existingItem != items.end(); ++existingItem) {
            if (existingItem->getName() == item) {
                // Create a new GroceryItem with the same name and incremented quantity
                GroceryItem updatedItem = *existingItem;
                updatedItem.addItem();
           
                items.erase(existingItem); // Frees memory
                items.insert(updatedItem);
                itemsUpdated++;
                found = true;
                break;
            }
        }
        if (!found) {
            items.emplace(item, 1); // Adds new item to set
            itemsAdded++;
        }
    }

    inputFile.close(); //Closes the file

    char user_input = 'a';
    while (user_input != '4') {
        cout << endl;
        cout << "Enter an option: ";

        cin >> user_input;

        // User input option menu
        switch (user_input) {
        case '1': {
            cout << "Enter the item name: ";
            cin >> item;
            int quantity = getItemQuantity(items, item);
            if (quantity > 0) {
                cout << "Quantity of " << item << " is " << quantity << endl;
            }
            else {
                cout << item << " not found" << endl;
            }
            break;
        }
        case '2': {
            printFrequencyList(items, itemsAdded, itemsUpdated);
            break;
        }
        case '3': {
            printFrequencyHistogram(items, itemsAdded, itemsUpdated);
            break;
        }
        case '4': {
            cout << "Program finished" << endl;
            outputFile(items); // Backup data before exiting
            break;
        }
        default:
            cout << "Option not valid" << endl;
        }
    }

    return 0;
}