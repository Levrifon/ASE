#ifndef _SWAP_H_
#define _SWAP_H_

#include "mi_syscall.h"

struct vm_mapping_s{
        unsigned vm_ppage:8;
        unsigned vm_allocate:1;
};

struct pm_mapping_s{
        unsigned pm_vpage:12;
        unsigned pm_allocate:1;
};

char init_swap(const char *path);
char store_to_swap(int vpage, int ppage);
char fetch_from_swap(int vpage, int ppage);

#endif
