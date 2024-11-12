// Fill.asm
// Fills the screen when a key is pressed; clears it when no key is pressed


@SCREEN
D=A
@place
M=D                

// Main loop
(LOOP)
    @KBD
    D=M            
    @WHITE
    D;JEQ          
    @BLACK
    0;JMP          

(WHITE)
    @SCREEN
    D=A
    @place
    M=D            

(CLEAR_LOOP)
    @place
    A=M            
    M=0           
    @place
    M=M+1          
    @SCREEN_END
    D=A
    @place
    D=M-D          
    @CLEAR_LOOP
    D;JLT          

    @LOOP          
    0;JMP

(BLACK)
    @SCREEN
    D=A
    @place
    M=D            

(FILL_LOOP)
    @place
    A=M           
    M=-1        
    @place
    M=M+1        
    @SCREEN_END
    D=A
    @place
    D=M-D          
    @FILL_LOOP
    D;JLT          

    @LOOP          // Go back to the main loop
    0;JMP

(SCREEN_END)
@24575
