// WalletManager.cpp
#include "WalletManager.h"
#include "OTPManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>

WalletManager::WalletManager(const std::string& walletFilePath)
    : walletFilePath(walletFilePath) {}

void WalletManager::addWalletToFile(const Wallet& wallet) {
    std::ofstream outFile(walletFilePath, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Khong the mo file de ghi: " << walletFilePath << std::endl;
        return;
    }

    outFile << wallet.getWalletId() << ";"
            << wallet.getUsername() << ";"
            << wallet.getPoint() << "\n";

    outFile.close();
}

void WalletManager::addWalletToFile(const std::string& username, int point) {
    std::string walletId = generateNextWalletId();
    Wallet wallet(walletId, username, point);
    addWalletToFile(wallet);
}

std::vector<Wallet> WalletManager::loadWallets() {
    std::vector<Wallet> wallets;
    std::ifstream inFile(walletFilePath);
    std::string line;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string walletId, username, pointStr;

        if (std::getline(ss, walletId, ';') &&
            std::getline(ss, username, ';') &&
            std::getline(ss, pointStr)) {
            try {
                int point = std::stoi(pointStr);
                wallets.emplace_back(walletId, username, point);
            } catch (...) {
                std::cerr << "Dong bi loi khi chuyen point sang so: " << line << std::endl;
            }
        }
    }

    return wallets;
}

Wallet* WalletManager::findWalletByUsername(const std::string& username) {
    std::vector<Wallet> wallets = loadWallets();
    for (Wallet& wallet : wallets) {
        if (wallet.getUsername() == username) {
            return new Wallet(wallet); // trả về bản sao
        }
    }
    return nullptr;
}

std::string WalletManager::generateNextWalletId() {
    std::vector<Wallet> wallets = loadWallets();
    int maxId = 0;

    for (const Wallet& wallet : wallets) {
        try {
            int id = std::stoi(wallet.getWalletId());
            if (id > maxId) maxId = id;
        } catch (...) {
            // bỏ qua nếu không phải số
        }
    }

    return std::to_string(maxId + 1);
}

bool WalletManager::transferPointsFromUserToUser(const std::string& fromUsername) {
                    int amount;
                    std::string toUsername;
                    std::cout << "=== Nhap thong tin chuyen diem ===" << std::endl;

                    std::cout << "Nhap ten nguoi nhan: ";
                    std::getline(std::cin, toUsername);

    std::vector<Wallet> wallets = loadWallets();
    int fromIndex = -1, toIndex = -1;

    // Tìm chỉ số ví gửi và ví nhận theo username
    for (size_t i = 0; i < wallets.size(); ++i) {
        if (wallets[i].getUsername() == fromUsername) fromIndex = i;
        if (wallets[i].getUsername() == toUsername) toIndex = i;
    }

    if (fromIndex == -1 || toIndex == -1) {
        std::string fromId = (fromIndex != -1) ? wallets[fromIndex].getWalletId() : "";
        std::string fromUser = (fromIndex != -1) ? wallets[fromIndex].getUsername() : fromUsername;
        std::string toUser = (toIndex != -1) ? wallets[toIndex].getUsername() : toUsername;
        std::string toId = (toIndex != -1) ? wallets[toIndex].getWalletId() : "unknownid";
        logTransaction(fromId.empty() ? "unknownid" : fromId, toId, fromUser, toUser, amount, "That bai: Khong tim thay vi gui/nhan");
        std::cerr << "Khong tim thay vi gui hoac nhan.\n";
        return false;
    }

    Wallet& fromWallet = wallets[fromIndex];
    Wallet& toWallet = wallets[toIndex];

    std::cout << "Nhap so diem can chuyen: ";
    std::cin >> amount;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (fromWallet.getPoint() < amount) {
        logTransaction(fromWallet.getWalletId(), toWallet.getWalletId(), fromWallet.getUsername(), toWallet.getUsername(), amount, "That bai: Khong du diem");
        std::cerr << "Khong du diem de chuyen.\n";
        return false;
    }

    OTPManager otpManager;
    std::string generatedOtp = otpManager.generateOTP(fromUsername);
    std::string enteredOtp;

    std::cout << "Nhap ma OTP da duoc sinh: " << generatedOtp << "\n";  // de test, ban co the an otp
    std::cout << "Vui long nhap lai ma OTP de xac nhan giao dich: ";
    std::getline(std::cin, enteredOtp);

    if (!otpManager.verifyOTP(fromUsername, enteredOtp)) {
        std::cerr << "OTP khong hop le hoac het han. Giao dich bi huy.";
        return false;
    }

    // Bắt đầu giao dịch (atomic)
    fromWallet.setPoint(fromWallet.getPoint() - amount);
    toWallet.setPoint(toWallet.getPoint() + amount);

    std::ofstream outFile(walletFilePath, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Khong the ghi lai file vi. Giao dich bi huy.\n";
        return false;
    }
    for (const Wallet& wallet : wallets) {
        outFile << wallet.getWalletId() << ";"
                << wallet.getUsername() << ";"
                << wallet.getPoint() << "\n";
    }
    outFile.close();

    logTransaction(fromWallet.getWalletId(), toWallet.getWalletId(), fromWallet.getUsername(), toWallet.getUsername(), amount, "Thanh cong");
    std::cout << "Giao dich thanh cong: " << amount << " diem tu " << fromUsername << " den nguoi dung " << toUsername << "\n";
    return true;
}

