#include <xc.inc>
;GLOBAL _addTest        ; make _add globally accessible
GLOBAL _fw_content_T


;SIGNAT _addTest,4217   ; tell the linker how it should be called
SIGNAT _fw_content_T,4218
; everything following will be placed into the mytext psect
PSECT mytext,local,class=STRING,delta=2,reloc=2;CODE;STRING;reloc=2;EEDATA
; our routine to add to ints and return the result
ORG 9ah
_fw_content_T: Dw 269ah
;TABLE:	DW 12H;RETLW 41H	
;_fw_content_T_ DW 1234h,2,3,4
;_addTest:
;TABLE1:	DB 12H
; W is loaded by the calling function;
;BANKSEL (PORTB) ; select the bank of this object
;ADDWF BANKMASK(PORTB),w ; add parameter to port
;MOVWF BANKMASK(PORTB),w ; add parameter to port
;MOVLW 50H
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;BANKSEL NVMADRL ; Select Bank for NVMCON registers
;MOVLW 11H ; 
;MOVWF NVMADRL ; Store LSB of address
;MOVLW 25H ; 
;MOVWF NVMADRH ; Store MSB of address
 
;BCF NVMCON1,1 ; Do not select Configuration Space
;BSF NVMCON1,1 ; Initiate read
;MOVF NVMDATL,W ; Get LSB of word
;MOVWF PROG_DATA_LO ; Store in user location
;MOVF NVMDATH,W ; Get MSB of word
;MOVWF PROG_DATA_HI ; Store in user location

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;BANKSEL NVMADRH
;MOVLW 11H
;MOVWF FSR0L
;MOVLW 25H
;MOVWF FSR0H
;MOVFW foobar;
;MOVWI [6]FSR0

;MOVIW [6]FSR0
;MOVF w,FSR0
;MOVWF ADDFSR,w
;TABLE RETLW 50h
;TABLE1 DW 1234h,2,3,4
; the result is already in the required location (W)so we can
; just return immediately
RETURN

;_ReadNV:
;BANKSEL NVMADRL ; Select Bank for NVMCON registers
;MOVLW PROG_ADDR_LO ; 
;MOVWF NVMADRL ; Store LSB of address
;MOVLW PROG_ADDR_HI ; 
;MOVWF NVMADRH ; Store MSB of address
 
;BCF NVMCON1,NVMREGS ; Do not select Configuration Space
;BSF NVMCON1,RD ; Initiate read
;MOVF NVMDATL,W ; Get LSB of word
;MOVWF PROG_DATA_LO ; Store in user location
;MOVF NVMDATH,W ; Get MSB of word
;MOVWF PROG_DATA_HI ; Store in user location
;RETURN

;PSECT absdata,abs,ovrld
;PSECT mydata,local,class=DATA,delta=2
;ORG 50h
