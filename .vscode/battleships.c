#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 16

/* Převedené pomocné struktury pro vrácení více hodnot */
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int shotSuccess;
    int coordX;
    int coordY;
} ComputerShotResult;

/* Deklarace funkcí */
void PrintBattleGround(int size, char arrayToPrint[MAX_SIZE][MAX_SIZE][8]);
void GenerateBattleGround(int size, char battleGround[MAX_SIZE][MAX_SIZE][8]);
int NumberTest(void);
int NumberInBattleGroundTest(int battleGroundSize);
void OrientationTest(char* result);
void ShotTypeTest(char* result);

Point ShipPlacementTest(int battleGroundSize, const char* shipType, int shipSize, const char* orientation, char battleGround[MAX_SIZE][MAX_SIZE][8]);
void ShipPlacement(int battleGroundSize, char playerBattleGround[MAX_SIZE][MAX_SIZE][8], int shipSize, const char* shipType);

Point ComputerShipPlacementTest(int battleGroundSize, const char* shipType, int shipSize, const char* orientation, char battleGround[MAX_SIZE][MAX_SIZE][8]);
void ComputerShipPlacement(int battleGroundSize, char battleGround[MAX_SIZE][MAX_SIZE][8], int shipSize, const char* shipType);

int ShipDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], int plusX, int plusY, int j, int coordinatesX, int coordinatesY, int test, int battleGroundSize);
void ShipTypeDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], char shootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int plusX, int plusY, int battleGroundSize);
int ComputerShipTypeDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], char shootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int i, int l, int battleGroundSize);

void PlayerShooting(char computerBattleGround[MAX_SIZE][MAX_SIZE][8], char playerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int* lineBombardation);
ComputerShotResult ComputerLineBombardation(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int coordinatesX, int coordinatesY, int lineBombardation, int shotSuccess, int plusX, int plusY);
ComputerShotResult NextComputerShot(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int shotSuccess, int plusX, int plusY, int battleGroundSize);
ComputerShotResult ComputerShooting(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int lineBombardation, int shotSuccess, int coordinatesX, int coordinatesY);

/* Implementace funkcí */

void PrintBattleGround(int size, char arrayToPrint[MAX_SIZE][MAX_SIZE][8]) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            printf("%s ", arrayToPrint[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void GenerateBattleGround(int size, char battleGround[MAX_SIZE][MAX_SIZE][8]) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            strcpy(battleGround[i][j], "-");
        }
    }
}

int NumberTest(void) {
    int numberToTest = 0;
    int test = 1;
    char buffer[100];

    while (test != 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &numberToTest) == 1) {
                if (numberToTest >= 10 && numberToTest <= 15) {
                    test = 0;
                } else {
                    printf("Nenapsal jsi cislo v rozmezi 10 - 15\n");
                }
            } else {
                printf("nenapsal jsi cislo, zkus to znovu\n");
            }
        }
    }
    return numberToTest;
}

int NumberInBattleGroundTest(int battleGroundSize) {
    int numberToTest = 0;
    int test = 1;
    char buffer[100];

    while (test != 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &numberToTest) == 1) {
                if (numberToTest >= 0 && numberToTest <= battleGroundSize) {
                    test = 0;
                } else {
                    printf("Nenapsal jsi cislo v rozmezi 0 - %d\n", battleGroundSize);
                }
            } else {
                printf("nenapsal jsi cislo, zkus to znovu\n");
            }
        }
    }
    return numberToTest;
}

void OrientationTest(char* result) {
    int test = 1;
    char buffer[100];

    while (test != 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\r\n")] = 0; // Odstranění nového řádku
            if (strcmp(buffer, "vertikalne") == 0 || strcmp(buffer, "horizontalne") == 0) {
                strcpy(result, buffer);
                test = 0;
            } else {
                printf("nenapsal jsi - vertikalne nebo horizontalne, zkus to znovu\n");
            }
        }
    }
}

