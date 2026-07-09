#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

/* Defined by the linker script */
extern char end;      /* End of .bss */
extern char _estack;  /* Top of RAM */

/* Current heap end */
static char* heap_end = NULL;

int _close(int file)
{
    (void)file;
    errno = EBADF;
    return -1;
}

int _fstat(int file, struct stat* st)
{
    (void)file;

    if (st != NULL)
    {
        st->st_mode = S_IFCHR;
    }

    return 0;
}

int _isatty(int file)
{
    (void)file;
    return 1;
}

off_t _lseek(int file, off_t offset, int whence)
{
    (void)file;
    (void)offset;
    (void)whence;
    return 0;
}

int _read(int file, void* ptr, size_t len)
{
    (void)file;
    (void)ptr;
    (void)len;

    errno = EBADF;
    return -1;
}

int _write(int file, const void* ptr, size_t len)
{
    (void)file;
    (void)ptr;

    /*
     * TODO:
     *  - SEGGER RTT
     *  - UART
     *  - ITM/SWO
     */
    return (int)len;
}

void* _sbrk(ptrdiff_t incr)
{
    if (heap_end == NULL)
    {
        heap_end = &end;
    }

    char* prev_heap_end = heap_end;

    if ((heap_end + incr) > &_estack)
    {
        errno = ENOMEM;
        return (void*)-1;
    }

    heap_end += incr;

    return prev_heap_end;
}

void _exit(int status)
{
    (void)status;

    while (1)
    {
    }
}

int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;

    errno = EINVAL;
    return -1;
}

int _getpid(void)
{
    return 1;
}
