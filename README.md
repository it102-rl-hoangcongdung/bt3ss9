# BÁO CÁO BÀI TẬP THỰC HÀNH 03: XÂY DỰNG PHÂN HỆ KIỂM SOÁT ĐỊNH MỨC MIỄN CƯỚC HÀNH LÝ BAY

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Activity Diagram)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt3.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu chương trình]) --> InputN[Nhập số lượng vé N, kiểm tra 1 <= N <= 100]
  InputN --> CheckN{N hợp lệ?}
  CheckN -- Không --> ErrN[In lỗi N và dừng chương trình] --> EndFail([Kết thúc])
  CheckN -- Hợp lệ --> LoopStart[Bắt đầu vòng lặp nhập N vé]
  LoopStart --> InputVe[Nhập mã vé, tên, hạng vé, cân nặng]
  InputVe --> ValCanNang{Cân nặng >= 0?}
  ValCanNang -- Không --> ErrCN[Báo lỗi và yêu cầu nhập lại cân nặng] --> InputVe
  ValCanNang -- Có --> CalcCuoc[Tính cước phí theo hạng vé: Business miễn 20kg, Eco/Deluxe tính từ kg đầu]
  CalcCuoc --> CheckLoop{Đủ N vé chưa?}
  CheckLoop -- Chưa --> LoopStart
  CheckLoop -- Đã đủ --> PrintTable1[Hiển thị bảng danh sách vé, tổng tiền và vé nặng nhất]
  PrintTable1 --> InputSearch[Nhập mã vé PNR cần cập nhật]
  InputSearch --> SearchVe{Tìm kiếm tuyến tính bằng strcmp()}
  SearchVe -- Không thấy --> ErrFind[In thông báo không tìm thấy mã vé] --> EndSuccess([Kết thúc])
  SearchVe -- Tìm thấy --> InputNewWeight[Nhập cân nặng hành lý mới và validate >= 0]
  InputNewWeight --> Recalc[Tính lại cước phí hành lý mới]
  Recalc --> PrintTable2[Hiển thị bảng danh sách vé sau khi cập nhật] --> EndSuccess
```

---

## Nhiệm vụ 1: Mục tiêu và Phân tích Nghiệp vụ

Bài thực hành số 03 tập trung củng cố kỹ năng lập trình cấu trúc dữ liệu nâng cao trong ngôn ngữ C, cụ thể là việc kết hợp struct, mảng struct (Array of Struct), các thuật toán tìm kiếm tuyến tính và kỹ thuật xử lý bộ đệm bàn phím an toàn.

Quy tắc nghiệp vụ hàng không yêu cầu hệ thống phải tính toán chính xác cước phí hành lý ký gửi dựa trên hạng vé của hành khách. Hạng vé Business được miễn phí 20kg đầu tiên, trong khi các hạng vé Eco và Deluxe phải chịu phí toàn bộ số kg hành lý mang theo với đơn giá chuẩn 50.000 VNĐ/kg.

- Đơn giá chuẩn: 50.000 VNĐ cho mỗi kg hành lý ký gửi.
- Hạng Business: Miễn cước 20kg đầu, vượt quá tính tiền phần dư (canNang - 20) * 50000.
- Hạng Eco và Deluxe: Tính phí toàn bộ canNang * 50000 ngay từ kg đầu tiên.
- Kiểm soát dữ liệu biên: Khối lượng hành lý nhập vào phải >= 0, số lượng vé N phải từ 1 đến 100.

## Nhiệm vụ 2: Thiết kế Cấu trúc Dữ liệu và Thuật toán

Để lưu trữ danh sách vé máy bay, chương trình định nghĩa struct VeMayBay chứa các trường thông tin mã vé, họ tên hành khách, hạng vé, cân nặng hành lý và cước phí. Một mảng một chiều danhSachVe với sức chứa tối đa MAX_VE = 100 được khởi tạo.

Quá trình xử lý bao gồm việc nhập dữ liệu với các bẫy trôi lệnh khi kết hợp scanf() và fgets(), làm sạch bộ đệm bằng lệnh while (getchar() != '
');, và duyệt mảng để thực hiện tìm kiếm tuyến tính bằng hàm strcmp() khi người dùng yêu cầu cập nhật thông tin.

| Tên trường struct | Kiểu dữ liệu | Độ rộng / Định dạng | Ý nghĩa nghiệp vụ |
| --- | --- | --- | --- |
| maVe | char[] | Tối đa 15 ký tự | Mã đặt chỗ PNR (Ví dụ: VJ101, VN201) |
| tenHanhKhach | char[] | Tối đa 50 ký tự | Họ và tên đầy đủ của hành khách |
| hangVe | char[] | Tối đa 20 ký tự | Loại hạng vé (Business, Deluxe, Eco) |
| canNangHanhLy | float | %12.1f | Khối lượng hành lý ký gửi tính bằng kg |
| cuocHanhLy | double / float | %15.0f | Số tiền cước phí hành lý cần thanh toán (VNĐ) |

## Nhiệm vụ 3: Mã nguồn chương trình C (quan_ly_hanh_ly_ve_may_bay.c)

Toàn bộ chương trình được cài đặt hoàn chỉnh trong khối lệnh main(), tuân thủ tiêu chuẩn C11, sử dụng các định dạng printf() để căn chỉnh cột ngay ngắn và xử lý đầy đủ các ngoại lệ dữ liệu.

- Biên dịch mã nguồn bằng lệnh: gcc -std=c11 quan_ly_hanh_ly_ve_may_bay.c -o quan_ly_hanh_ly_ve_may_bay
- Repository GitHub Organization: it102-rl-hoangcongdung

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt3.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt3.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `quan_ly_hanh_ly_ve_may_bay.c`: Mã nguồn chương trình.
