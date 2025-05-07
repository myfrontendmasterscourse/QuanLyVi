#ifndef OTPMANAGER_H
#define OTPMANAGER_H

#include <string>
#include <unordered_map>
#include <chrono>

class OTPManager
{
private:
    std::unordered_map<std::string, std::pair<std::string, std::chrono::steady_clock::time_point>> otpStore;
    const int otpValidDuration = 60; // seconds

    std::string generate6DigitOTP();

public:
    OTPManager();

    std::string generateOTP(const std::string &username);                // tạo OTP cho người dùng
    bool verifyOTP(const std::string &username, const std::string &otp); // xác thực OTP
    void clearOTP(const std::string &username);                          // xóa OTP sau khi dùng
};

#endif
