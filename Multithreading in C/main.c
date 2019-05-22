#include "stack.h"
#include "threads_func.h"
int main()
{
    	s.top = 0;
        s.data = malloc(max_length*sizeof(int));

        pthread_create (&p1,NULL,&thread_1,NULL);
        pthread_create (&p2	,NULL,&thread_2,NULL);
        pthread_create (&p3,NULL,&thread_3,NULL);
        pthread_create (&p4,NULL,&thread_4,NULL);
        pthread_create (&p5, NULL, &thread_5, NULL);
        pthread_create (&p6, NULL, &thread_6, NULL);

        pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        pthread_join(p3,NULL);
        pthread_join(p4,NULL);
        pthread_join(p5,NULL);
        pthread_join(p6,NULL);

        printf("All threads stopped!\n");

        return 0;
}
