#include <iostream>
#include <string>
#include "Seller.h"
#include "Storage.h"

class Admin : public Seller {
public:
    Admin(const std::string& username, const std::string& password, int sellerId);

    void approveSeller(Storage& storage, int sellerId);
    void removeProduct(Storage& storage, int seller_id) override;
};