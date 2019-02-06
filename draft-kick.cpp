#include "Led.h"

#include "Bouton.h"

#include "Son.h"

Led led1;

Bouton button1;

Son speaker1;

class Kick
{
    public:
        Kick();
        Kick(int frequency, int attack_duration_input, int decay_duration_input, int sample_rate_input);
        
        int time;
        int frequency;
        int sample_rate;
        int attack_duration;
        int decay_duration;
        int sutain;
        
        void jouer() const;
        void attack();
        void decay();
};
Kick::Kick(int frequency, int attack_duration_input, int decay_duration_input, int sample_rate_input)
{
    frequency = frequency_input;
    attack_duration = attack_duration_input;
    decay_duration = decay_duration_input;
    sample_rate = sample_rate_input;
}
void Kick::jouer() const
{
    led1.allume();
    speaker1.sonne(450);
    
    // attack
    attack();
    
    //decay
    decay();
    
    speaker1.arreteDeSonner();
    time = 0;
    led1.eteint();
}
void Kick::attack()
{
    float b = attack_duration / 10;
    float x = time;
    
    coef = x / b;
    
    frequency = frequency * coef;
    attendre(sample_rate);
}
void Kick::decay()
{
    int decay_starting_value = 100;
    float a = decay_starting_value;
    float c = decay_duration;
    float x = time;
    coef = exp(x*(1/c))*a;
    
    frequency = frequency * coef;
    attendre(sample_rate);
}


Kick kick1(5, 250, 1);

void setup()
{
    led1.allume();
    attendre(1*1000);
    led1.eteint();
}

void loop()
{
    if (button1.aEteAppuye()) {
        kick1.jouer(220);
    }

}
