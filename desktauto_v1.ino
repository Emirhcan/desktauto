#include <Stepper.h>

const int stepsPerRevolution = 200;
// Configurez le nombre de pas par tour pour votre moteur
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int buttonDown = 2;    // Numéro de broche pour le bouton de descente
int buttonUp = 3;      // Numéro de broche pour le bouton de montée
int buttonFavorite = 4;// Numéro de broche pour le bouton de position favorite
int currentPosition = 0;  // La position actuelle du bureau
int favoritePosition = 100;  // La position favorite du bureau

void setup() {
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonFavorite, INPUT_PULLUP);

  // Initialisez la position de départ du bureau
  myStepper.setSpeed(30);
  myStepper.step(currentPosition * stepsPerRevolution / 360);
}

void loop() {
  // Vérifiez si le bouton de descente est enfoncé
  if (digitalRead(buttonDown) == LOW) {
    currentPosition -= 10;
    if (currentPosition < 0) {
      currentPosition = 0;
    }
    myStepper.step(-10 * stepsPerRevolution / 360);
    delay(100);
  }

  // Vérifiez si le bouton de montée est enfoncé
  if (digitalRead(buttonUp) == LOW) {
    currentPosition += 10;
    if (currentPosition > 100) {
      currentPosition = 100;
    }
    myStepper.step(10 * stepsPerRevolution / 360);
    delay(100);
  }

  // Vérifiez si le bouton de position favorite est enfoncé
  if (digitalRead(buttonFavorite) == LOW) {
    myStepper.step((favoritePosition - currentPosition) * stepsPerRevolution / 360);
    currentPosition = favoritePosition;
    delay(100);
  }
}
