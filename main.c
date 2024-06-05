#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIRKA 40
#define VYSKA 15
#define VYSKAZDI 4

int leveSkore, praveSkore;

typedef struct {
    int x;
    int y;
} pozice;

void napoveda();
void nastaveni();
int bothra();
int hra2hracami();

int main()
{
    srand(time(NULL));
    int odpoved;
    while (true) {
        printf("_________________________\n");
        printf("       PONG GAME         \n");
        printf("_________________________\n");
        printf("Zadej 1. pro spusteni hry s Botem\n");
        printf("Zadej 2. pro spusteni hry s 2 Hracami\n");
        printf("Zadej 3. pro napoveda\n");
        printf("Zadej 4. pro nastaveni\n");
        printf("Zadej 5. pro vypnuti programu\n");
        scanf("%d", &odpoved);
        switch (odpoved) {
            case 1:
                bothra();
                break;
            case 2:
                hra2hracami();
                break;
            case 3:
                napoveda();
                break;
            case 4:
                nastaveni();
                break;
            case 5:
                puts("Odesel si ze hry");
                return 0;
            default:
                puts("Zadal si neplatne cislo");
        }
    }
}

int random()
{
    return rand() % 2 ? 1 : -1;
}

void nakresli(pozice mic, pozice levaZed, pozice pravaZed)
{
    system("cls");
    for (int i = 0; i < VYSKA; ++i) {
        for (int j = 0; j < SIRKA; ++j) {
            if (i == 0 || i == VYSKA - 1)
                printf("*"); // ohraničení
            else if (j == levaZed.x && i >= levaZed.y && i < levaZed.y + VYSKAZDI)
                printf("|");
            else if (j == pravaZed.x && i >= pravaZed.y && i < pravaZed.y + VYSKAZDI)
                printf("|");
            else if (i == mic.y && j == mic.x)
                printf("O"); // míč
            else if (j == SIRKA / 2)
                printf("|"); // dělící čára
            else
                printf(" "); // vyplnění volných míst
        }
        printf("\n");
    }
}

void pohybMice(pozice *mic, int *motionX, int *motionY, pozice levaZed, pozice pravaZed) {
    mic->x += *motionX;
    mic->y += *motionY;

    // odraz miče pomcí bočních zdí
    if (mic->y == 0 || mic->y == VYSKA - 1) {
        *motionY *= -1;
    }
    // funkce pro odražení miče pomocí zdí
    if (mic->x == levaZed.x + 1 && mic->y >= levaZed.y && mic->y < levaZed.y + VYSKAZDI) {
        *motionX *= -1;
    }
    if (mic->x == pravaZed.x - 1 && mic->y >= pravaZed.y && mic->y < pravaZed.y + VYSKAZDI) {
        *motionX *= -1;
    }
    // fukce pro resetovani miče při vyhře
    if (mic->x == 0)
    {
        mic->x = SIRKA / 2;
        mic->y = VYSKA / 2;
        *motionX = random();
        *motionY = random();
        praveSkore += 1;
    }
    if(mic->x == SIRKA - 1)
    {
        mic->x = SIRKA / 2;
        mic->y = VYSKA / 2;
        *motionX = random();
        *motionY = random();
        leveSkore += 1;
    }
}

void posunZdi(pozice *zed, int smer)
{
    zed->y += smer;
    // podmínky proti proniknutí do zdi
    if (zed->y < 1) {
        zed->y = 1;
    } else if (zed->y > VYSKA - VYSKAZDI - 1) {
        zed->y = VYSKA - VYSKAZDI - 1;
    }
}

void posunBota(pozice *pravaZed, pozice *mic)
{
    if(mic->y < pravaZed->y)
    {
        pravaZed->y += -1;
    }
    if(mic->y > pravaZed->y)
    {
        pravaZed->y += 1;
    }
    if (pravaZed->y < 1)
    {
        pravaZed->y = 1;
    }
    else if (pravaZed->y > VYSKA - VYSKAZDI - 1)
    {
        pravaZed->y = VYSKA - VYSKAZDI - 1;
    }
}

int hra2hracami()
{
    pozice mic = {SIRKA / 2, VYSKA / 2};
    pozice levaZed = {1, VYSKA / 2 - VYSKAZDI / 2};
    pozice pravaZed = {SIRKA - 2, VYSKA / 2 - VYSKAZDI / 2};
    int montionX = random();
    int montionY = random();

    while (true) {
        nakresli(mic, levaZed, pravaZed);
        pohybMice(&mic, &montionX, &montionY, levaZed, pravaZed);
        Sleep(100);

        if (_kbhit()) {
            char vystup = _getch();
            if (vystup == 'q')
                break;
            if (vystup == 'w')
                posunZdi(&levaZed, -1);
            if (vystup == 's')
                posunZdi(&levaZed, 1);
            if (vystup == 72)
                posunZdi(&pravaZed, -1);
            if (vystup == 80)
                posunZdi(&pravaZed, 1);
        }
    }
    return 0;
}

int bothra()
{
    pozice mic = {SIRKA / 2, VYSKA / 2};
    pozice levaZed = {1, VYSKA / 2 - VYSKAZDI / 2};
    pozice pravaZed = {SIRKA - 2, VYSKA / 2 - VYSKAZDI / 2};
    int montionX = random();
    int montionY = random();

    while (true) {
        nakresli(mic, levaZed, pravaZed);
        pohybMice(&mic, &montionX, &montionY, levaZed, pravaZed);
        Sleep(100);
        posunBota(&pravaZed, &mic);
        if (_kbhit()) {
            char vystup = _getch();
            if (vystup == 'q') break;
            if (vystup == 'w')
                posunZdi(&levaZed, -1);
            if (vystup == 's')
                posunZdi(&levaZed, 1);
        }
    }
    return 0;
}

void napoveda()
{
    printf("Napoveda:\n");
    printf("Ovladani: nahoru, dolu\n");
    printf(" Hrac1: w , s\n");
    printf(" Hrac2: šipka nahoru,"
                  "         šipka dolu\n");
    getchar();
    getchar();
}

void nastaveni()
{
    printf("Nastaveni hry...\n");
    getchar();
    getchar();
}
