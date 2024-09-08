#pragma once
#include <vector>
#include <string>
#include <memory>
#include <variant>
#include "Product.h"

enum class Field {
    Color,
    Price,
    Weight
};

class Storage {
private:
    std::vector<std::unique_ptr<Product>> products; // Вектор уникальных указателей на Product
public:
    void addProduct(std::unique_ptr<Product> product); // Принимает уникальный указатель
    bool removeProduct(const std::string_view name);
    void updateProduct(std::string_view name, Field updateField, const std::variant<double, std::string>& value);
    void productsList() const;
    std::vector<std::unique_ptr<Product>> findLowStockProd(int limit) const;
};

void addProduct(Storage& storage);
void removeProduct(Storage& storage);
void updateProduct(Storage& storage);
void showProducts(const Storage& storage);
void findLowStockProducts(const Storage& storage);