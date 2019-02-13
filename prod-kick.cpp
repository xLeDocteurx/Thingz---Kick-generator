#include "Led.h"
#include "Bouton.h"
#include "Son.h"
#include "Potentiometer.h"

Led led1;
Bouton button1;
Bouton button2;
Potentiometer potentiometer1;
Potentiometer potentiometer2;
Son speaker1;

class Kick
{
    public:
        Kick();
        Kick(int frequency_input, int octave_input,int attack_duration_input, int decay_duration_input, int sample_rate_input);

        int time;
        int current_frequency;
        
        int base_frequency;
        int octave;
        int attack_duration;
        int decay_duration;
        int sample_rate;
        
        // int sustain;
        
        void jouer();
        void attack();
        void decay();
};
Kick::Kick(int frequency_input, int octave_input, int attack_duration_input, int decay_duration_input, int sample_rate_input)
{
    base_frequency = frequency_input;
    octave = octave_input;
    attack_duration = attack_duration_input;
    decay_duration = decay_duration_input;
    sample_rate = sample_rate_input;
}
void Kick::jouer()
{
    current_frequency = base_frequency;
    
    led1.allume();
    // speaker1.sonne(current_frequency);
    
    // attack
    time = millis();
    while((millis() - time) < attack_duration * (potentiometer1.etat() / 100)){
        attack();
    }
    
    //decay
    time = millis();
    while((millis() - time) < decay_duration * (potentiometer2.etat() / 100)){
        decay();
    }

    speaker1.arreteDeSonner();
    led1.eteint();
}
void Kick::attack()
{
    // float b = attack_duration / 200 * 10  * (potentiometer1.etat() / 100);
    float b = attack_duration / 100 * (potentiometer1.etat() / 100);
    float x = millis() - time;
    
    float coef = x / b;
    current_frequency = base_frequency * octave * coef;
    
    speaker1.sonne(current_frequency);
    attendre(sample_rate);
    // speaker1.arreteDeSonner();
}
void Kick::decay()
{
    // int decay_starting_value = 100;
    // float a = decay_starting_value;
    // float a = 100;
    // float c = decay_duration * potentiometer2.etat();
    float c = decay_duration * (potentiometer2.etat() / 100);
    // fonction map
    float x = millis() - time;
    
    // float coef = exp(x*(1/c))*a;
    float coef = exp(-x*(1/c)) * octave * base_frequency;
    current_frequency = base_frequency * coef;
    
    speaker1.sonne(current_frequency);
    attendre(sample_rate);
}


/* TOUT EST SUPER GENIAL */


Kick kick1(110, 2, 2000, 2000, 1);

void setup()
{
    led1.allume();
    attendre(1*1000);
    led1.eteint();
}

void loop()
{
    if (button1.aEteAppuye()) {
        kick1.jouer();
    }
}
