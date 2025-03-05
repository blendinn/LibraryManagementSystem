#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CUSTOMERS 109
#define MAX_BOOKS 108
#define MAX_RENTED_BOOKS 110

struct Customer {
    int C_ID;
    char name[111];
    char surname[112];
    int age;
    float wallet;
};
struct Book {
    int B_ID;
    char name[113];
    char author[114];
    int age_limit;
    float price_per_week;
    int rented;
};
struct Rented {
    int R_ID;
    int C_ID;
    int B_ID;
    char rented_date[115];
    int week;
};

struct Customer customers[MAX_CUSTOMERS];
struct Book books[MAX_BOOKS];
struct Rented rented_books[MAX_RENTED_BOOKS];
int customer_count = 0;
int book_count = 0;
int rented_count = 0;

void readCustomersFromFile();
void readBooksFromFile();
void readRentedBooksFromFile();
void writeCustomersToFile();
void writeBooksToFile();
void writeRentedBooksToFile();
void createNewCustomer();
void depositMoneyToCustomer();
void addNewBook();
void rentABook();
void deliverABook();
void burnBook();
void updateCustomerInformation();
void updateBookInformation();
void listCustomersWhoRentBook();
void listCustomers();
void listBooks();
void RandomBook();
void b1();
int main() {
    readCustomersFromFile();
    readBooksFromFile();
    readRentedBooksFromFile();

    int choice;
    do {
        printf("\n        LIBRARY SYSTEM\n");
        printf("____________________________________\n");
        printf("1.  Create New Customer\n");
        printf("2.  Deposit Money to the Customer\n");
        printf("3.  Add New Book\n");
        printf("4.  Rent A Book\n");
        printf("5.  Delivery A Book\n");
        printf("6.  Burn Book\n");
        printf("7.  Update Customer Information\n");
        printf("8.  Update Book Information\n");
        printf("9.  List of Customers Who Rent a Book\n");
        printf("10. List of Customers\n");
        printf("11. List of Books\n");
        printf("12. Random book recommendation\n");
        printf("0.  Exit\n");
        printf("Enter number: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createNewCustomer();
                break;
            case 2:
                depositMoneyToCustomer();
                break;
            case 3:
                addNewBook();
                break;
            case 4:
                rentABook();
                break;
            case 5:
                deliverABook();
                break;
            case 6:
                burnBook();
                break;
            case 7:
                updateCustomerInformation();
                break;
            case 8:
                updateBookInformation();
                break;
            case 9:
                listCustomersWhoRentBook();
                break;
            case 10:
                listCustomers();
                break;
            case 11:
                listBooks();
                break;
            case 12:
                RandomBook();
                break;
            case 68:
                b1();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Enter a valid number.\n");
        }
    } while(choice != 0);
    writeCustomersToFile();
    writeBooksToFile();
    writeRentedBooksToFile();
    return 0;
}

void readCustomersFromFile() {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("Error opening customers.txt\n");
        return;
    }
    while (fscanf(file, "%d %s %s %d %f", &customers[customer_count].C_ID, customers[customer_count].name, customers[customer_count].surname, &customers[customer_count].age, &customers[customer_count].wallet) != EOF) {
        customer_count++;
    }
    fclose(file);
}

void readBooksFromFile() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening books.txt\n");
        return;
    }
    while (fscanf(file, "%d %s %s %d %f %d", &books[book_count].B_ID, books[book_count].name, books[book_count].author, &books[book_count].age_limit, &books[book_count].price_per_week, &books[book_count].rented) != EOF) {
        book_count++;
    }
    fclose(file);
}

void readRentedBooksFromFile() {
    FILE *file = fopen("rented.txt", "r");
    if (file == NULL) {
        printf("Error opening rented.txt\n");
        return;
    }
    while (fscanf(file, "%d %d %d %s %d", &rented_books[rented_count].R_ID, &rented_books[rented_count].C_ID, &rented_books[rented_count].B_ID, rented_books[rented_count].rented_date, &rented_books[rented_count].week) != EOF) {
        rented_count++;
    }
    fclose(file);
}

void writeCustomersToFile() {
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("Error opening customers.txt file for writing!\n");
        return;
    }
    for (int i = 0; i < customer_count; i++) {
        fprintf(file, "%d %s %s %d %.2f\n", customers[i].C_ID, customers[i].name, customers[i].surname, customers[i].age, customers[i].wallet);
    }
    fclose(file);
}

void writeBooksToFile() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening books.txt file for writing!\n");
        return;
    }
    for (int i = 0; i < book_count; i++) {
        fprintf(file, "%d %s %s %d %.2f %d\n", books[i].B_ID, books[i].name, books[i].author, books[i].age_limit, books[i].price_per_week, books[i].rented);
    }
    fclose(file);
}

