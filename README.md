![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![License](https://img.shields.io/badge/License-MIT-green)

# BTL07: Hệ thống phân tích đơn hàng và tối ưu lô hàng

## Thành viên
| Họ và tên | MSSV |
|-|-|
| Nguyễn Đức Bảo | 23280040 |
| Trần Trung Kiên | 23280066 |
| Nguyễn Đức Hiếu | 24280064 |

## Cấu trúc project

```bash
    BTL07_Ecommerce_Logistics/
    │
    ├── data/
    │   ├── target.txt
    │   └── test_cases/
    │       ├── orders.csv # normal case
    │       ├── test1_orders.csv # edge case: 1 ngày 1 đơn
    │       ├── test2_orders.csv # edge case: doanh thu âm (hoàn trả)
    │       └── test3_orders.csv # edge case: S không đạt được
    ├── include/
    │   ├── models.h
    │   ├── io.h
    │   ├── processing.h
    │   ├── analytics.h
    │   ├── algorithms.h
    │   └── utils.h
    │
    ├── output/
    │
    ├── src/
    │   ├── io.cpp
    │   ├── processing.cpp 
    │   ├── analytics.cpp 
    │   ├── algorithms.cpp
    │   ├── utils.cpp
    │   └── main.cpp
    │
    ├── .gitignore
    ├── LICENSE
    ├── README.md
    ├── Makefile
    └── run_all.bat
```

## Cấu trúc dữ liệu

Dự án sử dụng cấu trúc dữ liệu lồng nhau để tổ chức thông tin đơn hàng và các mục hàng:

- `DailySummary`
  - `vector<Order>`
    - `vector<LineItem>`

## Các thuật toán

Dự án tích hợp và áp dụng các thuật toán tối ưu hóa trên dãy con để phân tích dữ liệu:

- **Kadane**: Thuật toán tìm đoạn con có tổng lớn nhất, được sử dụng để xác định chuỗi ngày có doanh thu cao nhất.
- **Sliding Window**: Kỹ thuật cửa sổ trượt, được áp dụng để tìm khoảng thời gian ngắn nhất đạt được mục tiêu doanh thu $S$ cụ thể.
- **Prefix Sum**: Kỹ thuật tổng tiền tố, dùng để tính toán tổng doanh thu hiệu quả trong một khoảng thời gian (Range Sum Query).
- **LIS (Longest Increasing Subsequence)**: Một biến thể của thuật toán tìm dãy con tăng dài nhất, được sử dụng để xác định chuỗi ngày tăng trưởng doanh thu liên tiếp dài nhất.

## Hướng dẫn Build & Run

### Yêu cầu 

- **Trình biên dịch C++**: Hỗ trợ chuẩn C++17 (ví dụ: g++ phiên bản 7 trở lên).
- **Công cụ `make`**: Để tự động hóa quá trình biên dịch.
### Clone và change dir
1. **Clone và chuyển đổi thư mục**

    ```bash
    git clone https://github.com/ducbao210/BTL07_Ecommerce_Logistics.git
    ```

    ```bash
    cd BTL07_Ecommerce_Logistics
    ```

### Build

Mở terminal hoặc Command Prompt tại thư mục gốc của dự án và chạy lệnh sau để biên dịch mã nguồn:

```bash
make
```

Tạo ra file thực thi `logistics_app` trong thư mục gốc của dự án.

### Run

Có thể chạy ứng dụng theo các cách sau:

1.  **Chạy với dữ liệu mặc định:**

    ```bash
    ./logistics_app
    ```

2.  **Chạy với file test cụ thể:**

    ```bash
    ./logistics_app data/test_cases/test1_orders.csv data/target.txt
    ```

    *Lưu ý: Thay thế `data/test_cases/test1_orders.csv` bằng đường dẫn đến các file dữ liệu mong muốn.*

3.  **Chạy tất cả các bộ kiểm thử (trên Windows):**

    Sử dụng script `run_all.bat` để thực thi tất cả các bộ kiểm thử đã định nghĩa:

    ```bash
    .\run_all.bat
    ```

### Dọn dẹp

Để xóa các file đối tượng và file thực thi đã biên dịch, chạy lệnh sau:

```bash
make clean
```

## Test case:

1.  **Normal Case** (`orders.csv`):
    - **Mô tả:** Dữ liệu đầy đủ với nhiều ngày và nhiều đơn hàng, đại diện cho việc sử dụng thông thường.

2.  **Edge Case 1** (`test1_orders.csv`):
    - **Mô tả:** Dữ liệu chỉ chứa một ngày và một đơn hàng duy nhất.

3.  **Edge Case 2** (`test2_orders.csv`):
    - **Mô tả:** Dữ liệu bao gồm các trường hợp doanh thu âm (ví dụ: do hoàn trả hàng).

4.  **Edge Case 3** (`test3_orders.csv`):
    - **Mô tả:** Mục tiêu doanh thu $S$ được đặt ra không thể đạt được với dữ liệu hiện có.

## Thành phần Output

Sau khi chạy ứng dụng, các kết quả tính toán sẽ được lưu trữ trong thư mục `output/` với các file sau:

- `./revenue_report.csv`: Báo cáo thống kê chi tiết doanh thu theo từng ngày.
- `./best_period.txt`: Kết quả từ thuật toán Kadane, chỉ ra chuỗi ngày có doanh thu cao nhất.
- `./window.txt`: Kết quả từ thuật toán Sliding Window, hiển thị cửa sổ ngày ngắn nhất đạt mục tiêu doanh thu.

## License
[LICENSE](LICENSE)
#
