
// Noms des auteurs : Iknoor Singh Povar, Hossam Moustafa, Arnaud Grandisson et Hubert Khouzam 

// Description du programme : La classe ButtonInterrupt est conçue pour gérer les interruptions de bouton sur un microcontrôleur AVR. 
//                            Elle utilise les registres DDRD, EIMSK et EICRA pour configurer les interruptions en fonction du front désiré 
//                            et le type d’interruption. Lors de la construction de l’objet, les paramètres passés sont le 
//                            edgeType (FALLING, RISING ou ANY) et le interruptionType (INT0_, INT1_, INT2_). En fonction de ces paramètres, les 
//                            registres appropriés sont configurés. Par défaut, si aucun type d’interruption est spécifiée, l'interruption 
//                            est configurée pour utiliser INT0. L’utilisateur doit créer un objet ButtonInterrupt en passant les bons paramètres.

// Identification Matérielle:
//    - le registre DDRD est configuré pour mettre les broches désiré, selon le interruptionType, en mode sortie entrée
//    - le registre EIMSK est configuré pour activer les possibilités d'interruption du bouton poussoir sur une broche spécifique
//    - le registre EICRA est configuré pour activer les possibilités d'interruption du bouton poussoir
//    - l'utilisateur doit implémenter son propre ISR et le configuré selon le type d'interruption de l'objet
//    - la broche à connecter sur le boutton poussoir est D2 (par cavalier) si le type d'interruption est INT0
//    - la broche à connecter sur le boutton poussoir est D3 si le type d'interruption est INT1
//    - la broche à connecter sur le boutton poussoir est B2 si le type d'interruption est INT2


#include "ButtonInterrupt.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>


ButtonInterrupt::ButtonInterrupt(EdgeType edgeType, InterruptionType interrupt)
{
    cli();
    if (interrupt == InterruptionType::INT2_)
    {
        DDRB &= ~(1 << DDB2);
        EIMSK |= (1 << INT2);
    }
    else if (interrupt == InterruptionType::INT1_)
    {
        DDRD &= ~(1 << DDD3);
        EIMSK |= (1 << INT1);
    }
    else
    {
        DDRD &= ~(1 << DDD2);
        EIMSK |= (1 << INT0);
    }


    switch (edgeType)
    {
    case EdgeType::FALLING:
        if (interrupt == InterruptionType::INT2_)
        {
            EICRA |= (1 << ISC21);
        }
        else if (interrupt == InterruptionType::INT1_)
        {
            EICRA |= (1 << ISC11);
        }
        else
        {
            EICRA |= (1 << ISC01);
        }
        break;
    case EdgeType::RISING:
        if (interrupt == InterruptionType::INT2_)
        {
            EICRA |= (1 << ISC21 | 1 << ISC20);
        }
        else if (interrupt == InterruptionType::INT1_)
        {
            EICRA |= (1 << ISC11 | 1 << ISC10);
        }
        else
        {
            EICRA |= (1 << ISC01 | 1 << ISC00);
        }
        break;
    case EdgeType::ANY:
        if (interrupt == InterruptionType::INT2_)
        {
            EICRA |= (1 << ISC20);
        }
        else if (interrupt == InterruptionType::INT1_)
        {
            EICRA |= (1 << ISC10);
        }
        else
        {
            EICRA |= (1 << ISC00);
        }
        break;
    }
    sei();
}
