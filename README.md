Bài Tập Lớn C++: Hệ thống quản lý đăng nhập, đăng ký và ví điểm thưởng

1, Giới thiệu dự án

Dự án xây dựng hệ thống quản lý tài khoản người dùng, bao gồm chức năng đăng ký, đăng nhập, đổi mật khẩu, phân quyền (người dùng và quản trị viên), quản lý ví điểm thưởng và giao dịch điểm giữa người dùng. OTP được sử dụng để tăng cường bảo mật cho các thao tác quan trọng như chuyển điểm hoặc cập nhật thông tin tài khoản.

Ngôn ngữ: C++
Dữ liệu: Lưu trữ bằng tệp văn bản (txt).
Mục tiêu: Luyện tập lập trình hướng đối tượng (OOP), quản lý dữ liệu thực tiễn, kỹ năng xây dựng phần mềm.

2, Thành viên tham gia

| Họ và tên       | MSV        | Công việc đảm nhiệm                                |
| --------------- | ---------- | -------------------------------------------------- |
| Nguyễn Hữu Đạt  | K24DTCN179 | Đăng ký, Đăng nhập và quản lý tài khoản, Giao diện |
| Vũ Thị Yến      | K24DTCN251 | OTP xác thực hai lớp, sinh mật khẩu ,README.md     |
| Trần Quang Khôi | K24DTCN204 | Quản lý hoạt động ví                               |

3, Phân tích và đặc tả chức năng

- Chức năng tài khoản:
  - Đăng ký:
    Nhập thông tin cá nhân, tạo tên đăng nhập & mật khẩu (mã hóa).
  - Đăng nhập:
    Kiểm tra tên đăng nhập, mật khẩu, phân quyền.
  - Đổi mật khẩu:
    Kiểm tra mật khẩu cũ, cập nhật mật khẩu mới (băm hash).
  - Phân quyền:
    Quản trị viên và người dùng thông thường.
- Chức năng bảo mật:
  - Xác thực OTP:
    Khi đăng nhập, chuyển điểm hoặc cập nhật thông tin, chương trình sẽ sinh OTP yêu cầu xác thực.
- Quản lý ví và giao dịch:
  - Tạo ví:
    Mỗi người dùng được gán một (hoặc nhiều) ví điểm thưởng.
  - Xem số dư:
    Xem thông tin ví, lịch sử giao dịch.
  - Chuyển tiền:
    Giao dịch chuyển điểm giữa các ví (yêu cầu OTP).
- Quản lý dữ liệu:
  - Lưu trữ thông tin tài khoản: `accounts.txt`
  - Lưu trữ thông tin ví: `wallets.txt`
  - lưu trữ giao dịch: `transactions.txt`
  - Backup: thư mục backups

4, Cấu trúc thư mục

Project/
├── include/ # Header files (.h)
│ ├── User.h
│ ├── AccountManager.h
│ ├── Permission.h
│ ├── PasswordHasher.h
│ ├── OTPManager.h
│ ├── Account.h
│
│
├── src/ # Source files (.cpp)
│ ├── main.cpp
│ ├── User.cpp
│ ├── AccountManager.cpp
│ ├── Account.cpp
│ ├── Permission.cpp
│ ├── OTPManager.cpp
│
│
├── data/ # Lưu dữ liệu
│ ├── Accounts.txt
│ ├── wallets.txt
│ ├── transactions.txt
│
│
├── Makefile
└── README.md

5, Hướng dẫn tải, biên dịch chương trình

- Yêu cầu:

  - Hệ điều hành: Windows/Linux/Mac (ưu tiên Windows nếu dùng file exe có sẵn)
  - Trình biên dịch C++ hỗ trợ C++20 (vd: GCC,... )
  - Không sử dụng thư viện ngoài

- Cách tải:
  Tải toàn bộ mã nguồn về, giải nén ra một thư mục.

- Build trên Windows:
  Mở CMD/Powershell tại thư mục `QuanLyViCPP`, chạy:

```bash
g++ -std=c++17 *.cpp -o QuanLyTaiKhoan.exe
```

Hoặc sử dụng file `QuanLyTaiKhoan.exe` đã build sẵn\*\* nếu không muốn biên dịch lại.

Build trên Linux/Mac:

```bash
g++ -std=c++17 *.cpp -o QuanLyTaiKhoan
```

6, Hướng dẫn chạy chương trình và thao tác

Chạy chương trình:

- Windows:
  Nhấp đôi vào `QuanLyTaiKhoan.exe` hoặc mở CMD, chạy:
  ```bash
  QuanLyTaiKhoan.exe
  ```
- Linux/Mac:
  ```bash
  ./QuanLyTaiKhoan
  ```

**Thao tác chính trên giao diện dòng lệnh:**

- Làm theo hướng dẫn để:
  - Đăng ký tài khoản mới
  - Đăng nhập vào hệ thống
  - Thực hiện các chức năng ví: kiểm tra số dư, chuyển điểm
  - Đổi mật khẩu, xác thực OTP khi cần
- Các dữ liệu (tài khoản, ví, giao dịch) sẽ được lưu vào các file txt tương ứng trong thư mục chương trình.

7,Tài liệu tham khảo
-OTP và bảo mật: Wikipedia - OTP

-Hash mật khẩu: GeeksForGeeks - Hashing

-Tài liệu bài giảng môn Lập trình C++
