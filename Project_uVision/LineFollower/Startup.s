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
			END