mul128:  
  imul  %rdi, %rcx
  mov   %rdx, %rax
  imul  %rdx, %rsi
  add   %rsi, %rcx
  mul   %rdi
  add   %rcx, %rdx
  retq

