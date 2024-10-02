#include "Product.h"

double Product::getPrice() const {
	return price;
}
double Product::getWeight() const {
	return weight;
}
std::string Product::getName() const {
	return name;
}
std::string Product::getCategory() const {
	return category;
}
std::string Product::getColor() const {
	return color;
}
int Product::getAmount() const {
	return amount;
}

void Product::setPrice(double newPrice) {
	price = newPrice;
}
void Product::setWeight(double newWeight) {
	weight = newWeight;
}
void Product::setAmount(int newAmount) {
	amount = newAmount;
}
void Product::setColor(std::string_view const& newColor) {
	color = newColor;
}

void Product::printInfo() const {
	std::cout << "Название: " << name << "\n"
		<< "Категория: " << category << "\n"
		<< "Цена: " << price << "\n"
		<< "Вес: " << weight << "\n"
		<< "Цвет: " << color << "\n"
		<< "Количество: " << amount << std::endl;
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
