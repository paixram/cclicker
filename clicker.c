#include <stdlib.h>
#include <stdio.h>

/* Windows api library*/
#include <windows.h>


#define true 1
#define false 0

typedef int bool;

static bool state  = false;

DWORD WINAPI CheckKeyState(LPVOID vacio) {
    printf("%d", state);
    while(true) {
        if((GetAsyncKeyState(0x46) & 0x8000) != 0) {  // 0x8000 is "1" number status
            switch(state) {
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
            //printf("%d\n", state);
            
        }

        Sleep(100);
    };
}

int main() {

    //bool state = false;

    INPUT mouseinput;

    // Multithreading
    DWORD id;
    HANDLE handler;

    /*Crear hilo*/
    handler = CreateThread(NULL, 0, CheckKeyState, 0, 0, &id);


    // crear evento del mouse
    mouseinput.type = INPUT_MOUSE;
    mouseinput.mi.dwFlags = 0x0002;
    mouseinput.mi.time = 0;

    for(;;) {
        
        if(state == true) {
            // Baja el teclado del mouse
            SendInput(1, &mouseinput, sizeof(INPUT));
            printf("state mouse: %d\n", state);
        }else{
            printf("state mouse: %d\n", state);
        }
        Sleep(50);
    }

    if(handler != NULL) {
        WaitForSingleObject(handler, INFINITE); // Esperar a que el thread acabe
        CloseHandle(handler); // Cerrar el thread
    }
    printf("Fin");
    return 0;
}

