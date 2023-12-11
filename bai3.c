#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

void saveContactsToFile(const struct Contact contacts[], int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("khong the mo tep tin");
        exit(EXIT_FAILURE);
    }

    fwrite(contacts, sizeof(struct Contact), count, file);

    fclose(file);
}

void loadContactsFromFile(struct Contact contacts[], int* count, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("khong the mo tep tin");
        exit(EXIT_FAILURE);
    }

    *count = fread(contacts, sizeof(struct Contact), MAX_CONTACTS, file);

    fclose(file);
}

void displayContact(const struct Contact* contact) {
    printf("Ten: %s\n", contact->name);
    printf("So dien thoai: %s\n", contact->phone);
    printf("Email: %s\n", contact->email);
    printf("\n");
}

void addContact(struct Contact contacts[], int* count) {
    if (*count < MAX_CONTACTS) {
        struct Contact newContact;
        printf("Nhap ten: ");
        scanf("%s", newContact.name);
        printf("Nhap so dien thoai: ");
        scanf("%s", newContact.phone);
        printf("Nhap email: ");
        scanf("%s", newContact.email);

        contacts[*count] = newContact;
        (*count)++;
        printf("Lien lac da duoc them.\n");
    } else {
        printf("So lien lac da day. Khong the them lien lac.\n");
    }
}

void searchContact(const struct Contact contacts[], int count, const char* name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            displayContact(&contacts[i]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("khong tim thay lien lac co ten", name);
    }
}

void deleteContact(struct Contact contacts[], int* count, const char* name) {
    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            // Xoa lien lac bang cach dich chuyen casc phan tu sau no len
            for (int j = i; j < *count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Lien lac da duoc xoa.\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay lien lac co ten '%s'. Khong the xoa.\n", name);
    }
}

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int contactCount = 0;

    const char* filename = "contacts.dat";

    loadContactsFromFile(contacts, &contactCount, filename);

    int choice;
    char searchName[50];

    do {
        printf("1. Them lien lac\n");
        printf("2. Tim kiem lien lac\n");
        printf("3. Xoa lien lac\n");
        printf("4.Hien thi tat ca lien lac\n");
        printf("5. Luu va thoat \n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(contacts, &contactCount);
                break;
            case 2:
                printf("Nhap ten can tim kiem: ");
                scanf("%s", searchName);
                searchContact(contacts, contactCount, searchName);
                break;
            case 3:
                printf("Nhap ten can xoa: ");
                scanf("%s", searchName);
                deleteContact(contacts, &contactCount, searchName);
                break;
            case 4:
                for (int i = 0; i < contactCount; i++) {
                    displayContact(&contacts[i]);
                }
                break;
            case 5:
                saveContactsToFile(contacts, contactCount, filename);
                printf("Du lieu da duoc luu va thoat chuong trinh .\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 5);

    return 0;
}
