#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hw_config.h"
#include "mi_syscall.h"
#include "hardware.h"
#include "swap.h"

struct tlb_entry_s tlbe;
struct vm_mapping_s vm_mapping[VM_PAGES];
struct pm_mapping_s pm_mapping[PM_PAGES];
unsigned int rr_page;
unsigned int current_process;


// Fonctions d'interruption
// -----------------------------------------
static void switch_to_process0(void){
        current_process = 0;
        _out(MMU_CMD, MMU_RESET);
}

static void switch_to_process1(void){
        current_process = 1;
        _out(MMU_CMD, MMU_RESET);
}
// -----------------------------------------

// Fonction utilitaires
// -----------------------------------------
static int vpage_of_vaddr(unsigned int vaddr){
        return (vaddr>>12)&0xFFF;
}

static int ppage_of_vaddr(int process, unsigned int vaddr) {
	unsigned int ppage = -1;
	unsigned int vpage = (vaddr >> 12) & 0xfff;
	if((unsigned int) virtual_memory <= vaddr && vaddr < (unsigned int) virtual_memory + VM_SIZE && vpage < N/2) {
		if(current_process == 0)
			ppage = vpage +1;
		if(current_process ==1)
			ppage = vpage +1 + (N/2);
	}
	return ppage;
}
// -----------------------------------------

// Fonction handler
// -----------------------------------------
//OLD VERSION
static void mmu_handler(void){
	int ppage, vaddr;

	vaddr=_in(MMU_FAULT_ADDR);
	ppage=ppage_of_vaddr(current_process,vaddr);
	if(ppage==-1){
		fprintf(stderr,"Erreur de segmentation à cause de ppage\n");
		exit(EXIT_FAILURE);
	}else{
		tlbe.tlb_vpage = vpage_of_vaddr(vaddr);
		tlbe.tlb_ppage = ppage;
		tlbe.tlb_acces = 7;
		tlbe.tlb_valid = 1;
		_out(TLB_ADD_ENTRY,*((int *)&tlbe));
	}
}
/*
static void mmu_handler(void) {
	int f_vaddr,f_vpage;
	f_vaddr = _in(MMU_FAULT_ADDR);
	f_vpage = vpage_of_vaddr(f_vaddr);
	
	tlbe.tlb_ppage = rr_page;
	
	
	/* Si vpage deja allocated 
	if (vm_mapping[f_vpage].vm_allocate) {
		/* On change la tlb 
                tlbe.tlb_vpage = f_vpage;        
                tlbe.tlb_ppage = vm_mapping[f_vpage].vm_ppage;
	        tlbe.tlb_valid=1;
                _out(TLB_ADD_ENTRY, *(int*)&tlbe);
	}else{
	        /* Si rr_page dans pm_mapping deja allocated 
	        if(pm_mapping[rr_page].pm_allocate) {
	                /* On vide dans la swap 
		        store_to_swap(pm_mapping[rr_page].pm_vpage,rr_page);
		        pm_mapping[rr_page].pm_allocate = 0;
		        vm_mapping[pm_mapping[rr_page].pm_vpage].vm_allocate=0;
		        tlbe.tlb_ppage = rr_page;
		        _out(TLB_DEL_ENTRY,*(int*)&tlbe);
	        }
	        if(fetch_from_swap(f_vpage,rr_page)==-1){
	                //erreur
	        }
	        
		/* on pointe sur la prochaine page qu'on peut mapper 
		vm_mapping[f_vpage].vm_ppage = rr_page;
		vm_mapping[f_vpage].vm_allocate = 1;
		pm_mapping[rr_page].pm_vpage = f_vpage;
		pm_mapping[rr_page].pm_allocate = 1;
	        
	        Maj TLB 
	        tlbe.tlb_vpage = f_vpage;
	        tlbe.tlb_ppage = rr_page;
	        tlbe.tlb_acces = 7;
	        tlbe.tlb_valid = 1;
	        _out(TLB_ADD_ENTRY,*(int*)&tlbe);
	        
	        
		 Maj du round robin 
		rr_page=(rr_page%(PM_PAGES-1))+1;
        }
	
}*/
// -----------------------------------------


// Main
int main(int argc, char **argv){
        void *ptr;

        assert(init_hardware("hardware.ini") !=0);
        IRQVECTOR[MMU_IRQ] = mmu_handler;
        IRQVECTOR[SYSCALL_SWITCH_0] = switch_to_process0;
        IRQVECTOR[SYSCALL_SWITCH_1] = switch_to_process1;
        _mask(0x1001);
        init_user(ptr);
        return 0;
}
