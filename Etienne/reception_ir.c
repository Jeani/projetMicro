
	bool current_bit;
	
	char marge_haute = 1.2;
	char marge_basse = 0.8;
	
	int valeur_header = 9000;
	int valeur_bit1 = 1000;
	int valeur_bit0 = 2000;
	int valeur_stop = 45000;
	
	int valeur_stop_min = valeur_stop*marge_basse;
	int valeur_stop_max = valeur_stop*marge_haute
	int valeur_bit1_min = valeur_bit1*marge_basse;
	int valeur_bit1_max = valeur_bit1*marge_haute;
	int valeur_bit0_min = valeur_bit0*marge_basse;
	int valeur_bit0_max =  valeur_bit0*marge_haute
	int valeur_header_min = valeur_header*marge_basse;
	int valeur_header_max = valeur_header*marge_haute;


	bool flag_debut_transmission;
	bool flag_fin_transmission;
	bool flag_nouveau_bit;


	bool T[128];	// tableau de 128 bits
	char cpt;	// variable pour compter les bits
	bool flag_fin_enregistrement;
	bool flag_reception_bit;
	
	void enregistrement_message(bool);
	void init(void);
	bool capture_duree(int);

	cpt = 127;
	

/* Main ------------------------------------------------------------------------------ */

int main(void)
{
	
	
	while(1)
	{
		
		
	}


}



/* Initialisation des variables ----------------------------------------------------- */

void init()
{
	flag_debut_transmission = 0;
	flag_fin_transmission = 0;
	flag_fin_enregistrement = 0;
	flag_reception_bit = 0;
	
	flag_RCV = 0;
}


/* Initialisation du timer ---------------------------------------------------------- */

void TIMER0_IRQHandler()
{
	flag_RCV = TIM_GetIntStatus(TIMER0, TIM_CR0_INT);	// WTF ?
}


/* Capture du bit courant ----------------------------------------------------------- */

bool capture_duree(int duree)
{
		
	while (cpt >= 0)
	{
		if (duree > valeur_header_min && duree < valeur_header_max)		// debut de la transmission
		{
			flag_debut_transmission = 1;
		}
		
		else if (duree > valeur_bit1_min && duree < valeur_bit1_max)		// le bit vaut 1
		{
			flag_reception_bit = 1;
			current_bit = 1;
			T[cpt] = current_bit;			// on le stocke dans le tableau
			cpt--;
		}
		
		else if (duree > valeur_bit0_min && duree < valeur_bit0_max)		// le bit vaut 0
		{
			flag_reception_bit = 1;
			current_bit = 0;
			T[cpt] = current_bit;			// on le stocke dans le tableau
			cpt--;
		}
		
		else if (duree > valeur_stop_min && duree < valeur_stop_max)		// fin de la transmission
		{
			flag_fin_transmission = 1;
		}
		
		else		// il ne se passe rien -> on se cale à nouveau 
		{
			init();
		}
	}
	return current_bit;	

}

/* Decodage du message ------------------------------------------------------------------- */
