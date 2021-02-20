.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb



 /* make linker see this */



.global Reset_Handler




/* get these from linker script */
.word _sdata
.word _edata
.word _sbss
.word _ebss




.equ RCC_BASE, (0x40021000) // RCC base address
.equ RCC_IOPENR, (RCC_BASE + (0x34)) // RCC IOPENR address offset
.equ GPIOA_BASE, (0x50000000) // GPIOA base address
.equ GPIOA_MODER, (GPIOA_BASE + (0x00)) // GPIOA MODER address offset
.equ GPIOA_ODR, (GPIOA_BASE + (0x14)) // GPIOA ODR address offset



 /* vector table, +1 thumb mode */



.section .vectors
vector_table:
.word _estack /* Stack pointer */
.word Reset_Handler +1 /* Reset handler */
.word Default_Handler +1 /* NMI handler */
.word Default_Handler +1 /* HardFault handler */
 /* add rest of them here if needed */




 /* reset handler */
.section .text
Reset_Handler:
 /* set stack pointer */



ldr r0, =_estack
mov sp, r0



bl init_data



 /* call main */
bl main
 /* trap if returned */
b .



 /* initialize data and bss sections */
.section .text
init_data:



/* copy rom to ram */
ldr r0, =_sdata
ldr r1, =_edata
ldr r2, =_sidata
movs r3, #0
b LoopCopyDataInit




CopyDataInit:



 ldr r4, [r2, r3]
 str r4, [r0, r3]
 adds r3, r3, #4




LoopCopyDataInit:
 adds r4, r0, r3
 cmp r4, r1
 bcc CopyDataInit




/* zero bss */



 ldr r2, =_sbss
 ldr r4, =_ebss
 movs r3, #0
 b LoopFillZerobss



FillZerobss:



 str r3, [r2]
 adds r2, r2, #4




LoopFillZerobss:



 cmp r2, r4
 bcc FillZerobss




bx lr



 /* default handler */



 .section .text
 Default_Handler:
 b Default_Handler



 /* main function */
.section .text
main:

	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	// Configure the GPIOA for using PA pins.
	movs r4, 0x1
	orrs r5, r5, r4
	str r5, [r6]


	ldr r6, =GPIOA_MODER
	ldr r5, [r6]     // Clear the relevant bits with 3 instructions in below.
	ldr r4, =0xFFFF00
	mvns r4, r4
	ands r5, r5, r4
	//0101_0101_0101_0101_0000_0000 Arange the PA11-PA10-PA9-PA8-PA7-PA6-PA5-PA4 pins as general purpuse output mode
	ldr r4, =0x555500
	orrs r5, r5, r4
	str r5, [r6]
	loop:
		ldr r6, =GPIOA_ODR
		ldr r5, [r6]
		ldr r4,= 0xFF0 // 1111_1111_0000 Activate PA11-PA10-PA9-PA8-PA7-PA6-PA5-PA4
		orrs r5, r5, r4 // LEDs are lighting up
		str r5, [r6]

		ldr r1,= #3194888    // r1 = x/313ns ,x: How many seconds do you want to wait?
		delay:  // DELAY FUNCTION
			subs r1,r1,0x1
			cmp r1,0x0
			bne delay


		ldr r6, =GPIOA_ODR
		ldr r5, [r6]
		ldr r4,= 0x000  // LEDs are going off
		ands r5, r5, r4
		str r5, [r6]
		ldr r1,= #3194888
		delay_:  // DELAY FUNCTION
			subs r1,r1,0x1
			bne delay_
		b loop

/* for(;;); */



b .





/* this should never get executed */



nop
