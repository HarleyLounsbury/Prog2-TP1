#include "fonctions.h"

int lireNombre()
{
	// Pour lire toutes les b�tises que pourrait taper l'utilisateur, on se cr�e une variable de type cha�ne de caract�res
	// suffisamment longue.
	const int iMAXCLAVIER = 8190;
	char cClavier[iMAXCLAVIER + 1];
	int iNb;

	cin.getline(cClavier, sizeof(cClavier), '\n');

	// On lit toute ce que l'utilisateur tape au clavier dans une cha�ne de caract�res
	// qui accepte n'importe quel caract�re.

	// atof permet de convertir la cha�ne en valeur num�rique de type double
	// MAIS: elle retourne 0 si elle ne peut pas faire la convertion.

	// il faut s'assurer que cClavier commence par un chiffre sinon on redemande � l'utilisateur

	while (!((cClavier[0] >= '0' && cClavier[0] <= '9') || (cClavier[0] == '-' && (cClavier[1] >= '0' && cClavier[1] <= '9'))))
	{
		cout << "Erreur: Vous devez entrer un nombre: ";
		cin.getline(cClavier, sizeof(cClavier), '\n');
	}

	// Convertir la cha�ne de caract�res en entier.
	iNb = atoi(cClavier);

	return iNb;
}

void afficherMenuPrincipale()
{
	// �ffacer l'�cran avant d'afficher (au d�but du programme, ce n'est pas n�cessaire, mais quand on retourne au
	// menu principale d'ailleurs, on en a besoin.
	system("cls");

	// En-t�te
	cout << setw(iLARGEUR_MENU) << setfill('-') << "-" << setfill(' ') << endl;
	cout << setw((iLARGEUR_MENU - strlen(cTITRE)) / 2) << setfill(' ') << " " << cTITRE << endl;
	cout << setw((iLARGEUR_MENU - strlen(cAUTEUR)) / 2) << setfill(' ') << " " << cAUTEUR << endl;
	cout << setw(iLARGEUR_MENU) << setfill('-') << "-" << setfill(' ') << endl;

	cout << endl;

	// Menu des options
	cout << setw(iLARGEUR_MENU) << setfill('-') << "-" << setfill(' ') << endl;
	cout << cREGLES << endl;
	cout << cCONFIGURER << endl;
	cout << cCOMMENCER_PARTIE << endl;
	cout << cAFFICHER_ET_SAUVEGARDER << endl;
	cout << cQUITTER << endl;
	cout << setw(iLARGEUR_MENU) << setfill('-') << "-" << setfill(' ') << endl;
	cout << "Votre choix -- >";
}

int saisirChoixMenuPrincipale()
{
	// Appel � la fonction lireNombre pour assurer que iNb est bien un nombre.
	int iNb = lireNombre();
	// Boucle pour assurer que l'utilisateur n'a pas fait une mauvaise touche.
	while (!validerChoixMenuPrincipale(iNb))
	{
		afficherErreurDuChoix();
		afficherMenuPrincipale();
		iNb = lireNombre();
	}

	return iNb;
}

bool validerChoixMenuPrincipale(int iChoixMenu)
{
	// Si l'utilisateur frappe une option qui n'existe pas, on va dire la validation �tait un �chec, on retourne false.
	// Autrement, on retourne true.
	if(iChoixMenu < iMIN_MENU || iChoixMenu > iMAX_MENU)
	{
		return false;
	}
	return true;
}

void afficherErreurDuChoix()
{
	// Afficher un message d'erreur.
	cout << "Erreur : Le choix doit �tre compris entre " << iMIN_MENU << " et " << iMAX_MENU << endl;
	system("pause");
}

void erreurMenu()
{
	// Afficher un message d'erreur.
	cout << "Vous devez configurer le jeu avant de jouer." << endl;
	system("pause");
}

void erreurMenu2()
{
	// Afficher un message d'erreur.
	cout << "Vous devez jouer au jeu avant de faire �a!" << endl;
	system("pause");
}

