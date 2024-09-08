#pragma once
#include <iostream>

class Product {
private:
    std::string name;
    std::string category;
    std::string color;
    double price;
    double weight;
    int amount;

public:
    Product(std::string const& name, std::string const& category, double price,
        double weight = 0.0, std::string const& color = "?? ??????", int amount = 1)
        : name(name), category(category), color(color),
        price(price), weight(weight), amount(amount) {}

    double getPrice() const;
    double getWeight() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getColor() const;
    int getAmount() const;

    void setPrice(double newPrice);
    void setWeight(double newWeight);
    void setAmount(int newAmount);
    void setColor(std::string_view const& newColor);

    void printInfo() const;
};