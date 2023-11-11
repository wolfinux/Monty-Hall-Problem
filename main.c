#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
unsigned long long int n = ULLONG_MAX; //default value of n
int doors[3] = {0, 1, 2};
void simulation(unsigned long long int* k_won, unsigned long long int* c_won, unsigned long long int* k_lost, unsigned long long int* c_lost) {
  //c -> the first pick of door is changed
  //k -> the first pick of door is kept
  
  int car = rand() % 3;
  int pick = rand() % 3;
  int goats[2] = {0};
  int append_index = 0;
  
  for (int i = 0 ; i < 3 ; i++) {
    
    if (doors[i] != car) {
      goats[append_index] = doors[i];
      append_index++;
    }
  }
  if (car == pick) {
    
    int opened = goats[rand() % 2];
    int changed = rand() % 2;
    if (changed == 0){
      (*c_lost) ++;
    }
    else{
      (*k_won) ++;
    }
  }
    
  else{
    
    int opened_door;
    for (int i = 0 ; i < 2 ; i++) {
      if (goats[i] != pick) {
        opened_door = i;
      }
    }
    int changed = rand() % 2;
    //printf("Chosen door: %d\nOpened door: %d\nChanged ?: %d\n\n", pick, opened_door, changed);
    if (changed == 0) {
      (*k_lost) ++;
    }
    else{
      (*c_won) ++;
    }
  }
}
int main(int argc, char** argv) {
  
  if (argc > 1) {
    
    char* endptr = malloc(sizeof(char));
    n = strtoull(argv[1], &endptr, 10);
    
    if (endptr == argv[1]) {
      
      printf("Invalid number. Exiting...");
      return 1;
      
    }
    else if(endptr != argv[1] + strlen(argv[1])) {
      printf("Warning : at least one of the given characters wasn't a number.\nSetting the number of simulations to %llu ...\n\n", n);
    }
  }
  
  clock_t begin = clock();
  srand(time(NULL));
  
  unsigned long long k_won = 0;
  unsigned long long c_won = 0;
  unsigned long long k_lost = 0;
  unsigned long long c_lost = 0;
  
  for (unsigned long long int i = 0 ; i < n ; i++) {
    simulation(&k_won, &c_won, &k_lost, &c_lost);
  }
  
  printf("Changed and won: %llu -> %f%%\nKept and won: %llu -> %f%%\nTotal of won simulations: %llu\nTotal of simulations: %llu\n\n", c_won, (float) c_won / n * 100, k_won, (float) k_won / n * 100, k_won + c_won, n);
  printf("Simulations won by changing doors (among the won simulations): %f%%\nSimulations won by keeping the first pick of door (among the won simulations): %f%%\n\n", (float) c_won / (c_won + k_won) * 100, (float) k_won / (c_won + k_won) * 100);
  clock_t end = clock();
  
  double time = (double) (end - begin) / CLOCKS_PER_SEC;
  
  printf("\nProcessing time: %f seconds\n", time);
  
  FILE * file;
  
  file = fopen("Simulation results.txt", "w");
  
  if (file != NULL) {
    fprintf(file, "Changed and won: %llu -> %f%%\nKept and won: %llu -> %f%%\nTotal of won simulations: %llu\n\nChanged and lost: %llu -> %f%%\nKept and lost: %llu -> %f%%\nTotal of lost simulations: %llu\n\nTotal of simulations: %llu\n\n\n", c_won, (float) c_won / n * 100, k_won, (float) k_won / n * 100, k_won + c_won, c_lost, (float) c_lost / n, k_lost, (float) k_lost / n, c_lost + k_lost, n);
    fprintf(file, "Simulations won by changing doors (among the won simulations): %f%%\nSimulations won by keeping the first pick of door (among the won simulations): %f%%\n\n", (float) c_won / (c_won + k_won) * 100, (float) k_won / (c_won + k_won) * 100);
    fprintf(file, "Processing time: %f seconds", time);
  }
  
  fclose(file);
  
  return 0;
}
