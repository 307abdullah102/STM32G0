/* ELEC 335 Proje01 Problem 01
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

.equ GPIOB_BASE, (0x50000400) // GPIOA base address
.equ GPIOB_MODER, (GPIOB_BASE + (0x00)) // GPIOB MODER register offset
.equ GPIOB_ODR, (GPIOB_BASE + (0x14)) // GPIOB ODR register offset
.equ GPIOA_IDR, (GPIOA_BASE+(0x10)) //GPIOB IDR register offset
.equ GPIOA_PULL,(GPIOA_BASE+(0x0C))



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


Digit_1:	//Activating the first of 4 digits to write a number

	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x1
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

Digit_2:	//Activating the second of 4 digits to write a number

	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x2
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

Digit_3:	//Activating the third of 4 digits to write a number

	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x10
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

Digit_4:	//Activating the last of 4 digits to write a number


	ldr r0, =GPIOA_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x20
	orrs r3, r3, r4
	str r3, [r0]
	bx lr

One:		//Setting Output data register to write the number 1
 // B=C=0, A=D=E=F=G=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x3C8 //PB3-6-7-8-9 0011_1100_1000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Two:		//Setting Output data register to write the number 2
 // A=B=G=E=D=0, C=F=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x120 // PB5-8  0001_0010_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Three:		//Setting Output data register to write the number 3
// A=B=G=C=D=0, E=F=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x180 // PB7-8  0001_1000_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1


Four:		//Setting Output data register to write the number 4
// F=B=G=C=0 A=D=E=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0xC8 // PB3-6-7 0000_1100_1000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Five:		//Setting Output data register to write the number 5
//A=F=G=C=D=0 B=E=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x90 // PB4-7 0000_1001_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Six:		//Setting Output data register to write the number 6
//A=F=G=C=E=D=0 B=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x10 // PB4 0000_0001_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Seven:		//Setting Output data register to write the number 7
//A=B=C=0 D=E=F=G=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x3C0 // PB6-7-8-9 0011_1100_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Eight:		//Setting Output data register to write the number 8
//A=B=C=D=E=F=G=0
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x0 // All of them
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

Nine:		//Setting Output data register to write the number 9
//A=B=C=D=F=G=0 E=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x80 // PB7 0000_1000_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1
Zero:		//Setting Output data register to write the number 0
//A=B=C=D=E=F=0 G=1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x200 // PB9 0010_0000_0000
	orrs r3, r3, r4
	str r3, [r0]
	pop {r1}
	bx r1

delay:
	subs r1, r1, #1
	bne delay
	bx lr


LedControl:		//lighting up numbers based on the value in the counter register
	push {lr}
	cmp r1, #1
	beq One


	cmp r1,# 2
	beq Two

	cmp r1, #3
	beq Three

	cmp r1,#4
	beq Four

	cmp r1, #5
	beq Five

	cmp r1,#6
	beq Six

	cmp r1, #7
	beq Seven

	cmp r1,#8
	beq Eight

	cmp r1, #9
	beq Nine

	cmp r1,#0
	beq Zero

	bx lr




 /* main function */
.section .text
main:

    ldr r1, =RCC_IOPENR
    ldr r2, [r1]
   // Configure the GPIOA-B for PA-B pins
    movs r4, 0x3
    orrs r2, r2, r4
    str r2, [r1]
    ldr r1, =GPIOA_MODER
    ldr r2, [r1]
    ldr r4, =0xFFFF
    mvns r4, r4
    ands r2, r2, r4
    ldr r4, =0x1505 //0001_0101_0000_0101
	orrs r2, r2, r4
    str r2, [r1]

    ldr r1, =GPIOB_MODER
    ldr r2, [r1]
    ldr r4, =0xFFFFF
    mvns r4, r4
    ands r2, r2, r4
    ldr r4, =0x55540 //0000_0101_0101_0101_0100_0000
	orrs r2, r2, r4
    str r2, [r1]


	ldr r2, =#500 // Aprrox. 1 sec
	ZeroLoop:		//loop for lighting 0000 for 1 second before pressing id when the circuit is powered up
	 bl Digit_1
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

     ldr r1, =#3149
     bl delay
     bl Digit_2
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

     ldr r1, =#3149
	 bl delay
	 bl Digit_3
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

	 ldr r1, =#3149
	 bl delay
	 bl Digit_4
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

	 ldr r1, =#3149
	 bl delay

	 subs r2, r2, #1
	 cmp r2, 0x1
	 bne ZeroLoop
	 b InfLoop

 ldr r2, =#0 // Initial value for random number generation

   InfLoop: //Endless loop printing the ID until the button is pressed


    bl Digit_1     // DIGIT1 --> 4
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0xC8 // PB3-6-7 0000_1100_1000
	orrs r3, r3, r4
	str r3, [r0]

     ldr r1, =#3149
     bl delay
     bl Digit_2	//	 DIGIT2 --> 0
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

     ldr r1, =#3149
	 bl delay
	 bl Digit_3		// DIGIT3 --> 0
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

	 ldr r1, =#3149
	 bl delay
	 bl Digit_4		// DIGIT4 --> 1
	ldr r0, =GPIOB_ODR
	ldr r3, [r0]
	ldr r4, =0xFFFF
	mvns r4, r4
	ands r3, r3, r4
	ldr r4, =0x3C8 //PB3-6-7-8-9 0011_1100_1000
	orrs r3, r3, r4
	str r3, [r0]

	 ldr r1, =#3149
	 bl delay
