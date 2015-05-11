/**
 * @file Lien.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package informatique;

import virtual.GrapheType
import Exception.AreteException
import virtual.SommetType
import virtual.AreteType;



class Lien extends AreteType { 
  
  override type virtualGraphe = Reseau
  override type virtualSommet = Noeud
  override type virtualArete = Lien
  
  def this(sommet1: Noeud, sommet2: Noeud)
  {
		this()
    
		if (sommet1!=sommet2 && sommet1.getGraphe == (sommet2.getGraphe))
    {
			this.sommet1 = sommet1
			this.sommet2 = sommet2
			sommet1.addAretes(this)
			sommet2.addAretes(this)
		}
		else
    {
			throw new AreteException("Erreur d'instanciation; les noeuds n'ont peut être pas le même réseaux ou bien sont égaux.")
		}
	}
  
}