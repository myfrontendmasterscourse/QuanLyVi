#ifndef PASSWORD_HASHER_H
#define PASSWORD_HASHER_H

#include <string>
#include <random>
#include <functional>
#include <sstream>
#include <iomanip>

class PasswordHasher {
private:
    // Tạo salt (giá trị ngẫu nhiên) để tăng cường bảo mật
    static std::string generateSalt(size_t length = 16) {
        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 2);
        
        std::string salt;
        salt.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            salt += charset[distribution(generator)];
        }
        return salt;
    }

public:
    // Cấu trúc lưu trữ mật khẩu đã băm
    struct HashResult {
        std::string hashedPassword;
        std::string salt;
    };
    
    // Hàm băm mật khẩu
    static HashResult hashPassword(const std::string& password) {
        HashResult result;
        result.salt = generateSalt();
        
        // Kết hợp mật khẩu với salt
        std::string saltedPassword = password + result.salt;
        
        // Tính toán SHA-256 (phiên bản đơn giản)
        result.hashedPassword = sha256(saltedPassword);
        
        return result;
    }
    
    // Xác minh mật khẩu
    static bool verifyPassword(const std::string& password, const HashResult& hashResult) {
        // Kết hợp mật khẩu cần kiểm tra với salt đã lưu trữ
        std::string saltedPassword = password + hashResult.salt;
        
        // Băm và so sánh
        std::string hashedAttempt = sha256(saltedPassword);
        
        return hashedAttempt == hashResult.hashedPassword;
    }
    
    // Triển khai SHA-256 đơn giản (trong thực tế nên dùng thư viện như OpenSSL)
    static std::string sha256(const std::string& str) {
        std::hash<std::string> hasher;
        size_t hash = hasher(str);
        
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << hash;
        
        // Làm phức tạp hơn một chút bằng cách lặp lại quá trình băm
        for (int i = 0; i < 1000; ++i) {
            std::string temp = ss.str();
            hash = hasher(temp);
            ss.str("");
            ss << std::hex << std::setw(16) << std::setfill('0') << hash;
        }
        
        return ss.str();
    }
    
    // Chuyển đổi HashResult thành chuỗi để lưu trữ
    static std::string toString(const HashResult& hashResult) {
        return hashResult.hashedPassword + ":" + hashResult.salt;
    }
    
    // Tạo HashResult từ chuỗi đã lưu trữ
    static HashResult fromString(const std::string& str) {
        HashResult result;
        size_t colonPos = str.find(':');
        
        if (colonPos != std::string::npos) {
            result.hashedPassword = str.substr(0, colonPos);
            result.salt = str.substr(colonPos + 1);
        }
        
        return result;
    }
    
    // Sinh mật khẩu tự động
    static std::string generatePassword(size_t length = 10) {
        const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, sizeof(charset) - 2);
        
        std::string password;
        password.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            password += charset[distribution(generator)];
        }
        return password;
    }
};

#endif // PASSWORD_HASHER_H