Point ShipPlacementTest(int battleGroundSize, const char* shipType, int shipSize, const char* orientation, char battleGround[MAX_SIZE][MAX_SIZE][8]) {
    int coordinatesX = 0;
    int coordinatesY = 0;
    int test = 1;

    while (test != 0) {
        int test1 = 1;
        while (test1 != 0) {
            test1 = 0;
            printf("zadej X souradnici lode (cislo v rozmezi 0 - %d)\n", battleGroundSize);
            coordinatesX = NumberInBattleGroundTest(battleGroundSize);
            printf("zadej Y souradnici lode (cislo v rozmezi 0 - %d)\n", battleGroundSize);
            coordinatesY = NumberInBattleGroundTest(battleGroundSize);

            if (strcmp(orientation, "vertikalne") == 0) {
                if (coordinatesY + shipSize - 1 <= battleGroundSize) {
                    for (int i = 0; i < shipSize; i++) {
                        if (strcmp(battleGround[coordinatesY + i][coordinatesX], "-") == 0) {
                            test = 0;
                        } else {
                            printf("Lode se prekrivaji zkus jine souradnice\n");
                            test1 = 1;
                        }
                    }
                } else {
                    printf("Lod se nevejde do hraciho pole, zadej jine Y\n");
                    test1 = 1;
                }
            } else {
                if (coordinatesX + shipSize - 1 <= battleGroundSize) {
                    for (int i = 0; i < shipSize; i++) {
                        if (strcmp(battleGround[coordinatesY][coordinatesX + i], "-") == 0) {
                            test = 0;
                        } else {
                            printf("Lode se prekrivaji zkus jine souradnice\n");
                            test1 = 1;
                        }
                    }
                } else {
                    printf("Lod se nevejde do hraciho pole, zadej Jine X\n");
                    test1 = 1;
                }
            }
        }
    }
    Point p = {coordinatesX, coordinatesY};
    return p;
}

void ShipPlacement(int battleGroundSize, char playerBattleGround[MAX_SIZE][MAX_SIZE][8], int shipSize, const char* shipType) {
    printf(" zadej orientaci (vertikalne nebo horizontalne)\n");
    char orientation[20];
    OrientationTest(orientation);

    Point coords = ShipPlacementTest(battleGroundSize, shipType, shipSize, orientation, playerBattleGround);

    for (int i = 0; i < shipSize; i++) {
        if (strcmp(orientation, "horizontalne") == 0) {
            strcpy(playerBattleGround[coords.y][coords.x + i], shipType);
        } else {
            strcpy(playerBattleGround[coords.y + i][coords.x], shipType);
        }
    }
}

Point ComputerShipPlacementTest(int battleGroundSize, const char* shipType, int shipSize, const char* orientation, char battleGround[MAX_SIZE][MAX_SIZE][8]) {
    int coordinatesX = 0;
    int coordinatesY = 0;
    int test = 1;

    while (test != 0) {
        int test1 = 1;
        while (test1 != 0) {
            test1 = 0;
            coordinatesX = rand() % (battleGroundSize + 1);
            coordinatesY = rand() % (battleGroundSize + 1);

            if (strcmp(orientation, "vertikalne") == 0) {
                if (coordinatesY + shipSize - 1 <= battleGroundSize) {
                    for (int i = 0; i < shipSize; i++) {
                        if (strcmp(battleGround[coordinatesY + i][coordinatesX], "-") == 0) {
                            test = 0;
                        } else {
                            test1 = 1;
                        }
                    }
                } else {
                    test1 = 1;
                }
            } else {
                if (coordinatesX + shipSize - 1 <= battleGroundSize) {
                    for (int i = 0; i < shipSize; i++) {
                        if (strcmp(battleGround[coordinatesY][coordinatesX + i], "-") == 0) {
                            test = 0;
                        } else {
                            test1 = 1;
                        }
                    }
                } else {
                    test1 = 1;
                }
            }
        }
    }
    Point p = {coordinatesX, coordinatesY};
    return p;
}

void ComputerShipPlacement(int battleGroundSize, char battleGround[MAX_SIZE][MAX_SIZE][8], int shipSize, const char* shipType) {
    char orientation[20];
    int orientationNumber = (rand() % 2) + 1;

    if (orientationNumber == 1) {
        strcpy(orientation, "horizontalne");
    } else {
        strcpy(orientation, "vertikalne");
    }

    Point coords = ComputerShipPlacementTest(battleGroundSize, shipType, shipSize, orientation, battleGround);

    for (int i = 0; i < shipSize; i++) {
        if (strcmp(orientation, "horizontalne") == 0) {
            strcpy(battleGround[coords.y][coords.x + i], shipType);
        } else {
            strcpy(battleGround[coords.y + i][coords.x], shipType);
        }
    }
}

