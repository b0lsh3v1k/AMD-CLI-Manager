#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
void GetClock(char adapter);
void SetClock(char adapter);
void FanSpeed(char adapter);
void GetTemp(char adapter);

int main(void)
{
    system("clear");
    menu();
    return 0;
}

int menu(void)
{
  char option,adapter;
  printf("\n[+]-------------AMD CLI MANAGER by b0lsh3v1k-------------[+]\n");
  printf("Set (F)an speed.\n");
  printf("(L)ist disponible adapters.\n");
  printf("(G)et clock speeds for x adapter.\n");
  printf("(S)et new clock speeds for x adapter.\n");
  printf("(C)heck temperature for x adapter.\n");
  printf("(E)xit.\n");
  printf("Usage: Letter x [Letter = the letter corresponding to the desired option x = adapter number (default: 0)]\n");
  printf("[+]------------------------------------------------------[+]\n~> ");
  scanf("%c %c",&option, &adapter);
  switch (option)
  {
      case('L'):
          system("aticonfig --list-adapters");
          break;
      case('G'):
          GetClock(adapter);
          break;
      case('S'):
          SetClock(adapter);
          break;
      case('F'):
          FanSpeed(adapter);
          break;
      case('C'):
          GetTemp(adapter);
          break;
      case('E'):
          break;
      default:
          break;
  }
  if (option == 'E')
    return 1;
  else
    main();
}

void GetClock(char adapter)
{
    char GetClock[35];
    sprintf(GetClock, "aticonfig --adapter=%c --od-getclocks", adapter);
    system(GetClock);
}

void SetClock(char adapter)
{
    char SetClock[45];
    char Commit[38];
    int CoreClock,MemoryClock;
    printf("Enter desired Core Clock Speed and Memory Clock Speed.\nUsage: 1015 1500.\n~> ");
    scanf("%i %i",&CoreClock, &MemoryClock);
    sprintf(SetClock, "aticonfig --adapter=%c --od-setclocks=%c,%c", adapter, CoreClock, MemoryClock);
    system(SetClock);
    sprintf(Commit, "aticonfig --adapter=%c --od-commitclocks", adapter);
    system(Commit);
    system("clear");
    printf("[!]CHANGES APPLIED[!]\n.");
}

void FanSpeed(char adapter)
{
    char FanSpeed[41];
    int  speed;
    printf("Enter desired speed: ");
    scanf("%i", &speed);
    sprintf(FanSpeed, "aticonfig --pplib-cmd \"set fanspeed 0 %i\"",speed);
    system(FanSpeed);
    system("clear");
    printf("[!]CHANGES APPLIED[!]\n.");

}

void GetTemp(char adapter)
{
    char GetTemp[40];
    system(GetTemp);
    sprintf(GetTemp, "aticonfig --adapter=%c --od-gettemperature", adapter);
}
