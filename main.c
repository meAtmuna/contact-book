#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100

char *FILENAME = "contact_book_data.csv";

int add_new_entry();

int main() {
    add_new_entry();

    return 0;
}

int add_new_entry() {
    FILE *fptr;

    fptr = fopen(FILENAME, "a");

    char name[INPUT_LENGTH];
    char address[INPUT_LENGTH];
    char email[INPUT_LENGTH];
    char number[INPUT_LENGTH];

    printf("Enter name: ");
    fgets(name, INPUT_LENGTH, stdin);

    printf("Enter address: ");
    fgets(address, INPUT_LENGTH, stdin);

    printf("Enter email: ");
    fgets(email, INPUT_LENGTH, stdin);

    printf("Enter number: ");
    fgets(number, INPUT_LENGTH, stdin);

    name[strcspn(name, "\n")] = 0;
    address[strcspn(address, "\n")] = 0;
    email[strcspn(email, "\n")] = 0;
    number[strcspn(number, "\n")] = 0;

    fprintf(fptr, "\n%s, %s, %s, %s", name, address, email, number);
    fclose(fptr);

    printf("\nSaved contact!\n\n");

    return 0;
}