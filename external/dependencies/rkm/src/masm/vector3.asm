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
xx REAL4 0.6f
yy REAL4 -0.8f
zz REAL4 0.0f

; Vector B
aa REAL4 2.0
bb REAL4 -4.0
cc REAL4 1.0

crossX REAL4 ?
crossY  REAL4 ?
crossZ REAL4 ?
vectorResult REAL4 ?



.CODE			; start of code segment

; ===============================
; float Vector3::getMagnitude()
; ===============================

_asmMagnitude PROC C	; assembly main() - called from cpp file	

	; printing a vector3
	;push dword ptr [zz]	
	;push dword ptr [yy]	
	;push dword ptr [xx]	
	;call _printVector3
	;add esp, 12	; stack cleanup
	
	fld xx
	fmul xx
	fld yy
	fmul yy
	fld zz
	fmul zz
	
	fadd st(0), st(1)
	fadd st(0), st(2)
 	fsqrt
	fstp vectorResult

	push dword ptr [vectorResult]
	call _printMagnitude
	add esp, 4

	ret						; exits _asmMagnitude() and returns to main() in the cpp file

_asmMagnitude ENDP	; End of asmMain() function


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

	; load cross product values for printing
	; ----------------------------
	fxch st(1)		; send value at st(1) to st(0)
	fstp crossX

	fxch st(2)
	fstp crossY

	fxch st(3)
	fstp crossZ

	; printing a vector3
	push dword ptr [crossX]	
	push dword ptr [crossY]	
	push dword ptr [crossZ]	
	call _printVector3
	add esp, 12	; stack cleanup

	ret						; exits asmMain() and returns to main() in the cpp file

_asmCross ENDP	; End of _asmCross() function

END				; End of file identifier - tells the assembler to stop assembly process