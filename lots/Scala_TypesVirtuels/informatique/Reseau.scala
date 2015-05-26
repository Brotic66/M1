/**
 * @file Reseau.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package informatique;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;


class Reseau extends GrapheType
{   
  override type virtualGraphe = Reseau
  override type virtualSommet = Noeud
  override type virtualArete = Lien
}