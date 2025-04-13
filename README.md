# Aplicacion Tickets
Este programa en C gestiona tickets de soporte técnico utilizando un sistema de colas con prioridades, implementadas mediante el TDA de listas.

# Para Ejecutar
1) Asegurate de tener los archivos list.c, list.h y Apptickets.c y
Ademas asegura de tener gcc y git en tu maquina.

2) Copila el programa con  gcc -o programa Apptickets.c list.c

3) Ejecuta el programa con ./programa

# Funcionalidades del programa
Registrar ticket: Permite agregar nuevos tickets al sistema.

Asignar prioridad : Establece una prioridad (alta, media, baja) a un ticket existente ingresado por el usuario.

Mostrar tickets pendientes: Muestra los tickets pendientes, ordenados por prioridad y hora de registro.

Procesar siguiente ticket: Procesa el ticket más urgente y antiguo en la cola.

Buscar ticket por ID: Busca un ticket por su ID y muestra toda su información.

# Ejemplo de uso

 Menu principal
Presione 1 para registrar el ticket
Presione 2 para asignarle prioridad al ticket
Presione 3 para mostrar tickets los pendientes
Presione 4 para procesar el siguiente ticket
Presione 5 para buscar un ticket por ID
Precione 6 para cerrar el programa
Que deseas realizar?: 1
Ingrese el ID del ticket: 14
Ingrese el problema: Problema con la carga
Ticket registrado con una prioridad BAJA y hora actual.

 Menu principal
Presione 1 para registrar el ticket
Presione 2 para asignarle prioridad al ticket
Presione 3 para mostrar tickets los pendientes
Presione 4 para procesar el siguiente ticket
Presione 5 para buscar un ticket por ID
Precione 6 para cerrar el programa
Que deseas realizar?: 6
Cerrando