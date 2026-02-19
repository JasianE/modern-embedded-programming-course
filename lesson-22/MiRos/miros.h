#ifndef MIROS_H
#define MIROS_H

#endif /* MIROS_H */

//Each thread requires a private SP

/* Thread control block (TCB) */
typedef struct {
    void *sp;
} OSThread;

typedef void (*OSThreadHandler)();

void OS_sched(void);
// how to keep track of crr and next
void OSInit_();

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSo, uint32_t stkSize); 

// context switch algo occurs at interrupt, but we cannot add it directly in it
// this is becayse the context swtich cannot be written in C, must be written in cpu specific assembly code
// needs to build specific stack frames and cpu stack point register

// ARM allows you to write context switch only in one nterrupt
// use the PendSV interrupt <-- but any other interrupts work


