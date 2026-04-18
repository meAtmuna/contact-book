#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100

char *FILENAME = "contact_book_data.csv";

typedef struct contact {
    char name[INPUT_LENGTH];
    char address[INPUT_LENGTH];
    char email[INPUT_LENGTH];
    char number[INPUT_LENGTH];
} contact;

contact contact_array[100];

int list_contacts();
int read_from_csv(contact contact_array[]);
void print_contact(const contact *contact);
int add_new_entry();

int list_contacts() {
    int contact_count = read_from_csv(contact_array);

    for (int i = 0; i < contact_count; i++)
    {
        print_contact(&contact_array[i]);
    }
    
    return 0;
}

void print_contact(const contact *contact) {
    printf("Name: %s\n", contact->name);
    printf("Address: %s\n", contact->address);
    printf("Email: %s\n", contact->email);
    printf("Number: %s\n", contact->number);
    printf("\n");
}

int read_from_csv(contact contact_array[]) {
    FILE *fptr;
    char buffer[(INPUT_LENGTH * 4 + 5)];

    int i = 0;

    fptr = fopen(FILENAME, "r");
    if(fptr == NULL) {
        printf("could not open %s\n", FILENAME);
        return 0;
    }
    
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        if (buffer[0] == '\n' || buffer[0] == '\0') continue;
        
        char *new_line_pointer  = strchr(buffer, '\n');
        if (new_line_pointer)
        {
            *new_line_pointer = '\0';
        }

        char *field = strtok(buffer, ",");
        int x = 0;

        while (field != NULL)
        {
            if (x == 0)
            {
                strncpy(contact_array[i].name, field, INPUT_LENGTH -1);
                contact_array[i].name[INPUT_LENGTH -1] = '\0';
            }else if (x == 1)
            {
                strncpy(contact_array[i].address, field, INPUT_LENGTH -1);
                contact_array[i].address[INPUT_LENGTH -1] = '\0';
            }else if (x == 2)
            {
                strncpy(contact_array[i].email, field, INPUT_LENGTH -1);
                contact_array[i].email[INPUT_LENGTH -1] = '\0';
            }else if (x == 3)
            {
                strncpy(contact_array[i].number, field, INPUT_LENGTH -1);
                contact_array[i].number[INPUT_LENGTH -1] = '\0';
            }
            
            x++;

            field = strtok(NULL, ",");
            
        }

        i++;
        if (i >= 100) break;
    }
    
    fclose(fptr);

    return i;
}


int main() {
    add_new_entry();
    list_contacts();

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

    fprintf(fptr, "%s,%s,%s,%s\n", name, address, email, number);
    fclose(fptr);

    printf("\nSaved contact!\n\n");

    return 0;
}