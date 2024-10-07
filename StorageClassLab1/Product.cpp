#include "Product.h"

double Product::getPrice() const {
	return price;
}
std::string Product::getName() const {
	return name;
}
std::string Product::getDescription() const {
	return description;
}
int Product::getSellerId() const {
	return seller_id;
}

int Product::getCategoryId() const
{ return category_id; 
}

int Product::getAmount() const {
	return amount;
}

void Product::setPrice(double newPrice) 
{
	price = newPrice;
}

void Product::setSellerId(int newId)
{
	seller_id = newId;
}

void Product::setAmount(int newAmount) {
	amount = newAmount;
}

void Product::printInfo() const {
	std::cout << "��������: " << name << "\n"
		<< "��������: " << description << "\n"
		<< "����: " << price << "\n"
		<< "ID ��������: " << seller_id << "\n"
		<< "ID ���������: " << category_id << "\n"
		<< "����������: " << amount << std::endl;
}

Product& Product::operator+=(int amountToAdd) {
	this->amount += amountToAdd;
	return *this;
}

Product& Product::operator-=(int amountToSubtract) {
	if (this->amount >= amountToSubtract) {
		this->amount -= amountToSubtract;
	}
	else {
		this->amount = 0;
	}
	return *this;
}

void comprasionCheck(const Product* first, const Product* second)
{
	if (first && second) {
		std::cout << "��������� ��������� �������:\n";
		if (*first == *second) {
			std::cout << "�������� ���������" << std::endl;
		}
		else {
			std::cout << "�������� ����� ��������" << std::endl;
		}
	}
	else {
		std::cout << "���� ��� ��� �������� �� �������\n";
	}
}

