#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define file_products "my_products.txt"
#define file_inventory "my_inventory.txt"
#define file_money "my_money.txt"

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

void check_files();
void scan_products(Product products[], int *count);
void update_products(Product products[], int count);
void displayProducts(Product products[], int count);
void buyProduct(Product products[], int count, int *money);
void viewInventory(int money);
int loadMoney();
void saveMoney(int money);
void playMiniGame();
void aboutOwner();
int main() {
    Product products[10];
    int count = 0;
    int choice;
    int money;

    check_files();

    scan_products(products, &count);
    money = loadMoney();

    do {
        printf("\n===== PBCT VENDING MACHINE =====\n");
        printf("=== Barya mo. Saya mo. Adelante ===\n");
        printf("\nStudent Money: PHP %d\n\n", money);
        printf("1. 🛒Buy Products\n");
        printf("2. View Product\n");
        printf("3. View Inventory\n");
        printf("4. Play a mini game\n");
        printf("5. About the owner: \n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                buyProduct(products, count, &money);
                update_products(products, count);
                saveMoney(money);
                break;

            case 2:
            while(1) {
                printf("\nYou are now viewing the products.\n");
                displayProducts(products, count);
                printf("==============================\n");
                printf("Tap 1 to go back to main menu:");
                 int choice;
                scanf("%d", &choice);
                if(choice == 1) {
                 printf("Returning to Main Menu...\n");
                  break;
                 } else {
                  printf("Invalid choice. Returning to Main Menu...\n");
                 }
                }
                break;

            case 3:
                viewInventory(money);
                break;
            case 4:
                playMiniGame();
                break;
             case 5:
                aboutOwner();
                break;
            case 6:
                printf("Thank you for using the vending machine!Sa uulitin na naman!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 6);

    return 0;
}

void check_files() {
    FILE *fp;

    fp = fopen(file_products, "r");

    if (fp == NULL) {
        fp = fopen(file_products, "w");

        fprintf(fp, "Coke 35 10\n");
        fprintf(fp, "Water 20 15\n");
        fprintf(fp, "Chips 25 12\n");
        fprintf(fp, "Chocolate 30 8\n");
        fprintf(fp, "Sandwich 50 15\n");

        fclose(fp);
    } else {
        fclose(fp);
    }

    fp = fopen(file_inventory, "r");

    if (fp == NULL) {
        fp = fopen(file_inventory, "w");
        fclose(fp);
    } else {
        fclose(fp);
    }

    fp = fopen(file_money, "r");

    if (fp == NULL) {
        fp = fopen(file_money, "w");
        fprintf(fp, "500");
        fclose(fp);
    } else {
        fclose(fp);
    }
}

void scan_products(Product products[], int *count) {
    FILE *fp;
    fp = fopen(file_products, "r");

    *count = 0;

    while(fscanf(fp, "%s %d %d",
                 products[*count].name,
                 &products[*count].price,
                 &products[*count].stock) != EOF) {

        (*count)++;
    }

    fclose(fp);
}

void update_products(Product products[], int count) {
    FILE *fp;
    fp = fopen(file_products, "w");

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
    while(1) {
    int choice;
    FILE *fp;
    printf("\n==============================\n");
    printf("You are now buying a products.\n");
    printf("        ||            ||\n");
    displayProducts(products, count);

    printf("\nEnter product number to buy: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > count) {
        printf("Invalid product choice.\n");
        return;
    }

    choice--;
    int quantity;
    printf("Enter how many %s you want to buy: ", products[choice].name);
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

    fp = fopen(file_inventory, "a");
    getchar();
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
    printf("Your money now become: PHP %d\n", *money);
     int buyMore, timailhan=0;
    while(timailhan!=1){
    printf("\nDo you want to buy another product? (1 for Yes, 0 for No): ");
    scanf("%d", &buyMore);
    
    if(buyMore == 0) {
        timailhan=1;
        break;
    }else if(buyMore == 1) {
        break;
    }
}
if(timailhan==1) {
    printf("Returning to Main Menu...\n");
    break;
}
    }
}

void viewInventory(int money) {
    while(1) {
    printf("\n==================================\n");
    printf("  You are now viewing your inventory.\n");
    FILE *fp;
    char line[100];

    fp = fopen(file_inventory, "r");

    printf("\n===== STUDENT INVENTORY =====\n");

    while(fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);

    printf("\nRemaining Money: PHP %d\n", money);
    
    int choice;
    
   
    printf("\n==============================\n");
    printf("Tap 1 to go back to main menu:");
    scanf("%d", &choice);
    if(choice == 1) {
        break;
    }
    
    }

}

int loadMoney() {
    FILE *fp;
    int money;

    fp = fopen(file_money, "r");

    fscanf(fp, "%d", &money);

    fclose(fp);

    return money;
}

void saveMoney(int money) {
    FILE *fp;

    fp = fopen(file_money, "w");

    fprintf(fp, "%d", money);

    fclose(fp);
}
void playMiniGame() {
      int target;
    int choice;
    int attempts = 2;

    srand(time(0));

    target = rand() % 5 + 1;

    printf("=================================\n");
    printf("      Duwa Gamay Daog Dako      \n");
    printf("          Mystery Box      \n");
    printf("=================================\n");
    printf("Choose the right one!\n");
    printf("You have 2 attempts.\n\n");

    while (attempts > 0) {

        printf("Boxes:\n");
        printf("[1] [2] [3] [4] [5]\n");
        printf("Choose a box number: ");
        scanf("%d", &choice);

        if (choice == target) {
            printf("\n🎉 CONGRATULATIONS! 🎉\n");
            printf("You won a reward!\n");
            printf("-> Free Candy / Discount Coupon\n");
            break;
        } else {
            attempts--;
            if (attempts > 0) {
                printf("\nWrong box!\n");
                printf("You have %d attempts left.\n\n", attempts);
            } else {
                printf("\nGame Over!\n");
                printf("Better luck next time bro!\n");
                printf("Correct box was: %d\n", target);
            }
        }
    }

    printf("\nThank you for playing!\n");

}
void aboutOwner() {
    while(1){
        int timailhan=0;
    int choice;
    printf("\n===== ABOUT THE PBCT OWNER =====\n");
    printf("Name: Rodel E. Tan, Patricia Obejas, Rhealyn Cabarloc, and NIzzah Bejer\n");
    printf("Student ID: 2025025445, 2025025446, 2025025447, 2025025448\n");
    printf("Course: Associate in Computer Technology\n");
    printf("Currently studying at San Jose Recoleto\n");
    printf("Our Goal: To provide interactive and engaging vending machine experiences for our customers\n");
    printf("Barato na may tsansa pang manalo ka!\n");

    printf("=================================\n");
    printf("1. View Contact Info\n");
    printf("2. Back to Main Menu\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    if (choice == 1) {

        printf("\n=================================\n");
        printf("         CONTACT DETAILS         \n");
        printf("=================================\n");

        printf("Email    : rodeltangwapo28@gmail.com\n");
        printf("Phone    : 0962-825-6419\n");
        while(timailhan!=1){ 
            int go;
        printf("\n\n 1 to go back to the previous menu: ");
        printf("2 to go back to the main menu: ");
        scanf("%d", &go);
        if (go == 1) {
            printf("\nReturning to About the Owner...\n");
            break;

        }else if(go == 2) {
            printf("\nReturning to Main Menu...\n");
            timailhan=1;
            break;
        } else {
            printf("\nInvalid choice.\n");
        }
    }

    } else if (choice == 2) {
        printf("\nReturning to Main Menu...\n");
        break;
    } else {
        printf("\nInvalid choice.\n");
    }
    if(timailhan==1) {
        printf("Returning to Main Menu...\n");
        break;
    }
}
}