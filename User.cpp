#include "User.h"
#include <iostream>

User::User(const std::string& fullName, const std::string& dateOfBirth, 
           const std::string& address, const std::string& phoneNumber, 
           const std::string& email)
    : fullName(fullName), dateOfBirth(dateOfBirth), address(address),
      phoneNumber(phoneNumber), email(email) {}

// Getters
std::string User::getFullName() const { return fullName; }
std::string User::getDateOfBirth() const { return dateOfBirth; }
std::string User::getAddress() const { return address; }
std::string User::getPhoneNumber() const { return phoneNumber; }
std::string User::getEmail() const { return email; }

// Setters
void User::setFullName(const std::string& fullName) { this->fullName = fullName; }
void User::setDateOfBirth(const std::string& dateOfBirth) { this->dateOfBirth = dateOfBirth; }
void User::setAddress(const std::string& address) { this->address = address; }
void User::setPhoneNumber(const std::string& phoneNumber) { this->phoneNumber = phoneNumber; }
void User::setEmail(const std::string& email) { this->email = email; }

// Display user information
void User::displayInfo() const {
    std::cout << "Ho va ten: " << fullName << std::endl;
    std::cout << "Ngay sinh: " << dateOfBirth << std::endl;
    std::cout << "Dia chi: " << address << std::endl;
    std::cout << "So dien thoai: " << phoneNumber << std::endl;
    std::cout << "Email: " << email << std::endl;
}