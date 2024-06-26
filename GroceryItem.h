/*
* GroceryItem.h
* 
* Date: 6/13/24
* Author: Andrew Galipeau
*/

#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

class GroceryItem {
public:
    GroceryItem(std::string &name);
    GroceryItem(std::string &name, int quantity);

    std::string getName() const;
    int getQuantity() const;

    void addItem();
    void removeItem();  // Not used, implemented for future use

    bool operator<(const GroceryItem &other) const;

private:
    std::string name;
    int quantity;
};

#endif // GROCERYITEM_H