void ShotTypeTest(char* result) {
    int test = 1;
    char buffer[100];

    while (test != 0) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\r\n")] = 0;
            if (strcmp(buffer, "normalni") == 0 || strcmp(buffer, "plosna bombardace") == 0) {
                strcpy(result, buffer);
                test = 0;
            } else {
                printf("nenapsal jsi - normalni nebo plosna bombardace, zkus to znovu\n");
            }
        }
    }
}

int ShipDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], int plusX, int plusY, int j, int coordinatesX, int coordinatesY, int test, int battleGroundSize) {
    int y1 = coordinatesY + plusY;
    int x1 = coordinatesX + plusX + j;
    if (y1 >= 0 && y1 <= battleGroundSize && x1 >= 0 && x1 <= battleGroundSize) {
        if (strcmp(battleGround[y1][x1], "W") == 0) test++;
    }

    int x2 = coordinatesX + plusX - j;
    if (y1 >= 0 && y1 <= battleGroundSize && x2 >= 0 && x2 <= battleGroundSize) {
        if (strcmp(battleGround[y1][x2], "W") == 0) test++;
    }

    int y3 = coordinatesY + j + plusY;
    int x3 = coordinatesX + plusX;
    if (y3 >= 0 && y3 <= battleGroundSize && x3 >= 0 && x3 <= battleGroundSize) {
        if (strcmp(battleGround[y3][x3], "W") == 0) test++;
    }

    int y4 = coordinatesY - j + plusY;
    if (y4 >= 0 && y4 <= battleGroundSize && x3 >= 0 && x3 <= battleGroundSize) {
        if (strcmp(battleGround[y4][x3], "W") == 0) test++;
    }

    return test;
}

void ShipTypeDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], char shootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int plusX, int plusY, int battleGroundSize) {
    int test = 0;
    const char* ship = battleGround[coordinatesY + plusY][coordinatesX + plusX];

    if (strcmp(ship, "L") == 0) {
        for (int j = 0; j < 5; j++) test = ShipDestroyedTest(shootingBattleGround, plusX, plusY, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 5) printf("zasah potopeno\n");
    } else if (strcmp(ship, "B") == 0) {
        for (int j = 0; j < 4; j++) test = ShipDestroyedTest(shootingBattleGround, plusX, plusY, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 4) printf("zasah potopeno\n");
    } else if (strcmp(ship, "K") == 0 || strcmp(ship, "P") == 0) {
        for (int j = 0; j < 3; j++) test = ShipDestroyedTest(shootingBattleGround, plusX, plusY, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 3) printf("zasah potopeno\n");
    } else if (strcmp(ship, "T") == 0) {
        for (int j = 0; j < 2; j++) test = ShipDestroyedTest(shootingBattleGround, plusX, plusY, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 2) printf("zasah potopeno\n");
    }
}

int ComputerShipTypeDestroyedTest(char battleGround[MAX_SIZE][MAX_SIZE][8], char shootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int i, int l, int battleGroundSize) {
    int test = 0;
    int shotSuccess = 1;
    const char* ship = battleGround[coordinatesY][coordinatesX + i];

    if (strcmp(ship, "L") == 0) {
        for (int j = 0; j < 5; j++) test = ShipDestroyedTest(shootingBattleGround, i, l, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 5) shotSuccess = 2;
    } else if (strcmp(ship, "B") == 0) {
        for (int j = 0; j < 4; j++) test = ShipDestroyedTest(shootingBattleGround, i, l, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 4) shotSuccess = 2;
    } else if (strcmp(ship, "K") == 0 || strcmp(ship, "P") == 0) {
        for (int j = 0; j < 3; j++) test = ShipDestroyedTest(shootingBattleGround, i, l, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 3) shotSuccess = 2;
    } else if (strcmp(ship, "T") == 0) {
        for (int j = 0; j < 2; j++) test = ShipDestroyedTest(shootingBattleGround, i, l, j, coordinatesX, coordinatesY, test, battleGroundSize);
        if (test >= 2) shotSuccess = 2;
    }
    return shotSuccess;
}

