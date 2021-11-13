#include <stdio.h>
#define N 3 //number of resources
#define K 5 //number of processes

struct row{
  int value[N];
  int done;
};

void sum(struct row *R, struct row *A){
  for(int i=0; i<N;i++){
    A->value[i]+=R->value[i];
  }
}

int canTerminate(struct row *R, struct row *A){
  for(int i=0; i<N;i++){
    if (A->value[i]<R->value[i]) return 0;
  }
  return 1;
}

int main(void) {
  
  struct row A;
  struct row E;
  struct row C[K];
  struct row R[K];

  FILE* file = fopen("input_dl.txt","r");  
  
  for (int i=0; i<N; i++){
    fscanf(file, "%d", A.value+i);
  }
  
  for (int i=0; i<N; i++){
    fscanf(file, "%d", E.value+i);
  }

  for (int i=0; i<K; i++){
    for (int m=0; m<N; m++){
    fscanf(file, "%d", &C[i].value[m]);
  }
  }

  for (int i=0; i<K; i++){
    for (int m=0; m<N; m++){
    fscanf(file, "%d", &R[i].value[m]);
    R[i].done=0;
  }
  }

  int done = 0;
  while(1){

    if(done==K) {
      printf("Success\n");
      break;
    }

    int change = 0;
    int last_undone = -1;

    for (int m=0; m<K; m++){

      if (R[m].done==0){

      if (R[m].done==0&&canTerminate(&R[m], &A)){
        done++;
        R[m].done = 1;
        sum(&R[m], &A);
        change++;
        break;
      } else last_undone=m;
      
      }
    }
    
    if(change==0) {
      printf("Deadlock detected\n");
      printf("Process #%d is blocked\n", last_undone);
      break;
    }
  }

  return 0;
}