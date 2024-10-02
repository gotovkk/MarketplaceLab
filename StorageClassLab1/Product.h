#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>


class Product {
    friend bool operator==(const Product& lhs, const Product& rhs);

private:
    std::string name;
    std::string category;
    std::string color;
    double price;
    double weight;
    int amount;

public:
    Product(std::string const& name, std::string const& category, double price,
        double weight = 0.0, std::string const& color = "Не указан", int amount = 1)
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


    friend bool operator==(const Product& lhs, const Product& rhs) {
        bool isEqual = true;

        std::vector<std::pair<std::string, bool>> comparison = {
            {"Название", lhs.name == rhs.name},
            {"Категория", lhs.category == rhs.category},
            {"Цена", lhs.price == rhs.price},
            {"Вес", lhs.weight == rhs.weight},
            {"Цвет", lhs.color == rhs.color},
            {"Количество", lhs.amount == rhs.amount},
        };

        std::cout << "Сравнение характеристик продуктов:\n";

        for (const auto& [field, result] : comparison) {
            if (result) {
                std::cout << field << ": совпадает" << std::endl;
            }
            else {
                if (field == "Цена" || field == "Вес" || field == "Количество") {
                    std::cout << field << ": " << lhs.name << " (" << lhs.price << ") != " << rhs.name << " (" << rhs.price << ")" << std::endl;
                }
                else {
                    std::cout << field << ": " << lhs.name << " != " << rhs.name << std::endl;
                }
                isEqual = false;  
            }
        }

        return isEqual;
    }
};