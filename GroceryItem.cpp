/*
* GroceryItem.cpp
* 
* Date: 6/13/24
* Author: Andrew Galipeau
*/

#include "GroceryItem.h"

GroceryItem::GroceryItem(std::string& name) : name(name), quantity(0) {} // Sets quantity to '0'

GroceryItem::GroceryItem(std::string& name, int quantity) : name(name), quantity(quantity) {}

std::string GroceryItem::getName() const
{
    return name;
}

int GroceryItem::getQuantity() const
{
    return quantity;
}

void GroceryItem::addItem() { 
    quantity++;
}
// Not used, implemented for future use
void GroceryItem::removeItem()
{
    if (quantity > 0) {
        quantity--;
    }
}

bool GroceryItem::operator<(const GroceryItem& other) const
{
    return name < other.name;
}