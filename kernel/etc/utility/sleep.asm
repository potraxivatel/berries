[bits 32]

global pit_wait_ms
global calibrate_tsc
global kernel_sleep

section .data
    tsc_ticks_per_second dq 0

section .text

pit_wait_ms:
    push ebp
    mov ebp, esp
    push ebx

    mov ecx, [ebp+8]    
    test ecx, ecx
    jz .done

.loop_ms:
    mov al, 0xB0
    out 0x43, al

    mov al, 0xA9        
    out 0x42, al        
    mov al, 0x04        
    out 0x42, al        

    in al, 0x61
    or al, 0x01         
    and al, 0xFD        
    out 0x61, al

.wait_single_ms:
    in al, 0x61
    test al, 0x20       
    jz .wait_single_ms  

    in al, 0x61
    and al, 0xFE        
    out 0x61, al

    loop .loop_ms       

.done:
    pop ebx
    pop ebp
    ret


calibrate_tsc:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    rdtsc               
    mov ebx, eax
    mov ecx, edx

    push 100
    call pit_wait_ms
    add esp, 4          

    rdtsc               

    sub eax, ebx        
    sbb edx, ecx        

    mov esi, 10
    mov edi, edx        

    mul esi             
    mov ebx, eax        
    mov ecx, edx        

    mov eax, edi        
    mul esi             
    add eax, ecx        

    mov [tsc_ticks_per_second], ebx      
    mov [tsc_ticks_per_second + 4], eax  

    pop edi
    pop esi
    pop ebx
    pop ebp
    ret


kernel_sleep:
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi

    mov ecx, [ebp+8]
    test ecx, ecx
    jz .exit            

    mov eax, [tsc_ticks_per_second]
    mov edx, [tsc_ticks_per_second + 4]
    or eax, edx
    jz .exit            

    mov eax, [tsc_ticks_per_second]
    mov esi, ecx
    mul esi             
    mov edi, eax        
    mov ebx, edx        

    mov eax, [tsc_ticks_per_second + 4]
    mul esi             
    add eax, ebx        
    mov ecx, eax        
    

    rdtsc
    mov esi, eax        
    mov ebp, edx        

.wait_loop:
    pause               
    rdtsc               

    
    sub eax, esi
    sbb edx, ebp

    
    cmp edx, ecx
    jb .wait_loop       
    ja .timeout         
    cmp eax, edi
    jb .wait_loop       

.timeout:
.exit:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret
