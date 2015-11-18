#### PROGRAM
 .data
 printstr: .asciz "%d\n"
 .text
.globl Main_main
Test_setRoof:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### ASSIGNMENT
#### VARIABLE
 push 12(%ebp)
#### END VARIABLE
 pop %eax
 mov 8(%ebp), %ebx
 mov %eax, 0(%ebx)
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_setRoof2:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### ASSIGNMENT
#### VARIABLE
 push 12(%ebp)
#### END VARIABLE
 pop %eax
 mov 8(%ebp), %ebx
 mov %eax, 4(%ebx)
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_setRoof3:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### ASSIGNMENT
#### VARIABLE
 push 12(%ebp)
#### END VARIABLE
 pop %eax
 mov 8(%ebp), %ebx
 mov %eax, 8(%ebx)
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_getRoof:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### RETURN
#### VARIABLE
 mov 8(%ebp), %ebx
 push 0(%ebx)
#### END VARIABLE
 pop %eax
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_getRoof2:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### RETURN
#### VARIABLE
 mov 8(%ebp), %ebx
 push 4(%ebx)
#### END VARIABLE
 pop %eax
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_getRoof3:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### RETURN
#### VARIABLE
 mov 8(%ebp), %ebx
 push 8(%ebx)
#### END VARIABLE
 pop %eax
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Test_isOnFire:
 push %ebp
 mov %esp, %ebp
 sub $0, %esp
 push %ebx
 push %edi
 push %esi
#### RETURN
#### INTEGER
 push $1
 pop %eax
 pop %esi
 pop %edi
 pop %ebx
 mov %ebp, %esp
 pop %ebp
 ret
Main_main:
 push %ebp
 mov %esp, %ebp
 sub $4, %esp
 push %ebx
 push %edi
 push %esi
#### ASSIGNMENT
#### NEW
 push $12
 call malloc
 add $4, %esp
 push %eax
#### END NEW
 pop %eax
 mov %eax, -4(%ebp)
#### PRE-CALL
 push %ecx
 push %edx
#### INTEGER
 push $1
 push -4(%ebp)
#### END PRE-CALL
 call Test_setRoof
#### POST-CALL
 add $8, %esp
 pop %edx
 pop %ecx
#### PRE-CALL
 push %ecx
 push %edx
#### INTEGER
 push $2
 push -4(%ebp)
#### END PRE-CALL
 call Test_setRoof2
#### POST-CALL
 add $8, %esp
 pop %edx
 pop %ecx
#### PRE-CALL
 push %ecx
 push %edx
#### INTEGER
 push $3
 push -4(%ebp)
#### END PRE-CALL
 call Test_setRoof3
#### POST-CALL
 add $8, %esp
 pop %edx
 pop %ecx
#### IFELSE
#### PRE-CALL
 push %ecx
 push %edx
#### PRE-CALL
 push %ecx
 push %edx
 push -4(%ebp)
#### END PRE-CALL
 call Test_getRoof3
#### POST-CALL
 add $4, %esp
 pop %edx
 pop %ecx
 push %eax
#### PRE-CALL
 push %ecx
 push %edx
 push -4(%ebp)
#### END PRE-CALL
 call Test_getRoof2
#### POST-CALL
 add $4, %esp
 pop %edx
 pop %ecx
 push %eax
#### PRE-CALL
 push %ecx
 push %edx
 push -4(%ebp)
#### END PRE-CALL
 call Test_getRoof
#### POST-CALL
 add $4, %esp
 pop %edx
 pop %ecx
 push %eax
 push -4(%ebp)
#### END PRE-CALL
 call Test_isOnFire
#### POST-CALL
 add $16, %esp
 pop %edx
 pop %ecx
 push %eax
pop %eax
mov $0, %ebx
cmp %eax, %ebx
je Label_0
#### PRINT
#### INTEGER
 push $1
 push $printstr
 call printf
#### END PRINT
jmp END_1
Label_0:
jmp END_1
