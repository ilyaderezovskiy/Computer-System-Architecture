;------------------------------------------------------------------------------
; square.asm - единица компиляции, вбирающая функции вычисления площади
;------------------------------------------------------------------------------

extern PARALLELEPIPED
extern TETRAHEDRON
extern BALL

;----------------------------------------------
; Вычисление площади тетраэдра
global SquareTetrahedron
SquareTetrahedron:
section .text
push rbp
mov rbp, rsp
    ; В rdi адрес тетраэдра
    mov eax, [rdi]
    mul eax
    mov ebx, 1732
    mul ebx
    mov ebx, 1000
    div ebx
    cvtsi2sd    xmm0, eax

leave
ret

global SquareBall
SquareBall:
section .text
push rbp
mov rbp, rsp
    ; В rdi адрес шара
    mov eax, [rdi]
    mul eax             ; возведение в квадрат
    shl eax, 2          ; умножение на 4
    mov ebx, 314159
    mul ebx
    mov ebx, 100000
    div ebx
    cvtsi2sd    xmm0, eax

leave
ret


global SquareParallelepiped
SquareParallelepiped:
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес параллелепипеда
    mov eax, [rdi+4]
    mov ebx, [rdi+8]
    mul ebx
	mov ebx, [rdi]
	div ebx
	add eax, [rdi+4]
	add eax, [rdi+8]
	mov ebx, [rdi]
    mul ebx
    mov ebx, 2
    mul ebx
    cvtsi2sd    xmm0, eax

leave
ret

;----------------------------------------------
; Вычисление площади фигуры
global SquareShape
SquareShape:
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес фигуры
    mov eax, [rdi]
    cmp eax, [PARALLELEPIPED]
    je paralSquare
    cmp eax, [BALL]
    je ballSquare
    cmp eax, [TETRAHEDRON]
    je tetraSquare
    xor eax, eax
    cvtsi2sd    xmm0, eax
    jmp     return
paralSquare:
    ; Вычисление площади параллелепипеда
    add     rdi, 4
    call    SquareParallelepiped
    jmp     return
ballSquare:
    ; Вычисление площади шара
    add     rdi, 4
    call    SquareBall
    jmp     return
tetraSquare:
    ; Вычисление площади тетраэдра
    add     rdi, 4
    call    SquareTetrahedron
return:
leave
ret

;----------------------------------------------
; Вычисление суммы периметров всех фигур в контейнере
global PerimeterSumContainer
PerimeterSumContainer:
section .data
    .sum    dq  0.0
section .text
push rbp
mov rbp, rsp

    ; В rdi адрес начала контейнера
    mov rbx, rsi            ; число фигур
    xor rcx, rcx            ; счетчик фигур
    movsd xmm1, [.sum]      ; перенос накопителя суммы в регистр 1
.loop:
    cmp rcx, rbx            ; проверка на окончание цикла
    jge .return             ; Перебрали все фигуры

    mov r10, rdi            ; сохранение начала фигуры
    call SquareShape     ; Получение периметра первой фигуры
    addsd xmm1, xmm0        ; накопление суммы
    inc rcx                 ; индекс следующей фигуры
    add r10, 16             ; адрес следующей фигуры
    mov rdi, r10            ; восстановление для передачи параметра
    jmp .loop
.return:
    movsd xmm0, xmm1
leave
ret