void writeRentedBooksToFile() {
    FILE *file = fopen("rented.txt", "w");
    if (file == NULL) {
        printf("Error opening rented.txt file for writing!\n");
        return;
    }
    for (int i = 0; i < rented_count; i++) {
        fprintf(file, "%d %d %d %s %d\n", rented_books[i].R_ID, rented_books[i].C_ID, rented_books[i].B_ID, rented_books[i].rented_date, rented_books[i].week);
    }
    fclose(file);
}

void createNewCustomer() {
    if (customer_count >= MAX_CUSTOMERS) {
        printf("Customer limit reached.\n");
        return;
    }
    char name[111];
    char surname[112];
    int age;
    float wallet;
    printf("Enter customer name: ");
    scanf("%s", name);
    printf("Enter customer surname: ");
    scanf("%s", surname);
    printf("Enter customer age: ");
    scanf("%d", &age);
    printf("Enter customer wallet amount: ");
    scanf("%f", &wallet);

    for (int i = 0; i < customer_count; i++) {
        if (strcmp(customers[i].name, name) == 0 && strcmp(customers[i].surname, surname) == 0) {
            printf("Customer with the same name and surname already exists.\n");
            return;
        }
    }
    customers[customer_count].C_ID = customer_count + 1;
    strcpy(customers[customer_count].name, name);
    strcpy(customers[customer_count].surname, surname);
    customers[customer_count].age = age;
    customers[customer_count].wallet = wallet;
    customer_count++;
    printf("Customer created successfully.\n");
}

void depositMoneyToCustomer() {
    int customer_id;
    int amount;

    printf("Enter customer ID: ");
    scanf("%d", &customer_id);

    if (customer_id < 1 || customer_id > customer_count) {
        printf("Invalid customer ID.\n");
        return;
    }
    printf("Enter amount to deposit (whole numbers only): ");
    scanf("%d", &amount);

    customers[customer_id - 1].wallet += amount;

    printf("Amount deposited successfully.\n");
}
void addNewBook() {
    if (book_count >= MAX_BOOKS) {
        printf("Book limit reached.\n");
        return;
    }
    char name[113];
    char author[114];
    int age_limit;
    float price_per_week;
    printf("Enter book name: ");
    scanf("%s", name);
    printf("Enter book author: ");
    scanf("%s", author);
    printf("Enter book age limit: ");
    scanf("%d", &age_limit);
    printf("Enter price per week: ");
    scanf("%f", &price_per_week);

    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].name, name) == 0 && strcmp(books[i].author, author) == 0) {
            printf("Book with the same name and author already exists.\n");
            return;
        }
    }

    books[book_count].B_ID = book_count + 1;
    strcpy(books[book_count].name, name);
    strcpy(books[book_count].author, author);
    books[book_count].age_limit = age_limit;
    books[book_count].price_per_week = price_per_week;
    books[book_count].rented = 0;
    book_count++;
    printf("Book added successful\n");
}

void rentABook() {
    int customer_id, book_id, weeks;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);

    if (customer_id < 1 || customer_id > customer_count) {
        printf("Invalid customer ID.\n");
        return;
    }
    printf("Enter book ID to rent: ");
    scanf("%d", &book_id);

    if (book_id < 1 || book_id > book_count) {
        printf("Invalid book ID.\n");
        return;
    }
    printf("Enter number of weeks to rent: ");
    scanf("%d", &weeks);

    if (books[book_id - 1].rented == 1) {
        printf("Book is already rented.\n");
        return;
    }

    if (customers[customer_id - 1].age < books[book_id - 1].age_limit) {
        printf("Customer under of the age limit for this book.\n");
        return;
    }
    float total_price = books[book_id - 1].price_per_week * weeks;

    if (customers[customer_id - 1].wallet < total_price) {
        printf("Insufficient funds.\n");
        return;
    }
    books[book_id - 1].rented = 1;
    customers[customer_id - 1].wallet -= total_price;
    rented_books[rented_count].R_ID = rented_count + 1;
    rented_books[rented_count].C_ID = customer_id;
    rented_books[rented_count].B_ID = book_id;
    printf("Enter rental date (YYYY-MM-DD): ");
    scanf("%s", rented_books[rented_count].rented_date);
    rented_books[rented_count].week = weeks;
    rented_count++;
    printf("Book rented successfully.\n");
}