void afficherReglesDuJeu()
{
	// �ffacer l'�cran avant d'afficher.
	system("cls");

	// Variables pour les fichiers externes.
	ifstream ifCanal;

	// Appel du fonction pour ouvrir le fichier.
	ouvrirFichierRegles(ifCanal);

	// Stock� chaque ligne dans la variable.
	char cLigne[iMAX_LIGNE];

	// Lire la premi�re ligne du fichier.
	ifCanal.getline(cLigne, iMAX_LIGNE, '\n');

	// Lire tant qu'on arrive pas � la fin du fichier.
	while (!ifCanal.eof())
	{
		// Afficher la ligne.
		cout << cLigne << endl;
		// Lire la prochaine ligne du fichier.
		ifCanal.getline(cLigne, iMAX_LIGNE, '\n');
	}

	// � la fin, on ferme le fichier et donne � l'utilisateur le temps de lire les r�gles avec une pause.
	ifCanal.close();
	system("pause");
}

void ouvrirFichierRegles(ifstream & ifCanal)
{
	// Fonction pour ouvrir le ficher.
	ifCanal.open(cNOM_FICHIER_REGLES, ios::out);
	// Message d'erreur en cas d'�chec. 
	if (!ifCanal)
	{
		cerr << "Erreur : Le fichier " << cNOM_FICHIER_REGLES << " n'a pas pu se cr�er" << endl;
		system("pause");
		exit(1);
	}
}

void configurerJeu(char * &ptrNomDesJoueurs, int* &ptrPoints, int* &ptrNb_Char_Noms, int & iNbJoueurs)
{
	iNbJoueurs = demanderNombreDeJoueurs();
	// Allocation de m�moire en fonction du nombre de joueurs.
	ptrNomDesJoueurs = creerTableauChars(iNbJoueurs * iMAX_NOM); 
	ptrPoints = creerTableauInt(iNbJoueurs * iPOINTS_INDICES);
	ptrNb_Char_Noms = creerTableauInt(iNbJoueurs);
	demanderNomsJoueurs(ptrNomDesJoueurs, ptrNb_Char_Noms, iNbJoueurs);

	system("pause");
}

int demanderNombreDeJoueurs()
{
	// �ffacer l'�cran avant d'afficher.
	system("cls");
	cout << "Veuillez entrer le nombre de joueurs participant au jeu (minimum 2, maximum 4) :";
	int iNb;

	iNb = lireNombre();

	// Boucle pour assurer que le nombre de joueurs est bien dans les limites.
	while (iNb < iMIN_JOUEURS || iNb > iMAX_JOUEURS)
	{
		cout << "Erreur de saisie" << endl;
		cout << "Veuillez entrer le nombre de joueurs participant au jeu (minimum 2, maximum 4) :";
		iNb = lireNombre();
	}
	
	return iNb;
}

void demanderNomsJoueurs(char* ptrNomJoueurs, int* ptrNb_Char_Noms, int iNbJoueurs)
{
	// Pour lire toutes les b�tises que pourrait taper l'utilisateur, on se cr�e une variable de type cha�ne de caract�res
	// suffisamment longue.
	const int iMAXCLAVIER = 8190;
	char cClavier[iMAXCLAVIER + 1];

	for (int i = 0; i < iNbJoueurs; i++)
	{
		cout << "Veuillez entrer le nom du joueur #" << i + 1 << "(maximum " << iMAX_NOM << " caract�res) :";
		cin.getline(cClavier, iMAXCLAVIER, '\n');
		
		// Si le nom du joueur est moins de 15 caract�res, on va compter ce nombre et stocker le chiffre appropri�. Autrement, on va stocker 15.
		if (strlen(cClavier) < iMAX_NOM)
			*(ptrNb_Char_Noms + i) = strlen(cClavier);
		else
			*(ptrNb_Char_Noms + i) = 15;

		// Transfer du nom du joueur de la variable temporaire au tableau du configuration, caract�re par caract�re.
		for (int j = 0; j < iMAX_NOM; j++)
		{
			*(ptrNomJoueurs + i * iMAX_NOM + j) = *(cClavier + j);
		}
	}
}