void PlayerShooting(char computerBattleGround[MAX_SIZE][MAX_SIZE][8], char playerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int* lineBombardation) {
    char shotType[30];
    int test1 = 1;

    while (test1 != 0) {
        printf("vyber typ strely, (normalni,plosna bombardace), plosne bombardace zbiva: %d\n", *lineBombardation);
        ShotTypeTest(shotType);
        if (strcmp(shotType, "plosna bombardace") == 0 && *lineBombardation == 0) {
            printf("Uz ti nezbivaji plosne bombardace\n");
        } else {
            test1 = 0;
        }
    }

    if (strcmp(shotType, "plosna bombardace") == 0) {
        (*lineBombardation)--;
        printf("urci orientaci plosne bombardace (horizontalne, vertikalne)\n");
        char orientation[20];
        OrientationTest(orientation);

        int coordinatesX = 0, coordinatesY = 0;
        int test = 1, test2 = 1;

        while (test != 0) {
            while (test2 != 0) {
                printf("zadej X souradnici leveho/horniho plicka bombardace (cislo v rozmezi 0 - %d)\n", battleGroundSize);
                coordinatesX = NumberInBattleGroundTest(battleGroundSize);
                printf("zadej Y souradnici leveho/horniho plicka bombardace (cislo v rozmezi 0 - %d)\n", battleGroundSize);
                coordinatesY = NumberInBattleGroundTest(battleGroundSize);

                if (strcmp(playerShootingBattleGround[coordinatesY][coordinatesX], "-") == 0) {
                    test2 = 0;
                } else {
                    printf(" na toto pole jsi uz strilel\n");
                }
            }

            if (strcmp(orientation, "vertikalne") == 0) {
                if (coordinatesY + 3 <= battleGroundSize) {
                    for (int plusY = 0; plusY <= 3; plusY++) {
                        if (strcmp(computerBattleGround[coordinatesY + plusY][coordinatesX], "-") == 0) {
                            test = 0;
                            printf("%d,%d voda\n", coordinatesX, coordinatesY + plusY);
                            strcpy(playerShootingBattleGround[coordinatesY + plusY][coordinatesX], "0");
                        } else {
                            printf("%d,%d zasah\n", coordinatesX, coordinatesY + plusY);
                            test = 0;
                            strcpy(playerShootingBattleGround[coordinatesY + plusY][coordinatesX], "W");
                            ShipTypeDestroyedTest(computerBattleGround, playerShootingBattleGround, coordinatesX, coordinatesY, 0, plusY, battleGroundSize);
                        }
                    }
                } else {
                    printf("Bombardovani se nevejde do hraciho pole, zadej jine Y\n");
                    test2 = 1;
                }
            } else {
                if (coordinatesX + 3 <= battleGroundSize) {
                    for (int plusX = 0; plusX <= 3; plusX++) {
                        if (strcmp(computerBattleGround[coordinatesY][coordinatesX + plusX], "-") == 0) {
                            test = 0;
                            printf("%d,%d voda\n", coordinatesX + plusX, coordinatesY);
                            strcpy(playerShootingBattleGround[coordinatesY][coordinatesX + plusX], "0");
                        } else {
                            printf("%d,%d zasah\n", coordinatesX + plusX, coordinatesY);
                            test = 0;
                            strcpy(playerShootingBattleGround[coordinatesY][coordinatesX + plusX], "W");
                            ShipTypeDestroyedTest(computerBattleGround, playerShootingBattleGround, coordinatesX, coordinatesY, plusX, 0, battleGroundSize);
                        }
                    }
                } else {
                    printf("Bombardovani se nevejde do hraciho pole, zadej jine X\n");
                    test2 = 1;
                }
            }
        }
    } else {
        int test2 = 1;
        int coordinatesX = 0, coordinatesY = 0;
        while (test2 != 0) {
            printf("zadej X souradnici strely (cislo v rozmezi 0 - %d)\n", battleGroundSize);
            coordinatesX = NumberInBattleGroundTest(battleGroundSize);
            printf("zadej Y souradnici strely (cislo v rozmezi 0 - %d)\n", battleGroundSize);
            coordinatesY = NumberInBattleGroundTest(battleGroundSize);

            if (strcmp(playerShootingBattleGround[coordinatesY][coordinatesX], "-") == 0) {
                test2 = 0;
            } else {
                printf(" na toto pole jsi uz strilel\n");
            }
        }

        if (strcmp(computerBattleGround[coordinatesY][coordinatesX], "-") == 0) {
            printf("%d,%d voda\n", coordinatesX, coordinatesY);
            strcpy(playerShootingBattleGround[coordinatesY][coordinatesX], "0");
        } else {
            printf("%d,%d zasah\n", coordinatesX, coordinatesY);
            strcpy(playerShootingBattleGround[coordinatesY][coordinatesX], "W");
            ShipTypeDestroyedTest(computerBattleGround, playerShootingBattleGround, coordinatesX, coordinatesY, 0, 0, battleGroundSize);
        }
    }
}

