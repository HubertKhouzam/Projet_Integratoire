
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


#include <avr/io.h>

enum class EdgeType {
    FALLING,
    RISING,
    ANY
};

enum class InterruptionType {
    INT0_,
    INT1_,
    INT2_
};

class ButtonInterrupt {
public:
    ButtonInterrupt(EdgeType edgeType = EdgeType::RISING, InterruptionType interrupt = InterruptionType::INT0_);
    const uint8_t DEBOUNCE_DELAY = 30;
};