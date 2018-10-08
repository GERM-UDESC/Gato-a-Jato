			AREA RESET, DATA, READONLY				;Define a AREA called RESET of type DATA and READONLY
		
			EXPORT __Vectors						;I'm still have to know why do I have to call it like that
		
__Vectors	DCD 0x20002000							;The first adress of the stack
			DCD Reset_Handler						;The adress of Reset_Handler
			
			ALIGN
			
			AREA |.text|, CODE, READONLY, ALIGN=2	;Define a AREA called .text of tipe CODE and READONLY
			THUMB									;Uses only thumb mode (16 bits instructions)

			EXPORT		Reset_Handler				;Make the reset_handler callable by C functions
			
Reset_Handler    									;Reset_Handler label
               
;---------------------branches to main in C file---------------------------			   
			IMPORT  main							;Import the adress of function main in the C file main
    
            LDR     R0, =main						;Put the adress of main into the R0
            BX      R0								;Branch to the adress pointed by R0, which is the adress of main()
;-------------------------------------------------------------------------
			END										;It is needed by compiler