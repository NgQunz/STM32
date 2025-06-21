#include <stdio.h>
#include <stdint.h>

int main()
{

    uint8_t u8Buff = 0x5A; // Giả lập dữ liệu, ví dụ: 0x5A (90 trong hệ thập phân)

    // Mở file để ghi (ghi đè nếu file đã tồn tại)
    FILE *fp = fopen("dht11_data.txt", "w");
    if (fp == NULL)
    {
        perror("Không thể mở file");
        return 1;
    }
    for (int i = 0; i < 100; i++)
    {
        // Ghi dữ liệu vào file (ở đây ghi ở dạng số thập phân và hex)
        fprintf(fp, "Giá trị thập phân: %u\n", u8Buff);
        fprintf(fp, "Giá trị hexa: 0x%02X\n", u8Buff);
    }
    // Ghi dữ liệu vào file (ở đây ghi ở dạng số thập phân và hex)
    fprintf(fp, "Giá trị thập phân: %u\n", u8Buff);
    fprintf(fp, "Giá trị hexa: 0x%02X\n", u8Buff);

    // Đóng file
    fclose(fp);

    printf("Đã ghi dữ liệu vào file output.txt\n");

    return 0;
}
