#include "Seller.h"

class SellerManager {

public:
    bool registerSeller(sqlite3* db, const std::string& username, const std::string& password, int& seller_id) const;
    bool login(sqlite3* db, const std::string& username, const std::string_view& password) const;
    bool getSellerIdByUsername(sqlite3* db, const std::string& username, int& seller_id) const;

private:
    std::vector<Seller> sellers;
};
