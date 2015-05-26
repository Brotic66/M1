/**
 * @file Sommet.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package general;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;

/**
 * @class Sommet
 * 
 * Défini une classe Graphe en utilisant les nouveaux type à la place des virtuels.
 */
class Sommet extends SommetType
{ 
  override type virtualGraphe = Graphe
  override type virtualSommet = Sommet
  override type virtualArete = Arete  
  
  
  def this(graphe: Graphe, posX: String, posY: String)
  {
    this()
	  this.graphe = graphe
	  this.x = posX
	  this.y = posY
  }
}