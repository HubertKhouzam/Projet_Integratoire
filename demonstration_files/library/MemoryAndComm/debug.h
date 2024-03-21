/*
Auteur       : Iknoor Singh Povar, Arnaud Grandisson, Moustafa Hossam, Hubert Khouzam

Description  : Définition de la macro permettant de gérer les messages de débogage.

Branchements : 1 Branchement au total : - Sortie : Cavalier sur DbgEN

*/

#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_PRINT(x) Communication.debugPrint(x)
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0)
#endif