ComputerShotResult ComputerLineBombardation(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int coordinatesX, int coordinatesY, int lineBombardation, int shotSuccess, int plusX, int plusY) {
    char orientation[20];
    int orientationNumber = (rand() % 2) + 1;

    if (orientationNumber == 1) {
        strcpy(orientation, "horizontalne");
    } else {
        strcpy(orientation, "vertikalne");
    }

    int test = 1;
    while (test != 0) {
        if (strcmp(orientation, "vertikalne") == 0) {
            if (coordinatesY + plusY + 3 <= battleGroundSize) {
                for (int i = 0; i <= 3; i++) {
                    if (strcmp(playerBattleGround[coordinatesY + i + plusY][coordinatesX + plusX], "-") == 0) {
                        test = 0;
                        strcpy(computerShootingBattleGround[coordinatesY + i + plusY][coordinatesX + plusX], "0");
                        strcpy(playerBattleGround[coordinatesY + i + plusY][coordinatesX + plusX], "0");
                        shotSuccess = 0;
                    } else {
                        test = 0;
                        strcpy(computerShootingBattleGround[coordinatesY + i + plusY][coordinatesX + plusX], "W");
                        strcpy(playerBattleGround[coordinatesY + i + plusY][coordinatesX + plusX], "W");
                        shotSuccess = ComputerShipTypeDestroyedTest(playerBattleGround, computerShootingBattleGround, coordinatesX + plusX, coordinatesY + plusY, i, 0, battleGroundSize);
                    }
                }
            } else {
                coordinatesY--;
            }
        } else {
            if (coordinatesX + 3 + plusX <= battleGroundSize) {
                for (int i = 0; i <= 3; i++) {
                    if (strcmp(playerBattleGround[coordinatesY + plusY][coordinatesX + i + plusX], "-") == 0) {
                        test = 0;
                        strcpy(computerShootingBattleGround[coordinatesY + plusY][coordinatesX + i + plusX], "0");
                        strcpy(playerBattleGround[coordinatesY + plusY][coordinatesX + i + plusX], "0");
                        shotSuccess = 0;
                    } else {
                        test = 0;
                        strcpy(computerShootingBattleGround[coordinatesY + plusY][coordinatesX + i + plusX], "W");
                        strcpy(playerBattleGround[coordinatesY + plusY][coordinatesX + i + plusX], "W");
                        shotSuccess = ComputerShipTypeDestroyedTest(playerBattleGround, computerShootingBattleGround, coordinatesX + plusX, coordinatesY + plusY, 0, i, battleGroundSize);
                    }
                }
            } else {
                coordinatesX--;
            }
        }
    }

    ComputerShotResult res = {shotSuccess, coordinatesX + plusX, coordinatesY + plusY};
    return res;
}

