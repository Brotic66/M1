/**
 * @file Noeud.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package informatique;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;



class Noeud extends SommetType
{ 
  
  override type virtualGraphe = Reseau
  override type virtualSommet = Noeud
  override type virtualArete = Lien   
  
  def this(graphe: Reseau, posX: String, posY: String)
  {
	  this()
	  this.graphe = graphe
	  this.x = posX
	  this.y = posY
  }

}