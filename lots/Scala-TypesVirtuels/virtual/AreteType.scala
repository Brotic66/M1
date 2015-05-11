/**
 * @file AreteType.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package virtual

import Exception.AreteException
import Exception.GrapheException
import Exception.SommetException

/**
 * @class AreteType
 * 
 * Défini une classe permettant de gérer de façon générique une arete en utilisant
 * les types virtuels proposés par Scala.
 */
abstract class AreteType
{
	type virtualArete <: AreteType;
	type virtualSommet <: SommetType;
	type virtualGraphe <: GrapheType;

	protected var graphe: virtualGraphe = _;
	protected var sommet1: virtualSommet = _;
	protected var sommet2: virtualSommet = _; 
	protected var arete: virtualArete = _;
	

  /**
   * Permet de tester l'invariance d'une arete.
   */
	def invArrete: Boolean =
  {
		if ((this.sommet1 == null && this.sommet2 == null) || (this.sommet1 != null && this.sommet2 != null))
    {
			if (this.sommet1.getGraphe.eq(graphe) && (this.graphe eq this.sommet2.getGraphe))
      {
				System.out.println("Le test d'invariance de l'arete est valide")
				return true
			}
			else
      {
				throw new AreteException("Deux aretes n'ont pas le même graphe que celle testé actuellement")
				return false
			}
		}
		else
    {
			throw new GrapheException("L'arete n'a qu'un sommet")
			return false
		}
	}


  /**
   * Getter & Setter
   */

	def getGraphe: virtualGraphe =
  {
		return this.graphe
	}

	def setGraphe(graphe: virtualGraphe)
  {
		this.graphe = graphe
	}

	def getSommet1: virtualSommet =
  {
		return this.sommet1
	}

	def setSommet1(sommet1: virtualSommet)
  {
		this.sommet1 = sommet1
	}

	def getSommet2: virtualSommet =
  {
		return this.sommet2
	}

	def setSommet2(sommet2: virtualSommet)
  {
		this.sommet2 = sommet2
	}
}