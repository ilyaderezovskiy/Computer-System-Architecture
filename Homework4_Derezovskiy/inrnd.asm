; file.asm - использование файлов в NASM
extern printf
extern rand

extern PARALLELEPIPED
extern TETRAHEDRON
extern BALL

;----------------------------------------------
; Генератор случайных чисел в диапазоне от 1 до 20
global Random
Random:
section .data
    .i20     dq      20
    .rndNumFmt       db "Random number = %d",10,0
section .text
push rbp
mov rbp, rsp

    xor     rax, rax    ;
    call    rand        ; запуск генератора случайных чисел
    xor     rdx, rdx    ; обнуление перед делением
    idiv    qword[.i20]       ; (/%) -> остаток в rdx
    mov     rax, rdx
    inc     rax         ; должно сформироваться случайное число

    ;mov     rdi, .rndNumFmt
    ;mov     esi, eax
    ;xor     rax, rax
    ;call    printf


leave
ret

;----------------------------------------------
; Случайный ввод параметров тетраэдра
global InRndTetrahedron
InRndTetrahedron:
section .bss
    .prect  resq 1   ; адрес параллелепипеда
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес параллелепипеда
    mov     [.prect], rdi
    ; Генерация сторон параллелепипеда
    call    Random
    mov     rbx, [.prect]
    mov     [rbx], eax
    call    Random
    mov     rbx, [.prect]
    mov     [rbx+4], eax

leave
ret

;----------------------------------------------
; Случайный ввод параметров шара
global InRndBall
InRndBall:
section .bss
    .ball  resq 1   ; адрес шара
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес шара
    mov     [.ball], rdi
    ; Генерация радиуса  шара
    call    Random
    mov     rbx, [.ball]
    mov     [rbx], eax
    call    Random
    mov     rbx, [.ball]
    mov     [rbx+4], eax

leave
ret

;----------------------------------------------
; Случайный ввод параметров параллелепипеда
global InRndParallelepiped
InRndParallelepiped:
section .bss
    .paral  resq 1   ; адрес параллелепипеда
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес параллелепипеда
    mov     [.paral], rdi
    ; Генерация сторон параллелепипеда
    call    Random
    mov     rbx, [.paral]
    mov     [rbx], eax
    call    Random
    mov     rbx, [.paral]
    mov     [rbx+4], eax
    call    Random
    mov     rbx, [.paral]
    mov     [rbx+8], eax
    call    Random
    mov     rbx, [.paral]
    mov     [rbx+16], eax

leave
ret

;----------------------------------------------
; Случайный ввод обобщенной фигуры
global InRndShape
InRndShape:
section .data
    .i3     dq      3
    .rndNumFmt       db "Random number = %d",10,0
section .bss
    .pshape     resq    1   ; адрес фигуры
    .key        resd    1   ; ключ
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес фигуры
    mov [.pshape], rdi

    ; Формирование признака фигуры
    xor     rax, rax    ;
    call    rand        ; запуск генератора случайных чисел
    xor     rdx, rdx    ; обнуление перед делением
    idiv    qword[.i3]
    mov     rax, rdx
    inc     rax         ; должно сформироваться случайное число (1 - 3)

    ;mov     [.key], eax
    ;mov     rdi, .rndNumFmt
    ;mov     esi, [.key]
    ;xor     rax, rax
    ;call    printf
    ;mov     eax, [.key]

    mov     rdi, [.pshape]
    mov     [rdi], eax      ; запись ключа в фигуру
    cmp eax, [PARALLELEPIPED]
    je .paralInrnd
    cmp eax, [BALL]
    je .ballInrnd
    cmp eax, [TETRAHEDRON]
    je .tetraInRnd
    xor eax, eax        ; код возврата = 0
    jmp     .return
.paralInrnd:
    ; Генерация параллелепипеда
    add     rdi, 4
    call    InRndParallelepiped
    mov     eax, 1      ;код возврата = 1
    jmp     .return
.ballInrnd:
    ; Генерация шара
    add     rdi, 4
    call    InRndBall
    mov     eax, 1      ;код возврата = 1
    jmp     .return
.tetraInRnd:
    ; Генерация тетраэдра
    add     rdi, 4
    call    InRndTetrahedron
    mov     eax, 1      ;код возврата = 1
.return:
leave
ret

;----------------------------------------------
; Случайный ввод содержимого контейнера
global InRndContainer
InRndContainer:
section .bss
    .pcont  resq    1   ; адрес контейнера
    .plen   resq    1   ; адрес для сохранения числа введенных элементов
    .psize  resd    1   ; число порождаемых элементов
section .text
push rbp
mov rbp, rsp

    mov [.pcont], rdi   ; сохраняется указатель на контейнер
    mov [.plen], rsi    ; сохраняется указатель на длину
    mov [.psize], edx    ; сохраняется число порождаемых элементов
    ; В rdi адрес начала контейнера
    xor ebx, ebx        ; число фигур = 0
.loop:
    cmp ebx, edx
    jge     .return
    ; сохранение рабочих регистров
    push rdi
    push rbx
    push rdx

    call    InRndShape     ; ввод фигуры
    cmp rax, 0          ; проверка успешности ввода
    jle  .return        ; выход, если признак меньше или равен 0

    pop rdx
    pop rbx
    inc rbx

    pop rdi
    add rdi, 16             ; адрес следующей фигуры

    jmp .loop
.return:
    mov rax, [.plen]    ; перенос указателя на длину
    mov [rax], ebx      ; занесение длины
leave
ret
