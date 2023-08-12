
; ********************************************
; * Parcial II - Arquitectura del Computador *
; * Universidad Católica Andrés Bello        *
; * Arturo Hung - C.I: 29 621 867            *
; * Profesor: Manuel Peña                    *
; ********************************************

	LIST P = 16F84A                                    ;  PIC16F84A
    #INCLUDE P16f84a.inc                               ;  Libreria          
	__CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC  ;  Configuración por defecto

	; _CP_OFF     Protección del código
	; _WDT_OFF    Watchdog apagado
	; _PWRTE_ON   Retraso al reses activado
	; _XT_OSC     Oscilador de cristal de cuarzo 

	RADIX DEC    ; Sistema de Numeración Decimal

;***** Declaración de variables *****

STATUS  	EQU 	03H 	; Registro 'STATUS'
PUERTOA 	EQU 	05H 	; PUERTOA declarado en la dirección 05 H
PUERTOB 	EQU 	06H 	; PUERTOB declarado en la dirección 06 H
OPER_A		EQU		0x0C	; Primer operando 
OPER_B		EQU		0x0D	; Segundo operando
RESULT		EQU		0x0E	; Resultado
COUNTER     EQU     0x0F    ; Contador

;reset 
	org  0x00                    ; Vector de inicio del programa       
	goto INICIO                  ; Salto a inicio
	org  0x05                    ; Vector de interrupción

;***** Cuerpo del programa *****

INICIO  ; Invocación de inicio

		bsf STATUS,5             ; Cambio a banco 1 (memoria)
		movlw B'11100011'        ; Cargar W con el valor indicado, habilitar tres (3) salidas
		movwf PUERTOB            ; Mover el valor de W en el puerto B
		movlw B'00000111'        ; Cargar W con el valor indicado, habilita tres (3) entradas
		movwf PUERTOA            ; Mover el valor de W en el puerto A
		bcf STATUS,5             ; Cambio a banco 0 (memoria)
		goto COMPROBAR_OPER      ; Salto a COMPROBAR_OPER

OPERANDOS ; Configuración de puertos 

		clrf  OPER_A			 ; Limpieza del operando A
		btfsc PUERTOA,0    		 ; Asignación del bit A0 al operando 1
		bsf   OPER_A,0           ; Colocación en 0
		btfsc PUERTOA,1          ; Asignación del bit A1 al operando 1
		bsf   OPER_A,1 		     ; Colocación en 1
		btfsc PUERTOA,2          ; Asignación del bit A2 al operando 1
		bsf   OPER_A,2      	 ; Colocación en 2
	
		clrf  OPER_B             ; Limpieza del operando B
		btfsc PUERTOB,7          ; Asignación del bit B0 al operando 2
		bsf   OPER_B,0           ; Colocación en 0
		btfsc PUERTOB,6          ; Asignación del bit B1 al operando 2
		bsf   OPER_B,1        	 ; Colocación en 1
		btfsc PUERTOB,5          ; Asignación del bit B2 al operando 2
		bsf   OPER_B,2  		 ; Colocación en 2
		return                   ; Retorno desde la invocación
	
COMPROBAR_OPER ; Selección de operaciones - Condiciones

	    btfss PUERTOB,0			  ; S0 = 1 - La operación es suma o división
		call  RESTA_MULT        
		btfsc PUERTOB,0		 	  ; S0 = 0 - La operación es resta o multiplicación
		call  SUMA_DIV          
		goto  COMPROBAR_OPER      ; Salto a COMPROBAR_OPER

RESTA_MULT ; Definir si es 10 (Resta) o 00 (Multiplicación)

	    btfss PUERTOB,1            ; Verificar existencia de uno lógico en el puerto,  salto a la siguiente instrucción
	    call  MULTIPLICACION       ; Invocación a RESTA
		btfsc PUERTOB,1            ; Verificar existencia de cero (0) lógico en el puerto, salto a la siguiente instrucción
	    call  RESTA                ; Invocación a MULTIPLICACION
		return		               ; Retorno a COMPROBAR_OPER

SUMA_DIV ; Definir si es 01 (Suma)

	    btfss PUERTOB,1            ; Existencia de uno (1) lógico en el puerto
	    call  SUMA                 ; Invocación a SUMA
		return                     ; Retorno a comprobar operación

