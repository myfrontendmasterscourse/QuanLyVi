#include "OTPManager.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>

OTPManager::OTPManager()
{
    std::srand(std::time(nullptr));
}

std::string OTPManager::generate6DigitOTP()
{
    int otp = 100000 + std::rand() % 900000;
    return std::to_string(otp);
}

std::string OTPManager::generateOTP(const std::string &username)
{
    std::string otp = generate6DigitOTP();
    auto now = std::chrono::steady_clock::now();
    otpStore[username] = std::make_pair(otp, now);
    return otp;
}

bool OTPManager::verifyOTP(const std::string &username, const std::string &otp)
{
    auto it = otpStore.find(username);
    if (it == otpStore.end())
        return false;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - it->second.second).count();

    if (it->second.first == otp && elapsed <= otpValidDuration)
    {
        otpStore.erase(it); // OTP dùng 1 lần
        return true;
    }
    return false;
}

void OTPManager::clearOTP(const std::string &username)
{
    otpStore.erase(username);
}