bool WalletManager::transferPointsFromUserToUser(const std::string& fromUsername, const std::string& toUsername, int amount) {
    std::vector<Wallet> wallets = loadWallets();
    int fromIndex = -1, toIndex = -1;

    // Tìm chỉ số ví gửi và ví nhận theo username
    for (size_t i = 0; i < wallets.size(); ++i) {
        if (wallets[i].getUsername() == fromUsername) fromIndex = i;
        if (wallets[i].getUsername() == toUsername) toIndex = i;
    }

    if (fromIndex == -1 || toIndex == -1) {
        std::string fromId = (fromIndex != -1) ? wallets[fromIndex].getWalletId() : "";
        std::string fromUser = (fromIndex != -1) ? wallets[fromIndex].getUsername() : fromUsername;
        std::string toUser = (toIndex != -1) ? wallets[toIndex].getUsername() : toUsername;
        std::string toId = (toIndex != -1) ? wallets[toIndex].getWalletId() : "unknownid";
        logTransaction(fromId.empty() ? "unknownid" : fromId, toId, fromUser, toUser, amount, "That bai: Khong tim thay vi gui/nhan");
        std::cerr << "Khong tim thay vi gui hoac nhan.\n";
        return false;
    }

    Wallet& fromWallet = wallets[fromIndex];
    Wallet& toWallet = wallets[toIndex];

    if (fromWallet.getPoint() < amount) {
        logTransaction(fromWallet.getWalletId(), toWallet.getWalletId(), fromWallet.getUsername(), toWallet.getUsername(), amount, "That bai: Khong du diem");
        std::cerr << "Khong du diem de chuyen.\n";
        return false;
    }

    OTPManager otpManager;
    std::string generatedOtp = otpManager.generateOTP(fromUsername);
    std::string enteredOtp;
    // Bắt đầu giao dịch (atomic)
    fromWallet.setPoint(fromWallet.getPoint() - amount);
    toWallet.setPoint(toWallet.getPoint() + amount);

    std::ofstream outFile(walletFilePath, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Khong the ghi lai file vi. Giao dich bi huy.\n";
        return false;
    }
    for (const Wallet& wallet : wallets) {
        outFile << wallet.getWalletId() << ";"
                << wallet.getUsername() << ";"
                << wallet.getPoint() << "\n";
    }
    outFile.close();

    logTransaction(fromWallet.getWalletId(), toWallet.getWalletId(), fromWallet.getUsername(), toWallet.getUsername(), amount, "Thanh cong");
    std::cout << "Giao dich thanh cong: " << amount << " diem tu " << fromUsername << " den nguoi dung " << toUsername << "\n";
    return true;
}

void WalletManager::logTransaction(const std::string& fromId, const std::string& toId, const std::string& fromUsername, const std::string& toUsername, int amount, const std::string& status) {
    std::ofstream logFile(transactionFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Khong the mo file giao dich." << std::endl;
        return;
    }

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    logFile << timeStr << ";"
            << fromId << ";"
            << toId << ";"
            << fromUsername << ";"
            << toUsername << ";"
            << amount << ";"
            << status << "\n";

    logFile.close();
}

int WalletManager::getBalanceByUsername(const std::string& username) {
    std::vector<Wallet> wallets = loadWallets();
    for (const Wallet& wallet : wallets) {
        if (wallet.getUsername() == username) {
            return wallet.getPoint();
        }
    }
    return -1; // không tìm thấy
}

std::vector<std::string> WalletManager::getTransactionHistoryByUsername(const std::string& username) {
    std::vector<std::string> history;
    std::ifstream inFile(transactionFilePath);
    if (!inFile.is_open()) {
        std::cerr << "Khong the mo file lich su giao dich." << std::endl;
        return history;
    }

    // Lấy walletId từ username
    Wallet* userWallet = findWalletByUsername(username);
    if (!userWallet) {
        std::cerr << "Khong tim thay vi nguoi dung: " << username << std::endl;
        return history;
    }
    std::string userWalletId = userWallet->getWalletId();
    delete userWallet;

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string time, fromId, toId, amount, status, fromUsername, toUsername;

        std::getline(ss, time, ';');
        std::getline(ss, fromId, ';');
        std::getline(ss, toId, ';');
        std::getline(ss, fromUsername, ';');
        std::getline(ss, toUsername, ';');
        std::getline(ss, amount, ';');
        std::getline(ss, status);

        if (fromId == userWalletId || toId == userWalletId) {
            std::ostringstream formatted;
            formatted << time << " | From: " << fromUsername
                      << " | To: " << toUsername
                      << " | Amount: " << amount
                      << " | Status: " << status;
            history.push_back(formatted.str());
        }
    }

    inFile.close();
    return history;
}

