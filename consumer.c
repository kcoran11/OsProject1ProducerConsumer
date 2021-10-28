#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

int main(){
    const int SIZE =sizeof(int); // Const for size of int

    int shm_fd = shm_open("table", O_CREAT | O_RDWR, 0666); // creating the shared memory for the table
    ftruncate(shm_fd, SIZE);
    int* ptr = mmap (0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd,0);

    // creating and initializing the semaphores
    sem_t *full, *open, *locked; 
    full =sem_open("full", O_CREAT,0666, 0); // initializes full and defaults to 0 because table starts empty
    open = sem_open("open", O_CREAT, 0666, 2); // initializes open and defaults to 2 because table starts empty
    locked = sem_open("locked", O_CREAT, 0666, 1); // initalizes locked and defaults to 1 because table starts out not used

    printf("\nConsumer ready.\n");

    for (int i=0; i<24; ++i){
        sem_wait(full); // decrements full and proceeds if >0. if 0 waits until>0
        sem_wait(locked); // decrements locked and proceeds if >0. if 0 waits until>0
        --(*ptr); // decrementing the value of the table
        sem_post(locked); // increments the value of locked because no longer in use
        printf("Item Consumed. Table has %d items.\n", *ptr);
        sem_post(open);

    }

    // closing semaphores
    sem_close(full);
    sem_close(open);
    sem_close(locked);
    
    // unlinking semaphores
    sem_unlink("full");
    sem_unlink("open");
    sem_unlink("locked");

    // unmapping and unlinking shared memory
    munmap(ptr, SIZE);
    shm_unlink("table");

    printf("Consumer Finished\n");
}