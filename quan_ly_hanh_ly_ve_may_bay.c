#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong = 0;
    int i;

    printf("Nhập số lượng vé máy bay: ");
    if (scanf("%d", &soLuong) != 1 || soLuong < 1 || soLuong > 100) {
        printf("Lỗi: Số lượng vé không hợp lệ (1 <= N <= 100).\n");
        return 1;
    }
    while (getchar() != '\n');

    for (i = 0; i < soLuong; i++) {
        printf("--- Nhập thông tin vé thứ %d ---\n", i + 1);
        
        printf("Mã vé PNR: ");
        fgets(danhSachVe[i].maVe, sizeof(danhSachVe[i].maVe), stdin);
        danhSachVe[i].maVe[strcspn(danhSachVe[i].maVe, "\n")] = 0;

        printf("Họ tên hành khách: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = 0;

        printf("Hạng vé (Business/Deluxe/Eco): ");
        fgets(danhSachVe[i].hangVe, sizeof(danhSachVe[i].hangVe), stdin);
        danhSachVe[i].hangVe[strcspn(danhSachVe[i].hangVe, "\n")] = 0;

        do {
            printf("Khối lượng hành lý ký gửi (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Lỗi: Cân nặng hành lý không được âm. Vui lòng nhập lại!\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20) {
                danhSachVe[i].cuocHanhLy = 0;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000;
        }
    }

    double tongTienCuoc = 0;
    float maxCanNang = -1;
    int indexMax = 0;

    printf("\n================================== DANH SÁCH VÉ MÁY BAY CHUYẾN BAY ==================================\n");
    printf("%-4s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < soLuong; i++) {
        printf("%-4d %-12s %-25s %-12s %12.1f %15.0f\n", 
               i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, 
               danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        
        tongTienCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > maxCanNang) {
            maxCanNang = danhSachVe[i].canNangHanhLy;
            indexMax = i;
        }
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tổng tiền cước hành lý toàn chuyến: %.0f VNĐ\n", tongTienCuoc);
    printf("Vé có hành lý ký gửi nặng nhất: %s - %s (%.1f kg)\n", 
           danhSachVe[indexMax].maVe, danhSachVe[indexMax].tenHanhKhach, danhSachVe[indexMax].canNangHanhLy);

    char maTimKiem[15];
    printf("\nNhập mã vé PNR cần cập nhật hành lý: ");
    fgets(maTimKiem, sizeof(maTimKiem), stdin);
    maTimKiem[strcspn(maTimKiem, "\n")] = 0;

    int foundIndex = -1;
    for (i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, maTimKiem) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        do {
            printf("Nhập cân nặng hành lý ký gửi mới (kg): ");
            scanf("%f", &danhSachVe[foundIndex].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[foundIndex].canNangHanhLy < 0) {
                printf("Lỗi: Cân nặng hành lý không được âm. Vui lòng nhập lại!\n");
            }
        } while (danhSachVe[foundIndex].canNangHanhLy < 0);

        if (strcmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20) {
                danhSachVe[foundIndex].cuocHanhLy = 0;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20) * 50000;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000;
        }

        printf("Tìm thấy mã vé %s. Đã cập nhật cước hành lý mới: %.0f VNĐ.\n", 
               danhSachVe[foundIndex].maVe, danhSachVe[foundIndex].cuocHanhLy);

        printf("\n================================ DANH SÁCH VÉ MÁY BAY SAU CẬP NHẬT ================================\n");
        printf("%-4s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
        printf("----------------------------------------------------------------------------------------------------\n");

        for (i = 0; i < soLuong; i++) {
            printf("%-4d %-12s %-25s %-12s %12.1f %15.0f\n", 
                   i + 1, danhSachVe[i].maVe, danhSachVe[i].tenHanhKhach, 
                   danhSachVe[i].hangVe, danhSachVe[i].canNangHanhLy, danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    } else {
        printf("Không tìm thấy mã vé PNR này trong hệ thống!\n");
    }

    return 0;
}
