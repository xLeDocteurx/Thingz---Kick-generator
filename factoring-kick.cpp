#include "Led.h"
#include "Bouton.h"
#include "Son.h"
#include "Potentiometer.h"

Led led1;
Bouton button1;
Potentiometer potentiometer1;
Potentiometer potentiometer2;
Son speaker1;

class Kick
{
    public:
        Kick();
        Kick(int frequency_input, int attack_duration_input, int decay_duration_input, int sample_rate_input);

        int current_frequency;
        int base_frequency;
        int sample_rate;
        int attack_duration;
        int decay_duration;
        int sutain;
        
        void jouer();
        void attack();
        void decay();
};
Kick::Kick(int frequency_input, int attack_duration_input, int decay_duration_input, int sample_rate_input)
{
    base_frequency = frequency_input;
    attack_duration = attack_duration_input;
    decay_duration = decay_duration_input;
    sample_rate = sample_rate_input;
}
void Kick::jouer()
{
    current_frequency = base_frequency;
    
    led1.allume();
    speaker1.sonne(current_frequency);
    
    // attack
    for(int i = 0; i < attack_duration; i++)
    {
        attack();
    }
    // time = 0;
    
    //decay
/*    for(int i = 0; i < decay_duration; i++)
    {
        decay();
    }*/
    // time = 0;
    
    speaker1.arreteDeSonner();
    led1.eteint();
}
void Kick::attack()
{
    float b = attack_duration / 10 * potentiometer1.etat();
    float x = millis();
    
    float coef = x / b;
    current_frequency = current_frequency * coef;
    
    attendre(sample_rate);
}
void Kick::decay()
{
    int decay_starting_value = 100;
    float a = decay_starting_value;
    float c = decay_duration * potentiometer2.etat();
    // fonction map
    float x = millis();
    
    float coef = exp(x*(1/c))*a;
    current_frequency = current_frequency * coef;
    
    time += sample_rate;
    attendre(sample_rate);
}


Kick kick1(220, 5, 250, 1);

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