ComputerShotResult NextComputerShot(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int coordinatesX, int coordinatesY, int shotSuccess, int plusX, int plusY, int battleGroundSize) {
    if (strcmp(playerBattleGround[coordinatesY + plusY][coordinatesX + plusX], "-") == 0) {
        strcpy(computerShootingBattleGround[coordinatesY + plusY][coordinatesX + plusX], "0");
        strcpy(playerBattleGround[coordinatesY + plusY][coordinatesX + plusX], "0");
        shotSuccess = 0;
    } else {
        strcpy(computerShootingBattleGround[coordinatesY + plusY][coordinatesX + plusX], "W");
        strcpy(playerBattleGround[coordinatesY + plusY][coordinatesX + plusX], "W");
        shotSuccess = ComputerShipTypeDestroyedTest(playerBattleGround, computerShootingBattleGround, coordinatesX + plusX, coordinatesY + plusY, 0, 0, battleGroundSize);
    }

    ComputerShotResult res = {shotSuccess, coordinatesX + plusX, coordinatesY + plusY};
    return res;
}

ComputerShotResult ComputerShooting(char playerBattleGround[MAX_SIZE][MAX_SIZE][8], char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8], int battleGroundSize, int lineBombardation, int shotSuccess, int coordinatesX, int coordinatesY) {
    char shotType[30];
    int shotTypeNumber = 0;
    int test1 = 1;
    int shotDirectionY = 0;
    int shotDirectionX = 0;
    int shotDirection = 0;

    while (test1 != 0) {
        if (shotSuccess == 0 || shotSuccess == 2) {
            shotTypeNumber = rand() % 15;
        } else {
            shotTypeNumber = rand() % 5;
        }

        if (shotTypeNumber == 1) {
            strcpy(shotType, "plosna bombardace");
            if (lineBombardation != 0) {
                test1 = 0;
            }
        } else {
            strcpy(shotType, "normalni");
            test1 = 0;
        }
    }

    if (strcmp(shotType, "plosna bombardace") == 0) {
        if (shotSuccess == 0 || shotSuccess == 2) {
            test1 = 1;
            while (test1 != 0) {
                coordinatesX = rand() % (battleGroundSize + 1);
                coordinatesY = rand() % (battleGroundSize + 1);
                if (strcmp(computerShootingBattleGround[coordinatesX][coordinatesY], "-") != 0) {
                    ComputerShotResult res = ComputerLineBombardation(playerBattleGround, computerShootingBattleGround, battleGroundSize, coordinatesX, coordinatesY, lineBombardation, shotSuccess, 0, 0);
                    shotSuccess = res.shotSuccess;
                    coordinatesX = res.coordX;
                    coordinatesY = res.coordY;
                    test1 = 0;
                }
            }
        } else {
            test1 = 1;
            while (test1 != 0) {
                shotDirection = (rand() % 2) + 1;
                if (shotDirection == 1) {
                    if (coordinatesY == 0) shotDirectionY = 2;
                    else if (coordinatesY == battleGroundSize) shotDirectionY = 1;
                    else shotDirectionY = (rand() % 2) + 1;

                    if (shotDirectionY == 1) {
                        if (coordinatesY - 1 >= 0 && strcmp(computerShootingBattleGround[coordinatesX][coordinatesY - 1], "-") == 0) {
                            ComputerShotResult res = ComputerLineBombardation(playerBattleGround, computerShootingBattleGround, battleGroundSize, coordinatesX, coordinatesY, lineBombardation, shotSuccess, 0, -1);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    } else {
                        if (coordinatesY + 1 <= battleGroundSize && strcmp(computerShootingBattleGround[coordinatesX][coordinatesY + 1], "-") == 0) {
                            ComputerShotResult res = ComputerLineBombardation(playerBattleGround, computerShootingBattleGround, battleGroundSize, coordinatesX, coordinatesY, lineBombardation, shotSuccess, 0, 1);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    }
                } else {
                    if (coordinatesX == 0) shotDirectionX = 2;
                    else if (coordinatesX == battleGroundSize) shotDirectionX = 1;
                    else shotDirectionX = (rand() % 2) + 1;

                    if (shotDirectionX == 1) {
                        if (coordinatesX - 1 >= 0 && strcmp(computerShootingBattleGround[coordinatesX - 1][coordinatesY], "-") == 0) {
                            ComputerShotResult res = ComputerLineBombardation(playerBattleGround, computerShootingBattleGround, battleGroundSize, coordinatesX, coordinatesY, lineBombardation, shotSuccess, -1, 0);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    } else {
                        if (coordinatesX + 1 <= battleGroundSize && strcmp(computerShootingBattleGround[coordinatesX + 1][coordinatesY], "-") == 0) {
                            ComputerShotResult res = ComputerLineBombardation(playerBattleGround, computerShootingBattleGround, battleGroundSize, coordinatesX, coordinatesY, lineBombardation, shotSuccess, 1, 0);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    }
                }
            }
        }
    } else {
        if (shotSuccess == 0 || shotSuccess == 2) {
            test1 = 1;
            while (test1 != 0) {
                coordinatesX = rand() % (battleGroundSize + 1);
                coordinatesY = rand() % (battleGroundSize + 1);
                if (strcmp(computerShootingBattleGround[coordinatesY][coordinatesX], "-") == 0) {
                    test1 = 0;
                    if (strcmp(playerBattleGround[coordinatesY][coordinatesX], "-") == 0) {
                        strcpy(computerShootingBattleGround[coordinatesY][coordinatesX], "0");
                        strcpy(playerBattleGround[coordinatesY][coordinatesX], "0");
                        shotSuccess = 0;
                    } else {
                        strcpy(computerShootingBattleGround[coordinatesY][coordinatesX], "W");
                        strcpy(playerBattleGround[coordinatesY][coordinatesX], "W");
                        shotSuccess = ComputerShipTypeDestroyedTest(playerBattleGround, computerShootingBattleGround, coordinatesX, coordinatesY, 0, 0, battleGroundSize);
                    }
                }
            }
        } else {
            test1 = 1;
            while (test1 != 0) {
                shotDirection = (rand() % 2) + 1;
                if (shotDirection == 1) {
                    if (coordinatesY == 0) shotDirectionY = 2;
                    else if (coordinatesY == battleGroundSize) shotDirectionY = 1;
                    else shotDirectionY = (rand() % 2) + 1;

                    if (shotDirectionY == 1) {
                        if (coordinatesY - 1 >= 0 && strcmp(computerShootingBattleGround[coordinatesX][coordinatesY - 1], "-") == 0) {
                            ComputerShotResult res = NextComputerShot(playerBattleGround, computerShootingBattleGround, coordinatesX, coordinatesY, shotSuccess, 0, -1, battleGroundSize);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    } else {
                        if (coordinatesY + 1 <= battleGroundSize && strcmp(computerShootingBattleGround[coordinatesX][coordinatesY + 1], "-") == 0) {
                            ComputerShotResult res = NextComputerShot(playerBattleGround, computerShootingBattleGround, coordinatesX, coordinatesY, shotSuccess, 0, 1, battleGroundSize);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    }
                } else {
                    if (coordinatesX == 0) shotDirectionX = 2;
                    else if (coordinatesX == battleGroundSize) shotDirectionX = 1;
                    else shotDirectionX = (rand() % 2) + 1;

                    if (shotDirectionX == 1) {
                        if (coordinatesX - 1 >= 0 && strcmp(computerShootingBattleGround[coordinatesX - 1][coordinatesY], "-") == 0) {
                            ComputerShotResult res = NextComputerShot(playerBattleGround, computerShootingBattleGround, coordinatesX, coordinatesY, shotSuccess, -1, 0, battleGroundSize);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    } else {
                        if (coordinatesX + 1 <= battleGroundSize && strcmp(computerShootingBattleGround[coordinatesX + 1][coordinatesY], "-") == 0) {
                            ComputerShotResult res = NextComputerShot(playerBattleGround, computerShootingBattleGround, coordinatesX, coordinatesY, shotSuccess, 1, 0, battleGroundSize);
                            shotSuccess = res.shotSuccess;
                            coordinatesX = res.coordX;
                            coordinatesY = res.coordY;
                            test1 = 0;
                        }
                    }
                }
            }
        }
    }

    ComputerShotResult res = {shotSuccess, coordinatesX, coordinatesY};
    return res;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("Vitam te ve hre Battle Ship\n");
    printf("Jako prvni si zvol rozmery pole (10 - 15)\n");

    int battleGroundSize = NumberTest() - 1;
    int lineBombardation = 3;
    int computerLineBombardation = 3;
    int shotSuccess = 0;
    int computerShotCoordinatesX = 0;
    int computerShotCoordinatesY = 0;

    static char playerBattleGround[MAX_SIZE][MAX_SIZE][8];
    static char computerBattleGround[MAX_SIZE][MAX_SIZE][8];
    static char playerShootingBattleGround[MAX_SIZE][MAX_SIZE][8];
    static char computerShootingBattleGround[MAX_SIZE][MAX_SIZE][8];

    GenerateBattleGround(battleGroundSize, playerBattleGround);
    GenerateBattleGround(battleGroundSize, computerBattleGround);
    GenerateBattleGround(battleGroundSize, playerShootingBattleGround);
    GenerateBattleGround(battleGroundSize, computerShootingBattleGround);

    int playerScore = 0;
    int computerScore = 0;

    PrintBattleGround(battleGroundSize, playerBattleGround);

    printf("rozmisti lode\n");
    printf("Letadlova lod - souradnice se vztahuji k levemu/hornimu policku lode\n");
    ShipPlacement(battleGroundSize, playerBattleGround, 5, "L");
    PrintBattleGround(battleGroundSize, playerBattleGround);

    printf("Bitevni lod - souradnice se vztahuji k levemu/hornimu policku lode\n");
    ShipPlacement(battleGroundSize, playerBattleGround, 4, "B");
    PrintBattleGround(battleGroundSize, playerBattleGround);

    printf("Kriznik - souradnice se vztahuji k levemu/hornimu policku lode\n");
    ShipPlacement(battleGroundSize, playerBattleGround, 3, "K");
    PrintBattleGround(battleGroundSize, playerBattleGround);

    printf("Ponorka - souradnice se vztahuji k levemu/hornimu policku lode\n");
    ShipPlacement(battleGroundSize, playerBattleGround, 3, "P");
    PrintBattleGround(battleGroundSize, playerBattleGround);

    printf("Torpedoborec - souradnice se vztahuji k levemu/hornimu policku lode\n");
    ShipPlacement(battleGroundSize, playerBattleGround, 2, "T");
    PrintBattleGround(battleGroundSize, playerBattleGround);

    ComputerShipPlacement(battleGroundSize, computerBattleGround, 5, "L");
    ComputerShipPlacement(battleGroundSize, computerBattleGround, 4, "B");
    ComputerShipPlacement(battleGroundSize, computerBattleGround, 3, "K");
    ComputerShipPlacement(battleGroundSize, computerBattleGround, 3, "P");
    ComputerShipPlacement(battleGroundSize, computerBattleGround, 2, "T");

    while (playerScore < 17 && computerScore < 17) {
        playerScore = 0;
        computerScore = 0;

        for (int i = 0; i <= battleGroundSize; i++) {
            for (int j = 0; j <= battleGroundSize; j++) {
                if (strcmp(computerShootingBattleGround[i][j], "W") == 0 || strcmp(computerShootingBattleGround[i][j], "w") == 0) {
                    computerScore++;
                }
                if (strcmp(playerShootingBattleGround[i][j], "W") == 0) {
                    playerScore++;
                }
            }
        }

        if (playerScore >= 17 || computerScore >= 17) {
            break;
        }

        printf("jsi na rade\n");
        PlayerShooting(computerBattleGround, playerShootingBattleGround, battleGroundSize, &lineBombardation);
        PrintBattleGround(battleGroundSize, playerShootingBattleGround);

        printf("pocitac je na rade\n");
        ComputerShotResult res = ComputerShooting(playerBattleGround, computerShootingBattleGround, battleGroundSize, computerLineBombardation, shotSuccess, computerShotCoordinatesX, computerShotCoordinatesY);
        shotSuccess = res.shotSuccess;
        computerShotCoordinatesX = res.coordX;
        computerShotCoordinatesY = res.coordY;

        printf("tvoje pole po zasahu pocitace\n");
        PrintBattleGround(battleGroundSize, playerBattleGround);
    }

    if (playerScore >= 17) {
        printf("VYHRAL JSI\n");
    } else {
        printf("PROHRAL JSI\n");
    }

    getchar();
    return 0;
}