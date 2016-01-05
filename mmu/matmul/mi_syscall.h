#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#define HW_CONFIG "hardware.ini"


#define SYSCALL_SWITCH_0 16
#define SYSCALL_SWITCH_1 17


#define PAGE_SIZE 4096
#define PM_PAGES 256		
#define VM_PAGES 4096
#define PM_SIZE PM_PAGES * PAGE_SIZE	
#define VM_SIZE VM_PAGES * PAGE_SIZE
#define N 254 // 20 ?
#define NB_PROCESS 2


	

extern unsigned int current_process;

struct tlb_entry_s{
        unsigned int tlb_name  :8;
        unsigned int tlb_vpage :12;
        unsigned int tlb_ppage :8;
        unsigned int tlb_acces :3;
        unsigned int tlb_valid :1;
};

void init_user();

#endif
