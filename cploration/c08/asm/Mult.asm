// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Mult.asm

@R0
D=M         
@R2
M=0         

(LOOP)
@R1
D=M        
@END
D;JEQ      

@R0
D=M        
@R2
M=D+M       

@R1
M=M-1     
@LOOP
0;JMP     

(END)
@END
0;JMP       // Infinite loop at the end of the program

