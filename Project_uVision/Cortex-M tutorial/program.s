RCC			EQU	0x40021000		
RCC_APB2ENR	EQU RCC + 0x18		
PORTC_BASE	EQU	0x40011000
GPIOC_CRL	EQU PORTC_BASE
GPIOC_CRH	EQU PORTC_BASE + 0x04
GPIOC_IDR	EQU PORTC_BASE + 0x08
GPIOC_ODR	EQU PORTC_BASE + 0x0C
GPIOC_BSRR	EQU PORTC_BASE + 0x10
GPIOC_BSR	EQU PORTC_BASE + 0x14
GPIOC_LCKR	EQU	PORTC_BASE + 0x18
			
			AREA RESET, DATA, READONLY				;Define a AREA called RESET of type DATA and READONLY
		
			EXPORT __Vectors
		
__Vectors	DCD 0x20002000
			DCD Reset_Handler
			
			ALIGN
			
			AREA |.text|, CODE, READONLY, ALIGN=2
			THUMB

			EXPORT		Reset_Handler
			
Reset_Handler    
               
;---------------------branches to main in C file---------------------------			   
			IMPORT  main
    
            LDR     R0, =main
            BX      R0
;-------------------------------------------------------------------------

			
			
			BL		GPIOF_Init
			
loop
			BL		LIGHT_ON
			BL		LIGHT_OFF
FIM			B		loop
			
GPIOF_Init
			LDR R1, =RCC_APB2ENR
			LDR R0, [R1]
			ORR R0, R0, #0x10
			STR R0, [R1]
			NOP
			NOP
			LDR R1, =GPIOC_CRH
			LDR R0, [R1]
			ORR R0, R0, #0x00700000
			AND R0, R0, #0xFF3FFFFF
			STR R0, [R1]
			
			BX	LR
			
LIGHT_OFF
			LDR	R1, =GPIOC_BSRR
			LDR R0, [R1]
			ORR R0, R0, #0x2000
			STR R0, [R1]
			BX	LR
			
LIGHT_ON
			LDR	R1, =GPIOC_ODR
			LDR R0, [R1]
			AND R0, R0, #0xFFFFDFFF
			STR R0, [R1]
			BX	LR
			
			ALIGN
			END

					