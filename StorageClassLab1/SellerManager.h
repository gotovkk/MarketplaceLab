#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Seller.h"

class SellerManager {
public:
    bool registerSeller(sqlite3* db, const std::string& username, const std::string& password, int& seller_id) const {
        const char* sqlCreateTable =
            "CREATE TABLE IF NOT EXISTS sellers ("
            "seller_id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT NOT NULL UNIQUE, "
            "password TEXT NOT NULL"
            ");";

        char* errMsg = nullptr;
        if (int rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg); rc != SQLITE_OK) {
            std::cerr << "������ ��� �������� ������� sellers: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        std::string sqlSelect = "SELECT COUNT(*) FROM sellers WHERE username = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sqlSelect.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
                std::cout << "������������ � ����� ������� ��� ����������!" << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }
        }
        sqlite3_finalize(stmt);

        if (std::string sqlInsert = "INSERT INTO sellers (username, password) VALUES (?, ?);"; sqlite3_prepare_v2(db, sqlInsert.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                std::cerr << "������ ����������� ������������!" << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }
            seller_id = static_cast<int>(sqlite3_last_insert_rowid(db));
        }
        else {
            std::cerr << "������ ���������� SQL-������� INSERT: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }
        sqlite3_finalize(stmt);

        std::cout << "����������� �������! seller_id: " << seller_id << std::endl;
        return true;
    }

    bool login(sqlite3* db, const std::string& username, const std::string_view& password) const {
        std::string sqlSelect = "SELECT password FROM sellers WHERE username = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sqlSelect.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string storedPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                if (storedPassword == password) {
                    std::cout << "���� �������� �������!" << std::endl;
                    sqlite3_finalize(stmt);
                    return true;
                }
            }
        }
        sqlite3_finalize(stmt);

        std::cout << "�������� ����� ��� ������!" << std::endl;
        return false;
    }

    bool getSellerIdByUsername(sqlite3* db, const std::string& username, int& seller_id) const {
        std::string sqlSelect = "SELECT seller_id FROM sellers WHERE username = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sqlSelect.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                seller_id = sqlite3_column_int(stmt, 0);
                sqlite3_finalize(stmt);
                return true;
            }
        }
        sqlite3_finalize(stmt);
        return false;
    }
private:
    std::vector<Seller> sellers;
};