void deliverABook() {
    int rental_id, remaining_weeks;
    printf("Enter rental ID: ");
    scanf("%d", &rental_id);

    if (rental_id < 1 || rental_id > rented_count) {
        printf("Invalid rental ID.\n");
        return;
    }
    printf("Enter remaining weeks: ");
    scanf("%d", &remaining_weeks);

    float refund_amount = (books[rented_books[rental_id - 1].B_ID - 1].price_per_week * remaining_weeks) * 0.8;

    customers[rented_books[rental_id - 1].C_ID - 1].wallet += refund_amount;
    books[rented_books[rental_id - 1].B_ID - 1].rented = 0;

    for (int i = rental_id - 1; i < rented_count - 1; i++) {
        rented_books[i] = rented_books[i + 1];
    }
    rented_count--;
    printf("Book delivered successfully. Refund amount: %.2f\n", refund_amount);
}

void burnBook() {
    int book_id;
    printf("Enter book ID: ");
    scanf("%d", &book_id);

    if (book_id < 1 || book_id > book_count) {
        printf("Invalid book ID.\n");
        return;
    }
    if (books[book_id - 1].rented == 1) {
        printf("Rented books cannot burn.\n");
        return;
    }
    for (int i = book_id - 1; i < book_count - 1; i++) {
        books[i] = books[i + 1];
    }
    book_count--;
    printf("Book burned successfully.\n");
}

void updateCustomerInformation() {
    int customer_id, choice;
    printf("Enter customer ID: ");
    scanf("%d", &customer_id);

    if (customer_id < 1 || customer_id > customer_count) {
        printf("Invalid customer ID.\n");
        return;
    }
    printf("1. Update name\n");
    printf("2. Update surname\n");
    printf("3. Update age\n");
    printf("4. Update wallet\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf("%s", customers[customer_id - 1].name);
            break;
        case 2:
            printf("Enter new surname: ");
            scanf("%s", customers[customer_id - 1].surname);
            break;
        case 3:
            printf("Enter new age: ");
            scanf("%d", &customers[customer_id - 1].age);
            break;
        case 4:
            printf("Enter new wallet amount: ");
            scanf("%f", &customers[customer_id - 1].wallet);
            break;
        default:
            printf("Invalid choice.\n");
    }
    printf("Updated successfully.\n");
}
void updateBookInformation() {
    int book_id, choice;
    printf("Enter book ID: ");
    scanf("%d", &book_id);

    if (book_id < 1 || book_id > book_count) {
        printf("Invalid book ID.\n");
        return;
    }
    printf("1. Update name\n");
    printf("2. Update author\n");
    printf("3. Update age limit\n");
    printf("4. Update price per week\n");
    printf("5. Update rented status\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf("%s", books[book_id - 1].name);
            break;
        case 2:
            printf("Enter new author: ");
            scanf("%s", books[book_id - 1].author);
            break;
        case 3:
            printf("Enter new age limit: ");
            scanf("%d", &books[book_id - 1].age_limit);
            break;
        case 4:
            printf("Enter new price per week: ");
            scanf("%f", &books[book_id - 1].price_per_week);
            break;
        case 5:
            printf("Enter new rented status (0 for not rented, 1 for rented): ");
            scanf("%d", &books[book_id - 1].rented);
            break;
        default:
            printf("Invalid choice.\n");
    }
    printf("Book information updated successfully.\n");
}

void listCustomersWhoRentBook() {
    printf("Customers who rent a book:\n");
    for (int i = 0; i < rented_count; i++) {
        printf("Rental ID: %d, Customer ID: %d, Book ID: %d, Rented Date: %s, Weeks: %d\n", rented_books[i].R_ID, rented_books[i].C_ID, rented_books[i].B_ID, rented_books[i].rented_date, rented_books[i].week);
    }
}
void listCustomers() {
    printf("List of customers:\n");
    for (int i = 0; i < customer_count; i++) {
        printf("Customer ID: %d, Name: %s %s, Age: %d, Wallet: %.2f\n", customers[i].C_ID, customers[i].name, customers[i].surname, customers[i].age, customers[i].wallet);
    }
}
void b1() {
    printf("");
}
void RandomBook() {
    if (book_count == 0) {
        printf("No books available.\n"); // hep istediğim bir özellikti eklemek istedim.
        return;
    }
    srand(time(NULL));

    int index;
    do {
        index = rand() % book_count;
    } while (books[index].rented);

    printf("Your random recommendation is :\n");
    printf("Book ID: %d, Name: %s, Author: %s, Age Limit: %d, Price per Week: %.2f\n",
           books[index].B_ID, books[index].name, books[index].author, books[index].age_limit, books[index].price_per_week);
}

void listBooks() {
    printf("List of books:\n");
    for (int i = 0; i < book_count; i++) {
        printf("Book ID: %d, Name: %s, Author: %s, Age Limit: %d, Price per Week: %.2f, Rented: %s\n", books[i].B_ID, books[i].name, books[i].author, books[i].age_limit, books[i].price_per_week, books[i].rented ? "Yes" : "No");
    }
}
