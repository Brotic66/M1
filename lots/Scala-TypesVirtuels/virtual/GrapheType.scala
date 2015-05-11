/**
 * @file GrapheType.scala
 * @author brice VICO
 * @date 09/05/2015
 */

package virtual

import java.util.HashSet
import Exception.GrapheException
import Exception.AreteException
import java.util.Set
import scala.collection.JavaConversions._

/**
 * @class GrapheType
 * 
 * Défini une classe permettant de gérer de façon générique un graphe en utilisant
 * les types virtuels proposés par Scala.
 */
class GrapheType {

	type virtualSommet <: SommetType;
	type virtualArete <: AreteType;
	type virtualGraphe <: GrapheType;
	
	protected var ensembleSommets = new  HashSet[virtualSommet]();
	protected var ensembleAretes  = new  HashSet[virtualArete]();
	protected var nom: String = null

	def this(nom: String)
  {
		this()
		this.nom = nom
	}

  /**
   * @param sommet Un virtualSommet
   * 
   * Ajoute un sommet au graphe
   */
	def addSommet(sommet: virtualSommet)
  {
		this.ensembleSommets.add(sommet)
	}

  /**
   * @arete Une virtualArete
   * 
   * Ajoute une arete au graphe en vérifiant bien que les sommet de l'arete existe dans le graphe.
   */
	def addArete(arete: virtualArete)
  {
		if (this.ensembleSommets.isEmpty)
    {
			throw new GrapheException("Le graphe ne compte aucun sommet")
		}
		if ((this.ensembleSommets.contains(arete.getSommet1) && this.ensembleSommets.contains(arete.getSommet2)))
    {
			System.out.println("Les sommet de l'arete sont dans le graphe, alors on ajoute l'arete.")
			this.ensembleAretes.add(arete)
			arete.setGraphe(this.asInstanceOf[arete.virtualGraphe])
		}
		else
    {
			throw new GrapheException("Les sommets de l'arete ne sont pas dans le graphe.")
		}
	}
  
  /**
   * Teste l'invariance du graphe
   */
  def invGraphe: Boolean =
  {
      for (ar <- this.ensembleAretes)
      {
        if (this ne ar.getGraphe)
        {
          throw new GrapheException("Une des aretes n'appartient pas au Graphe")
          return false
        }
      }
      
      System.out.println("Toutles les arretes ont le graphe courant")
      return true
  }

  /**
   * @param sommet Un virtualSommet
   * 
   * Supprime un sommet du graphe, ainsi qu'une arete qui lui serait reliée.
   */
	def removeSommet(sommet: virtualSommet)
  {
		if (this.ensembleSommets.remove(sommet))
    {
			System.out.println("Sommet (" + sommet.getX + "," + sommet.getY + ") suppression dans removeSommet")

			for (ar <- this.ensembleAretes)
      {
				if ((ar.getSommet1 == sommet) || (ar.getSommet2 == sommet))
        {
					this.ensembleAretes.remove(ar)
					System.out.println("Suppression de l'arete.")
				}
			}
		}
		else {
			throw new GrapheException("Sommet (" + sommet.getX + "," + sommet.getY + ") ne fait pas partie du graphe " + this.getNom)
		}
	}

  /**
   * @param arete Une virtualArete
   * 
   * Supprime une arete du graphe.
   */
	def removeArete(arete: virtualArete)
  {
		if (this.ensembleAretes.remove(arete))
    {
			System.out.println("Arete supprimée : " + this.getNom)
		}
		else
    {
			throw new AreteException("l'arete ne fait pas partie du graphe " + this.getNom)
		}
	}

  /**
   * Getter & Setter
   */
  
	def getEnsembleSommets: HashSet[virtualSommet] =
  {
		return this.ensembleSommets
	}

	def setEnsembleSommets(ensembleSommets: HashSet[virtualSommet])
  {
		this.ensembleSommets = ensembleSommets
	}

	def getEnsembleAretes: HashSet[virtualArete] =
  {
		return this.ensembleAretes
	}

	def setEnsembleAretes(ensembleAretes: HashSet[virtualArete])
  {
		this.ensembleAretes = ensembleAretes
	}

	def getNom: String =
  {
		return this.nom
	}

	def setNom(nom: String)
  {
		this.nom = nom
  }
}