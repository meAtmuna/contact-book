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
void wait_for_enter();
void search_contacts();

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

void clear_screen() {
    #ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter() {

    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}

void sanitize_input(char *str) {
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == ',')
        {
            str[i] = ';';
        }
    }
    
}

void remove_quotes(char * str) {
    int i = 0, j = 0;

    while (str[i])
    {
        if (str[i] != '"')
        {
            str[j++] = str[i];
        }
        
        i++;
    }
    
    str[j] = '\0';
}

void search_contacts() {
    char query[INPUT_LENGTH];

    printf("Enter name to search: ");
    fgets(query, INPUT_LENGTH, stdin);

    query[strcspn(query, "\n")] = 0;

    int contact_count = read_from_csv(contact_array);
    int found = 0;

    for (int i = 0; i < contact_count; i++)
    {
        if (strstr(contact_array[i].name, query) != NULL)
        {
            print_contact(&contact_array[i]);
            found = 1;
        }
    }
    
    if (!found)
    {
        printf("\nNo contact found!\n");
    }
}

char* get_field(char *str, int *i){
    static char field[INPUT_LENGTH];
    int j = 0;
    int in_quotes = 0;

    while (str[*i] != '\0')
    {
        char current_char = str[*i];
        (*i)++;

        if (current_char == '"')
        {
            in_quotes = !in_quotes;
            continue;
        }
        
        if (current_char == ',' && !in_quotes)
        {
            break;
        }
        
        field[j++] = current_char;
    }
    
    field[j] = '\0';
    return field;

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

        int i_buf = 0;
        int x = 0;

        while (buffer[i_buf] != '\0')
        {
            char *field = get_field(buffer, &i_buf);
            remove_quotes(field);

            if (x >= 4) break;

            if (x == 0)
            {
                strncpy(contact_array[i].name, field, INPUT_LENGTH -1);
                contact_array[i].name[INPUT_LENGTH -1] = '\0';
            }
            else if (x == 1)
            {
                strncpy(contact_array[i].address, field, INPUT_LENGTH -1);
                contact_array[i].address[INPUT_LENGTH -1] = '\0';
            }
            else if (x == 2)
            {
                strncpy(contact_array[i].email, field, INPUT_LENGTH -1);
                contact_array[i].email[INPUT_LENGTH -1] = '\0';
            }
            else if (x == 3)
            {
                strncpy(contact_array[i].number, field, INPUT_LENGTH -1);
                contact_array[i].number[INPUT_LENGTH -1] = '\0';
            }
            
            x++;
        }

        i++;
        if (i >= 100) break;
    }
    
    fclose(fptr);

    return i;
}


int main(int argc, char *argv[]) {

    if (argc > 1)
    {
        FILENAME = argv[1];
    }
    
    char input[10];

    while (1)
    {
        clear_screen();

        printf("\n--- Contact Book ---\n");
        printf("[A] Add Contact\n");
        printf("[L] List Contacts\n");
        printf("[s] Search Contacts\n");
        printf("[H] Help\n");
        printf("[Q] Quit\n");
        printf("Enter choice: ");

        fgets(input, sizeof(input), stdin);

        char choice = tolower(input[0]);

        if (choice == 'a')
        {
            add_new_entry();
            wait_for_enter();
        }
        else if (choice == 'l')
        {
            list_contacts();
            wait_for_enter();
        }
        else if (choice == 's')
        {
            search_contacts();
            wait_for_enter();
        }
        else if (choice == 'h')
        {
            printf("\nCommands:\n");
            printf("A - Add contact\n");
            printf("L - List contacts\n");
            printf("H - Help\n");
            printf("Q - Quit\n\n");

            wait_for_enter();
        }
        else if (choice == 'q')
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Unknown command!\n");
        }
    }

    return 0;
}

int add_new_entry() {
    FILE *fptr;

    fptr = fopen(FILENAME, "a");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    
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

    sanitize_input(name);
    sanitize_input(address);
    sanitize_input(email);
    sanitize_input(number);

    fprintf(fptr, "\"%s\",\"%s\",\"%s\",\"%s\"\n", name, address, email, number);
    fclose(fptr);

    printf("\nSaved contact!\n\n");

    return 0;
}