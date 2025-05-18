* Bài Tập Lớn C++: Hệ thống quản lý đăng nhập, đăng ký và ví điểm thưởng


1, Giới thiệu dự án

Dự án xây dựng hệ thống quản lý tài khoản người dùng, bao gồm chức năng đăng ký, đăng nhập, đổi mật khẩu, phân quyền (người dùng và quản trị viên), quản lý ví điểm thưởng và giao dịch điểm giữa người dùng. OTP được sử dụng để tăng cường bảo mật cho các thao tác quan trọng như chuyển điểm hoặc cập nhật thông tin tài khoản.

Dự án được phát triển bằng ngôn ngữ C++, không sử dụng thư viện bên ngoài, toàn bộ dữ liệu được lưu trữ bằng tệp văn bản.


2, Thành viên tham gia

| Họ và tên       | MSV        | Công việc đảm nhiệm                                  |
|-----------------|----------  |------------------------------------------------------|
| Nguyễn Hữu Đạt  | K24DTCN179 | Xử lý đăng ký, đăng nhập và quản lý tài khoản 
                               |Giao diện người dùng và lưu trữ lịch sử giao dịch
| Vũ Thị Yến      | K24DTCN251 | OTP xác thực hai lớp, sinh mật khẩu ,README.md       |
| Trần Đăng Khôi  | K24DTCN204 | Quản lý hoạt động ví                                 | 


3, Phân tích và đặc tả chức năng

- Quản lý tài khoản: Đăng ký, đăng nhập, đổi mật khẩu, sinh mật khẩu tự động (nếu cần).
- OTP bảo mật 2 lớp: Mã xác nhận gửi về tài khoản khi thực hiện các thay đổi nhạy cảm.
- Phân quyền: Người dùng thường và người quản lý (có thể tạo tài khoản hộ, cập nhật thông tin hộ).
- Quản lý ví: Mỗi người dùng có 1 ví, có thể chuyển điểm qua lại giữa các ví.
- Lưu trữ: Thông tin người dùng, ví, và log được lưu vào file trong thư mục accounts.



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
│ ├── QuanLyTaiKhoan.exe
│ 
│
├── Makefile
└── README.md




5, Hướng dẫn thao tác chương trình
-Chạy main, chọn chức năng từ menu: Đăng ký, đăng nhập, quản lý ví, đổi mật khẩu,...

-Khi thực hiện giao dịch hoặc cập nhật thông tin, hệ thống sẽ gửi mã OTP để xác nhận.

-Người quản trị có thể tạo tài khoản cho người khác hoặc cập nhật hộ.

6,Tài liệu tham khảo
-OTP và bảo mật: Wikipedia - OTP

-Hash mật khẩu: GeeksForGeeks - Hashing

-Tài liệu bài giảng môn Lập trình C++

7,  Mã nguồn
-Toàn bộ source code đều có chú thích chi tiết từng class, hàm và chức năng.

-Mỗi class được thiết kế rõ ràng theo mô hình hướng đối tượng.

-Các thao tác như input/output, xử lý OTP, ghi log đều có mô tả cụ thể trong mã.
