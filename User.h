#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string fullName;
    std::string dateOfBirth;
    std::string address;
    std::string phoneNumber;
    std::string email;
    
public:
    // Constructors
    User() = default;
    User(const std::string& fullName, const std::string& dateOfBirth, 
         const std::string& address, const std::string& phoneNumber, 
         const std::string& email);
    
    // Getters
    std::string getFullName() const;
    std::string getDateOfBirth() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    
    // Setters
    void setFullName(const std::string& fullName);
    void setDateOfBirth(const std::string& dateOfBirth);
    void setAddress(const std::string& address);
    void setPhoneNumber(const std::string& phoneNumber);
    void setEmail(const std::string& email);
    
    // Display user information
    void displayInfo() const;
};

#endif // USER_H