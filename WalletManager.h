// WalletManager.h
#ifndef WALLETMANAGER_H
#define WALLETMANAGER_H

#include "Wallet.h"
#include <vector>
#include <string>

class WalletManager {
private:
    std::string walletFilePath;
    std::string transactionFilePath = "transactions.txt";

public:
    // Constructor
    WalletManager(const std::string& walletFilePath = "wallets.txt");

    // Thêm ví vào file
    void addWalletToFile(const Wallet& wallet);
    void addWalletToFile(const std::string& username, int point);

    // Tìm ví theo username
    Wallet* findWalletByUsername(const std::string& username);

    // Tải toàn bộ ví từ file
    std::vector<Wallet> loadWallets();

    // Sinh ID số tự tăng, bắt đầu từ 1
    std::string generateNextWalletId();

    // Chuyển điểm từ username đến ví nhận theo username (atomic)
    bool transferPointsFromUserToUser(const std::string& fromUsername, const std::string& toUsername, int amount);

    bool transferPointsFromUserToUser(const std::string& fromUsername);

    // Ghi lịch sử giao dịch (thêm trạng thái)
    void logTransaction(const std::string& fromId, const std::string& toId, const std::string& fromUsername, const std::string& toUsername, int amount, const std::string& status);

    int getBalanceByUsername(const std::string& username);

    std::vector<std::string> getTransactionHistoryByUsername(const std::string& username);

};

#endif // WALLETMANAGER_H
