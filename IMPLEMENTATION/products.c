#include "../HEADERS/products.h"

void addProduct(Product *productsList, int *totalProducts) {

    Product myNewProduct;
    int readyToContinue = 0;

    fflush(stdin);
    fflush(stdout);

    printf("\n\n------- PRODUCT ADDER --------\n");
    printf("\nPlease specify your product name --> ");
    scanf("%s", myNewProduct.name);

    printf("\nCode of the product --> ");
    scanf("%d", &myNewProduct.code);


    if (*totalProducts > 0) {
        for (int i = 0; i < *totalProducts; i++) {
            if (myNewProduct.code == productsList[i].code) {
                printf("\nCritical error : another product with this code already exist. Aborting creation.\n\n");
                return;
            }
        }
    }
    do {
        printf("\nPrice HT of the product (please specify decimals) --> ");
        scanf("%f", &myNewProduct.priceHT);
    } while (myNewProduct.priceHT < 0);

    myNewProduct.priceTTC = (float) (1.20 * myNewProduct.priceHT);

    do {
        printf("\nQuantity to add --> ");
        scanf("%d", &myNewProduct.stock);
    } while (myNewProduct.stock < 1);

    productsList[*totalProducts] = myNewProduct;
    *totalProducts = *totalProducts + 1;

    printf("\nProduct added with success.\n");

    do {
        printf("\nPress 1 to go back to the main menu -->");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);
}

