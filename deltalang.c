#ifndef __LemonOS__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#else
// already included by gcc but will get compiler warnings if not do this
// this should be a `.h` file with only the function declarations, but im lazy
#include "lemonstd.c"
#endif

int64_t _add (int64_t inp1, int64_t inp2) {return(inp1 + inp2);};
int64_t _sub (int64_t inp1, int64_t inp2) {return(inp1 - inp2);};
int64_t _div (int64_t inp1, int64_t inp2) {return(inp1 / inp2);};
int64_t _mul (int64_t inp1, int64_t inp2) {return(inp1 * inp2);};
int64_t _mod (int64_t inp1, int64_t inp2) {return(inp1 % inp2);};
char instructionList[5][5] = {"ADD", "SUB", "DIV", "MUL", "MOD"};
typedef int64_t (*math_function) (int64_t, int64_t);
math_function instructions[] = {&_add, &_sub, &_div, &_mul, &_mod};

void seed_time() {
  #ifndef __LemonOS__
  struct timespec now;
  timespec_get(&now, TIME_UTC);
  srand(((int64_t) now.tv_sec) * 1000 + ((int64_t) now.tv_nsec) / 1000000);
  #else
  srand(time()); // no way to get milisecond time in LemonOS
  #endif
}
int main(){
  char * program[16]; // = Proccess (Contents); Process input to 3 seperate inputs put in an array
  #ifndef __LemonOS__
  printf("Running program: \n");
  #else
  printf(u"Running program: \n");
  // Addresses in `instructions` are invalid under LemonOS, weird?
  instructions[0] = &_add;
  instructions[1] = &_sub;
  instructions[2] = &_div;
  instructions[3] = &_mul;
  instructions[4] = &_mod;
  #endif
  seed_time();
  for(int c = 0; c < 5; c++){
    // randomly generate a program, ! bad: should change !
    #ifndef __LemonOS__
    program[c] = (char*) (malloc(32));
    strcpy(program[c], instructionList[(rand() % 5)]);
    usleep(100000); // ignoire this is weird dont worry
    seed_time();
    program[c][3] = ' ';
    program[c][4] = (rand() % 10) + '0';
    program[c][5] = ' ';
    program[c][6] = (rand() % 10) + '0';
    printf("%s\n", program[c]);
    #else
    program[c] = (char *) (malloc(64) + 16);
    strcpy(program[c], instructionList[rand() % 5]);
    program[c][3] = ' ';
    program[c][4] = (rand() % 10) + '0';
    program[c][5] = ' ';
    program[c][6] = (rand() % 10) + '0';
    printf(u"%8\n", program[c]);
    #endif
  }
  #ifndef __LemonOS__
  printf("\n");
  #else
  printf(u"\n");
  #endif
  for(int b = 0; b < 5; b++){
    for(int i = 0; i < 5; i++){
      if (program[b][0] == instructionList[i][0] && program[b][1] == instructionList[i][1] && program[b][2] == instructionList[i][2]) {
        // hack: should change
        #ifndef __LemonOS__
        int64_t result = instructions[i](program[b][4] - '0', program[b][6] - '0');
        printf("%c%c%c(%c, %c) == %ld\n", program[b][0], program[b][1], program[b][2], program[b][4], program[b][6], result);
        #else
        int64_t result = instructions[i](program[b][4] - '0', program[b][6] - '0');
        printf(u"%c%c%c(%c, %c) == %d\n", program[b][0], program[b][1], program[b][2], program[b][4], program[b][6], result);
        #endif
      }
    }
  }
  return 0;
}
