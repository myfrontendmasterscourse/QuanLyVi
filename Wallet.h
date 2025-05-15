#ifndef WALLET_H
#define WALLET_H

#include <string>

class Wallet {
private:
    std::string walletId;
    std::string username;
    int point;

public:
    // Constructors
    Wallet() = default;
    Wallet(const std::string& walletId, const std::string& username, int point);

    // Getters
    std::string getWalletId() const;
    std::string getUsername() const;
    int getPoint() const;

    // Setters
    void setWalletId(const std::string& walletId);
    void setUsername(const std::string& username);
    void setPoint(int point);

    // Display wallet information
    void displayInfo() const;
};

#endif // WALLET_H
