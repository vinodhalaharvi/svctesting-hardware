/**
 * svc.c
 * Routines for supervisor calls
 *
 * ARM-based K70F120M microcontroller board
 *   for educational purposes only
 * CSCI E-92 Spring 2014, Professor James L. Frankel, Harvard Extension School
 *
 * Written by James L. Frankel (frankel@seas.harvard.edu)
 */

/*
 * Size of the supervisor call stack frame (no FP extension):
 *   No alignment => 32 (0x20) bytes
 *   With alignment => 36 (0x24) bytes
 *   
 * Format of the supervisor call stack frame (no FP extension):
 *   SP Offset   Contents
 *   +0			 R0
 *   +4			 R1
 *   +8			 R2
 *   +12		 R3
 *   +16		 R12
 *   +20		 LR (R14)
 *   +24		 Return Address
 *   +28		 xPSR (bit 9 indicates the presence of a reserved alignment
 *   				   word at offset +32)
 *   +32		 Possible Reserved Word for Alignment on 8 Byte Boundary
 *   
 * Size of the supervisor call stack frame (with FP extension):
 *   No alignment => 104 (0x68) bytes
 *   With alignment => 108 (0x6C) bytes
 *   
 * Format of the supervisor call stack frame (with FP extension):
 *   SP Offset   Contents
 *   +0			 R0
 *   +4			 R1
 *   +8			 R2
 *   +12		 R3
 *   +16		 R12
 *   +20		 LR (R14)
 *   +24		 Return Address
 *   +28		 xPSR (bit 9 indicates the presence of a reserved alignment
 *   				   word at offset +104)
 *   +32		 S0
 *   +36		 S1
 *   +40		 S2
 *   +44		 S3
 *   +48		 S4
 *   +52		 S5
 *   +56		 S6
 *   +60		 S7
 *   +64		 S8
 *   +68		 S9
 *   +72		 S10
 *   +76		 S11
 *   +80		 S12
 *   +84		 S13
 *   +88		 S14
 *   +92		 S15
 *   +96		 FPSCR
 *   +100		 Reserved Word for 8 Byte Boundary of Extended Frame
 *   +104		 Possible Reserved Word for Alignment on 8 Byte Boundary
 */

#include <derivative.h>
#include <stdio.h>
#include "svc.h"
#include "led.h"
#include "pushbutton.h"
#include "capacitivepads.h"
#include "potentiometer.h"


#define XPSR_FRAME_ALIGNED_BIT 9
#define XPSR_FRAME_ALIGNED_MASK (1<<XPSR_FRAME_ALIGNED_BIT)

struct frame {
	union {
		int r0;
		int arg0;
		int returnVal;
	};
	union {
		int r1;
		int arg1;
	};
	union {
		int r2;
		int arg2;
	};
	union {
		int r3;
		int arg3;
	};
	int r12;
	union {
		int r14;
		int lr;
	};
	int returnAddr;
	int xPSR;
};

#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCLedInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_LED_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCLedInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_LED_INIT));
}
#endif


#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCPushButtonInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_PUSHBUTTON_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCPushButtonInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_PUSHBUTTON_INIT));
}
#endif


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int __attribute__((naked)) __attribute__((noinline)) SVCPushButtonRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_PUSHBUTTON_READ));
	__asm("bx lr");
}
#pragma GCC diagnostic pop
#else
int __attribute__((never_inline)) SVCPushButtonRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_PUSHBUTTON_READ));
}
#endif


#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCCapacitivePadInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVEPAD_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCCapacitivePadInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVEPAD_INIT));
}
#endif
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int __attribute__((naked)) __attribute__((noinline)) SVCCapacitivePadRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVE_PAD_READ));
	__asm("bx lr");
}
#pragma GCC diagnostic pop
#else
int __attribute__((never_inline)) SVCCapacitivePadRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVE_PAD_READ));
}
#endif





#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCPotentiometerInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_POTENTIOMETER_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCPotentiometerInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_POTENTIOMETER_INIT));
}
#endif
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int __attribute__((naked)) __attribute__((noinline)) SVCPotentiometerRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVE_PAD_READ));
	__asm("bx lr");
}
#pragma GCC diagnostic pop
#else
int __attribute__((never_inline)) SVCPotentiometerRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_CAPACITIVE_PAD_READ));
}
#endif







