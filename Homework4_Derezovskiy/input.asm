; file.asm - использование файлов в NASM
extern printf
extern fscanf

extern PARALLELEPIPED
extern TETRAHEDRON
extern BALL

;----------------------------------------------
; Ввод параметров параллелепипеда из файла
global InTetrahedron
InTetrahedron:
section .data
    .infmt db "%d%d",0
section .bss
    .FILE   resq    1   ; временное хранение указателя на файл
    .paral  resq    1   ; адрес параллелепипеда
section .text
push rbp
mov rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.paral], rdi          ; сохраняется адрес параллелепипеда
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Ввод прямоугольника из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt         ; Формат - 1-й аргумент
    mov     rdx, [.paral]       ; &x
    mov     rcx, [.paral]
    add     rcx, 4              ; &y = &x + 4
    mov     rax, 0              ; нет чисел с плавающей точкой
    call    fscanf

leave
ret

global InBall
InBall:
section .data
    .infmt db "%d%d",0
section .bss
    .FILE   resq    1   ; временное хранение указателя на файл
    .ball  resq    1   ; адрес шара
section .text
push rbp
mov rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.ball], rdi          ; сохраняется адрес шара
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Ввод шара из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt         ; Формат - 1-й аргумент
    mov     rdx, [.ball]       ; &x
    mov     rcx, [.ball]
    add     rcx, 4              ; &y = &x + 4
    mov     rax, 0              ; нет чисел с плавающей точкой
    call    fscanf

leave
ret

; Ввод параметров тетраэдра из файла
global InParallelepiped
InParallelepiped:
section .data
    .infmt db "%d%d%d",0
section .bss
    .FILE   resq    1   ; временное хранение указателя на файл
    .tetra  resq    1   ; адрес тетраэдра
section .text
push rbp
mov rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.tetra], rdi          ; сохраняется адрес треугольника
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Ввод треугольника из файла
    mov     rdi, [.FILE]
    mov     rsi, .infmt         ; Формат - 1-й аргумент
    mov     rdx, [.tetra]       ; &a
    mov     rcx, [.tetra]
    add     rcx, 4              ; &b = &a + 4
    mov     r8, [.tetra]
    add     r8, 8               ; &c = &x + 8
    mov     rbx, [.tetra]
    add     rbx, 16
    mov     rax, 0              ; нет чисел с плавающей точкой
    call    fscanf

leave
ret

; Ввод параметров обобщенной фигуры из файла
global InShape
InShape:
section .data
    .tagFormat   db      "%d",0
    .tagOutFmt   db     "Tag is: %d",10,0
section .bss
    .FILE       resq    1   ; временное хранение указателя на файл
    .pshape     resq    1   ; адрес фигуры
    .shapeTag   resd    1   ; признак фигуры
section .text
push rbp
mov rbp, rsp

    ; Сохранение принятых аргументов
    mov     [.pshape], rdi          ; сохраняется адрес фигуры
    mov     [.FILE], rsi            ; сохраняется указатель на файл

    ; чтение признака фигуры и его обработка
    mov     rdi, [.FILE]
    mov     rsi, .tagFormat
    mov     rdx, [.pshape]      ; адрес начала фигуры (ее признак)
    xor     rax, rax            ; нет чисел с плавающей точкой
    call    fscanf

    ; Тестовый вывод признака фигуры
;     mov     rdi, .tagOutFmt
;     mov     rax, [.pshape]
;     mov     esi, [rax]
;     call    printf

    mov rcx, [.pshape]          ; загрузка адреса начала фигуры
    mov eax, [rcx]              ; и получение прочитанного признака
    cmp eax, [PARALLELEPIPED]
    je .paralIn
    cmp eax, [TETRAHEDRON]
    je .tetraIn
    cmp eax, [BALL]
    je .ballIn
    xor eax, eax    ; Некорректный признак - обнуление кода возврата
    jmp     .return
.paralIn:
    ; Ввод параллелепипеда
    mov     rdi, [.pshape]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InParallelepiped
    mov     rax, 1  ; Код возврата - true
    jmp     .return
.ballIn:
    ; Ввод шара
    mov     rdi, [.pshape]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InBall
    mov     rax, 1  ; Код возврата - true
    jmp     .return
.tetraIn:
    ; Ввод тетраэдра
    mov     rdi, [.pshape]
    add     rdi, 4
    mov     rsi, [.FILE]
    call    InTetrahedron
    mov     rax, 1  ; Код возврата - true
.return:

leave
ret

; Ввод содержимого контейнера из указанного файла
global InContainer
InContainer:
section .bss
    .pcont  resq    1   ; адрес контейнера
    .plen   resq    1   ; адрес для сохранения числа введенных элементов
    .FILE   resq    1   ; указатель на файл
section .text
push rbp
mov rbp, rsp

    mov [.pcont], rdi   ; сохраняется указатель на контейнер
    mov [.plen], rsi    ; сохраняется указатель на длину
    mov [.FILE], rdx    ; сохраняется указатель на файл
    ; В rdi адрес начала контейнера
    xor rbx, rbx        ; число фигур = 0
    mov rsi, rdx        ; перенос указателя на файл
.loop:
    ; сохранение рабочих регистров
    push rdi
    push rbx

    mov     rsi, [.FILE]
    mov     rax, 0      ; нет чисел с плавающей точкой
    call    InShape     ; ввод фигуры
    cmp rax, 0          ; проверка успешности ввода
    jle  .return        ; выход, если признак меньше или равен 0

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

