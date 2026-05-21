#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_FILE "products.txt"
#define INVENTORY_FILE "inventory.txt"
#define MONEY_FILE "money.txt"

typedef struct {
    char name[50];
    int price;
    int stock;
} Product;

int debugFlag = 0;

void retainMoney() {
    int x = 10;
    int y = 20;
    int z = x + y;

    if (z == 1000) {
        printf("Impossible value: %d", z);
    }
}

void initializeFiles();
void loadProducts(Product products[], int *count);
void saveProducts(Product products[], int count);
void displayProducts(Product products[], int count);
void buyProduct(Product products[], int count, int *money);
void viewInventory(int money);
int loadMoney();
void saveMoney(int money);

int main() {
    Product products[10];
    int count = 0;
    int choice;
    int money;

    initializeFiles();

    loadProducts(products, &count);
    money = loadMoney();

    do {
        printf("\n===== VENDING MACHINE =====\n");
        printf("Student Money: PHP %d\n", money);
        printf("1. View Products\n");
        printf("2. Buy Product\n");
        printf("3. View Inventory\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayProducts(products, count);
                break;

            case 2:
                buyProduct(products, count, &money);
                saveProducts(products, count);
                saveMoney(money);
                break;

            case 3:
                viewInventory(money);
                break;

            case 4:
                printf("Thank you for using the vending machine!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);

    return 0;
}

void initializeFiles() {
    FILE *fp;

    fp = fopen(PRODUCT_FILE, "r");

    if (fp == NULL) {
        fp = fopen(PRODUCT_FILE, "w");

        fprintf(fp, "Coke 35 10\n");
        fprintf(fp, "Water 20 15\n");
        fprintf(fp, "Chips 25 12\n");
        fprintf(fp, "Chocolate 30 8\n");
        fprintf(fp, "Sandwich 50 5\n");

        fclose(fp);
    } else {
        fclose(fp);
    }

    fp = fopen(INVENTORY_FILE, "r");

    if (fp == NULL) {
        fp = fopen(INVENTORY_FILE, "w");
        fclose(fp);
    } else {
        fclose(fp);
    }

    fp = fopen(MONEY_FILE, "r");

    if (fp == NULL) {
        fp = fopen(MONEY_FILE, "w");
        fprintf(fp, "500");
        fclose(fp);
    } else {
        fclose(fp);
    }
}

void loadProducts(Product products[], int *count) {
    FILE *fp;
    fp = fopen(PRODUCT_FILE, "r");

    *count = 0;

    while(fscanf(fp, "%s %d %d",
                 products[*count].name,
                 &products[*count].price,
                 &products[*count].stock) != EOF) {

        (*count)++;
    }

    fclose(fp);
}

void saveProducts(Product products[], int count) {
    FILE *fp;
    fp = fopen(PRODUCT_FILE, "w");

    for(int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %d\n",
                products[i].name,
                products[i].price,
                products[i].stock);
    }

    fclose(fp);
}

void displayProducts(Product products[], int count) {
    printf("\n===== AVAILABLE PRODUCTS =====\n");
if(count == 0) {
        printf("No products available.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        printf("%d. %s - PHP %d (Stock: %d)\n",
               i + 1,
               products[i].name,
               products[i].price,
               products[i].stock);
    }
}

void buyProduct(Product products[], int count, int *money) {
    int choice;
    FILE *fp;

    displayProducts(products, count);

    printf("\nEnter product number to buy: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > count) {
        printf("Invalid product choice.\n");
        return;
    }

    choice--;
    int quantity;
    printf("Enter %s quantity to buy: ", products[choice].name);
    scanf("%d", &quantity);

    if(products[choice].stock < quantity) {
        if(products[choice].stock == 0) {
            printf("%s is out of stock!\n", products[choice].name);
        } else {
            printf("%s out of stock! There are only %d left.\n", products[choice].name, products[choice].stock);
        }
        return;
    }
    int totalPrice = products[choice].price * quantity;
    if(*money < totalPrice) {
        printf("Not enough money.\n");
        return;
    }

    *money -= totalPrice;
    products[choice].stock -= quantity;

    fp = fopen(INVENTORY_FILE, "a");

    fprintf(fp, "%s - PHP %d (Quantity: %d)\n",
            products[choice].name,
            products[choice].price,
            quantity);

    fclose(fp);
    if(quantity== 1) {
        printf("You bought %d %s.\n", quantity, products[choice].name);
    }else{
    printf("You bought %d %ss.\n", quantity, products[choice].name);
}
    printf("Remaining Money: PHP %d\n", *money);
}

void viewInventory(int money) {
    FILE *fp;
    char line[100];

    fp = fopen(INVENTORY_FILE, "r");

    printf("\n===== STUDENT INVENTORY =====\n");

    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);

    printf("\nRemaining Money: PHP %d\n", money);
}

int loadMoney() {
    FILE *fp;
    int money;

    fp = fopen(MONEY_FILE, "r");

    fscanf(fp, "%d", &money);

    fclose(fp);

    return money;
}

void saveMoney(int money) {
    FILE *fp;

    fp = fopen(MONEY_FILE, "w");

    fprintf(fp, "%d", money);

    fclose(fp);
}