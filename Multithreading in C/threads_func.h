#include "common.h"
#include "stack.h"
int rc = 0;

void* thread_1(void* arg){
    __sync_sub_and_fetch(&unsigned_long_2, 4);
    __sync_sub_and_fetch(&long_1, 7);
    __sync_nand_and_fetch(&unsigned_type_1, 7);
    __sync_nand_and_fetch(&int_type_1, 7);
    while (flag){
    	printf("11\n");
        sem_post(&scr22);
        sem_wait(&scr21); 

        printf("12\n");
        pthread_mutex_lock(&mut);
        flag2 = 1;
        flag5 = 1;
		pthread_cond_broadcast (&sig21);
		pthread_mutex_unlock(&mut);

        long lb = __sync_fetch_and_and(&long_2, 0);
        //printf("Thread1: long_2 = %ld\n", lb);
        long fa = __sync_fetch_and_add(&long_1, 5);
        //printf("Thread1: long_1 = %ld\n", fa);
        int b = __sync_fetch_and_xor(&int_type_2, 0);
		 //printf("Thread1: int_type_2 = %d\n", b);
		long la = __sync_fetch_and_sub(&long_1, 0);
		//printf("Thread1: long_1 = %ld\n", la);
		lb--;
		fa--;
		b++;
		la++;
		usleep(2);
	}
	printf("1 ends\n");
	rc++;
    return NULL;
}
void* thread_2(void* arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
	while(flag){
		printf("21\n");
		pthread_mutex_lock(&mut);
		while(!flag2 && flag){
			pthread_cond_wait(&sig21, &mut);
		}
		flag2 = 0;
		pthread_mutex_unlock(&mut);
		//використовуємо та записуємо до буфера
		unsigned a = __sync_fetch_and_or(&unsigned_type_1, 4); // using var
	    //printf("Thread2: unsigned_type_1 = %d\n", a);
		unsigned b = __sync_fetch_and_xor(&unsigned_type_2, 0);
		//printf("Thread2: unsigned_type_2 = %d\n", b);
		unsigned long la = __sync_and_and_fetch(&unsigned_long_1, 0);
		//printf("Thread2: unsigned_long_1 = %lu\n", la);
		unsigned long lb = __sync_fetch_and_add(&unsigned_long_2, 0);
		//printf("Thread2: unsigned_long_2 = %lu\n", lb);
		__sync_val_compare_and_swap(&int_type_2, 0, 1);
		//printf("Thread2: changed value int_type_2 on = %d\n", int_type_2);
		__sync_fetch_and_xor(&int_type_2, 0);

		printf("22\n");
		pthread_mutex_lock(&MCR1);
		while(is_full() && flag){
			pthread_cond_wait(&sig2, &MCR1);
		}
		if(!flag)
			break;
		push(int_type_2);
		printf("Producer thread2:  element %d CREATED. len = %d; \n", elem, s.top);
		pthread_mutex_unlock(&MCR1);
		pthread_cond_broadcast(&sig1);
		usleep(2);
	}
	printf("2 ends\n");
	rc++;
	return NULL;
}
void* thread_3(void* arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
	while (flag) {
		printf("31\n");
		if(is_full()){
			printf("\tENDING FLAG\n");
			flag = 0;
			while(rc != 5){
				sem_post(&scr21);
				sem_post(&scr22);
				pthread_cond_broadcast(&sig1);
				pthread_cond_broadcast(&sig2);
				pthread_mutex_unlock(&MCR1);
				pthread_cond_broadcast(&sig21);
				pthread_mutex_unlock(&mut);
			}
			break;
		}
		printf("32\n");
		pthread_mutex_lock(&MCR1);
		while (is_empty()){
		   pthread_cond_wait(&sig1, &MCR1);
        }
			elem = pop();
			printf("Consumer thread3:  element %d TAKEN. len = %d; \n", elem, s.top);
			pthread_mutex_unlock(&MCR1);
			pthread_cond_broadcast(&sig2);
	}
    printf("3 ends\n");
	return NULL;
}
void* thread_4(void* arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);

	__sync_sub_and_fetch(&int_type_1, 7);
	__sync_sub_and_fetch(&long_2, 4);
	__sync_and_and_fetch(&unsigned_type_1, 2);
	__sync_or_and_fetch(&int_type_2, 5);
	__sync_bool_compare_and_swap(&int_type_2, 6, 6);
	//  модифікація
	while(flag){
		printf("41\n");
		sem_post(&scr21);
		sem_wait(&scr22);

		printf("42\n");
		pthread_mutex_lock(&mut);
		flag2 = 1;
		flag5 = 1;
		pthread_cond_broadcast (&sig21);	//сигнал sig21
		pthread_mutex_unlock(&mut);
	// використання та модифікація
        long a = __sync_val_compare_and_swap(&long_2, 0, 1);
        //printf("Thread1: long_2 = %ld\n", a);
		int b = __sync_fetch_and_xor(&int_type_2, 0);
		//printf("Thread1: int_type_2 = %d\n", b);
		long la = __sync_fetch_and_sub(&long_1, 0);
		//printf("Thread1: long_1 = %ld\n", la);
		long lb = __sync_fetch_and_and(&long_2, 0);
		//printf("Thread1: long_2 = %ld\n", lb);
		long fa = __sync_fetch_and_add(&long_1, 5);
		//printf("Thread1: long_1 = %ld\n", fa);
		a++;
		b++;
		la--;
		lb--;
		fa--;
		usleep(2);
	}
	printf("4 ends\n");
	rc++;
	return NULL;
}
void* thread_5(void* arg){
	pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
	while(flag){
		printf("51\n");
		pthread_mutex_lock(&mut);
		while(!flag5 && flag){
			pthread_cond_wait(&sig21, &mut);
		}
		flag5 = 0;
		pthread_mutex_unlock(&mut);

		// використання та запис до буфера
		int a = __sync_fetch_and_or(&int_type_1, 0); // using var
		//printf("Thread5: int_type_1 = %d\n", a);
		int b = __sync_fetch_and_xor(&int_type_2, 0);
		//printf("Thread5: int_type_2 = %d\n", b);
		unsigned long lb = __sync_fetch_and_add(&unsigned_long_2, 0);
		//printf("Thread5: unsigned_long_2 = %lu\n", lb);
		__sync_val_compare_and_swap(&long_2, 0, 1);
		 //printf("Thread5: changed value long_1 on = %ld \n", long_2);

		printf("52\n");
			pthread_mutex_lock(&MCR1);
			while(is_full() && flag){
				pthread_cond_wait(&sig2, &MCR1);
			}
			elem++;
			if(!flag)
				break;
			push(int_type_1);
			printf("Producer thread5: element %d CREATED len = %d; \n",elem, s.top);
			pthread_mutex_unlock(&MCR1);
			pthread_cond_broadcast(&sig1);
		usleep(2);

	}
	printf("5 ends\n");
	rc++;
	return NULL;
}
void* thread_6(void* arg){
		pthread_setcanceltype(PTHREAD_CANCEL_ENABLE,NULL);
		while (flag) {
			printf("61\n");
			pthread_mutex_lock(&MCR1);
			while(is_full() && flag){
				pthread_cond_wait(&sig2, &MCR1);
			}
			printf("62\n");
			elem++;
			if(!flag)
				break;
			push(elem);
			printf("Producer thread6:  element %d CREATED. len = %d; \n",elem, s.top);
			pthread_mutex_unlock(&MCR1);
			pthread_cond_broadcast(&sig1);
		usleep(2);
	    }
	printf("6 ends\n");
	rc++;
	return NULL;
}
