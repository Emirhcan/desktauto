//Déclaration des broches du moteur
const int moteurPin1 = 2;
const int moteurPin2 = 3;
const int moteurPin3 = 4;
const int moteurPin4 = 5;

//Déclaration des broches des boutons
const int bouton1Pin = 6;
const int bouton2Pin = 7;
const int bouton3Pin = 8;

//Variables pour stocker l'état des boutons
int etatBouton1 = 0;
int etatBouton2 = 0;
int etatBouton3 = 0;

//Variable pour stocker la hauteur actuelle du bureau
int hauteurBureau = 70;

//Fonction pour faire monter le bureau
void monterBureau() {
  digitalWrite(moteurPin1, HIGH);ààà
  digitalWrite(moteurPin2, LOW);
  digitalWrite(moteurPin3, HIGH);
  digitalWrite(moteurPin4, LOW);
}

//Fonction pour faire descendre le bureau
void descendreBureau() {
  digitalWrite(moteurPin1, LOW);
  digitalWrite(moteurPin2, HIGH);
  digitalWrite(moteurPin3, LOW);
  digitalWrite(moteurPin4, HIGH);
}

//Fonction pour arrêter le moteur
void arreterMoteur() {
  digitalWrite(moteurPin1, LOW);
  digitalWrite(moteurPin2, LOW);
  digitalWrite(moteurPin3, LOW);
  digitalWrite(moteurPin4, LOW);
}

void setup() {
  //Initialisation des broches du moteur en mode sortie
  pinMode(moteurPin1, OUTPUT);
  pinMode(moteurPin2, OUTPUT);
  pinMode(moteurPin3, OUTPUT);
  pinMode(moteurPin4, OUTPUT);

  //Initialisation des broches des boutons en mode entrée avec une résistance de pull-up
  pinMode(bouton1Pin, INPUT_PULLUP);
  pinMode(bouton2Pin, INPUT_PULLUP);
  pinMode(bouton3Pin, INPUT_PULLUP);
}

void loop() {
  //Lecture de l'état des boutons
  etatBouton1 = digitalRead(bouton1Pin);
  etatBouton2 = digitalRead(bouton2Pin);
  etatBouton3 = digitalRead(bouton3Pin);

  //Si le bouton 1 est appuyé, on fait monter le bureau
  if (etatBouton1 == LOW) {
    monterBureau();
    delay(10);
    arreterMoteur();
    hauteurBureau += 5;
  }

  //Si le bouton 2 est appuyé, on fait descendre le bureau
  if (etatBouton2 == LOW) {
    descendreBureau();
    delay(10);
    arreterMoteur();
    hauteurBureau -= 5;
  }

//Si le bouton 3 est appuyé, on positionne le bureau au centre
if (etatBouton3 == LOW) {
  //Calcul de la hauteur centrale
  int hauteurCentrale = (120 + 70) / 2;
  //Détermination du sens de rotation pour atteindre la hauteur centrale
  if (hauteurBureau < hauteurCentrale) {
    monterBureau();
    while (hauteurBureau < hauteurCentrale) {
      etatBouton1 = digitalRead(bouton1Pin);
      if (etatBouton1 == LOW) {
        arreterMoteur();
        break;
      }
      hauteurBureau += 5;
      delay(10);
    }
  } else {
    descendreBureau();
    while (hauteurBureau > hauteurCentrale) {
      etatBouton2 = digitalRead(bouton2Pin);
      if (etatBouton2 == LOW) {
        arreterMoteur();
        break;
      }
      hauteurBureau -= 5;
      delay(10);
    }
  }
  arreterMoteur();
}

//Si la hauteur du bureau est inférieure à la hauteur minimum, on l'arrête à cette hauteur
if (hauteurBureau <= 70) {
  arreterMoteur();
  hauteurBureau = 70;
}

//Si la hauteur du bureau dépasse la hauteur maximum, on l'arrête à cette hauteur
if (hauteurBureau >= 120) {
  arreterMoteur();
  hauteurBureau = 120;
}