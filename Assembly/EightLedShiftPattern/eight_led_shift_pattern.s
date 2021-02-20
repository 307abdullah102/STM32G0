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



/* define peripheral addresses from RM0444 page 57, Tables 3-4 */
.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR register offset

.equ GPIOA_BASE,       (0x50000000)          // GPIOA base address
.equ GPIOA_MODER,      (GPIOA_BASE + (0x00)) // GPIOA MODER register offset
.equ GPIOA_ODR,        (GPIOA_BASE + (0x14)) // GPIOA ODR register offset
.equ GPIOA_IDR,        (GPIOA_BASE + (0x10))

.equ GPIOB_BASE,       (0x50000400)          // GPIOB base address
.equ GPIOB_MODER,      (GPIOB_BASE + (0x00)) // GPIOB MODER register offset
.equ GPIOB_IDR,        (GPIOB_BASE + (0x10))


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

delay:
	subs r1, r1, #1
	bne delay
	bx lr


LeftShift:



	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x70
	bics r3, r3, r4
	str r3, [r0]

	bl t9
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x830
	bics r3, r3, r4
	str r3, [r0]

	bl t8
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xC10
	bics r3, r3, r4
	str r3, [r0]

	bl t7
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xE00
	bics r3, r3, r4
	str r3, [r0]

	bl t6
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x700
	bics r3, r3, r4
	str r3, [r0]

	bl t5
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x380
	bics r3, r3, r4
	str r3, [r0]

	bl t4
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x1C0
	bics r3, r3, r4
	str r3, [r0]

	bl t3
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xE0
	bics r3, r3, r4
	str r3, [r0]

	bl t2
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x70
	bics r3, r3, r4
	str r3, [r0]

	ldr r6, =GPIOB_IDR
	ldr r5, [r6]
	ldr r4, =0x1
	cmp r5, r4
	bne RightShift
	b LeftShift

ShiftControl:
	ldr r6, =GPIOB_IDR
	ldr r5, [r6]
	ldr r4, =0x1
	cmp r5, r4
	beq LeftShift
	bx lr

RightShift:

	ldr r2, =0x1

	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x70
	bics r3, r3, r4
	str r3, [r0]

	bl t2
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x70
	bics r3, r3, r4
	str r3, [r0]


	bl t3
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xE0
	bics r3, r3, r4
	str r3, [r0]

	bl t4
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x1C0
	bics r3, r3, r4
	str r3, [r0]


	bl t5
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x380
	bics r3, r3, r4
	str r3, [r0]

	bl t6
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x700
	bics r3, r3, r4
	str r3, [r0]

	bl t7
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xE00
	bics r3, r3, r4
	str r3, [r0]

	bl t8
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xC10
	bics r3, r3, r4
	str r3, [r0]

	bl t9
	ldr r1, =#319488
	bl delay
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x830
	bics r3, r3, r4
	str r3, [r0]
	bl ShiftControl

	b RightShift




t0:

	// LED1 lighting up
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0x10
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t1:
	//LED1-LED2 lighting up
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	ldr r4, =0x30
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t2:
	//LED1-LED2-LED3 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	ldr r4, =0x70
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t3:
	//LED2-LED3-LED4 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	lsls r4,r4,0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t4:
	//LED3-LED4-LED5 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	lsls r4,r4,0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t5:
	//LED4-LED5-LED6 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	lsls r4,r4,0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t6:
	//LED5-LED6-LED7 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	lsls r4,r4,0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t7:
	//LED6-LED7-LED8 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	lsls r4,r4,0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t8:
	//LED7-LED8-LED1 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	ldr r4, =0xC10//1100_0000_0001_0000
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

t9:
	//LED8-LED1-LED2 lighting up.
	ldr r0, =GPIOA_ODR
	ldr r3, [r0]

	ldr r4, =0x830
	orrs r3, r3, r4
	str r3, [r0]
	bx lr





/* main function */
.section .text
main:

	/* configure GPIOB and GPIOA clock,IOPENR */
	ldr r0, =RCC_IOPENR
	ldr r3, [r0]

	movs r4, 0x3 // 000..._0011(00_GPIOB_GPIOA)
	orrs r3, r3, r4
	str r3, [r0]


	ldr r0, =GPIOA_MODER
	ldr r3, [r0]
	ldr r4, =0xFFFF00
	mvns r4, r4
	ands r3,r3,r4
	ldr r4, =0x555500
	orrs r3, r3, r4
	str r3, [r0]


	ldr r0, =GPIOB_MODER
	ldr r3, [r0]

	ldr r4, =#0x3 //0000_0011 //PB0_INPUT DATA REGISTER
	mvns r4, r4
	ands r3, r3, r4
	str r3, [r0]


	bl t0


	ldr r1, =#319488
	bl delay

	bl t1




	ldr r1, =#319488
	bl delay

	b RightShift










