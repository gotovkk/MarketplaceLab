#pragma once
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include "Product.h"
#include <sqlite3.h>

enum class Field {
    Color,
    Price,
    Weight
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
    std::vector<Product> filterByPrice(double maxPrice) const;
};

void addProduct(Storage& storage);
void removeProduct(Storage& storage);
void updateProduct(const Storage& storage);
void showProducts(const Storage& storage);
void findLowStockProducts(const Storage& storage);