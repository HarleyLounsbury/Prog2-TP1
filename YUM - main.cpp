// But: D�velopper le jeu de YUM en version console. - TP-1
// Auteur: Harley Lounsbury
// Date de d�but: 20/02/2019

#include "fonctions.h"

int main()
{
	// Pour afficher les caract�res sp�ciaux
	setlocale(LC_ALL, "");

	// Modifier le grandeur du console.
	system("mode con cols=90 lines=60");

	// Pour que le pseudo-al�atoire soit bas� sur l'heure du syst�me actuelle.
	srand(time(NULL));

	// Variable pour stock� le choix de l'utilisateur du menu principale.
	int iChoix;

	// Structure qui va contenir les donn�es du jeu.
	Configuration Config;

	// Afficher le menu principale.
	afficherMenuPrincipale();

	// Saisir le choix de l'utilisateur dans le menu principale.
	iChoix = saisirChoixMenuPrincipale();
	
	// V�rifier que l'utilisateur n'essaie pas de joueur ou afficher/sauvegarder avant d'avoir configurer le jeu.
	while (iChoix == 3 || iChoix == 4)
	{
		erreurMenu();
		afficherMenuPrincipale();
		iChoix = saisirChoixMenuPrincipale();
	}

	// Boucle pour contenir le programme principale.
	while (iChoix != iQUITTER)
	{		
		// Switch pour faire ce que l'utilisateur veut.
		switch (iChoix)  
		{
		case iREGLES:
			afficherReglesDuJeu();
			break;
		case iCONFIGURER:
			configurerJeu(Config.ptrNomDesJoueurs, Config.ptrPoints, Config.ptrNb_Char_Noms, Config.iNbJoueurs);
			break;
		case iCOMMENCER_PARTIE:
			commencerPartie(Config.ptrNomDesJoueurs, Config.ptrNb_Char_Noms, Config.ptrPoints, Config.iNbJoueurs);
			break;
		case iAFFICHER_ET_SAUVEGARDER:
			// if pour le cas sp�ciale que l'utilisateur essaie cette option apr�s avoir configurer le jeu. Les utilisateurs sont pr�ts � tout pour planter le programme. :)
			if (*(Config.ptrPoints) < 0)
			{
				erreurMenu2();
				break;
			}
			afficherEtSauvegarder(Config.ptrNomDesJoueurs, Config.ptrNb_Char_Noms, Config.ptrPoints, Config.iNbJoueurs);
				break;
		}
		afficherMenuPrincipale();
		iChoix = saisirChoixMenuPrincipale();
	}
	
	// Ergonomie.
	cout << endl;
	system("pause");
	// Supprimer la m�moire dynamique.
	delete [] Config.ptrNb_Char_Noms;
	delete [] Config.ptrNomDesJoueurs;
	delete [] Config.ptrPoints;
	return 0;
}
