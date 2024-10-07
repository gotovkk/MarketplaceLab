#include "ErrorManager.h"

void ErrorManager::reportError(const std::string& msg, sqlite3* db) {
    std::cerr << msg << ": " << (db ? sqlite3_errmsg(db) : "����������� ������") << std::endl;
}

void ErrorManager::loginError()
{
    std::cerr << "������ �����. ��������� ��������� ����� ��� ������.\n" << std::endl;
}

void ErrorManager::choiceError()
{
    std::cerr << "�������� �����, ���������� �����.\n" << std::endl;

}
