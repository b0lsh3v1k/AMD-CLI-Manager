#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GetClock(char adapter);
void SetClock(char adapter);
void FanSpeed(char adapter);
void GetTemp(char adapter);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(
        "[+]-------------AMD CLI MANAGER by b0lsh3v1k-------------[+]\n"
        "\nToo few arguments. Atleast 2 required (option and adapter)"
        "\n./AMDManager F (Set fan speed) 0 (#adapter)"
        "\n./AMDManager L (List available adapters)"
        "\n./AMDManager G (Get clock speeds) 0 (#adapter)"
        "\n./AMDManager S (Set new clock speeds) 0 (#adapter)"
        "\n./AMDManager C (Check temperature) 0 (#adapter)"
        "\n\n[+]------------------------------------------------------[+]\n");
    return 1;
  }
  char option = argv[1][0], adapter = argv[2][0];
  system("clear");
  switch (option) {
  case ('L'):
    system("aticonfig --list-adapters");
    break;
  case ('G'):
    GetClock(adapter);
    break;
  case ('S'):
    SetClock(adapter);
    break;
  case ('F'):
    FanSpeed(adapter);
    break;
  case ('C'):
    GetTemp(adapter);
    break;
  default:
    break;
  }
  return 0;
}

void GetClock(char adapter) {
  char GetClock[35];
  sprintf(GetClock, "aticonfig --adapter=%c --od-getclocks", adapter);
  system(GetClock);
}

void SetClock(char adapter) {
  char SetClock[45];
  char Commit[38];
  int CoreClock, MemoryClock;
  printf("Enter desired Core Clock Speed and Memory Clock Speed."
         "\nUsage: 1015(core speed) 1500(memory speed).\n~> ");
  scanf("%i %i", &CoreClock, &MemoryClock);
  sprintf(SetClock, "aticonfig --adapter=%c --od-setclocks=%c,%c", adapter,
          CoreClock, MemoryClock);
  system(SetClock);
  sprintf(Commit, "aticonfig --adapter=%c --od-commitclocks", adapter);
  system(Commit);
  printf("[!]CHANGES APPLIED[!]\n");
}

void FanSpeed(char adapter) {
  char FanSpeed[41];
  int speed;
  printf("Enter desired speed: ");
  scanf("%i", &speed);
  sprintf(FanSpeed, "aticonfig --pplib-cmd \"set fanspeed 0 %i\"", speed);
  system(FanSpeed);
  printf("[!]CHANGES APPLIED[!]\n");
}

void GetTemp(char adapter) {
  char GetTemp[40];
  sprintf(GetTemp, "aticonfig --adapter=%c --od-gettemperature", adapter);
  system(GetTemp);
}
