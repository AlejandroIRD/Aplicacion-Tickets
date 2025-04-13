#include <stdio.h>
#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef enum { ALTA = 2, MEDIA = 1, BAJA = 0 } Priority;
List* cola[3];

typedef struct {
    int id;
    Priority prioridad;
    char desc[10];
    time_t Horallegada;
} Ticket;

const char* PrioToText(Priority prio) {
    switch (prio) {
        case BAJA: return "BAJA";
        
        case MEDIA: return "MEDIA";
        
        case ALTA: return "ALTA";
        
        default: return "No se sabe";
    }
}

int HoraMenor(void* TicketA, void* TicketB) {
    Ticket* Ticket1 = (Ticket*) TicketA;
    Ticket* Ticket2 = (Ticket*) TicketB;
    return Ticket1->Horallegada < Ticket2->Horallegada;
}

void RegistrarT() {
    Ticket* ticketNew = (Ticket*)malloc(sizeof(Ticket));
    ticketNew->prioridad = BAJA;
    ticketNew->Horallegada = time(NULL);

    printf("Ingrese el ID del ticket: ");
    scanf("%d", &ticketNew->id);
    getchar();

    printf("Ingrese el problema: ");
    fgets(ticketNew->desc, sizeof(ticketNew->desc), stdin);
    ticketNew->desc[strcspn(ticketNew->desc, "\n")] = '\0';

    sortedInsert(cola[BAJA], ticketNew, HoraMenor);

    printf("Ticket registrado con una prioridad BAJA y la hora actual.\n");
}

void ShowTickets(Ticket* Ticket) {
    char Fecha[26];
    struct tm* tm_info;
    tm_info = localtime(&Ticket->Horallegada);
    strftime(Fecha, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    
    printf("ID ticket: %d\n", Ticket->id);
    
    printf("Prioridad del ticket: %s\n", PrioToText(Ticket->prioridad));
    
    printf("Descripcion ticket: %s\n", Ticket->desc);
    
    printf("Hora de llegada del registro: %s\n", Fecha);
}

void PrioAsig() {
    int idTicket, nuevaPrio;
    printf("Ingrese el ID del ticket: ");
    scanf("%d", &idTicket);

    printf("Ingrese la nueva prioridad (2 = ALTA, 1 = MEDIA, 0 = BAJA): ");
    scanf("%d", &nuevaPrio);

    if (nuevaPrio < 1 || nuevaPrio > 3) {
        printf("Prioridad Inexistente.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        void* ptr = firstList(cola[i]);
        while (ptr != NULL) {
            Ticket* ticket = (Ticket*)ptr;
            if (ticket->id == idTicket) {
                popCurrent(cola[i]);
                ticket->prioridad = (Priority)nuevaPrio;
                sortedInsert(cola[nuevaPrio], ticket, HoraMenor);
                printf("Prioridad del ticket ID %d actualizada a %s.\n", idTicket, PrioToText(ticket->prioridad));
                return;
            }
            ptr = nextList(cola[i]);
        }
    }
    printf("No se encontro ningun ticket con el id registrado.\n");
}

void TicketPend() {
    int TicketsPe = 0;
    for (int i = 2; i >= 0; i--) {
        void* ptr = firstList(cola[i]);
        if (ptr != NULL) {
            printf("\nTickets con prioridad %s:\n", PrioToText(i));
            TicketsPe = 1;
        }
        while (ptr != NULL) {
            Ticket* ticket = (Ticket*)ptr;
            ShowTickets(ticket);
            ptr = nextList(cola[i]);
        }
    }
    if (!TicketsPe) printf("No se encuentran tickets pendientes.\n");
}

void SigTicket() {
    for (int i = 2; i >= 0; i--) {
        Ticket* ticket = (Ticket*)firstList(cola[i]);
        if (ticket != NULL) {
            popFront(cola[i]);
            printf("\nProcesando el ticket:\n");
            ShowTickets(ticket);
            free(ticket);
            return;
        }
    }
    printf("No hay tickets pendientes por procesar.\n");
}
void buscarTicket() {
    int idTicket;
    printf("Ingrese el ID del ticket a buscar: ");
    scanf("%d", &idTicket);

    for (int i = 2; i >= 0; i--) {
        void* ptr = firstList(cola[i]);
        while (ptr != NULL) {
            Ticket* ticket = (Ticket*)ptr;
            if (ticket->id == idTicket) {
                printf("El ticket ha sido encontrado:\n");
                ShowTickets(ticket);
                return;
            }
            ptr = nextList(cola[i]);
        }
    }
    printf("No se encontro ningun ticket pendiente con el ID registrado.\n");
}

void showMenu(){
    printf("\n Menu principal \n");
    printf("Presione 1 para registrar el ticket\n");
    printf("Presione 2 para asignarle prioridad al ticket\n");
    printf("Presione 3 para mostrar tickets los pendientes\n");
    printf("Presione 4 para procesar el siguiente ticket\n");
    printf("Presione 5 para buscar un ticket por ID\n");
    printf("Precione 6 para cerrar el programa\n");
    printf("Que deseas realizar?: ");
}

int main() {
    for (int i = 0; i < 3; i++) {
        cola[i] = createList();
    }

    int opcion;
    do {

        showMenu();
        scanf("%d", &opcion);
        getchar( );

        switch (opcion) {
            case 1: RegistrarT(); break;
            case 2: PrioAsig(); break;
            case 3: TicketPend(); break;
            case 4: SigTicket(); break;
            case 5: buscarTicket(); break;
            case 6: printf("Cerrando\n"); break;
            default: printf("Error Opcion invalida\n"); break;
        }
    } while (opcion != 6);

    return 0;
}