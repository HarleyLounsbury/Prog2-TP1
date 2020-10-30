#pragma once

// Inclure les librairies nécessaire pour le roulement de programme.
// iostream pour gérer les entrées/sorties des données
#include <iostream>
// time.h pour générer une graine aléatoire basé sur l'heure du système actuelle.
#include <time.h>
// iomanip pour gérer l'affichage.
#include <iomanip>
// Pour le gestion des fichiers externes.
#include <fstream>

// Utilisé pour les symboles incluses dans std
using namespace std;

// Déclaration de constantes

// Titres
const int iLARGEUR_MENU = 49;
const char cTITRE[] = "Bienvenue au jeu de Yum";
const char cAUTEUR[] = "Présenté par Harley Lounsbury";
 
// Options de menu
// Mises en constantes pour simplifier l'affichage.
const char cREGLES[] = "1. Lire les règles du jeu";
const char cCONFIGURER[] = "2. Configurer le jeu";
const char cCOMMENCER_PARTIE[] = "3. Commencer la partie";
const char cAFFICHER_ET_SAUVEGARDER[] = "4. Afficher et sauvegarder la grille de points";
const char cQUITTER[] = "5. Quitter";

// Constantes pour les choix du menu principale.
const int iMIN_MENU = 1;
const int iMAX_MENU = 5;
const int iREGLES = 1;
const int iCONFIGURER = 2;
const int iCOMMENCER_PARTIE = 3;
const int iAFFICHER_ET_SAUVEGARDER = 4;
const int iQUITTER = 5;

// Pour le fichier des règles.
const char cNOM_FICHIER_REGLES[] = "Regles du jeu de YUM.txt";
const int iMAX_LIGNE = 100;

// Pour le nombre de joueurs
const int iMIN_JOUEURS = 2;
const int iMAX_JOUEURS = 4;

// Pour le nombre de dés maximum.
const int iDES = 5;

// Pour le nombre de caractères permis dans le nom d'un joueur.
const int iMAX_NOM = 15;

// Affichage du grille du jeu
const int iCOL_GRILLE = 17;

// Pour les points
const int iSOUS_TOTAL_MIN = 63;

// Pour les points, ils seront indexé en ordre du jeu, avec le totaux à la fin.
// 0. les uns
// 1. les deux
// 2. les trois
// 3. les quatres
// 4. les cinqs
// 5. les six
// 6. Brelan
// 7. Full
// 8. Petite suite
// 9. Grande suite
// 10. Carré
// 11. YUM
// 12. Chance
// 13. sous-total (somme de partie mineure)
// 14. prime
// 15. Total 1
// 16. Total 2 (somme de partie majeure)
// 17. Total final

// On a donc besoin de 18 cases par joueur
const int iPOINTS_INDICES = 18;

// 13 tours max, par jeu.
const int iMAX_TOURS = 13;

// Les Dés
const int iMIN_DE = 1;
const int iMAX_DE = 6;

// Le nom du fichier pour sauvegarder.
const char cNOM_FICHIER_SAUVEGARDE[] = "Yum - Grille de points.txt";

// Structure pour les données.
struct Configuration
{
	// Variable pour le nombre de joueurs.
	int iNbJoueurs;

	// Les pointeurs pour allouer de la mémoire dynamiquement
	// Tableau pour le nom de chaque joueur. 
	char* ptrNomDesJoueurs = NULL;
	// Tableau pour stocké les points de chaque case de points.
	int* ptrPoints = NULL;
	// Pour savoir combien de caractères sont dans chaque nom.
	int* ptrNb_Char_Noms = NULL;
};

// Fonctions générique.
int lireNombre();


// Fonction pour afficher le menu principale
void afficherMenuPrincipale();

// Pour saisir le choix de l'utilisateur
int saisirChoixMenuPrincipale();

// Pour valider le choix de l'utilisateur.
bool validerChoixMenuPrincipale(int iChoixMenu);
void afficherErreurDuChoix();
void erreurMenu();
void erreurMenu2();

// Pour afficher les regles du jeu.
void afficherReglesDuJeu();
void ouvrirFichierRegles(ifstream & ifCanal);

// Pour configurer le jeu.
void configurerJeu(char* &ptrNomDesJoueurs, int* &ptrPoints, int* &ptrNb_Char_Noms, int & iNbJoueurs);
int demanderNombreDeJoueurs();
void demanderNomsJoueurs(char* ptrNomJoueurs, int* ptrNb_Char_Noms, int iNbJoueurs);
char* creerTableauChars(const int iTAILLE);
int* creerTableauInt(const int iTAILLE);

// Jouer au jeu
void commencerPartie(char* ptrNomDesJoueurs, int* ptrNb_Char_Noms, int* ptrPoints, int iNbJoueurs);
void initialiserPoints(int* ptrPoints, int iNbJoueurs);
void afficherGrilleDuJeu(char* ptrNomDesJoueurs, int* ptrNb_Char_Noms, int* &ptrPoints, int iNbJoueurs, ostream& of);
int retournePoints(int* ptrPoints, int iJoueur, int iIndexe);
void afficherLignePoints(int* &ptrPoints, int iNbJoueurs, int iIndexe, ostream& of);
void afficherLigneTotaux(int* &ptrPoints, int iNbJoueurs, int iIndexe, ostream& of);
void calculerTotaux(int* &ptrPoints, int iNbJoueurs);
void tourJoueur(char* ptrNomDesJoueurs, int* ptrNb_Chars_Noms, int iNbJoueurs, int iJoueurTour, int* &ptrPoints);
void afficherAQuiLeTour(char * ptrNomDesJoueurs, int * ptrNb_Chars_Noms, int iJoueurTour);
int deAleatoire();
void trierCombinaison(int* ptrJet);
void permuter(int & iChiffre1, int & iChiffre2);
void roulerLesDes(int* &ptrPoints, int iNbJoueurs, int iJoueurTour);
void afficherDes(int* ptrJet);
void demanderChoixDeDes(int* ptrJet, int &iCompteur);
void garderNumero(int* &ptrJet, int iNumAGarder);
void genererUnDe(int* ptrJet);
int demanderFigure(int* ptrPoints, int iJoueurTour);
void placerPoints(int* &ptrPoints, int* ptrJet, int iFigure, int iJoueurTour, int iNbJoueurs);
int analyserDesPartieMineure(int* ptrJet, int iFigure);
void saisirChoixDeDes(char* &ptrChoix);
int analyserDesBrelan(int* ptrJet);
int analyserDesFull(int* ptrJet);
int analyserDesPetiteSuite(int* ptrJet);
int analyserDesGrandeSuite(int* ptrJet);
int analyserDesCarre(int* ptrJet);
int analyserDesYum(int* ptrJet);
int analyserDesChance(int* ptrJet);

// Pour afficher et sauvegarder.
void afficherEtSauvegarder(char* ptrNomDesJoueurs, int* ptrNb_Char_Noms, int* ptrPoints, int iNbJoueurs);
void sauvegarderGrille(char* ptrNomDesJoueurs, int* ptrNb_Char_Noms, int* ptrPoints, int iNbJoueurs);
void creerFichier(ofstream& ofCanal, const char cNOMFICHIER[]);