#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCLedWrite(int argo, int arg1) {
	__asm("svc %0" : : "I" (SVC_LED_WRITE));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCLedWrite(int arg0, int arg1) {
	__asm("svc %0" : : "I" (SVC_LED_WRITE));
}
#endif



#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCUartInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_UART_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCUartInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_UART_INIT));
}
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int __attribute__((naked)) __attribute__((noinline)) SVCUartRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_UART_READ));
	__asm("bx lr");
}
#pragma GCC diagnostic pop
#else
int __attribute__((never_inline)) SVCUartRead(int arg0) {
	__asm("svc %0" : : "I" (SVC_UART_READ));
}
#endif


#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCUartWrite(int argo, int arg1) {
	__asm("svc %0" : : "I" (SVC_UART_WRITE));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCUartWrite(int arg0, int arg1) {
	__asm("svc %0" : : "I" (SVC_UART_WRITE));
}
#endif


#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCLcdcInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_LCDC_INIT));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCLcdcInit(int arg0) {
	__asm("svc %0" : : "I" (SVC_LCDC_INIT));
}
#endif


#ifdef __GNUC__
void __attribute__((naked)) __attribute__((noinline)) SVCLcdcWrite(int argo, int arg1) {
	__asm("svc %0" : : "I" (SVC_LCDC_WRITE));
	__asm("bx lr");
}
#else
void __attribute__((never_inline)) SVCLcdcWrite(int arg0, int arg1) {
	__asm("svc %0" : : "I" (SVC_LCDC_WRITE));
}
#endif


/* This function sets the priority at which the SVCall handler runs (See
 * B3.2.11, System Handler Priority Register 2, SHPR2 on page B3-723 of
 * the ARM�v7-M Architecture Reference Manual, ARM DDI 0403Derrata
 * 2010_Q3 (ID100710)).
 * 
 * If priority parameter is invalid, this function performs no action.
 * 
 * The ARMv7-M Architecture Reference Manual in section "B1.5.4 Exception
 * priorities and preemption" on page B1-635 states, "The number of
 * supported priority values is an IMPLEMENTATION DEFINED power of two in
 * the range 8 to 256, and the minimum supported priority value is always 0.
 * All priority value fields are 8-bits, and if an implementation supports
 * fewer than 256 priority levels then low-order bits of these fields are RAZ."
 * 
 * In the K70 Sub-Family Reference Manual in section "3.2.2.1 Interrupt
 * priority levels" on page 85, it states, "This device supports 16 priority
 * levels for interrupts.  Therefore, in the NVIC each source in the IPR
 * registers contains 4 bits."  The diagram that follows goes on to confirm
 * that only the high-order 4 bits of each 8 bit field is used.  It doesn't
 * explicitly mention the System Handler (like the SVC handler) priorities,
 * but they should be handled consistently with the interrupt priorities.
 * 
 * It is important to set the SVCall priority appropriately to allow
 * or disallow interrupts while the SVCall handler is running. */

void svcInit_SetSVCPriority(unsigned char priority) {
	if(priority > SVC_MaxPriority)
		return;

	SCB_SHPR2 = (SCB_SHPR2 & ~SCB_SHPR2_PRI_11_MASK) |
			SCB_SHPR2_PRI_11(priority << SVC_PriorityShift);
}

void svcHandlerInC(struct frame *framePtr);

/* Exception return behavior is detailed in B1.5.8 on page B1-652 of the
 * ARM�v7-M Architecture Reference Manual, ARM DDI 0403Derrata 2010_Q3
 * (ID100710) */

/* When an SVC instruction is executed, the following steps take place:
 * (1) A stack frame is pushed on the current stack (either the main or
 *     the process stack, depending on how the system is configured)
 *     containing the current values of R0-R3, R12, LR, the return
 *     address for the SVC instruction, xPSR, and, if appropriate, the
 *     floating point registers,
 * (2) An appropriate value is loaded into the LR register indicating
 *     that a stack frame is present on the stack (this will cause a
 *     special return sequence later when this value is loaded into
 *     the PC),
 * (3) Values of R0-R3 and R12 are no longer valid,
 * (4) The PC is set to the address in the interrupt vector table for
 * 	   the interrupt service routine for the SVC instruction,
 * (5) The processor switches to Handler mode (code execution in
 *     Handler mode is always privileged),
 * (6) The xPSR is set to indicate appropriate SVC state,
 * (7) The processor switches to the main stack by now using the main
 * 	   stack pointer.
 *     
 * These steps are discussed in detail in the pseudo-code given for
 * processor action ExceptionEntry() on page B1-643 of the ARM�v7-M
 * Architecture Reference Manual, ARM DDI 0403Derrata 2010_Q3
 * (ID100710).  ExceptionEntry() invokes PushStack() and
 * ExceptionTaken() on page B1-643. */

