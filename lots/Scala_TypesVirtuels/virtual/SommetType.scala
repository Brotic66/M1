/**
 * @file SommetType.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package virtual

import java.util.HashSet
import Exception.AreteException
import Exception.GrapheException
import Exception.SommetException
import java.util.Set
import scala.collection.mutable.ArrayBuffer


/**
 * @class SommetType
 * 
 * Défini une classe permettant de gérer de façon générique un sommet en utilisant
 * les types virtuels proposés par Scala.
 */
class SommetType
{  
	type virtualArete <: AreteType;
	type virtualSommet <: SommetType;
	type virtualGraphe <: GrapheType;

	protected var x: String = null
	protected var y: String = null
	protected var graphe: virtualGraphe = _;
	protected var nom: String = null
	protected var ensembleAretes = new  HashSet[virtualArete]();

	def this(posX: String, posY: String)
  {
		this()
		this.x = posX
		this.y = posY
	}

  /**
   * Getter & Setter
   */
  
  def getGraphe: virtualGraphe =
  {
      return graphe
  }
  
  def setGraphe(graphe: virtualGraphe)
  {
    this.graphe = graphe
  }

  def getEnsembleArretes: HashSet[virtualArete] =
  {
    return ensembleAretes
  }

  def setEnsembleArretes(ensembleAretes: HashSet[virtualArete])
  {
    this.ensembleAretes = ensembleAretes
  }

  def getNom: String =
  {
    return nom
  }

  def setNom(nom: Nothing)
  {
    this.nom = nom
  }

  def getX: String =
  {
    return x
  }

  def setX(x: String)
  {
    this.x = x
  }

  def getY: String =
  {
    return y
  }

  def setY(y: String)
  {
    this.y = y
  }

  /**
   * @param arete Une virtualArete
   * 
   * Ajoute une arete au virtuaSommet actuel
   */
	def addAretes(arete: virtualArete)
  {
		this.ensembleAretes.add(arete);
	}

  /**
   * @param arete Une virtualArete
   * @param sommet Un virtualSommet
   * 
   * Ajoute un sommet à "arete" et ajoute l'arete au sommet actuel
   */
	def addAretes(arete: virtualArete, sommet: virtualSommet)
  {
		if (this.graphe != null && graphe == sommet.getGraphe)
    {
			System.out.println("vérification des graphes ok dans addArretes")
      
			if ((arete.getSommet1 != this && arete.getSommet2 != sommet))
      {
				arete.setSommet1(this.asInstanceOf[arete.virtualSommet])
        
				if (sommet != null)
        {
					arete.setSommet2(sommet.asInstanceOf[arete.virtualSommet])
				}
        
				ensembleAretes.add(arete)
				System.out.println("L'arete a été remplacé et ajouté")
			}
			else
      {
				throw new AreteException("L'arete se trouve déjà entre les deux sommets")
			}
		}
		else
    {
			throw new GrapheException("Veuillez vérifier le graphe de l'arete et des sommets")
		}
  }

  /**
   * @param arete Une virtualArete
   * 
   * Supprime une arete si celle-ci est liée au sommet actuel.
   */
	def removeArete(arete: virtualArete)
  {
		if (ensembleAretes.remove(arete))
    {
			System.out.println("L'arete a bien été supprimé")
		}
		else
    {
			throw new AreteException("L'arrete ne se trouve pas au sommet indiqué")
		}
	}
}