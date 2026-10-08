#ifndef ASSETS_H
#define ASSETS_H

#include "common.h"

#define MAX_ASSETS 50

void addAsset(void);
void displayAssets(void);
void searchAsset(void);
void assetMenu(void);

int getAssetCount(void);
double calculateTotalAssetValue(void);

#endif
