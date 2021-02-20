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
.equ GPIOA_IDR, (GPIOA_BASE+(0x10))
.equ GPIOA_PULL,(GPIOA_BASE+(0x0C))






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



    ldr r1, =RCC_IOPENR
    ldr r2, [r1]
   // Configure the GPIOA for PA pins
    movs r4, 0x1
    orrs r2, r2, r4
    str r2, [r1]


    ldr r1, =GPIOA_MODER
    ldr r2, [r1]
    ldr r4, =0xF
    mvns r4, r4
    ands r2, r2, r4
    ldr r4, =0x4 //0000_..._0100
	orrs r2, r2, r4
    str r2, [r1]


    loop:
        ldr r1, =GPIOA_ODR
        ldr r2, [r1]
        ldr r4,= 0x0
        ands r2, r2, r4
        str r2, [r1]



        ldr r0,=GPIOA_IDR
        ldr r1,[r0]
        movs r5, 0x0001
        ands r1, r1, r5
        ldr r2,=0x1
        cmp r1,r2
        beq button
        b  loop

	button:
        ldr r1, =GPIOA_ODR
        ldr r2, [r1]
        ldr r4,= 0x2
        orrs r2, r2, r4
        str r2, [r1]
        b  loop


/* for(;;); */





b .







/* this should never get executed */





nop



