#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

int assetIds[MAX_ASSETS];
char assetNames[MAX_ASSETS][NAME_LEN];
char assetTypes[MAX_ASSETS][NAME_LEN];
double assetValues[MAX_ASSETS];
char assetDepartments[MAX_ASSETS][DEPT_LEN];
char assetConditions[MAX_ASSETS][COND_LEN];
int assetCount = 0;

void displayAssetDetails(int index);

void addAsset(void)
{
    int id;

    if (assetCount >= MAX_ASSETS)
    {
        printf("\nError: Asset register is full (maximum %d).\n", MAX_ASSETS);
        return;
    }

    id = getValidatedInt("Enter Asset ID: ", 1, 999999);

    for (int i = 0; i < assetCount; i++)
    {
        if (assetIds[i] == id)
        {
            printf("Error: Asset ID %d already exists.\n", id);
            return;
        }
    }

    assetIds[assetCount] = id;
    getValidatedString("Enter Asset Name: ", assetNames[assetCount], NAME_LEN);
    getValidatedString("Enter Asset Type (e.g. Vehicle, Computer, Building): ",
                       assetTypes[assetCount], NAME_LEN);
    assetValues[assetCount] = getValidatedDouble("Enter Purchase Value (N$): ", 0.0);
    getValidatedString("Enter Department: ", assetDepartments[assetCount], DEPT_LEN);
    getValidatedString("Enter Condition (e.g. New, Good, Fair, Poor): ",
                       assetConditions[assetCount], COND_LEN);

    printf("\nAsset '%s' added successfully.\n", assetNames[assetCount]);

    assetCount++;
}

void displayAssets(void)
{
    if (assetCount == 0)
    {
        printf("\nNo assets recorded yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-15s %15s %-15s %-12s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Condition");
    printLine(88);

    for (int i = 0; i < assetCount; i++)
    {
        printf("%-6d %-20s %-15s %15.2f %-15s %-12s\n",
               assetIds[i],
               assetNames[i],
               assetTypes[i],
               assetValues[i],
               assetDepartments[i],
               assetConditions[i]);
    }
}

void displayAssetDetails(int index)
{
    printf("\n--- Asset Found ---\n");
    printf("ID:             %d\n", assetIds[index]);
    printf("Name:           %s\n", assetNames[index]);
    printf("Type:           %s\n", assetTypes[index]);
    printf("Purchase Value: N$%.2f\n", assetValues[index]);
    printf("Department:     %s\n", assetDepartments[index]);
    printf("Condition:      %s\n", assetConditions[index]);
}

void searchAsset(void)
{
    int searchChoice;
    int found = 0;
    int id;
    char name[NAME_LEN];

    if (assetCount == 0)
    {
        printf("\nNo assets recorded yet.\n");
        return;
    }

    searchChoice = getValidatedInt("Search by (1) Asset ID or (2) Name: ", 1, 2);

    if (searchChoice == 1)
    {
        id = getValidatedInt("Enter Asset ID to search: ", 1, 999999);
        for (int i = 0; i < assetCount; i++)
        {
            if (assetIds[i] == id)
            {
                found = 1;
                displayAssetDetails(i);
                break;
            }
        }
    }
    else
    {
        getValidatedString("Enter Asset Name to search: ", name, NAME_LEN);
        for (int i = 0; i < assetCount; i++)
        {
            if (strcmp(assetNames[i], name) == 0)
            {
                found = 1;
                displayAssetDetails(i);
                break;
            }
        }
    }

    if (!found)
    {
        printf("\nNo asset matched your search.\n");
    }
}

int getAssetCount(void)
{
    return assetCount;
}

double calculateTotalAssetValue(void)
{
    double total = 0.0;

    for (int i = 0; i < assetCount; i++)
    {
        total += assetValues[i];
    }
    return total;
}

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n---- ASSET MANAGEMENT ----\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        choice = getValidatedInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