//Random number generated with the time before pressing the button
	 adds r2,r2,#1
	 movs r7,r2 //random number from 1000 to 9999 for countdown R7=MYRANDOMNUMBER

	 ldr r0,=GPIOA_IDR
     ldr r1,[r0]
     ldr r0,=#24744 // if button pressed then r1 24744
     cmp r1,r0
     beq FindPlaceLoop


	 b InfLoop


FirstDigitZero: //light up zero on first digit
	 bl Digit_1
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]
	 b HundredControl

SecondDigitZero://light up zero on second digit
	 bl Digit_2
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]
	 b TensControl

ThirdDigitZero: //light up zero on third digit
	 bl Digit_3
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]
	 b UnitControl

FindPlaceLoop: //the FindPlaceLoop creates a wait time for 4 digits and decreases the random number for the countdown

	 ldr r0,=GPIOA_IDR
     ldr r1,[r0]
     ldr r2,=#0 // if button pressed then r1 24744
     ands r1,r1,r2
	movs r6, #2
	subs r7,r7,#1
	FindPlaceValue:	//the FindPlaceValue loop determines which number will be light up in which digit.
		ldr r1,=#0 //Counter
		movs r5,r7
		subs r6,r6,#1

		ldr r2,= #1000
		cmp r5,r2
		blt FirstDigitZero // Check if the thousands of number digit is zero then First Digit is zero.
		ThousandsPlace:		//finds the number in thousands
			ldr r2,= #1000
			subs r5,r5,r2
			adds r1,r1,#1 //counter++
			cmp r2,r5
			blt ThousandsPlace
			LightDigit1:	//Lighting up the number in thousands on the first digit
				bl Digit_1
				bl LedControl



		HundredControl: // Check if the hundreds digit of number is zero then Second Digit is zero.

			ldr r1,=#350
			bl delay
			ldr r1,=#0
			ldr r2,= #100
			cmp r5,r2
			blt SecondDigitZero
		HundredPlace: //finds the number in hundreds
			ldr r2,= #100
			subs r5,r5,r2
			adds r1,r1,#1
			cmp r2,r5
			blt HundredPlace
			LightDigit2: //Lighting up the number in hundreds on the second digit
				bl Digit_2
				bl LedControl
				ldr r1,=#650
				bl delay



		TensControl: // Check if the tens digit of number is zero then Second Digit is zero.
			ldr r1,=#350
			bl delay
			ldr r1,=#0
			ldr r2,= #10
			cmp r5,r2
			blt ThirdDigitZero
		TensPlace: //finds the number in tens

			ldr r2,= #10
			subs r5,r5,r2
			adds r1,r1,#1
			cmp r2,r5
			blt TensPlace


			LightDigit3: //Lighting up the number in hundreds on the third digit
				bl Digit_3
				bl LedControl
			UnitControl:
				ldr r1,=#350
				bl delay
				movs r1, r5
 // Since the remaining number after the thousands and hundreds and tens digits are zeroed will be the units digit, it is written directly to the fourth digit.

			bl Digit_4
			bl LedControl
			ldr r1,=#350
			bl delay
			cmp r6,#0
			bne FindPlaceValue
			cmp r7, #0
			bne FindPlaceLoop
			b FourDigitZero
FourDigitZero:
	// countdown is complete
	bl Digit_1
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

     ldr r1, =#3149
     bl delay
     bl Digit_2
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

     ldr r1, =#3149
	 bl delay
	 bl Digit_3
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

	 ldr r1, =#3149
	 bl delay
	 bl Digit_4
     ldr r0, =GPIOB_ODR
	 ldr r3, [r0]
	 ldr r4, =0xFFFF
	 mvns r4, r4
	 ands r3, r3, r4
	 ldr r4, =0x200 // PB9 0010_0000_0000
	 orrs r3, r3, r4
	 str r3, [r0]

	 ldr r1, =#3149
	 bl delay
//turn on the led when the countdown is complete
	 ldr r1, =GPIOA_ODR
     ldr r2, [r1]
     ldr r4,= 0x40
     orrs r2, r2, r4
     str r2, [r1]

	 b FourDigitZero




