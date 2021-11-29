; file.asm - использование файлов в NASM
extern printf
extern fprintf

extern SquareTetrahedron
extern SquareParallelepiped
extern SquareBall

extern PARALLELEPIPED
extern TETRAHEDRON
extern BALL

;----------------------------------------------
; Вывод параметров тетраэдра в файл
global OutTetrahedron
OutTetrahedron:
section .data
    .outfmt db "It is Tetrahedron: a = %d, materialDensity = %d. Square = %g",10,0
section .bss
    .prect  resq  1
    .FILE   resq  1       ; временное хранение указателя на файл
    .p      resq  1       ; вычисленая площадь тетраэдра
section .text
push rbp
mov rbp, rsp

    ; Сохранени принятых аргументов
    mov     [.prect], rdi          ; сохраняется адрес тетраэдра
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Вычисление площадь тетраэдра (адрес уже в rdi)
    call    SquareTetrahedron
    movsd   [.p], xmm0          ; сохранение (может лишнее) площади

    ; Вывод информации о тетраэдре в файл
    mov     rdi, [.FILE]
    mov     rsi, .outfmt        ; Формат - 2-й аргумент
    mov     rax, [.prect]        ; адрес тетраэдра
    mov     edx, [rax]          ; x
    mov     ecx, [rax+4]        ; y
    movsd   xmm0, [.p]
    mov     rax, 1              ; есть числа с плавающей точкой
    call    fprintf

leave
ret

;// Вывод параметров шара в файл
global OutBall
OutBall:
section .data
    .outfmt db "It is Ball: r = %d, materialDensity = %d. Square = %g",10,0
section .bss
    .ball  resq  1
    .FILE   resq  1       ; временное хранение указателя на файл
    .p      resq  1       ; вычисленный периметр шара
section .text
push rbp
mov rbp, rsp

    ; Сохранени принятых аргументов
    mov     [.ball], rdi          ; сохраняется адрес шара
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Вычисление периметра прямоугольника (адрес уже в rdi)
    call    SquareBall
    movsd   [.p], xmm0          ; сохранение (может лишнее) площадт шара

    ; Вывод информации о шаре в файл
    mov     rdi, [.FILE]
    mov     rsi, .outfmt        ; Формат - 2-й аргумент
    mov     rax, [.ball]        ; адрес шара
    mov     edx, [rax]          ; x
    mov     ecx, [rax+4]        ; y
    movsd   xmm0, [.p]
    mov     rax, 1              ; есть числа с плавающей точкой
    call    fprintf

leave
ret

;----------------------------------------------
; Вывод параметров параллелепипеда в файл
global OutParallelepiped
OutParallelepiped:
section .data
    .outfmt db "It is Parallelepiped: a = %d, b = %d, c = %d, materialDensity = %d. Square = %g",10,0
section .bss
    .ptrian  resq  1
    .FILE   resq  1       ; временное хранение указателя на файл
    .p      resq  1       ; вычисленный периметр параллелепипеда
section .text
push rbp
mov rbp, rsp

    ; Сохранени принятых аргументов
    mov     [.ptrian], rdi        ; сохраняется адрес параллелепипеда
    mov     [.FILE], rsi          ; сохраняется указатель на файл

    ; Вычисление периметра треугольника (адрес уже в rdi)
    call    SquareParallelepiped
    movsd   [.p], xmm0          ; сохранение (может лишнее) периметра

    ; Вывод информации о треугольнике в файл
    mov     rdi, [.FILE]
    mov     rsi, .outfmt        ; Формат - 2-й аргумент
    mov     rax, [.ptrian]      ; адрес параллелепипеда
    mov     edx, [rax]          ; x
    mov     ecx, [rax+4]        ; b
    mov      r8, [rax+8]        ; c
    mov      r15, [rax+15]      ; materialDensity
    movsd   xmm0, [.p]
    mov     rax, 1              ; есть числа с плавающей точкой
    call    fprintf

leave
ret

;----------------------------------------------
; Вывод параметров текущей фигуры в файл
global OutShape
OutShape:
section .data
    .erShape db "Incorrect figure!",10,0
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес фигуры
    mov eax, [rdi]
    cmp eax, [PARALLELEPIPED]
    je paralOut
    cmp eax, [BALL]
    je ballOut
    cmp eax, [TETRAHEDRON]
    je tetraOut
    mov rdi, .erShape
    mov rax, 0
    call fprintf
    jmp     return
paralOut:
    ; Вывод прямоугольника
    add     rdi, 4
    call    OutParallelepiped
    jmp     return
ballOut:
    ; Вывод прямоугольника
    add     rdi, 4
    call    OutBall
    jmp     return
tetraOut:
    ; Вывод треугольника
    add     rdi, 4
    call    OutTetrahedron
return:
leave
ret

;----------------------------------------------
; Вывод содержимого контейнера в файл
global OutContainer
OutContainer:
section .data
    numFmt  db  "%d: ",0
section .bss
    .pcont  resq    1   ; адрес контейнера
    .len    resd    1   ; адрес для сохранения числа введенных элементов
    .FILE   resq    1   ; указатель на файл
section .text
push rbp
mov rbp, rsp

    mov [.pcont], rdi   ; сохраняется указатель на контейнер
    mov [.len],   esi     ; сохраняется число элементов
    mov [.FILE],  rdx    ; сохраняется указатель на файл

    ; В rdi адрес начала контейнера
    mov rbx, rsi            ; число фигур
    xor ecx, ecx            ; счетчик фигур = 0
    mov rsi, rdx            ; перенос указателя на файл
.loop:
    cmp ecx, ebx            ; проверка на окончание цикла
    jge .return             ; Перебрали все фигуры

    push rbx
    push rcx

    ; Вывод номера фигуры
    mov     rdi, [.FILE]    ; текущий указатель на файл
    mov     rsi, numFmt     ; формат для вывода фигуры
    mov     edx, ecx        ; индекс текущей фигуры
    xor     rax, rax,       ; только целочисленные регистры
    call fprintf

    ; Вывод текущей фигуры
    mov     rdi, [.pcont]
    mov     rsi, [.FILE]
    call OutShape     ; Получение периметра первой фигуры

    pop rcx
    pop rbx
    inc ecx                 ; индекс следующей фигуры

    mov     rax, [.pcont]
    add     rax, 16         ; адрес следующей фигуры
    mov     [.pcont], rax
    jmp .loop
.return:
leave
ret