void updateProduct(Product *productsList, int *totalProducts) {

    int readyToContinue = 0;
    int codeToModify = 0;
    int indexToModify = 0;

    printf("\n\n------- STOCK UPDATER --------\n");

    if (*totalProducts == 0) {
        printf("\nError : you have currently 0 product.\n\n");
        do {
            printf("\nPress 1 to go back to the main menu -->");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
        return;
    } else {
        do {
            printf("\nEnter the product code--> ");
            scanf("%d", &codeToModify);

            for (int i = 0; i < *totalProducts; i++) {
                if (codeToModify == productsList[i].code) {
                    indexToModify = i;
                    readyToContinue = 2;
                }
            }
            if (readyToContinue == 2) {
                printf("You selected %s, with the code %d.\n", productsList[indexToModify].name,
                       productsList[indexToModify].code);
            } else {
                printf("Unable to find product with this code, please retry.\n");
            }
        } while (readyToContinue != 2);

        printf("\nEnter the new quantity --> ");
        scanf("%d", &productsList[indexToModify].stock);

        printf("\nProduct updated with success. New quantity : %d\n", productsList[indexToModify].stock);

        do {
            printf("\nPress 1 to go back to the main menu -->");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    }
}

void removeProduct(Product *productsList, int *totalProducts) {

    int inputChoice;
    bool successRemove = false;
    int readyToContinue = 0;

    printf("------- PRODUCTS REMOVER ------\n");
    printf("What is the code of the product to remove ?\n");
    printf("Press 0 to cancel.\n");
    printf("-->");

    scanf("%d", &inputChoice);
    if (inputChoice == 0) {
        return;
    } else if (*totalProducts == 0) {
        printf("Error : you currently have 0 product in stock.\n");
        return;
    } else {
        successRemove = removeFromCode(productsList, totalProducts, inputChoice);
        if (successRemove) {
            printf("Successfuly removing product.\n");
        } else {
            printf("Error : this code does not exist.\n");
        }
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    }
}

bool removeFromCode(Product *productsList, int *totalProducts, int codeToRemove) {

    int foundCode = false;
    int indexToRemove;

    // First we find the good index
    for (int i = 0; i < *totalProducts; i++) {
        if (codeToRemove == productsList[i].code) {
            indexToRemove = i;
            foundCode = true;
        }
    }
    if (!foundCode)
        return false;

    // Then, we check if it's not the last element of the array
    if (indexToRemove == MAX_STOCK_PRODUCTS) { //
        *totalProducts = *totalProducts - 1;
    }
        // Finally we copy all the value above the item to remove
    else {
        for (int j = indexToRemove; j < *totalProducts; j++) {
            productsList[j] = productsList[j + 1];
        }
        // Since the last item of the list is present twice, we downgrade the total of the list
        *totalProducts = *totalProducts - 1;
    }
    return true;
}


void viewProductList(Product *productsList, int *totalProducts) {

    int readyToContinue = 0;

    printf("\n\n---------- YOUR STOCK -------------\n");

    if (*totalProducts == 0) {
        printf("You currently have no products in your stock.\n\n");
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    } else {
        for (int i = 0; i < *totalProducts; i++) {
            printf("%d x ", productsList[i].stock);
            printf("%s | ", productsList[i].name);
            printf("Code : %d | ", productsList[i].code);
            printf("Price TTC = %f | ", productsList[i].priceTTC);
            printf("Price HT = %f | \n\n", productsList[i].priceHT);
        }
    }

    do {
        printf("Press 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);

    return;
}


void buyProducts(Product *productsList, int *totalProducts, Sell* sellList, int* totalSells, struct tm time) {

    Sell newSell;
    int codeToBuy;
    int indexToBuy;
    int quantityToBuy;
    bool foundCode = false;
    int readyToContinue = 0;

    printf("\n------- BUY PRODUCT -------\n");
    printf("Please insert the code of the product that you want to buy --> ");
    scanf("%d", &codeToBuy);

    for (int i = 0; i < *totalProducts; i++) {
        if (codeToBuy == productsList[i].code) {
            indexToBuy = i;
            foundCode = true;
        }
    }
    if (!foundCode) {
        printf("\nError : no product with this code in stock.\n");
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);

        return;

    } else {
        printf("\nThe current price of the article is %f TTC.\n", productsList[indexToBuy].priceTTC);
        printf("There is currently %d %s in stock.\n\n", productsList[indexToBuy].stock, productsList[indexToBuy].name);
        printf("How many do you want to buy ? --> ");
        scanf("%d", &quantityToBuy);

        if (quantityToBuy <= 0) {
            printf("\nNo product has been bought. Returning to main menu...\n");
            return;

        } else if (quantityToBuy > productsList[indexToBuy].stock) {
            printf("\nNot enough stock for this demand...\n");
            do {
                printf("Press 1 to go back to the main menu.\n");
                scanf("%d", &readyToContinue);
            } while (readyToContinue != 1);

            return;
        }
        else {
            // Check if user want to buy all the item of this type
            if (quantityToBuy == productsList[indexToBuy].stock) {

                // In this case we remvoe totally the item
                removeFromCode(productsList, totalProducts, codeToBuy);

                // Register new sell
                strcpy(newSell.name, productsList[indexToBuy].name);
                newSell.priceTTC = quantityToBuy * productsList[indexToBuy].priceTTC;
                newSell.priceHT = quantityToBuy * productsList[indexToBuy].priceHT;
                newSell.quantity = quantityToBuy ;
                newSell.code = productsList[indexToBuy].code;

            } else {
                // If he want to buy only some item of this type, we only remove the quantity
                productsList[indexToBuy].stock = productsList[indexToBuy].stock - quantityToBuy;

                // Register new sell
                strcpy(newSell.name, productsList[indexToBuy].name);
                newSell.priceTTC = quantityToBuy * productsList[indexToBuy].priceTTC;
                newSell.priceHT = quantityToBuy * productsList[indexToBuy].priceHT;
                newSell.quantity = quantityToBuy ;
                newSell.code = productsList[indexToBuy].code;
            }

            // Registering the date of the purchase
            newSell.year = 1900 + time.tm_year;
            newSell.month = time.tm_mon + 1;
            newSell.day = time.tm_mday;
            newSell.hour = time.tm_hour;
            newSell.min = time.tm_min;
            newSell.sec = time.tm_sec;

            // Add the new Sale
            sellList[*totalSells] = newSell;
            *totalSells = *totalSells +1;

            printf("\nYou successfully bought %d %s ! \n", quantityToBuy, productsList[indexToBuy].name);

            do {
                printf("Press 1 to go back to the main menu.\n");
                scanf("%d", &readyToContinue);
            } while (readyToContinue != 1);
        }
    }
}

void displayProducts(Product *productsList, int *totalProducts) {

    int inputChoice = 0;

    printf("\n----- DISPLAY MENU ------\n");
    printf("1 - Display normally your product\n");
    printf("2 - Display stock by price\n");
    printf("3 - Display stock by name\n");
    printf("4 - Display article low in stock\n\n");
    printf("-->");
    scanf("%d", &inputChoice);


    switch (inputChoice) {

        case 1 : {
            viewProductList(productsList, totalProducts);
            break;
        }
        case 2 : {
            if (*totalProducts != 0) {
                viewProductList(swapByPrice(productsList, totalProducts), totalProducts);
            }
            else {
                printf("Error : you currently not have any products.\n\n");
            }
            break;
        }
        case 3 : {
            if (*totalProducts != 0) {
                viewProductList(swapByName(productsList, totalProducts), totalProducts);
            }
            else {
                printf("Error : you currently not have any products.\n\n");
            }
            break;
        }
        case 4: {
            if (*totalProducts != 0) {
                displayLowStock(productsList, totalProducts);
            }
            else {
                printf("Error : you currently not have any products.\n\n");
            }
            break;
        }
        default: {
            printf("Error.\n");
            return;
        }
    }
}

Product* swapByPrice(Product *productsList, int *totalProducts) {

    Product copyList[MAX_STOCK_PRODUCTS];
    Product* pointerOnCopy = copyList;

    // Copying the original array
    for (int i = 0; i < MAX_STOCK_PRODUCTS; i++) {
        copyList[i] = productsList[i];
    }

    // Swap by price
    for (int i = 0; i < *totalProducts; i++) {
        for (int j = i + 1; j < *totalProducts; j++) {

            // Bubble algorithm : if a > b, a is moving to one positionright
            if (copyList[i].priceTTC > copyList[j].priceTTC) {
                Product temp = copyList[i];
                copyList[i] = copyList[j];
                copyList[j] = temp;
            }
        }
    }
    return pointerOnCopy;
}

Product* swapByName(Product *productsList, int *totalProducts) {

    Product copyList[MAX_STOCK_PRODUCTS];
    Product* pointerOnCopy = copyList;

    // Copying the original array
    for (int i = 0; i < MAX_STOCK_PRODUCTS; i++) {
        copyList[i] = productsList[i];
    }

    // Swap by name
    for (int i = 0; i < *totalProducts; i++) {

        // Bubble algorithm : if a > b, a is moving to one positionright
        for (int j = i + 1; j < *totalProducts; j++) {
            if (strcmp(copyList[i].name, copyList[j].name) > 0) {
                Product temp = copyList[i];
                copyList[i] = copyList[j];
                copyList[j] = temp;
            }
        }
    }
    return pointerOnCopy;
}



void searchProduct(Product* productsList, int* totalProducts) {

    int inputChoice = 0;

    printf("\n----- DISPLAY MENU ------\n");
    printf("1 - Search a product by quantity\n");
    printf("2 - Search a product by code\n");
    printf("Press 0 to cancel.\n");

    printf("-->");
    scanf("%d", &inputChoice);

    if(inputChoice == 0) return;

    switch (inputChoice) {

        case 1 : {
            searchByQuantity(productsList, totalProducts);
            break;
        }
        case 2 : {
            searchByCode(swapByPrice(productsList, totalProducts), totalProducts);
            break;
        }
        default: {
            printf("Error in specified argument.\n");
            return;
        }
    }
}

void searchByQuantity(Product* productsList, int* totalProducts) {

    int quantityToLookup = 0;

    int readyToContinue = 0;
    bool itemFound = false;

    printf("------ SEARCH BY QUANTITY ------\n");
    printf("Specify the quantity of item that you want to lookup.\n");
    printf("-->");
    scanf("%d", &quantityToLookup);

    if (*totalProducts == 0) {
        printf("Error : you currently not have any products.\n\n");
    }
    else {
        printf("Result : \n");
        for (int i = 0; i < *totalProducts; i++) {
            if (productsList[i].stock == quantityToLookup) {
                itemFound = true;
                printf("%d x ", productsList[i].stock);
                printf("%s | ", productsList[i].name);
                printf("Code : %d | ", productsList[i].code);
                printf("Price TTC = %f | ", productsList[i].priceTTC);
                printf("Price HT = %f | \n\n", productsList[i].priceHT);
            }
        }
        if (!itemFound) {
            printf("Error : no item with this quantity has been found.\n\n");
        }
    }
    do {
        printf("Press 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);
}

void searchByCode(Product* productsList, int* totalProducts) {

    int codeToLookup = 0;

    int readyToContinue = 0;
    bool itemFound = false;

    printf("------ SEARCH BY QUANTITY ------\n");
    printf("Specify the code of item that you want to lookup.\n");
    printf("-->");
    scanf("%d", &codeToLookup);

    if (*totalProducts == 0) {
        printf("Error : you currently not have any products.\n\n");
    }
    else {
        for (int i = 0; i < *totalProducts; i++) {

            // We look into the array, if we find the code, we display the item
            if (productsList[i].stock == codeToLookup) {
                itemFound = true; // To know what message to display
                printf("%d x ", productsList[i].stock);
                printf("%s | ", productsList[i].name);
                printf("Code : %d | ", productsList[i].code);
                printf("Price TTC = %f | ", productsList[i].priceTTC);
                printf("Price HT = %f | \n\n", productsList[i].priceHT);
            }
        }
        if (!itemFound) { //  Because item does not exist
            printf("Error : no item with this code has been found.\n\n");
        }
    }
    do {
        printf("Press 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);
}

void displaySells(Sell* sellList, int* totalSells) {

    int readyToContinue = 0;
    float totalProfit = 0;
    int totalQuantity = 0;
    float averagePrice = 0;

    printf("\n------- SELL HISTORY ---------\n");

    if (*totalSells == 0) {
        printf("You currently have 0 sell in your history.\n\n");
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    }
    else {
        for (int i = 0; i < *totalSells; i++) {
            totalProfit = totalProfit + sellList[i].priceTTC; // Addition of all the sales
            totalQuantity = totalQuantity + sellList[i].quantity; // Same with quantity
        }

        averagePrice = totalProfit / (float) *totalSells; // All the price divided by quantity

        printf("Total profit with tax : %f\n", totalProfit);
        printf("Total sells : %d\n", *totalSells);
        printf("Total quantity : %d\n", totalQuantity);
        printf("Average price of selling: %f\n\n", averagePrice);
        printf("--- Details :\n");

        for (int i = 0; i < *totalSells; i++) {
            printf("[%d-%02d-%02d %02d:%02d:%02d] - ", sellList[i].year, sellList[i].month, sellList[i].day, sellList[i].hour, sellList[i].min, sellList[i].sec);
            printf("%d x ", sellList[i].quantity);
            printf("%s | ", sellList[i].name);
            printf("Code : %d | ", sellList[i].code);
            printf("Profit TTC = %f | ", sellList[i].priceTTC);
            printf("Profit HT = %f | \n\n", sellList[i].priceHT);
        }
    }

    do {
        printf("Press 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);

    return;
}

void displayLowStock(Product* productsList, int* totalProducts) {

    int readyToContinue = 0;
    int counter =0;

    printf("\n\n---------- LOW STOCK REVIEWER  -------------\n");

    if (*totalProducts == 0) {
        printf("You currently have no products in your stock.\n\n");
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    } else {
        for (int i = 0; i < *totalProducts; i++) {
            if (productsList[i].stock <= 3 ) {
                printf("Remaining : %d x ", productsList[i].stock);
                printf("%s | ", productsList[i].name);
                printf("Code : %d | ", productsList[i].code);
                printf("Price TTC = %f | ", productsList[i].priceTTC);
                printf("Price HT = %f | ", productsList[i].priceHT);
                counter++;
            }
        }
    }
    if (counter == 0) {
        printf("There is now item below 3 unity in your stock !");
    }
    do {
        printf("\n\nPress 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);
    return;
}

void displayTodaySells(Sell* sellList, int* totalSells, struct tm time) {

    int readyToContinue = 0;
    float todayProfit = 0;
    int todayQuantity = 0;
    float averagePrice = 0;
    int todaySells = 0;

    printf("\n------- TODAY SELLS ---------\n");

    if (*totalSells == 0) {
        printf("You currently have made 0 today.\n\n");
        do {
            printf("Press 1 to go back to the main menu.\n");
            scanf("%d", &readyToContinue);
        } while (readyToContinue != 1);
    }
    else {
        for (int i = 0; i < *totalSells; i++) {
            if (sellList[i].day == time.tm_mday) {
                todayProfit = todayProfit + sellList[i].priceTTC; // Addition of all the sales
                todayQuantity = todayQuantity + sellList[i].quantity; // Same with quantity
                todaySells++;
            }
        }

        averagePrice = todayProfit / (float) todaySells; // All the price divided by quantity

        printf("Today profit with tax : %f\n", todayProfit);
        printf("Today sells : %d\n", todaySells);
        printf("Today quantity : %d\n", todayQuantity);
        printf("Average price of selling: %f\n\n", averagePrice);
        printf("--- Details :\n");

        for (int i = 0; i < *totalSells; i++) {
            printf("[%d-%02d-%02d %02d:%02d:%02d] - ", sellList[i].year, sellList[i].month, sellList[i].day, sellList[i].hour, sellList[i].min, sellList[i].sec);
            printf("%d x ", sellList[i].quantity);
            printf("%s | ", sellList[i].name);
            printf("Code : %d | ", sellList[i].code);
            printf("Profit TTC = %f | ", sellList[i].priceTTC);
            printf("Profit HT = %f | \n\n", sellList[i].priceHT);
        }
    }

    do {
        printf("Press 1 to go back to the main menu.\n");
        scanf("%d", &readyToContinue);
    } while (readyToContinue != 1);

    return;
}