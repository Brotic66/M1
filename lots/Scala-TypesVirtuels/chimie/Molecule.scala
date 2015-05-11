/**
 * @file Noeud.scala
 * @author brice VICO
 * @date 10/05/2015
 */

package chimie;

import virtual.GrapheType;
import virtual.SommetType;
import virtual.AreteType;


class Molecule extends GrapheType
{ 
  override type virtualGraphe = Molecule
  override type virtualSommet = Atome
  override type virtualArete = Liaison
}