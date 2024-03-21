// Noms des auteurs : Iknoor Singh Povar, Hossam Moustafa, Arnaud Grandisson et Hubert Khouzam

// Description du programme : La classe LED est conçue pour contrôler une LED bicolores (vert et rouge) sur un microcontrôleur AVR.
//                            Elle utilise les registres de mode et de port pour configurer les broches correspondantes en sortie.
//                            Lors de la construction de l'objet, les paramètres passés sont les adresses des registres de mode (mode)
//                            et de port (port), ainsi que les positions des broches vertes (pinGreen) et rouges (pinRed).
//                            Les méthodes fournies permettent de contrôler l'état de la LED en allumant la couleur verte, la couleur rouge,
//                            une couleur ambrée (en alternant entre vert et rouge) et en éteignant la LED.
//
//                            - La méthode setGreen() allume la LED en vert en désactivant la LED rouge.
//                            - La méthode setRed() allume la LED en rouge en désactivant la LED verte.
//                            - La méthode setAmber() allume alternativement la LED en vert et rouge pour simuler une couleur ambrée.
//                            - La méthode setOff() éteint complètement la LED en désactivant les deux couleurs.

// Identification Matérielle:
//    - Les broches pour la LED verte et rouge sont configurées en sortie à l'aide du registre de mode (mode).
//    - L'utilisateur doit s'assurer que les broches spécifiées sont connectées correctement aux LED vertes et rouges.

#pragma once
#include <avr/io.h>
#include <util/delay.h>

typedef volatile uint8_t *Register;
typedef volatile uint8_t Port;

class LED
{
public:
    LED(Register port = &DDRC, Register mode = &PORTC, Port pinGreen = PC2, Port pinRed = PC3);

    void setGreen();
    void setRed();
    void setAmber();
    void setOff();

private:
    Register port_;
    const uint8_t pinGreenPosition;
    const uint8_t pinRedPosition;
};