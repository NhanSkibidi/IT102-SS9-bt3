#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    float cuocHanhLy;
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int soLuong = 0;
    printf("Nhập số lượng vé máy bay: ");
    if (scanf("%d", &soLuong) != 1 || soLuong < 1 || soLuong > MAX_VE) {
        printf("Số lượng vé không hợp lệ! Chương trình kết thúc.\n");
        return 0;
    }
    while (getchar() != '\n');
    for (int i = 0; i < soLuong; i++) {
        printf("\n--- Nhập thông tin vé thứ %d ---\n", i + 1);
        printf("Mã vé PNR: ");
        scanf("%s", danhSachVe[i].maVe);
        while (getchar() != '\n');
        printf("Họ tên hành khách: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        size_t len = strlen(danhSachVe[i].tenHanhKhach);
        if (len > 0 && danhSachVe[i].tenHanhKhach[len - 1] == '\n') {
            danhSachVe[i].tenHanhKhach[len - 1] = '\0';
        }
        printf("Hạng vé (Business/Deluxe/Eco): ");
        scanf("%s", danhSachVe[i].hangVe);
        do {
            printf("Khối lượng hành lý ký gửi (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Khối lượng hành lý không được âm! Vui lòng nhập lại.\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy <= 20.0f) {
                danhSachVe[i].cuocHanhLy = 0.0f;
            } else {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20.0f) * 50000.0f;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000.0f;
        }
    }
    float tongTienCuoc = 0.0f;
    int maxIndex = 0;
    for (int i = 0; i < soLuong; i++) {
        tongTienCuoc += danhSachVe[i].cuocHanhLy;
        if (danhSachVe[i].canNangHanhLy > danhSachVe[maxIndex].canNangHanhLy) {
            maxIndex = i;
        }
    }
    printf("\n================================== DANH SÁCH VÉ MÁY BAY CHUYẾN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < soLuong; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1,
               danhSachVe[i].maVe,
               danhSachVe[i].tenHanhKhach,
               danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy,
               danhSachVe[i].cuocHanhLy);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tổng tiền cước hành lý toàn chuyến: %.0f VNĐ\n", tongTienCuoc);
    printf("Vé có hành lý ký gửi nặng nhất: %s - %s (%.1f kg)\n",
           danhSachVe[maxIndex].maVe,
           danhSachVe[maxIndex].tenHanhKhach,
           danhSachVe[maxIndex].canNangHanhLy);
    char pnrTimKiem[15];
    printf("\nNhập mã vé PNR cần cập nhật hành lý: ");
    scanf("%s", pnrTimKiem);
    int foundIndex = -1;
    for (int i = 0; i < soLuong; i++) {
        if (strcmp(danhSachVe[i].maVe, pnrTimKiem) == 0) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf("Không tìm thấy mã vé PNR này trong hệ thống!\n");
    } else {
        do {
            printf("Nhập cân nặng hành lý ký gửi mới (kg): ");
            scanf("%f", &danhSachVe[foundIndex].canNangHanhLy);
            if (danhSachVe[foundIndex].canNangHanhLy < 0) {
                printf("Khối lượng hành lý không được âm! Vui lòng nhập lại.\n");
            }
        } while (danhSachVe[foundIndex].canNangHanhLy < 0);
        if (strcmp(danhSachVe[foundIndex].hangVe, "Business") == 0) {
            if (danhSachVe[foundIndex].canNangHanhLy <= 20.0f) {
                danhSachVe[foundIndex].cuocHanhLy = 0.0f;
            } else {
                danhSachVe[foundIndex].cuocHanhLy = (danhSachVe[foundIndex].canNangHanhLy - 20.0f) * 50000.0f;
            }
        } else {
            danhSachVe[foundIndex].cuocHanhLy = danhSachVe[foundIndex].canNangHanhLy * 50000.0f;
        }
        printf("\n--- CẬP NHẬT THÔNG TIN HÀNH LÝ ---\n");
        printf("Tìm thấy mã vé %s. Đã cập nhật cước hành lý mới: %.0f VNĐ.\n",
               danhSachVe[foundIndex].maVe,
               danhSachVe[foundIndex].cuocHanhLy);
        printf("\n================================ DANH SÁCH VÉ MÁY BAY SẠU CẬP NHẬT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n", "STT", "MÃ VÉ", "HỌ TÊN HÀNH KHÁCH", "HẠNG VÉ", "HÀNH LÝ (KG)", "CƯỚC PHÍ (VNĐ)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < soLuong; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
                   i + 1,
                   danhSachVe[i].maVe,
                   danhSachVe[i].tenHanhKhach,
                   danhSachVe[i].hangVe,
                   danhSachVe[i].canNangHanhLy,
                   danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    }
    return 0;
}