char * creerTableauChars(const int iTAILLE)
{
	// Pointeur temporaire.
	char* ptrTab = new char[iTAILLE];

	// Message d'erreur.
	if (ptrTab == nullptr)
	{
		cerr << "Erreur: m�moire insuffisante." << endl;
		system("pause");
		abort();
	}

	return ptrTab;
}

int * creerTableauInt(const int iTAILLE)
{
	// Pointeur temporaire.
	int* ptrTab = new int[iTAILLE];

	// Message en cas d'erreur.
	if (ptrTab == nullptr)
	{
		cerr << "Erreur: m�moire insuffisante." << endl;
		system("pause");
		abort();
	}

	return ptrTab;
}

void commencerPartie(char * ptrNomDesJoueurs, int* ptrNb_Chars_Noms, int* ptrPoints, int iNbJoueurs)
{
	initialiserPoints(ptrPoints, iNbJoueurs);
	// Le nom de la variable dit tout.
	int iCompteurTours = 0;
	
	// Boucle pour chaque tour du jeu (l'ensemble des joueurs).
	// Chaque joueur va jouer 13 tours, donc la limite de tours de jeu est 13 * le nombre de joueurs. On va tenir compte de quel joueur joue en faisant le modulo de iCompteurTours et le nombre de joueurs.
	// Cela fonctionne tr�s bien, car les possibles r�ponses sont de 0 � le nombre de joueurs - 1...qui est le multiplicateur quand on veut chercher les donn�s d'un joueur! Et que la programmation est bien fait :)
	for (iCompteurTours; iCompteurTours < iMAX_TOURS * iNbJoueurs; iCompteurTours++)
	{
		afficherGrilleDuJeu(ptrNomDesJoueurs, ptrNb_Chars_Noms, ptrPoints, iNbJoueurs, cout);

		tourJoueur(ptrNomDesJoueurs, ptrNb_Chars_Noms, iNbJoueurs, iCompteurTours % iNbJoueurs, ptrPoints);
	}

	// Possible ajout au jeu:
	//afficherGagnant(ptrNomDesJoueurs, ptrNb_Chars_Noms, ptrPoints, iNbJoueurs);
}

void initialiserPoints(int * ptrPoints, int iNbJoueurs)
{
	// Passer le tableau de points dans une boucle pour mettre les valeurs � 999 pour afficher/pas afficher.
	// Le nombre 999 a �t� choisi arbitrairement pour l'affichage, et ne sera pas compt� dans les totaux.
	for (int i = 0; i < iNbJoueurs; i++)
	{
		for (int j = 0; j < iPOINTS_INDICES; j++)
		{
			*(ptrPoints + i * iPOINTS_INDICES + j) = 999;
		}
	}
}

