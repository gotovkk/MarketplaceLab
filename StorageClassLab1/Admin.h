#include <iostream>
#include <string>
#include "Seller.h"
#include "Storage.h"

class Admin : public Seller {
public:
    Admin(const std::string& username, const std::string& password, int sellerId);

    void approveSeller([[maybe_unused]]const Storage& storage, [[maybe_unused]] int sellerId) const;
    void removeProduct(Storage& storage, int seller_id) override;
};