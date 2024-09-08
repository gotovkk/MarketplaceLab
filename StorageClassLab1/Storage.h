#include <vector>
#include <string>
#include <variant>
#include <memory>
#include "Product.h"

enum class field {
    color,
    price,
    weight
};

class Storage {
private:
    std::vector<Product> products;
public:
    void addProduct(const Product& product);
    bool removeProduct(const std::string_view name);
    void updateProduct(const std::string_view name, field updateField, const std::variant<double, std::string>& value);
    void productsList() const;
    std::vector<Product> findLowStockProd(int limit) const;
};

void addProduct(Storage& storage);
void removeProduct(Storage& storage);
void updateProduct(Storage& storage);
void showProducts(const Storage& storage);
void findLowStockProducts(const Storage& storage);