void afficherGrilleDuJeu(char * ptrNomDesJoueurs, int* ptrNb_Chars_Noms, int* &ptrPoints, int iNbJoueurs, ostream& of)
{
	// �ffacer l'�cran avant d'afficher.
	system("cls");
	// Avant d'afficher quoi que ce soit, on va calculer les totaux.
	calculerTotaux(ptrPoints, iNbJoueurs);
	// Ligne de tirets.
	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;
	of << setw(iCOL_GRILLE + 1) << setfill(' ') << "|";

	// Ligne avec les noms des joueurs.
	for (int i = 0; i < iNbJoueurs; i++)
	{
		of << setw((iCOL_GRILLE - *(ptrNb_Chars_Noms + i)) / 2 + 1) << setfill(' ');
		for (int j = 0; j < *(ptrNb_Chars_Noms + i); j++)
		{
			of << *(ptrNomDesJoueurs + i * iMAX_NOM + j);
		}
		of << setw((iCOL_GRILLE - *(ptrNb_Chars_Noms + i)) / 2) << setfill(' ') << "|";
	}
	of << endl;

	// Ligne de tirets.
	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	// En-t�te de partie mineure.
	of << left << setw(iCOL_GRILLE) << "Partie mineure" << "|" << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	// On continue ligne par ligne de la grille de points.
	of << left << setw(iCOL_GRILLE) << "1. Un" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 0, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "2. Deux" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 1, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "3. Trois" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 2, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "4. Quatre" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 3, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "5. Cinq" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 4, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "6. Six" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 5, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "SOUS TOTAL" << "|";
	afficherLigneTotaux(ptrPoints, iNbJoueurs, 13, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;
	
	of << left << setw(iCOL_GRILLE) << "PRIME" << "|";
	afficherLigneTotaux(ptrPoints, iNbJoueurs, 14, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "TOTAL 1" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 15, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "Partie majeure" << "|" << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "7. Brelan" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 6, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "8. Full" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 7, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "9. Petite Suite" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 8, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "10. Grande Suite" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 9, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "11. Carr�" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 10, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "12. YUM" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 11, of);
	of << endl;

	of << left << setw(iCOL_GRILLE) << "13. Chance" << "|";
	afficherLignePoints(ptrPoints, iNbJoueurs, 12, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "TOTAL 2" << "|";
	afficherLigneTotaux(ptrPoints, iNbJoueurs, 16, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;

	of << left << setw(iCOL_GRILLE) << "TOTAL FINAL" << "|";
	afficherLigneTotaux(ptrPoints, iNbJoueurs, 17, of);
	of << endl;

	of << setw(iCOL_GRILLE + (iNbJoueurs * iCOL_GRILLE)) << setfill('-') << "-" << setfill(' ') << endl;
}

int retournePoints(int * ptrPoints, int iJoueur, int iIndexe)
{
	// Chercher dans le tableau de points pour les points d'un champ d'un joueur.
	int iPointsARetourner = *(ptrPoints + iPOINTS_INDICES * iJoueur + iIndexe);
	
	return iPointsARetourner;
}

void afficherLignePoints(int* &ptrPoints, int iNbJoueurs, int iIndexe, ostream& of)
{
	// Boucle pour cycler en travers les joueurs pour le champ de points r�quise.
	for (int i = 0; i < iNbJoueurs; i++)
	{
		of << right << setw(iCOL_GRILLE / 2 + 1);
		// Si le champ de points n'est pas �gal � 999, on va l'afficher. (et donc voila pourquoi on a choisi le chiffre 999...0 peut quand-m�me �tre une valeur de points!)
		(retournePoints(ptrPoints, i, iIndexe) != 999 ? of << retournePoints(ptrPoints, i, iIndexe) : of << "  ");
		of << setw((iCOL_GRILLE - 1) / 2) << setfill(' ') << "|";
	}
}

void afficherLigneTotaux(int *& ptrPoints, int iNbJoueurs, int iIndexe, ostream& of)
{
	// Calculer les totaux avant d'afficher.
	calculerTotaux(ptrPoints, iNbJoueurs);
	for (int i = 0; i < iNbJoueurs; i++)
	{
		// M�me principe que afficherLignePoints()
		of << right << setw(iCOL_GRILLE / 2 + 1);
		(retournePoints(ptrPoints, i, iIndexe) >= 0 ? of << retournePoints(ptrPoints, i, iIndexe) : of << "  ");
		of << setw((iCOL_GRILLE - 1) / 2) << setfill(' ') << "|";
	}
}

void calculerTotaux(int * &ptrPoints, int iNbJoueurs)
{
	// Boucle pour calculer les sommes par joueur.
	for (int i = 0; i < iNbJoueurs; i++)
	{
	// Variable temporaire pour chaque somme.
	int iSousTotal = 0;
	int iTotal1 = 0;
	int iTotal2 = 0;
		// Sous-total partie mineure.
		for (int j = 0; j < 6; j++)
		{
			// On ajoute la valeur d'un champ s'il n'est pas 999.
			if (*(ptrPoints + i * iPOINTS_INDICES + j) != 999)
				iSousTotal += *(ptrPoints + i * iPOINTS_INDICES + j);
		}
		*(ptrPoints + i * iPOINTS_INDICES + 13) = iSousTotal;

		// V�rifier si la prime s'applique.
		(iSousTotal >= 63 ? *(ptrPoints + i * iPOINTS_INDICES + 14) = 37 : *(ptrPoints + i * iPOINTS_INDICES + 14) = 0);


		// Total 1 partie mineure.
		for (int j = 13; j < 15; j++) 
		{
			if (*(ptrPoints + i * iPOINTS_INDICES + j) != 999)
				iTotal1 += *(ptrPoints + i * iPOINTS_INDICES + j);
		}
		*(ptrPoints + i * iPOINTS_INDICES + 15) = iTotal1;
		// Total 2 partie majeure.
		for (int j = 6; j < 13; j++)
		{
			if (*(ptrPoints + i * iPOINTS_INDICES + j) != 999)
				iTotal2 += *(ptrPoints + i * iPOINTS_INDICES + j);
		}
		*(ptrPoints + i * iPOINTS_INDICES + 16) = iTotal2;
		*(ptrPoints + i * iPOINTS_INDICES + 17) = iTotal1 + iTotal2;
	}
}

void tourJoueur(char * ptrNomDesJoueurs, int * ptrNb_Chars_Noms, int iNbJoueurs, int iJoueurTour, int* &ptrPoints)
{
	// Afficher c'est � qui de jouer.
	afficherAQuiLeTour(ptrNomDesJoueurs, ptrNb_Chars_Noms, iJoueurTour);
	// Les trois jets de d�s.
	roulerLesDes(ptrPoints, iNbJoueurs, iJoueurTour);
}

void afficherAQuiLeTour(char * ptrNomDesJoueurs, int * ptrNb_Chars_Noms, int iJoueurTour)
{
	// Afficher le joueur � qui c'est le tour.
	cout << "C'est � ";
	for (int i = 0; i < *(ptrNb_Chars_Noms + iJoueurTour); i++)
	{
		cout << *(ptrNomDesJoueurs + iJoueurTour * iMAX_NOM + i);
	}
	cout << " de jouer: ";
	cout << endl << endl;
}

int deAleatoire()
{
	// Choisir un nombre al�atoire entre 1 et 6 inclusivement.
	return rand() % (iMAX_DE - iMIN_DE + 1) + iMIN_DE;
}

void trierCombinaison(int* ptrJet)
{
	// Boucle pour compter le nombre de passes.
	for (int iNombreDePasses = 0; iNombreDePasses < iDES; iNombreDePasses++)
	{
		// Boucle pour traiter le tableau index par index.; i++
		for (int iCompteur = 0; iCompteur < iDES - 1; iCompteur++)
		{
			// On va compar� deux nombres qui sont c�te � c�te, et si celui avec le plus petit index est plus grand, on appelle 
			// la fonction pour les �changer de place. 
			if (*(ptrJet + iCompteur) > *(ptrJet + iCompteur + 1))
			{
				permuter(*(ptrJet + iCompteur), *(ptrJet + iCompteur + 1));
			}
		}
	}
}

void permuter(int & iChiffre1, int & iChiffre2)
{
	// Variable interm�diaire.
	int iTemp;
	// On copie la valeur du premier nombre dans la variable.
	iTemp = iChiffre1;
	// On �crase le premier avec le deuxi�me.
	iChiffre1 = iChiffre2;
	// On copie le premier dans le deuxi�me.
	iChiffre2 = iTemp;
}

void roulerLesDes(int *& ptrPoints, int iNbJoueurs, int iJoueurTour)
{
	// Tableau temporaire pour les d�s, avant de les stocker chez le joueur.
	// Valeurs de 0 choisis pour controler lesquels seront garder par le joueur, et faciliter de lecture dans le code.
	int iJet[iDES] = { 0, 0, 0, 0, 0 };
	
	// Boucle pour 3 jets du joueur par tour.
	// Pas besoin d'une constante ici, car c'est les r�gles fixes du jeu, avec l'optique que le choix de -1 est consider� comme un cas sp�ciale.
	// Il va afficher et demander 2 fois, le troisi�me fois ce n'est que de l'affichage.
	for (int i = 0; i < 3; i++)
	{
		cout << "Lanc� #" << i + 1 << ": " << endl;
		// Imprimer chaque d�.
		// Parcourir le tableau en mettant des valeurs de d�s al�atoire dans chaque case.
		genererUnDe(iJet);
		// Trier en ordre croissant.
		trierCombinaison(iJet);
		// Afficher le jet.
		afficherDes(iJet);
		// On demande de de garder des d�s pour la premi�re (i = 0) et deuxi�me (i = 1) jets.
		if (i <= 1)		
		demanderChoixDeDes(iJet, i); // Ici on passe i par r�f�rence pour le cas que le joueur aime ses d�s et choisi -1 pour les garder. 
	}
	// Mettre le points accumul� dans le tableau de points.
	placerPoints(ptrPoints, iJet, demanderFigure(ptrPoints, iJoueurTour), iJoueurTour, iNbJoueurs);
}

void afficherDes(int * ptrJet)
{
	// Le nom de la fonction dit 1000 mots.
	for (int i = 0; i < iDES; i++)
	{
		cout << *(ptrJet + i) << " ";
	}
	cout << endl;
}

void demanderChoixDeDes(int * ptrJet, int &iCompteur)
{
	// Tableau pour si le joueur r�pond avec les lettres 'o' ou 'n'
	char* ptrChoix = new char[iDES];

	// Saisir la r�ponse du joueur.
	saisirChoixDeDes(ptrChoix);

	// Garder le num�ro, si choisi par le joueur.
	switch (*(ptrChoix))
	{
	case '-':
		// Pour termin� le tour de joueur et garder les d�s.
		if (*(ptrChoix) == '-' && *(ptrChoix + 1) == '1')
			// Mettre la valeur � deux (une valeur autrement impossible dans la boucle), pour ne pas faire la troisi�me brass� de d�s.
			iCompteur = 3;
		break;
	// Les cas 1 � 6 pour quand le joueur veut garder un chiffre en particulier.
	case '1':
		garderNumero(ptrJet, 1);
		break;
	case '2':
		garderNumero(ptrJet, 2);
		break;
	case '3':
		garderNumero(ptrJet, 3);
		break;
	case '4':
		garderNumero(ptrJet, 4);
		break;
	case '5':
		garderNumero(ptrJet, 5);
		break;
	case '6':
		garderNumero(ptrJet, 6);
		break;
	default:
		// Si le joueur frappe des lettres, o� il a frappe des 'o' seront garder, autrement, ils sont r�initialis� � 0 (valeur impossible de d�) pour la fonction qui g�n�re des d�s al�atoire.
		for (int i = 0; i < iDES; i++)
		{
			if (*(ptrChoix + i) != 'o')
			{
				*(ptrJet + i) = 0;
			}
		}
		break;
	}
	// Supprimer la m�moire dynamique.
	// Honn�tement, je ne sais pas si c'est obligatoire, alors que le pointeur est encapsul� dans la fonction. Une qu�stion pour apr�s l'examen. 
	delete ptrChoix;
}

void garderNumero(int* &ptrJet, int iNumAGarder)
{
	// Parcourir le tableau et garder seulement ceux que l'utilisateur a choisi. Les autres, on va mettre a '0'.
	for (int i = 0; i < iDES; i++)
	{
		if (*(ptrJet + i) != iNumAGarder)
		{
			*(ptrJet + i) = 0;
		}
	}
}

void genererUnDe(int * ptrJet)
{
	// Parcourir le tableau et mettre des valeurs al�atoire en place des 0.
	for (int i = 0; i < iDES; i++)
	{
		if (*(ptrJet + i) == 0)
			*(ptrJet + i) = deAleatoire();
	}
}

int demanderFigure(int* ptrPoints, int iJoueurTour)
{
	// Variable temporaire.
	int iFigure;
	// Demander la figure.
	cout << "Veuillez indiquer la figure de 1 � 13 dans laquelle vous souhaitez enregistrer vos points: ";
	// Assurer que c'est bien un nombre.
	iFigure = lireNombre();
	// Assurer que l'option est possible. 
	while ((iFigure < 1 || iFigure > 13) || *(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) != 999)
	{
		cout << "Erreur de saisie : Le choix doit �tre compris entre 1 et 13 et cette figure doit �tre libre." << endl;
		cout << "Veuillez indiquer la figure de 1 � 13 dans laquelle vous souhaitez enregistrer vos points: ";
		cin >> iFigure;
	}
	return iFigure;
}

void placerPoints(int * &ptrPoints, int * ptrJet, int iFigure, int iJoueurTour, int iNbJoueurs)
{
	// Selon quel figure le joueur a choisi et quels d�s sont pr�sent.
	switch (iFigure)
	{
	case 1:
	case 2:	
	case 3:	
	case 4:	
	case 5:	
	case 6:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesPartieMineure(ptrJet, iFigure);
		break;
	case 7:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesBrelan(ptrJet);
		break;
	case 8:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesFull(ptrJet);
		break;
	case 9:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesPetiteSuite(ptrJet);
		break;
	case 10:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesGrandeSuite(ptrJet);
		break;
	case 11:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesCarre(ptrJet);
		break;
	case 12:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesYum(ptrJet);
		break;
	case 13:
		*(ptrPoints + (iJoueurTour * iPOINTS_INDICES) + iFigure - 1) = analyserDesChance(ptrJet);
		break;
	}
}

int analyserDesPartieMineure(int * ptrJet, int iFigure)
{
	// On part le compteur � 0, car si l'utilisateur n'en a pas de d�s pour la figure qu'il a choisi, ses points sont 0!
	int iCompteurPoints = 0;
	for (int i = 0; i < iDES; i++)
	{
		// Faire la somme des d�s choisi, s'ils sont pr�sent.
		if (*(ptrJet + i) == iFigure)
		{
			iCompteurPoints += iFigure;
		}
	}
	return iCompteurPoints;
}

void saisirChoixDeDes(char * &ptrChoix)
{
	// Pour lire toutes les b�tises que pourrait taper l'utilisateur, on se cr�e une variable de type cha�ne de caract�res
	// suffisamment longue.
	const int iMAXCLAVIER = 8190;
	char cClavier[iMAXCLAVIER + 1];

	// On lit toute ce que l'utilisateur tape au clavier dans une cha�ne de caract�res
	// qui accepte n'importe quel caract�re.
	cin.getline(cClavier, sizeof(cClavier), '\n');

	// Transf�re de caract�res. (que les 5 premi�res)
	for (int i = 0; i < iDES; i++)
		*(ptrChoix + i) = *(cClavier + i);
}

int analyserDesBrelan(int * ptrJet)
{
	// Pour savoir si le joueur a 3 ou plus.
	int iCompteurBrelan;
	int iCompteurPoints = 0;
	for (int i = 0; i < iDES - 1; i++)
	{
		// On commence avec le premier, et on assume que c'est le bon. Si ce n'est pas, la prochaine passe dans la boucle va le remettre � 1.
		iCompteurPoints = *(ptrJet + i);
		iCompteurBrelan = 1;
		
		for (int j = i + 1; j < iDES; j++)
		{
			if (*(ptrJet + i) == *(ptrJet + j))
			{
				iCompteurPoints += *(ptrJet + i);
				iCompteurBrelan++;
			}
		}
		// Si on a 3 ou plus, on peut arr�ter.
		if (iCompteurBrelan >= 3)
		{
			return iCompteurPoints;
		}
	}
	return 0;
}

int analyserDesFull(int * ptrJet)
{
	// Il existe deux options: 2 pareil + 3 pareil ou 3 pareil + 2 pareil
	// Pour v�rifier si c'est 2+3 ou 3+2.
	if ((*(ptrJet) == *(ptrJet + 1)) && (*(ptrJet + 2) == *(ptrJet + 3) && *(ptrJet + 3) == *(ptrJet + 4)) || (*(ptrJet) == *(ptrJet + 1) && *(ptrJet + 1) == *(ptrJet + 2) && (*(ptrJet + 3) == *(ptrJet + 4))))
		return 30;
	else
		return 0;
}

int analyserDesPetiteSuite(int * ptrJet)
{
	// Condition pour v�rifier la suite. (1, 2, 3, 4, 5)
	if (*(ptrJet) == 1 && *(ptrJet + 1) == 2 && *(ptrJet + 2) == 3 && *(ptrJet + 3) == 4 && *(ptrJet + 4) == 5)
		return 40;
	else
		return 0;
}

int analyserDesGrandeSuite(int * ptrJet)
{
	// Condition pour v�rifier la suite. (2, 3, 4, 5, 6)
	if (*(ptrJet) == 2 && *(ptrJet + 1) == 3 && *(ptrJet + 2) == 4 && *(ptrJet + 3) == 5 && *(ptrJet + 4) == 6)
		return 40;
	else
		return 0;
}

int analyserDesCarre(int * ptrJet)
{
	// Il existe deux possibilit�s: (4 pareil + 1 pareil ou non) ou (1 pareil ou non + 4 pareil)
	// De toute fa�on, on a juste � v�rifier sooit les 4 premiers ou les 4 derniers.
	if ((*(ptrJet) == *(ptrJet + 1) && *(ptrJet + 1) == *(ptrJet + 2) && *(ptrJet + 2) == *(ptrJet + 3)) || *(ptrJet + 1) == *(ptrJet + 2) && *(ptrJet + 2) == *(ptrJet + 3) && *(ptrJet + 4))
		return 40;
	else
		return 0;
}

int analyserDesYum(int * ptrJet)
{
	// V�rifier qu'ils sont toutes pareils.
	if (*(ptrJet) == *(ptrJet + 1) && *(ptrJet + 1) == *(ptrJet + 2) && *(ptrJet + 2) == *(ptrJet + 3) && *(ptrJet + 3) == *(ptrJet + 4))
		return 50;
	else
		return 0;
}

int analyserDesChance(int * ptrJet)
{
	// Faire la somme des valeurs de d�s.
	int iCompteurPoints = 0;
	for (int i = 0; i < iDES; i++)
	{
		iCompteurPoints += *(ptrJet + i);
	}
	return iCompteurPoints;
}

void afficherEtSauvegarder(char * ptrNomDesJoueurs, int * ptrNb_Char_Noms, int * ptrPoints, int iNbJoueurs)
{
	// Afficher la grille du jeu.
	afficherGrilleDuJeu(ptrNomDesJoueurs, ptrNb_Char_Noms, ptrPoints, iNbJoueurs, cout);

	system("pause");

	// Sauvegarder la grille du jeu.
	sauvegarderGrille(ptrNomDesJoueurs, ptrNb_Char_Noms, ptrPoints, iNbJoueurs);
}

void sauvegarderGrille(char * ptrNomDesJoueurs, int * ptrNb_Char_Noms, int * ptrPoints, int iNbJoueurs)
{
	// On est sur la 15 sud.
	ofstream ofCanal;
	creerFichier(ofCanal, cNOM_FICHIER_SAUVEGARDE);
	// �ffectue la m�me chose que quand on affiche � l'�cran, mais avec ofCanal comme param�tre, on �crit directment dans le fichier. Merci Mme. Moreau :)
	afficherGrilleDuJeu(ptrNomDesJoueurs, ptrNb_Char_Noms, ptrPoints, iNbJoueurs, ofCanal);
	// ecrireGrilleDansFichier(ptrNomDesJoueurs, ptrNb_Char_Noms, ptrPoints, iNbJoueurs, ofCanal);

	// Fermer!
	// Une chance qu'on ne ferme jamais la 15 sud!
	ofCanal.close();
}

void creerFichier(ofstream & ofCanal, const char cNOMFICHIER[])
{
	// Fonction pour ouvrir le ficher.
	ofCanal.open(cNOMFICHIER, ios::out);
	// Message d'erreur en cas d'�chec. 
	if (!ofCanal)
	{
		cerr << "Erreur : Le fichier " << cNOMFICHIER << " n'a pas pu se cr�er" << endl;
		system("pause");
		exit(1);
	}
}