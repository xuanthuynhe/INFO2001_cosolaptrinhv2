#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char namewriter[50];
    float price;
} Book;

int searchBook(Book* arr, int size, char* target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, target) == 0) {
            return i;
        }
    }
    return -1; 
}

int main() {
    Book* arr;
    int n;
    printf("Nhap so luong sach: ");
    scanf("%d", &n);
    
    // Cap phat lai bo nho
    arr = (Book*)malloc(n * sizeof(Book));
    if (arr == NULL) {
        printf("Khong the cap phat bo nho.");
        exit(1);
    }
    
    //Nhap gia tri cho mang
    for (int i = 0; i < n; i++) {
        printf("Nhap ten sach thu %d: ", i + 1);
        fflush(stdin);
        gets(arr[i].name);
        
        printf("Nhap ten tac gia thu %d: ", i + 1);
        fflush(stdin);
        gets(arr[i].namewriter);
        
        printf("Nhap gia cua sach thu %d: ", i + 1);
        scanf("%f", &arr[i].price);
    }
    
    // Hien thi thong tin sach
    printf("\nThong tin cac sach:\n");
    for (int i = 0; i < n; i++) {
        printf("Sach thu %d:\n", i + 1);
        printf("Ten: %s\n", arr[i].name);
        printf("Tac gia: %s\n", arr[i].namewriter);
        printf("Gia: %.2f\n", arr[i].price);
        printf("\n");
    }
    
    // Tìm kiem sach
    char target[50];
    printf("Nhap ten sach can tim: ");
    fflush(stdin);
    gets(target);
    
    int index = searchBook(arr, n, target);
    if (index != -1) {
        printf("Sach _%s_ co mat trong danh sach tai vi tri %d.\n", target, index + 1);
    } else {
        printf("Sach _%s_ khong co trong danh sach.\n", target);
    }
    
    // Giai phong bo nho khi khong sd
    free(arr);
    
    return 0;
}
