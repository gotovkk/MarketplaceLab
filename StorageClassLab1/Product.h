#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>


class Product {
    friend bool operator==(const Product& lhs, const Product& rhs);

private:
    std::string name;
    std::string description;
    double price;
    int amount;
    int seller_id;
    int category_id;

public:
    Product(std::string const& name, std::string const& description, double price, int amount,
        int seller_id, int category_id)
        : name(name), description(description), price(price), amount(amount),
        seller_id(seller_id), category_id(category_id){}

    double getPrice() const;
    int getAmount() const;
    std::string getName() const;
    std::string getDescription() const;
    int getSellerId() const;
    int getCategoryId() const;
    void setPrice(double newPrice);
    void setAmount(int newAmount);
    void printInfo() const;

    Product& operator+=(int amount);
    Product& operator-=(int amount);

    friend bool operator==(const Product& lhs, const Product& rhs) {
        bool isEqual = true;

        std::vector<std::pair<std::string, bool>> comparison = {
            {"��������", lhs.name == rhs.name},
            {"��������", lhs.description == rhs.description},
            {"����", lhs.price == rhs.price},
            {"ID ��������", lhs.seller_id == rhs.seller_id},
            {"ID ���������", lhs.category_id == rhs.category_id},
            {"����������", lhs.amount == rhs.amount},
        };


        std::cout << "��������� ������������� ���������:\n";

        for (const auto& [field, result] : comparison) {
            if (result) {
                std::cout << field << ": ���������" << std::endl;
            }
            else {
                if (field == "����" || field == "����������") {
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

void comprasionCheck(const Product* first, const Product* second);
