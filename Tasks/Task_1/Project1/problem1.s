/* ELEC 335 Lab02 Problem 01
* Abdullah MEMİSOGLU 171024001
*/

.syntax unified
.cpu cortex-m0
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
.equ RCC_IOPENR, (RCC_BASE + (0x34)) // RCC IOPENR register offset
.equ GPIOA_BASE, (0x50000000) // GPIOA base address
.equ GPIOA_MODER, (GPIOA_BASE + (0x00)) // GPIOA MODER register offset
.equ GPIOA_ODR, (GPIOA_BASE + (0x14)) // GPIOA ODR register offset

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
// Configure the GPIOA for using PA pins.
ldr r1, =RCC_IOPENR
ldr r0, [r1]

movs r4, 0x1
orrs r0, r0, r4
str r0, [r1]


 ldr r7,= #3194888  // It is for delay function
 movs r6,r7			// R6 = 3194888 (1/313ns)
 loop_start:


 	subs r6, #1		// Substract 1 from R6 until R6 = 1
 	bne loop_start  // Waiting approx. 1 second in here

	ldr r1, =GPIOA_MODER
	ldr r0, [r1]

	ldr r4, =0x30000 // 3 instruction below here, clear bits that we are going to work on.
	mvns r4, r4
	ands r0, r0, r4
	/* For PA8 change the 16-17 bits into the GPIOx_MODER*/
	ldr r4, =0x10000 // Arrange the relevant bits as general purpose output mode.
	orrs r0, r0, r4
	str r0, [r1]     // Now led is lighting up.

	ldr r1, =GPIOA_ODR
	ldr r0, [r1]
	ldr r4,=0x100  // Arrange the relevant bit as enabled for PA8 port
	orrs r0, r0, r4
	str r0, [r1]


 	movs r6,r7      // R6 = 3194888
 	loop:
 		subs r6, #1 // Delay function
 		bne loop	// Waiting approx. 1 second in these instructions.


	ldr r1, =GPIOA_MODER
	ldr r0, [r1]


	ldr r4, =0xEBFFFFFF // Set the relevant bits as default
	orrs r0, r0, r4
	str r0, [r1]		// Led is extincting.

	ldr r1, =GPIOA_ODR
	ldr r0, [r1]
	ldr r4,=0x000000000 // Set the relevant bits as default
	orrs r0, r0, r4
	str r0, [r1]


	ldr r7,= #3194888  // Arrange the r7 register for another loop step.
	movs r6,r7
	b loop_start	   // Jump the loop_start loop and do every step again.


