///////////////////////////////////////////////////////////////////////////
/// @file vect.h
/// @author equipe06
/// @date 2016-09-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VECTOR_H__
#define __UTILITAIRE_VECTOR_H__

#include <iostream>
#include <cmath>
#include "CLectureFichierBinaire.h"
#include "CEcritureFichierBinaire.h"
///////////////////////////////////////////////////////////////////////////
/// @class Vect
/// 
/// cette classe générique nous permet d'implémenter des vecteurs à n dimensions 
/// le type de vecteur sera aussi générique pour une utilisation global
///Nous implementerons différente fonctions communes aux vecteurs 
///
///@author equipe06
/// @date 2016-09-13
////////////////////////////////////////////////////////////////////////////

template <class T=double,const int N=3>

class Vect
{
    public:
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect()
/// constructeur par defaut
/// 
/// return aucun
///////////////////////////////////////////////////////////////////////////   
    inline Vect()
    {
    }

///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect(const Vect<T2,N>& x)
/// constructeur par copie
/// @param[in] x : Le vecteur à copier.
/// return aucun
///////////////////////////////////////////////////////////////////////////

template <class T2>
inline Vect(const Vect<T2,N>& x)
{
    for (int i=0;i<N;i++)
    {
        vector_[i]= static_cast<T>(x[i]);
    }
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline T& operator[] (const int& i)
/// surcharge de l'operateur  [] modele non constant
/// @param[in] x : Le vecteur à copier.
/// return la composante souhaitée
///////////////////////////////////////////////////////////////////////////
inline T& operator[] (const int& i)
{
    return vector_[i];

}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline T& operator[] (const int& i)const
/// surcharge de l'operateur  [] modele constant
/// @param[in] x : Le vecteur à copier.
/// return la composante souhaitée
///////////////////////////////////////////////////////////////////////////
inline const T& operator[] (const int& i)const
{
    return vector_[i];

}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline T normeCarre()const
/// cette fonction permet de calculer le carré de la norme d'un vecteur
/// 
/// return le carre de la norme du vecteur
///////////////////////////////////////////////////////////////////////////
inline T normeCarre()const
{
    T x=0;
    T carre;
    for (int i=0;i<N;i++)
    {
        carre = vector_[i];
        carre *=carre;
        x +=carre;
    }
    return x;

}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline T norme()const
/// cette fonction permet de calculer la norme d'un vecteur
///
/// return la norme du vecteur
///////////////////////////////////////////////////////////////////////////
inline T norme()const
{
    return sqrt(normeCarre());

}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline void normalise()
/// permet de normaliser un vecteur
///
/// return aucun
///////////////////////////////////////////////////////////////////////////
inline void normalise()
{
    const T a=norme();
    if(n!=0)
    (*this)/=a;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline bool estNul()const
/// cette fonction permet de savoir si un vecteur est nul
///
/// return la norme du vecteur
///////////////////////////////////////////////////////////////////////////
inline bool estNul()const
{
    return (norme()==0);
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator=(const Vect<T,N>& x)
/// surcharge de l'operateur =(assignation)
///
/// return une reférence vers l'objet assigné 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator =(const Vect<T,N>& x)
{
    for(int i=0; i<N;i++)
    {
        vector_[i] = x.vector_[i];
    }
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline bool operator ==(const Vect<T,N>& x)
/// surcharge de l'operateur d'égalité
///
/// return vrai si deux vcteur sont egaux
///////////////////////////////////////////////////////////////////////////
inline bool operator ==(const Vect<T,N>& x)
{
    for(int i=0; i<N;i++)
    {
        if(vector_[i] != x.vector_[i];)
            return false;
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator +=(const Vect<T,N>& x)const
/// surcharge de l'operateur d'addition
///
/// return une reférence vers l'objet assigné 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator +=(const Vect<T,N>& x)const
{
    for(int i=0; i<N;i++)
    {
        vector_ += x.vector_[i];
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator -=(const Vect<T,N>& x)const
/// surcharge de l'operateur de soustraction
///
/// return une reférence vers l'objet assigné 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator -=(const Vect<T,N>& x)const
{
    for(int i=0; i<N;i++)
    {
        vector_ -= x.vector_[i];
    }
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator *=(const T a)
/// surcharge de l'operateur de multiplication
///
/// return une reférence vers l'objet assigné 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator *=(const T a)
{
    for(int i=0; i<N;i++)
    {
        vector_ *= a;
    }
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator /=(const T a)
/// surcharge de l'operateur de division
///
/// return une reférence vers l'objet assigné 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator /=(const T a)
{
    for(int i=0; i<N;i++)
    {
        vector_ /= a;
    }
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator +(const Vect<T,N>& x)const
/// surcharge de l'operateur d'addition
///
/// return la somme de des vecteurs 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator +(const Vect<T,N>& x)const
{
    Vect<T,N> z(*this);
    z+=x;
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator -(const Vect<T,N>& x)const
/// surcharge de l'operateur de soustraction
///
/// return la différence des deux vecteurs 
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator -(const Vect<T,N>& x)const
{
    Vect<T,N> z(*this);
    z -=x;
    return *this;
}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator *(constT a)const
/// surcharge de l'operateur de multiplication par un scalaire
///
/// return le vecteur multiplié
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator *(const T a)const
{
    Vect<T,N> z(*this);
    z *=x;
    return z;
}
///////////////////////////////////////////////////////////////////////////
//// @fonction inline Vect<T,N>& operator *(const Vect<T,N>& x,const T a)const
/// surcharge de l'operateur de multiplication d'un vecteur par un scalaire
///
/// return le vecteur multiplié
///////////////////////////////////////////////////////////////////////////
//inline Vect<T,N>& operator *(const Vect<T,N>& x,const T a)const
//{ 
//    return z * a;
//}
///////////////////////////////////////////////////////////////////////////
/// @fonction inline Vect<T,N>& operator +(const T a)const
/// surcharge de l'operateur de division par un scalaire 
///
/// return le vecteur divisé
///////////////////////////////////////////////////////////////////////////
inline Vect<T,N>& operator /(const T a)const
{
    Vect<T,N> z(*this);
     z /=a;
     return z;
}
////////////////////////////////////////////////////////////////////////////
///
/// @fonction inline Vecteur<T, N> operator >> ( const Vect<T,N>& d ) const
///
/// Surcharge de l'opérateur de projection d'un vecteur sur un autre.
///
/// @param[in] d : La direction sur laquelle projeter.
///
/// @return La projection du vecteur sur l'autre.
///
////////////////////////////////////////////////////////////////////////////
   inline Vect<T, N> operator >> ( const Vect<T,N>& d) const
   {
      T a = produitScalaire(*this, d) / produitScalaire(d, d);
      Vecteur<T, N> z ( dir );
      z *= a;
      return z;
   }
////////////////////////////////////////////////////////////////////////////
///
//// @fonction inline friend T produitScalaire ( const Vect<T,N>& u,const Vect<T,N>& v) const
///
/// Surcharge de l'opérateur de projection d'un vecteur sur un autre.
///@param[in] u : Le premier vecteur du produit scalaire.
/// @param[in] v : Le second vecteur du produit scalaire.
/// @return La projection du vecteur sur l'autre.
///
////////////////////////////////////////////////////////////////////////////
   inline friend T produitScalaire( const Vect<T,N>& u,const Vect<T,N>& v) 
   {
      T a = 0;
     for(int i=0;i<N;i++)
     {
        a+=u.vector_[i] * v.vector_[i];
     }
      return a;
   }

////////////////////////////////////////////////////////////////////////////
///
/// @fonction inline friend T calculReflexion ( const Vect<T,N>& u,const Vect<T,N>& v) const
///
/// Surcharge de l'opérateur de projection d'un vecteur sur un autre.
///@param[in] u : Le premier vecteur du produit scalaire.
/// @param[in] v : Le second vecteur du produit scalaire.
/// @return La projection du vecteur sur l'autre.
///
////////////////////////////////////////////////////////////////////////////
   inline friend T calculReflexion( const Vect<T,N>& u,const Vect<T,N>& v) 
   {
      
      return u-n*(2* produitScalaire(u,v));
   }
////////////////////////////////////////////////////////////////////////////
///
/// @fonction inline friend T calculProjectionPlan ( const Vect<T,N>& u,const Vect<T,N>& v) 
///
/// Surcharge de l'opérateur de projection d'un vecteur sur un autre.
///@param[in] u : Le premier vecteur du produit scalaire.
/// @param[in] v : Le second vecteur du produit scalaire.
/// @return La projection du vecteur sur l'autre.
///
////////////////////////////////////////////////////////////////////////////
   inline friend T calculProjectionPlan( const Vect<T,N>& u,const Vect<T,N>& v) 
   {
      
      return u-n*(produitScalaire(u,v));
   }

////////////////////////////////////////////////////////////////////////////
///
/// @fonction inline friend T calculProjectionDroite ( const Vect<T,N>& u,const Vect<T,N>& v) const
///
/// Surcharge de l'opérateur de projection d'un vecteur sur un autre.
///@param[in] u : Le premier vecteur du produit scalaire.
/// @param[in] v : Le second vecteur du produit scalaire.
/// @return La projection du vecteur sur l'autre.
///
////////////////////////////////////////////////////////////////////////////
   inline friend T calculProjectionDroite( const Vect<T,N>& u,const Vect<T,N>& v) 
   {
      
      return v*(produitScalaire(v,u));
   }
////////////////////////////////////////////////////////////////////////////
///
/// @fn inline friend std::ostream& operator<< ( std::ostream& out, const Vecteur<T, N>& v )
///
/// Surcharge de l'opérateur de flux de sortie pour
/// l'affichage.
///
/// @param[in] out : Le flux de sortie.
/// @param[in] v   : Le vecteur à afficher.
///
/// @return Le flux de sortie.
///
////////////////////////////////////////////////////////////////////////////
inline friend std::ostream& operator<< (std::ostream& out, const Vect<T, N>& v)
   {
      for ( int i = 0; i < N; i++ ) {
         out << v[i];
         if ( i < N - 1 ) out << ' ';
      }
      return out;
   }   

////////////////////////////////////////////////////////////////////////////
///
/// @fn inline friend std::istream& operator>> ( std::istream& out, const Vecteur<T, N>& v )
///
/// Surcharge de l'opérateur de flux d'entrée pour
/// l'affichage.
///
/// @param[in] out : Le flux de sortie.
/// @param[in] v   : Le vecteur à afficher.
///
/// @return Le flux de sortie.
///
////////////////////////////////////////////////////////////////////////////
   inline friend std::istream& operator>> (
	   std::istream& in, const Vect<T, N>& v
	   )
   {
	   for (int i = 0; i < N; i++) {
		   in >> v[i];
		   return in;
	   }
   }
////////////////////////////////////////////////////////////////////////////
///
//// fonction inline friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const Vecteur<T, N>& u )
///
/// Surcharge de l'op�rateur de sortie dans un fichier binaire.
///
/// @param[in] out : Le fichier binaire de sortie.
/// @param[in] u   : Le vecteur � �crire.
///
/// @return Le fichier binaire de sortie.
///
////////////////////////////////////////////////////////////////////////////
   inline friend CEcritureFichierBinaire& operator< (CEcritureFichierBinaire& out, const Vect<T, N>& u)
   {
      for ( int i = 0; i < N; i++ ) {
         out < u[i];
      }
      return out;
   }  

////////////////////////////////////////////////////////////////////////////
///
/// fonction inline friend CEcritureFichierBinaire& operator> ( CEcritureFichierBinaire& out, const Vecteur<T, N>& u )
///
/// Surcharge de l'op�rateur de sortie dans un fichier binaire.
///
/// @param[in] in : Le fichier binaire d'entrée.
/// @param[in] u   : Le vecteur � �crire.
///
/// @return Le fichier binaire de sortie.
///
////////////////////////////////////////////////////////////////////////////
   inline friend CEcritureFichierBinaire& operator> (CEcritureFichierBinaire& in, const Vect<T, N>& u)
   {
      for ( int i = 0; i < N; i++ ) 
	  {
         in > u[i];
      }
      return in;
   } 
////////////////////////////////////////////////////////////////////////////
///
/// fonction inline Vecteur<T, N> operator- () const
///
/// Surcharge de l'opérateur unaire de négation.
///
/// @return L'opposé du vecteur.
///
////////////////////////////////////////////////////////////////////////////
   inline Vect<T, N> operator- () const
   {
      Vect<T, N> r;
      for ( int i = 0; i < N; i++ ) {
         r[i] = - ( *this ) [i];
      }
      return r;
   }

   /*template <const int N2>
   inline Vect<T, N2> convertir() const
   {
	   return convertir<T, N2>();
   }
   template <class T2, const int N2>
   inline Vect<T2, N2> convertir() const
   {
	   Vect<T2, N2> nouveauVecteur;
	   if (N2 <= N) {
		   for (int i = 0; i < N2; ++i)
			   nouveauVecteur[i] = static_cast<T2>(vect[i]);
	   }
	   else {
		   int i;
		   for (i = 0; i < N; ++i)
			   nouveauVecteur[i] = static_cast<T2>(vect[i]);
		   for (i = N; i < N2; ++i)
			   nouveauVecteur[i] = 0;
	   }

	   return nouveauVecteur;
   }*/
    protected:
        T vector_[N];
};
////////////////////////////////////////////////////////////////////////////
///
/// @class Vect2D
///
/// implantation des vecteurs en 2 dimensions
///
///
////////////////////////////////////////////////////////////////////////////
template<class T>
class Vect2D: public Vect<T, 2>
{
public:
   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vect2D( const Vect2D<T2>& u )
   ///
   /// Constructeur avec conversion.
   ///
   /// @param[in] u : Le vecteur à copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   template<class T2>
   inline Vect2D( const Vect2D<T2>& u )
      : Vect<T, 2> ( u )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vect2D( const T x = 0, const T y = 0 )
   ///
   /// Constructeur par paramètres.
   ///
   /// @param[in] x : La coordonnée en @a x.
   /// @param[in] y : La coordonnée en @a y.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vect2D(const T x = 0, const T y = 0)
   {
	   vector_[0] = x;
	   vector_[1] = y;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vect2D ( const Vect<T, 2>& v )
   ///
   /// Constructeur copie.
   ///
   /// @param[in] v : Le vecteur à copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vect2D( const Vect<T, 2>& v )
      : Vect<T, 2> ( v )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vect2D& operator= ( const Vect<T, 2>& v )
   ///
   /// Surcharge de l'opérateur d'assignation.
   ///
   /// @param[in] v : Le vecteur à copier.
   ///
   /// @return La référence vers l'objet assigné 
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vect2D& operator= ( const Vect<T, 2>& v )
   {
      Vect<T, 2>::operator= ( v );
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T angle() const
   ///
   /// Cette fonction calcule l'angle du vecteur par rapport � l'axe des X
   /// positifs dans le sens anti-horaire.
   ///
   /// @return L'angle du vecteur par rapport � l'axe des X dans le sens
   ///         anti-horaire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T angle() const
   {
      return atan2 ( vector_[1], vector_[0] );
   }
};
template<class T>
class Vect3D : public Vect<T, 3>
{
	public:
	template<class T2>
	   inline Vect3D ( const Vect3D<T2>& u ): Vect<T, 3> ( u )
	   {
	   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vect3D ( const T x = 0, const T y = 0, const T z = 0 )
   ///
   /// Constructeur par paramètres.
   ///
   /// @param[in] x : La coordonnée en @a x.
   /// @param[in] y : La coordonnée en @a y.
   /// @param[in] z : La coordonnée en @a z.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vect3D ( const T x = 0, const T y = 0, const T z = 0 )
   {
      vector_[0] = x;
      vector_[1] = y;
      vector_[2] = z;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   ////fonction inline Vect3D ( const Vect<T, 3>& v1, const Vect<T, 3>& v2 )
   ///
   /// Constructeur à partir de deux points.
   ///
   /// @param[in] v1 : Le premier vecteur (source).
   /// @param[in] v2 : Le second vecteur (destination).
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vect3D ( const Vect<T, 3>& v1, const Vect<T, 3>& v2 )
      : Vect<T, 3> ( v2 - v1 )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   //// fonction inline Vect3D ( const Vect<T, 3>& v )
   ///
   /// Constructeur copie.
   ///
   /// @param[in] v : Le vecteur � copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vect3D ( const Vect<T, 3>& v ): Vect<T, 3> ( v )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   //// fonction inline const Vect3D& operator= ( const Vect<T, 3>& v )
   ///
   /// Surcharge de l'op�rateur d'assignation.
   ///
   /// @param[in] v : Le vecteur � copier.
   ///
   /// @return La r�f�rence vers l'objet assign� afin de respecter la
   ///         s�mantique de l'op�rateur d'assignation C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vect3D& operator= ( const Vect<T, 3>& v )
   {
      Vect<T, 3>::operator= ( v );
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// fonction inline T lireTheta() const
   ///
   /// Cette fonction calcule l'angle de rotation (@a xy) du vecteur 3D.
   ///
   /// @return L'angle de rotation du vecteur 3D.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T lireTheta() const
   {
      Vect2D<T> xy ( vector_[0], vector_[1] );
      return xy.angle();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// fonction inline T lirePhi() const
   ///
   /// Cette fonction calcule l'angle d'�l�vation du vecteur 3D.  Le vecteur
   /// dirig� vers l'axe des Z positifs, k, (0,0,1), aura comme angle 0.
   ///
   /// @return L'angle d'�l�vation du vecteur 3D.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T lirePhi() const
   {
      Vect2D<T> xy ( vector_[0], vector_[1] );
      Vect2D<T> zr ( vector_[2], xy.norme() );
      return zr.angle();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// fonction inline void lireCoordSpheriques ( T& r, T& phi, T& theta ) const
   ///
   /// Cette fonction retourne les coordonn�es sph�riques du vecteur via les
   /// param�tres pass�s en r�f�rence.
   ///
   /// @param[out] r     : Le rayon des coordonn�es sph�riques.
   /// @param[out] phi   : L'angle d'�l�vation des coordonn�es sph�riques.
   /// @param[out] theta : L'angle de rotation des coordonn�es sph�riques.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline void lireCoordSpheriques ( T& r, T& phi, T& theta ) const
   {
      r     = norme();
      theta = lireTheta();
      phi   = lirePhi();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// fonction inline void assignerCoordSpheriques ( const T r, const T phi, const T theta )
   ///
   /// Cette fonction assigne les coordonn�es du vecteur qui sont donn�es en
   /// coordonn�es sph�riques.
   ///
   /// @param[in] r     : Le rayon des coordonn�es sph�riques.
   /// @param[in] phi   : L'angle d'�l�vation des coordonn�es sph�riques.
   /// @param[in] theta : L'angle de rotation des coordonn�es sph�riques.
   ///
   /// @return Aucune.
   ///
   ///////////////////////////////////////////////////////////////////////////////
   inline void assignerCoordSpheriques ( const T r, const T phi, const T theta )
   {
      // Calcul de la position � partir des coordonn�es sph�riques
      vector_[0] = r * sin(phi) * cos(theta);
      vector_[1] = r * sin(phi) * sin(theta);
      vector_[2] = r * cos(phi);
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// fonction inline friend Vecteur3D produitVectoriel ( const Vecteur3D& A, const Vecteur3D& B )
   ///
   /// Cette fonction calcule le produit vectoriel des deux vecteurs.
   ///
   /// @param[in] A : Le premier vecteur du produit.
   /// @param[in] B : Le second vecteur du produit.
   ///
   /// @return Le produit vectoriel des deux vecteurs.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend Vect3D produitVectoriel (
      const Vect3D& A, const Vect3D& B
      )
   {
      return Vect3D(
         A[1] * B[2] - A[2] * B[1],
         A[2] * B[0] - A[0] * B[2],
         A[0] * B[1] - A[1] * B[0]
      );
   }
};

/// Définition de type de vecteur à 2 coordonnées de type double.
typedef Vect2D<double> Vect2;
/// Définition de type de vecteur à 3 coordonnées de type double.
typedef Vect3D<double> Vect3;

/// Définition de type de vecteur à 2 coordonnées de type float.
typedef Vect2D<float> Vect2f;
/// Définition de type de vecteur à 3 coordonnées de type float.
typedef Vect3D<float> Vect3f;

/// Définition de type de vecteur à 2 coordonnées de type int.
typedef Vect2D<int> Vect2i;
/// Définition de type de vecteur à 3 coordonnées de type int.
typedef Vect3D<int> Vect3i;
#endif //__UTILITAIRE_VECTOR_H__