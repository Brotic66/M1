/**
 * @file Arete.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package general;

import virtual.GrapheType
import Exception.AreteException
import virtual.SommetType
import virtual.AreteType;

/**
 * @class Arete
 * 
 * Défini une classe Graphe en utilisant les nouveaux type à la place des virtuels.
 */
class Arete extends AreteType
{
  override type virtualGraphe = Graphe
  override type virtualSommet = Sommet
  override type virtualArete = Arete
  
  def this(sommet1: Sommet, sommet2: Sommet)
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
			throw new AreteException("Erreur d'instanciation; les sommet n'ont peut être pas le même graphe ou bien sont égaux.")
		}
	}
}