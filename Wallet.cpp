#include "Wallet.h"
#include <iostream>

// Constructor có đối số
Wallet::Wallet(const std::string& walletId, const std::string& username, int point)
    : walletId(walletId), username(username), point(point) {}

// Getters
std::string Wallet::getWalletId() const { return walletId; }
std::string Wallet::getUsername() const { return username; }
int Wallet::getPoint() const { return point; }

// Setters
void Wallet::setWalletId(const std::string& walletId) { this->walletId = walletId; }
void Wallet::setUsername(const std::string& username) { this->username = username; }
void Wallet::setPoint(int point) { this->point = point; }

// Display wallet information
void Wallet::displayInfo() const {
    std::cout << "Ma vi: " << walletId << std::endl;
    std::cout << "Ten dang nhap: " << username << std::endl;
    std::cout << "So diem: " << point << std::endl;
}
