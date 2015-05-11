/**
 * @file Graphe.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package general;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;

/**
 * @class Graphe
 * 
 * Défini une classe Graphe en utilisant les nouveaux type à la place des virtuels.
 */
class Graphe extends GrapheType
{ 
  override type virtualGraphe = Graphe
  override type virtualSommet = Sommet
  override type virtualArete = Arete
}

