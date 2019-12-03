; Vector3 assembly implementation - Computer Architecture Final Project
; MASM
; Walter Hill 11/26/19

.686
.MODEL FLAT, C
.STACK 4096

_printMagnitude PROTO C	; Protoype for display
_printVector3 PROTO C	; Protoype for display

.DATA				 ; Data segment, including .bss
; Vector A
xx REAL4 0.6
yy REAL4 -0.8
zz REAL4 0.0

; Vector B
aa REAL4 2.0
bb REAL4 -4.0
cc REAL4 1.0

crossX REAL4 0.0
crossY  REAL4 0.0
crossZ REAL4 0.0
vectorResult REAL4 0.0


.CODE			; start of code segment

; ===============================
; float Vector3::getMagnitude()
; ===============================

_asmMagnitude PROC C	; assembly main() - called from cpp file		
	fld xx
	fmul st(0), st(0)	; square it
	fld yy
	fmul st(0), st(0)
	fld zz
	fmul st(0), st(0)
	
	fadd st(0), st(1)
	fadd st(0), st(2)
 	fsqrt
	fstp vectorResult

	ret						; exits _asmMagnitude() and returns to main() in the cpp file

_asmMagnitude ENDP	; End of _asmMagnitude() function


; ===============================
; Vector3::cross(Vector3 a, Vector3 b)
; ===============================

_asmCross PROC C	; assembly main() - called from cpp file
	
	; float_x = (yy * cc) - (zz * bb)
	; ----------------------------
	fld yy
	fmul cc	; st(1)
	fld zz
	fmul bb	; st(0)

	fsub st(1), st(0)

	; float_y = (zz * aa) - (xx * cc)
	; ----------------------------
	fld zz
	fmul aa	; st(1)
	fld xx
	fmul cc	; st(0)

	fsub st(1), st(0)


	; float_z = (xx * bb) - (yy * aa)
	; ----------------------------
	fld xx
	fmul bb	; st(1)
	fld yy
	fmul aa	; st(0)

	fsub st(1), st(0)

	; load cross product result values 
	; ----------------------------
	fxch st(1)		; send value at st(1) to st(0)
	fstp crossX

	fxch st(2)
	fstp crossY

	fxch st(3)
	fstp crossZ

	ret						; exits _asmCross() and returns to main() in the cpp file

_asmCross ENDP	; End of _asmCross() function

; ===============================
; Print result of _asmMagnitude
; ===============================

_asmPrintMagnitude PROC C	; assembly main() - called from cpp file		

	; Print out reselt of getMagnitude() to console
	;---------------------------------
	push dword ptr [vectorResult]
	call _printMagnitude
	add esp, 4

	ret						; exits _asmPrintMagnitude() and returns to main() in the cpp file

_asmPrintMagnitude ENDP	; End of _asmPrintMagnitude() function

; ===============================
; Print result of _asmcross
; ===============================

_asmPrintCross PROC C	; assembly main() - called from cpp file

	; Print out Vector3 reselt of cross() to console
	;---------------------------------
	push dword ptr [crossX]	
	push dword ptr [crossY]	
	push dword ptr [crossZ]	
	call _printVector3
	add esp, 12	; stack cleanup

	ret						; exits _asmPrintCross() and returns to main() in the cpp file

_asmPrintCross ENDP	; End of _asmPrintCross() function

END				; End of file identifier - tells the assembler to stop assembly process