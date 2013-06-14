/*	ClException.cpp
 *		Contient les d�finitions n�cessaires � l'utilistion de la classe 
 *		d'exception.
 *
 *	Modifi� le	:	2011-01-03
 */
#include <fstream>
#include <iomanip>
#include <sstream>

#include "ClConvertion.h"
#include "ClException.h"

using namespace std;


// PUBLIQUE

// ClException		# Construteur
//	Lance une exception d�s qu'un des param�tres {std::string}
//	 est vide puis initialise {m_what} avec ces derniers.
//	Si {p_estEnregistree}, Enregistrer() est appel�e.
_UTILGXT ClException :: ClException(
	const string& p_fichier,
	int p_ligne,
	const string& p_fonction,
	const string& p_description,
	const bool p_estEnregistree)
	throw(exception)
	: m_fichier(p_fichier),
	  m_ligne(p_ligne),
	  m_fonction(p_fonction),
	  m_description(p_description)
	{
	ExceptionSiVide(m_fichier);
	ExceptionSiVide(m_fonction);
	ExceptionSiVide(m_description);

	ostringstream oss;
	oss << m_fichier << '(' << m_ligne << ") "
		<< m_fonction << " : " << m_description;
	m_what= oss.str();

	if (p_estEnregistree)
		Enregistrer();
	}

// Fichier			# Acc�sseur
const string& _UTILGXT ClException :: Fichier() const throw()
	{
	return m_fichier;
	}

// Ligne			# Acc�sseur
int _UTILGXT ClException :: Ligne() const throw()
	{
	return m_ligne;
	}

// Fonction			# Acc�sseur
const string& _UTILGXT ClException :: Fonction() const throw()
	{
	return m_fonction;
	}

// Description		# Acc�sseur
const string& _UTILGXT ClException :: Description() const throw()
	{
	return m_description;
	}

// what				# Acc�sseur
const char* _UTILGXT ClException :: what() const throw()
	{
	return m_what.c_str();
	}

// Fichier o� les exceptions seront inscrites.
string _UTILGXT ClException :: JOURNAL_CHEMIN = "exceptions.log";


// PROT�G�

// Enregistrer
//	Un fichier est ouvert � la position d�finie par 
//	 {ClException::JOURNAL_CHEMIN}, est cr�� si inexistant, puis {m_what}
//	 est ajout� � la fin de celui-ci.
bool _UTILGXT ClException :: Enregistrer() const throw()
	{
	ofstream journal(JOURNAL_CHEMIN, ofstream::app);

	if ( ! journal.is_open())
		return false;

	journal << m_what << '\n';
	return true;
	}