;***** Operaciones aritméticas *****

SUMA    ; Operación de suma de números de tres (3) bits

		call  OPERANDOS	           ; Se asignan los valores a los operandos
		clrw					   ; Borrado de W
	    movf  OPER_A, 0 		   ; Mover el contenido del operando A a W
	    addwf OPER_B, 0		       ; W + OPERB, guardado de la operacion en W
		movwf RESULT		       ; Mover el contenido de W a Resultado
		
		btfss RESULT, 3			   ; Muestra si existe acarreo
		bcf   PUERTOB,3            ; Puesta en 0 del bit del pin RA3 del puerto B
		btfsc RESULT, 3            ; Testeo del bit RA3 en RESULT, salto si es 0
		bsf   PUERTOB,3            ; Puesta en 1 del bit del pin RA3 del puerto B
		
		call IMPRIMIR			  ; Invocación a IMPRIMIR
		return	 				  ; Retorno a SUMA_DIV

MULTIPLICACION ; Operación de multiplicación de números de tres (3) bits

		call  OPERANDOS           ; Llamada a operandos
		movf  OPER_B,0            ; Mover el contenido de f
		movwf COUNTER             ; Movel el contenido de f en la variable de contador
		clrw
	
BUCLE   ; Lazo/Ciclo

		addwf  OPER_A, 0 	  	  ; Sumatoria OPERA, se guarda en W
	    decfsz COUNTER,1	      ; Se produce un salto si COUNTER = 0
		goto   BUCLE              ; Salto a bucle
		movwf  RESULT             ; Mover el contenido de W a la variable de resultado
		btfss  RESULT, 3	      ; Muestra si hubo acarreo
		bcf    PUERTOB,3          ; Limpiar bit de RA3
		btfsc  RESULT,3           ; Testeo del bit 3 en RESULT, salto si es 0
		bsf    PUERTOB,3          ; Puesta en 1 del bit 3 en el puerto B
		call   IMPRIMIR           ; Invocación a IMPRIMIR
		return

RESTA   ; Operación de resta de números de tres (3) bits

		call   OPERANDOS          ; Invocación a operandos
		movf   OPER_B, 0          ; Mover f a OPER_B
	   	SUBWF  OPER_A, 0		  ; OPERA-W, se guarda en W	
		movwf  RESULT	          ; Mover el contenido de W a RESULT

;***** Asignación del bit signo negativo a CDS (bandera de carry se pone en cero si es negativo el resultado) *****
						          
	   	btfsc  STATUS, 0          ; Si es cero (0) salta
		bcf	   PUERTOB,3  	 	  ; Limpiar bit de RA3
		btfss  STATUS, 0	 	  ; Si B es menor o igual que A salta   
		call   B_Mayor	          ; Invocación a B_Mayor
	
		call   IMPRIMIR           ; Invocación a IMPRIMIR
		return                    ; Retorno de la subrutina

B_Mayor ; Comprobación del número mayor para el muestreo de acarreo de signo

		movf   OPER_A, 0          ; Mover f a OPER_A
	   	SUBWF  OPER_B, 0		  ; OPER_A - W, guardado en W	
		movwf  RESULT	          ; Mover el contenido de W a la variable de resultado
		bsf    PUERTOB,3	      ; Asignación del bit signo negativo a CDS (bandera de carry se pone en cero si es negativo el resultado)
		return                    ; Retorno de la subrutina
	
IMPRIMIR ; Impresión del resultado

		btfss RESULT,0            ; Asignación del bit 0 del resultado a D0
		bcf   PORTA, 3        
		btfsc RESULT,0     
		bsf   PORTA, 3	  	
		btfss RESULT,1            ; Asignación del bit 1 del resultado a D1
		bcf   PORTB, 2        
		btfsc RESULT,1     
		bsf   PORTB, 2	
		btfss RESULT,2            ; Asignación del bit 2 del resultado a D2
		bcf   PORTB, 4        
		btfsc RESULT,2     
		bsf   PORTB, 4	
		return				      ; Retorna a la operación

FIN ; Fin del programa

		end						  
