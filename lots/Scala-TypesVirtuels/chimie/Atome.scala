/**
 * @file Atome.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package chimie;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;



class Atome extends SommetType { 
  
  override type virtualGraphe = Molecule
  override type virtualSommet = Atome
  override type virtualArete = Liaison  
  
  
  def this(graphe: Molecule, posX: String, posY: String)
  {
	  this()
	  this.graphe = graphe
	  this.x = posX
	  this.y = posY
  }
}