/* The following assembler function makes R0 point to the top-of-stack
 * for the stack that was current (either the main or the process stack)
 * before the SVC interrupt service routine began running.  This is
 * where the stack frame was stored by the SVC instruction.  Then, this
 * function calls the svcHandlerInC function.  Note that when a C
 * function is called, R0 contains the first parameter.  Therefore, the
 * first parameter passed to svcHandlerInC is a pointer to the
 * top-of-stack of the stack containing the stack frame. */


void svcHandlerInC(struct frame *framePtr) {
    unsigned minor_num; 
	printf("Entering svcHandlerInC\n");

	printf("framePtr = 0x%08x\n", (unsigned int)framePtr);

	/* framePtr->returnAddr is the return address for the SVC interrupt
	 * service routine.  ((unsigned char *)framePtr->returnAddr)[-2]
	 * is the operand specified for the SVC instruction. */
	printf("SVC operand = %d\n",
			((unsigned char *)framePtr->returnAddr)[-2]);

	switch(((unsigned char *)framePtr->returnAddr)[-2]) {
	case SVC_LED_INIT:
		printf("SVC LED INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = ledinit(minor_num); 
		break;
	case SVC_LED_WRITE:
		printf("SVC LED WRITE has been called\n");
		printf("parameters: %d %d\n", framePtr->arg0, framePtr->arg1);
        int ch = (unsigned) framePtr->arg0; 
        minor_num = framePtr->arg1;
        framePtr->returnVal = ledwrite(ch, minor_num); 
		break;
	case SVC_PUSHBUTTON_INIT:
		printf("SVC PUSHBUTTON INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = pushbutton_init(minor_num); 
		break;
	case SVC_PUSHBUTTON_READ:
		printf("SVC PUSHBUTTON WRITE has been called\n");
		printf("parameters: %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = pushbutton_read(minor_num); 
		break;
	case SVC_CAPACITIVEPAD_INIT:
		printf("SVC CAPACITIVEPAD INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = capacitivepad_init(minor_num); 
		break;
	case SVC_CAPACITIVEPAD_READ:
		printf("SVC CAPACITIVEPAD WRITE has been called\n");
		printf("parameters: %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = capacitivepad_read(minor_num); 
		break;
	case SVC_POTENTIOMETER_INIT:
		printf("SVC POTENTIOMETER INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = potentiometerpad_init(minor_num); 
		break;
	case SVC_POTENTIOMETER_READ:
		printf("SVC POTENTIOMETER WRITE has been called\n");
		printf("parameters: %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = potentiometerpad_read(minor_num); 
		break;
	case SVC_UART_INIT:
		printf("SVC UART INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = uart_init(minor_num); 
		break;
	case SVC_UART_WRITE:
		printf("SVC UART WRITE has been called\n");
		printf("parameters: %d %d\n", framePtr->arg0, framePtr->arg1);
        int ch = (unsigned) framePtr->arg0; 
        minor_num = framePtr->arg1;
        framePtr->returnVal = uart_write(ch, minor_num); 
		break;
	case SVC_UART_READ:
		printf("SVC UART WRITE has been called\n");
		printf("parameters: %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = uart_read(minor_num); 
		break;

	case SVC_LCDC_INIT:
		printf("SVC LCDC INIT has been called\n");
		printf("Only parameter is %d\n", framePtr->arg0);
        minor_num = (unsigned) framePtr->arg0; 
        framePtr->returnVal = lcdc_init(minor_num); 
		break;
	case SVC_LCDC_WRITE:
		printf("SVC LCDC WRITE has been called\n");
		printf("parameters: %d %d\n", framePtr->arg0, framePtr->arg1);
        int ch = (unsigned) framePtr->arg0; 
        minor_num = framePtr->arg1;
        framePtr->returnVal = lcdc_write(ch, minor_num); 
		break;

	default:
		printf("Unknown SVC has been called\n");
	}
	
	printf("Exiting svcHandlerInC\n");
}
