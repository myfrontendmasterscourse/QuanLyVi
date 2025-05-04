#include "Permission.h"
#include "Account.h"
#include <iostream>
#include <algorithm>

std::string permissionToString(PermissionType permission) {
    switch (permission) {
        case PermissionType::VIEW_OWN_ACCOUNT: 
            return "Xem thong tin tai khoan ca nhan";
        case PermissionType::EDIT_OWN_FULLNAME: 
            return "Sua ho ten ca nhan";
        case PermissionType::EDIT_OWN_DOB: 
            return "Sua ngay sinh ca nhan";
        case PermissionType::EDIT_OWN_ADDRESS: 
            return "Sua dia chi ca nhan";
        case PermissionType::EDIT_OWN_PHONE: 
            return "Sua so dien thoai ca nhan";
        case PermissionType::EDIT_OWN_EMAIL: 
            return "Sua email ca nhan";
        case PermissionType::CHANGE_OWN_PASSWORD: 
            return "Doi mat khau ca nhan";
        case PermissionType::VIEW_GROUP_LIST: 
            return "Xem danh sach nhom nguoi dung";
        case PermissionType::CREATE_ACCOUNT: 
            return "Tao tai khoan moi";
        case PermissionType::EDIT_OTHER_ACCOUNT: 
            return "Chinh sua thong tin tai khoan nguoi khac (lam ho)";
        case PermissionType::BACKUP_DATA: 
            return "Sao luu du lieu";
        case PermissionType::RESTORE_DATA: 
            return "Phuc hoi du lieu";
        default: 
            return "Quyen khong xac dinh";
    }
}

PermissionManager::PermissionManager() {
    // Thiết lập quyền cho người dùng thường (REGULAR)
    rolePermissions[static_cast<int>(AccountType::REGULAR)] = {
        PermissionType::VIEW_OWN_ACCOUNT,
        PermissionType::EDIT_OWN_FULLNAME,
        PermissionType::EDIT_OWN_DOB,
        PermissionType::EDIT_OWN_ADDRESS,
        PermissionType::EDIT_OWN_PHONE,
        PermissionType::EDIT_OWN_EMAIL,
        PermissionType::CHANGE_OWN_PASSWORD
    };
    
    // Thiết lập quyền cho người quản lý (ADMIN)
    rolePermissions[static_cast<int>(AccountType::ADMIN)] = {
        // Quyền của người dùng thường
        PermissionType::VIEW_OWN_ACCOUNT,
        PermissionType::EDIT_OWN_FULLNAME,
        PermissionType::EDIT_OWN_DOB,
        PermissionType::EDIT_OWN_ADDRESS,
        PermissionType::EDIT_OWN_PHONE,
        PermissionType::EDIT_OWN_EMAIL,
        PermissionType::CHANGE_OWN_PASSWORD,
        
        // Quyền quản lý
        PermissionType::VIEW_GROUP_LIST,
        PermissionType::CREATE_ACCOUNT,
        PermissionType::EDIT_OTHER_ACCOUNT,
        PermissionType::BACKUP_DATA,
        PermissionType::RESTORE_DATA
    };
}

bool PermissionManager::hasPermission(AccountType accountType, PermissionType permission) const {
    int typeIndex = static_cast<int>(accountType);
    
    // Kiểm tra xem loại tài khoản có tồn tại trong ánh xạ không
    if (rolePermissions.find(typeIndex) == rolePermissions.end()) {
        return false;
    }
    
    // Tìm kiếm quyền trong danh sách quyền của loại tài khoản
    const auto& permissions = rolePermissions.at(typeIndex);
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

std::vector<PermissionType> PermissionManager::getPermissions(AccountType accountType) const {
    int typeIndex = static_cast<int>(accountType);
    
    if (rolePermissions.find(typeIndex) != rolePermissions.end()) {
        return rolePermissions.at(typeIndex);
    }
    
    return {}; // Trả về danh sách rỗng nếu không tìm thấy
}

void PermissionManager::displayPermissions(AccountType accountType) const {
    std::cout << "Quyen cua " 
              << (accountType == AccountType::ADMIN ? "Nguoi quan ly" : "Nguoi dung thong thuong") 
              << ":" << std::endl;
    
    const auto& permissions = getPermissions(accountType);
    
    if (permissions.empty()) {
        std::cout << "Khong co quyen nao!" << std::endl;
        return;
    }
    
    for (const auto& permission : permissions) {
        std::cout << "- " << permissionToString(permission) << std::endl;
    }
}