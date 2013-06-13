/*	ClConvertion.h
 *		Les classes de ClConvertion.h font le pont entre les types num�riques de base 
 *		et la classe standard de texte. Ainsi {ClConvertionTexte} et 
 *		{ClConvertionNumerique} effectuent les op�rations n�cessaire en une seule s�rie 
 *		d'instruction ce que �clairci le code o� elles sont utilisi�e.
 *		Des typedef sont fournis pour faciliter leur fonctionnement.
 *
 *	Modifi� le	:	2011-01-03
 */
#ifndef _CLCONVERTION_H_INLCUS_
#define _CLCONVERTION_H_INLCUS_

#include <sstream>
#include <string>

#include "utils.h"
#include "ClException.h"


_UTILGXT_DEBUT

// ClConvertionTexte
//	Fait la conversion entre {std::string} et un type num�rique de base.
template <typename T>
class ClConvertionTexte
	{
	public:
		// ClConvertionTexte
		//	ClConvertionTexte de ClConvertionTexte.
		//	NB*	{p_texte} ne devrait contenir que l'expression � �tre 
		//		convertie. Si ce n'est pas le cas, ClConvertionTexte::Reusit()
		//		retournera {false}.
		ClConvertionTexte(
			const std::string& p_texte)		// Texte contenant la valeur
			: m_texte(p_texte)
			{
			ExceptionSiVide(m_texte);
			}

		// Resultat
		//	Retourne la valeur {T} du texte.
		//	NB*	{T} doit �tre {int}, {long}, {long long}, {double} ou {float}.
		T Resultat()
			{
			bool estMauvaisType= 
				typeid(T) != typeid(int)
				&& typeid(T) != typeid(double)
				&& typeid(T) != typeid(float)
				&& typeid(T) != typeid(long)
				&& typeid(T) != typeid(long long);
			ExceptionSi(T, estMauvaisType, 
				"Il est impossible d'effectuer une convertion sur le type donn�.");

			return Convertisseur<T>(m_texte);
			}

		// Reussit
		//	Retourne l'�tat de la derni�re op�ration �x�cut�e sur le texte.
		//	NB*	{true} si le texte ne contenait que l'expression. 
		//		{false} si non.
		bool Reussit() const
			{
			return m_reussit;
			}

	private:
		template <typename T>
		T Convertisseur(
			const std::string& p_texte)
			{
			istringstream iss(p_texte);
			T variableTemp;
			iss >> variableTemp;

			m_reussit= !iss.fail();
			if (m_reussit)
				{
				char c;
				iss >> c;
				m_reussit= iss.fail();
				}		

			return variableTemp;
			}

		std::string m_texte;
		bool m_reussit;
	};

// ClConvertionNumerique
//	Fait la convertion entre les types num�riques de base et {std::string}.
template <typename T>
class ClConvertionNumerique
	{
	public:
		// ClConvertionNumerique
		//	Constructeur de ClConvertionNumerique.
		////
		// Lance une exception si le type donn� n'est pas un des types num�riques 
		//	de base : {int}, {long}, {long long}, {double} et {float}.
		ClConvertionNumerique(
			const T p_nombre)
			{
			bool estMauvaisType= 
				typeid(p_nombre) != typeid(int)
				&& typeid(p_nombre) != typeid(double)
				&& typeid(p_nombre) != typeid(float)
				&& typeid(p_nombre) != typeid(long)
				&& typeid(p_nombre) != typeid(long long);
			ExceptionSi(p_nombre, estMauvaisType, 
				"Il est impossible d'efftuer une convertion sur le type donn�.");

			m_nombre= p_nombre;
			}

		// Texte
		//	Retourne le nombre sous forme de texte.
		const std::string& Resultat()
			{
			return Convertisseur(m_nombre);
			}

	private:
		std::string& Convertisseur(
			const T p_nombre)
			{
			std::ostringstream oss;
			oss << p_nombre;
			return (m_resultat= oss.str());
			}

		T m_nombre;
		std::string m_resultat;
	};

_UTILGXT_FIN


#define StringToInt(p_texte)		_UTILGXT ClConvertionTexte<int>((p_texte)).Resultat()
#define StringToLong(p_texte)		_UTILGXT ClConvertionTexte<long>((p_texte)).Resultat()
#define StringToLongLong(p_texte)	_UTILGXT ClConvertionTexte<long long>((p_texte)).Resultat()
#define StringToDouble(p_texte)		_UTILGXT ClConvertionTexte<double>((p_texte)).Resultat()
#define StringToFloat(p_texte)		_UTILGXT ClConvertionTexte<float>((p_texte)).Resultat()

#define IntToString(p_nombre)		_UTILGXT ClConvertionNumerique<int>((p_nombre)).Resultat()
#define LongToString(p_nombre)		_UTILGXT ClConvertionNumerique<long>((p_nombre)).Resultat()
#define LongLongToString(p_nombre)	_UTILGXT ClConvertionNumerique<long long>((p_nombre)).Resultat()
#define DoubleToString(p_nombre)	_UTILGXT ClConvertionNumerique<double>((p_nombre)).Resultat()
#define FloatToString(p_nombre)		_UTILGXT ClConvertionNumerique<float>((p_nombre)).Resultat()


#endif // _CLCONVERTION_H_INLCUS_