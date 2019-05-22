#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t p1;
pthread_t p2;
pthread_t p3;
pthread_t p4;
pthread_t p5;
pthread_t p6;

int max_length = 100;
sem_t scr21;
sem_t scr22;

//not empty, not full
pthread_cond_t  sig1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t  sig2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  sig21 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;


int flag2 = 0;
int flag5 = 0;

int flag = 1;

int elem = 0;
int int_type_1;
int int_type_2;
unsigned  unsigned_type_1;
unsigned  unsigned_type_2;
long  long_1;
long  long_2;
unsigned long unsigned_long_1;
unsigned long unsigned_long_2;
#endif //LAB4_4_COMMON_H
