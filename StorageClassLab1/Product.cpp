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
	std::cout << "��������: " << name << "\n"
		<< "���������: " << category << "\n"
		<< "����: " << price << "\n"
		<< "���: " << weight << "\n"
		<< "����: " << color << "\n"
		<< "����������: " << amount << std::endl;
}

/*��� ��������� ������������� ��� �� ���������*/
bool operator==(const Product& first, const Product& second)
{
	bool isEqual = true;
	std::vector<std::pair<std::string, bool>>comprassion =
	{
		{"��������", first.name == second.name},
		{"���������", first.category == second.category},
		{"����", first.price == second.price},
		{"���", first.weight == second.weight},
		{"����", first.color == second.color},
		{"����������", first.amount == second.amount},
	};
	std::cout << "��������� ������������� ���������:\n";

	for (const auto& [field, result] : comprassion) {
		std::cout << field << ": "
			<< first.name << " = "
			<< (field == "����" || field == "���" || field == "����������"
				? std::to_string(first.price) : first.name)
			<< ", " << second.name << " = "
			<< (field == "����" || field == "���" || field == "����������"
				? std::to_string(second.price) : second.name)
			<< (result ? " (���������)" : " (�����������)") << "\n";
	}

	return isEqual;
}
