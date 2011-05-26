#ifndef IPC_H
#define IPC_H

#ifdef SUNOS4
#ifndef __USE_FIXED_PROTOTYPES__
#define __USE_FIXED_PROTOTYPES__
#endif
#endif

/* to get size_t */
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
   These functions are a simplified interface to the semaphore and
   shared memory functions. For more information, see ipc.c or the man
   pages for shmget, shmat, shmdt, shmctl, semget, semctl, semop.
*/

/* ===== Shared memory ===== */

/* 
   Returns a pointer to a shared memory segment of 
   size <size>, or NULL on error.
 */
void *shmalloc(size_t size);

/*
   Frees a shared memory segment.
   Returns -1 on error.
*/
int shfree(void *shm);



/* ===== Semaphores ===== */

/* Declare your semaphores 'semid_t' */	
typedef int semid_t;

/*
   Creates and returns a semaphore, or -1 on error.
   The semaphore is initialized to n.
*/
semid_t semcreate(int n);

/*
   Destroys a semaphore.
   Returns -1 on error.
*/
int semdestroy(semid_t sem);

/* 
   Obtains the semaphore and decrements the counter, or blocks
   until the semaphore is available. Returns -1 on error.
*/
int semwait(semid_t sem);

/* 
   Releases the semaphore, and increments the counter. 
   Returns -1 on error.
*/
int semsignal(semid_t sem);

/* alternate interface to semwait & semsignal */
#define p(sem) semwait(sem)
#define v(sem) semsignal(sem)

#ifdef __cplusplus
};
#endif

#endif
