#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mi_syscall.h"
#include "hardware.h"

struct tlb_entry_s tlbe;
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

static int ppage_of_vaddr(int process, unsigned int vaddr){
        unsigned int vpage = vpage_of_vaddr(vaddr);
        unsigned int ppage;
	if(vaddr > ((int)virtual_memory + VM_SIZE - 1)){
		return -1;
	}
	if((vpage<0 || vpage>N/NB_PROCESS)){
		return -1;
	}

        ppage = vpage + 1 + (process* N/NB_PROCESS);
        return ppage;
}
// -----------------------------------------

// Fonction handler
// -----------------------------------------
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
