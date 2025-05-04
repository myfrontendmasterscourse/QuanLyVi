#ifndef PERMISSION_H
#define PERMISSION_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Account.h" // Thêm dòng này để import AccountType

// Định nghĩa các quyền hệ thống theo yêu cầu
enum class PermissionType {
    // Quyền người dùng thông thường
    VIEW_OWN_ACCOUNT,        // Xem thông tin tài khoản cá nhân
    EDIT_OWN_FULLNAME,       // Sửa họ tên
    EDIT_OWN_DOB,            // Sửa ngày sinh
    EDIT_OWN_ADDRESS,        // Sửa địa chỉ
    EDIT_OWN_PHONE,          // Sửa số điện thoại
    EDIT_OWN_EMAIL,          // Sửa email
    CHANGE_OWN_PASSWORD,     // Thay đổi mật khẩu
    
    // Quyền người dùng quản lý
    VIEW_GROUP_LIST,         // Xem danh sách nhóm người dùng
    CREATE_ACCOUNT,          // Tạo tài khoản mới
    EDIT_OTHER_ACCOUNT,      // Điều chỉnh thông tin tài khoản người khác (làm hộ)
    
    // Quyền hệ thống bổ sung
    BACKUP_DATA,             // Sao lưu dữ liệu
    RESTORE_DATA             // Phục hồi dữ liệu
};

// Chuyển đổi PermissionType thành chuỗi mô tả
std::string permissionToString(PermissionType permission);

// Lớp quản lý phân quyền
class PermissionManager {
private:
    // Ánh xạ từ loại tài khoản đến danh sách quyền
    std::unordered_map<int, std::vector<PermissionType>> rolePermissions;
    
public:
    PermissionManager();
    
    // Kiểm tra xem một loại tài khoản có quyền cụ thể không
    bool hasPermission(AccountType accountType, PermissionType permission) const;
    
    // Lấy tất cả quyền của một loại tài khoản
    std::vector<PermissionType> getPermissions(AccountType accountType) const;
    
    // Hiển thị quyền của một loại tài khoản
    void displayPermissions(AccountType accountType) const;
};

#endif // PERMISSION_H