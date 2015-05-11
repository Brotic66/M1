/**
 * @file Liaison.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package chimie;

import virtual.GrapheType
import Exception.AreteException
import virtual.SommetType
import virtual.AreteType;



class Liaison extends AreteType
{ 
  
  override type virtualGraphe = Molecule
  override type virtualSommet = Atome
  override type virtualArete = Liaison  
  
  def this(sommet1: Atome, sommet2: Atome)
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
			throw new AreteException("Erreur d'instanciation; les Atomes n'ont peut être pas la même molécule ou bien sont égaux.")
		}
	}
  
}