#ifndef MMU_MANAGER_H
#define MMU_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"
#include "swap.c"
#include "hw_config.h"

struct tlb_entry_s tlbe;

/* for mmu_handler1 */
int current_vpage = -1;

/* for mmu_handler2 */
int rr_ppage = 1;
struct pm_mapping_s pm_mapping[PM_PAGES];
struct vm_mapping_s vm_mapping[VM_PAGES];

extern void user_process();

#endif
