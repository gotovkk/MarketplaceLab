#pragma once
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include <format>
#include "Product.h"
#include <sqlite3.h>

enum class Field {
    Color,
    Price,
    Weight,
    Amount
};

class Storage {
private:
    std::vector<std::unique_ptr<Product>> products;     
public:
    const std::vector<std::unique_ptr<Product>>& productsList() const;


    void addProduct(std::unique_ptr<Product> product);
    bool removeProduct(const std::string_view name);
    void updateProduct(std::string_view name, Field updateField, const std::variant<double, std::string>& value) const;
    void allProductsList() const;
    std::vector<std::unique_ptr<Product>> findLowStockProd(int limit) const;
};

void addToTable(Storage& storage, sqlite3* db);
void removeProduct(Storage& storage);
void updateProduct(const Storage& storage);
void amountChange(const Storage& storage, std::string& name);
void showProducts(const Storage& storage);
void findLowStockProducts(const Storage& storage);