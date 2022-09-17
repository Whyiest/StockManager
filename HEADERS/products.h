#ifndef STOCKMANAGER_PRODUCTS_H
#define STOCKMANAGER_PRODUCTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "string.h"
#include <time.h>


#define  MAX_NAME_SIZE 30
#define MAX_STOCK_PRODUCTS 200
#define MAX_LOGGED_SELL 2000



typedef struct {
    char name [MAX_NAME_SIZE];
    int code;
    int stock;
    float priceHT;
    float priceTTC;
} Product;

typedef struct {
    char name [MAX_NAME_SIZE];
    int code;
    int quantity;
    float priceHT;
    float priceTTC;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} Sell;

// ACTION
void addProduct (Product* productsList, int* totalProducts);
void updateProduct (Product* productsList, int* totalProducts);
void removeProduct(Product* productsList, int* totalProducts);
void buyProducts (Product* productsList, int* totalProducts, Sell* sellList, int* totalSells, struct tm time);
bool removeFromCode (Product* productsList, int* totalProducts, int codeToRemove); // return true if remove with sucess

// TOOLS
Product* swapByPrice (Product* productsList, int* totalProducts);
Product* swapByName (Product* productsList, int* totalProducts);
int indexFromCode (Product* productsList, int* totalProducts, int codeToRemove);

// DISPLAY
void displayProducts(Product* productsList, int* totalProducts);
void viewProductList(Product* productsList, int* totalProducts);
void displaySells(Sell* sellList, int* totalSells);
void displayTodaySells(Sell* sellList, int* totalSells, struct tm time);
void displayLowStock(Product* productsList, int* totalProducts);

// SEARCH
void searchProduct(Product* productsList, int* totalProducts);
void searchByCode(Product* productsList, int* totalProducts);
void searchByQuantity(Product* productsList, int* totalProducts);


#endif //STOCKMANAGER_PRODUCTS_H
