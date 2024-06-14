.data
n30: .word 30   
n40: .word 40  
n41: .word 41          
resultado_30: .asciiz "30º termo da sequência de Fibonacci: "
resultado_40: .asciiz "40º termo da sequência de Fibonacci: "
resultado_41: .asciiz "41º termo da sequência de Fibonacci: "
resultado_aurea: .asciiz "Razão áurea entre o 40º e o 41º termo: "
novaLinha: .asciiz "\n"     # Nova linha para formatação

.text
.globl main

main:
#Fibonacci do termo 30
    lw $a0, n30
    jal calcularFibonacci
    move $s1, $v0 
#Fibonacci do termo 40
    lw $a0, n40
    jal calcularFibonacci
    move $s3, $v0
#Fibonacci do termo 41
    lw $a0, n41
    jal calcularFibonacci       
    move $s2, $v0 
#Razão aurea
    jal calcularRazaoAurea
#Termo 30
    li $v0, 4
    la $a0, resultado_30
    syscall
    li $v0, 1
    move $a0, $s1
    syscall
    li $v0, 4     
    la $a0, novaLinha
    syscall
#Termo 40
    li $v0, 4
    la $a0, resultado_40 
    syscall
    li $v0, 1       
    move $a0, $s3    
    syscall
    li $v0, 4        
    la $a0, novaLinha 
    syscall
# Termo 41
    li $v0, 4   
    la $a0, resultado_41
    syscall
    li $v0, 1       
    move $a0, $s2    
    syscall
    li $v0, 4           
    la $a0, novaLinha   
    syscall
#Razão áurea
    li $v0, 4        
    la $a0, resultado_aurea   
    syscall
    li $v0, 2         
    mov.s $f12, $f0      
    syscall
    li $v0, 4        
    la $a0, novaLinha    
    syscall
#Fim
    li $v0, 10      
    syscall
#funções
calcularRazaoAurea:
    mtc1 $s2, $f4   
    mtc1 $s3, $f5  
    cvt.s.w $f4, $f4 
    cvt.s.w $f5, $f5 
    div.s $f0, $f4, $f5
    jr $ra 
calcularFibonacci:
    li $t0, 1       
    li $t1, 1   
    blez $a0, fib_fim  
    beq $a0, 1, fib_base  
    beq $a0, 2, fib_base 
    sub $a0, $a0, 2    
rep_fibonacci:
    beqz $a0, fib_fim 
    sub $a0, $a0, 1   
    add $t2, $t0, $t1  
    move $t0, $t1         
    move $t1, $t2    
    j rep_fibonacci 
fib_base:
    li $v0, 1          
    jr $ra         
fib_fim:
    move $v0, $t1    
    jr $ra 
