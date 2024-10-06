//#pragma once
//#include <string>
//#include <iostream>
//#include <sqlite3.h>
//#include <unordered_map>
//
//
//class Seller {
//public:
//    virtual void login() = 0;
//
//    virtual void addProduct() = 0;
//
//    virtual ~Seller() = default;
//
//    Seller(const std::string& username, const std::string& password)
//        : username(username), password(password) {}
//
//
//protected:
//    // ����, ��������� ��� ����������� �������
//    std::string username;
//    std::string password;
//};
//
//class RegularSeller : public Seller {
//public:
//	RegularSeller(const std::string& username) : Seller(username) {}
//
//	void addProduct() override {
//		// ������ ���������� �������� ��� �������� ��������
//	}
//};
//
//
//class AdminSeller : public Seller {
//public:
//	AdminSeller(const std::string& username) : Seller(username) {}
//
//	void addProduct() override {
//		// ������ ���������� �������� ��� ��������������
//	}
//
//	void manageSellers() {
//		// ������ ���������� ������� ����������
//	}
//};