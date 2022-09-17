#include <stdio.h>
#include <stdbool.h>
#include "HEADERS/products.h"

int main() {

    time_t t = time(NULL);
    struct tm time = *localtime(&t);

    Product productsList[MAX_STOCK_PRODUCTS];
    Product* pointerOnProductList = productsList;

    Sell sellList[MAX_LOGGED_SELL];
    Sell* pointerOnSellList = sellList;

    bool programStarted = true;
    int userChoice;
    int totalProducts = 0;
    int totalSell = 0;

    do {
        printf("\n------ STOCK MANAGER ----- \n");
        printf("Please, input your choice.\n\n");
        printf("1 - Display your stock\n");
        printf("2 - Add a new product\n");
        printf("3 - Update product quantity\n");
        printf("4 - Remove a product\n");
        printf("5 - Buy a product\n");
        printf("6 - Search Product\n");
        printf("7 - Display sells\n");
        printf("8 - Today summary\n\n");
        printf("Press any other key to exit.\n");
        printf("--> ");
        scanf("%d", &userChoice);


        switch (userChoice) {

            case 1 : {
                displayProducts(pointerOnProductList, &totalProducts);
            } break;

            case 2: {
                addProduct(pointerOnProductList, &totalProducts);
            } break;

            case 3: {
                updateProduct(pointerOnProductList, &totalProducts);
            } break;

            case 4: {
                removeProduct(pointerOnProductList, &totalProducts);
            } break;

            case 5 : {
                buyProducts(pointerOnProductList, &totalProducts, pointerOnSellList, &totalSell, time);
                break;
            }
            case 6 : {
                searchProduct(pointerOnProductList, &totalProducts);
                break;
            }
            case 7 : {
                displaySells(pointerOnSellList, &totalSell);
                break;
            }
            case 8 : {
                displayTodaySells(pointerOnSellList, &totalSell, time);
                break;
            }
            default:{
                printf("Exiting the Stock Manager.\n");
                programStarted = false;
            }

        }
    } while (programStarted == true);
    return 0;
}
