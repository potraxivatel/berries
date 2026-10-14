[bits 32]

global outb
global inb
global keyboard_read
global keyboard_write
global check_keyboard

outb:
  push ebp
  mov ebp, esp
  mov dx, [ebp+8]   
  mov al, [ebp+12] 
  out dx, al
  pop ebp
  ret

inb:
  push ebp
  mov ebp, esp
  mov dx, [ebp+8]   
  in al, dx        
  movzx eax, al     
  pop ebp
  ret

keyboard_read:
  push ebp
  mov ebp, esp
  mov dx, 0x60      
  in al, dx         
  movzx eax, al
  pop ebp
  ret

keyboard_write:
  push ebp
  mov ebp, esp
  mov dx, 0x60     
  mov al, [ebp+8]   
  out dx, al        
  pop ebp
  ret

check_keyboard:
  in al, 0x64       
  test al, 1        
  jz .nodata        
  in al, 0x60       
  movzx eax, al     
  ret
.nodata:
  xor eax, eax      
  ret
