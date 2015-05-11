package main

import general.Sommet
import general.Graphe
import general.Arete
import informatique.Reseau
import general.Arete
import general.Arete
import chimie.Molecule
import informatique.Noeud
import informatique.Lien
import chimie.Liaison
import chimie.Atome

object Executer {

  def main(args: Array[String]): Unit = {
    
    
		System.out.println(" ");
		System.out.println("------Test de Graphe---------");
		System.out.println(" ");	
		val graphe1 = new Graphe();
		val arete1 = new Arete();
		val sommet1 = new Sommet(graphe1,"1","2");
		val sommet12 = new Sommet(graphe1,"3","4");
		val sommet3 = new Sommet(graphe1, "4","5");
		val sommet4 = new Sommet(graphe1, "8","7");
		val arete11 = new Arete(sommet3,sommet4);
		
		graphe1.addSommet(sommet3);
		arete1.setGraphe(graphe1);
		arete1.setSommet1(sommet3);
		arete1.setSommet2(sommet4);
		sommet12.setGraphe(graphe1);
		sommet1.setGraphe(graphe1);
		sommet1.addAretes(arete11, sommet12);
		graphe1.addArete(arete11);
		//graphe1.removeArete(arete11);
		//graphe1.removeSommet(sommet4);
		
		
		System.out.println(" ");
		System.out.println("------Test de Chimie---------");
		System.out.println(" ");
		
		val molecule = new Molecule();
		val liaison0 = new Liaison();
		val atome1 = new Atome(molecule,"10","11");
		val atome2 = new Atome(molecule,"5","6");
		val atome3 = new Atome(molecule,"7","9");
		atome2.setGraphe(molecule);
		atome3.setGraphe(molecule);
		val liaison1 = new Liaison(atome2,atome3);
		val liaison2 = new Liaison(atome1,atome2);
		
		atome3.setGraphe(molecule);
		molecule.addSommet(atome3);
		molecule.addSommet(atome1);
		molecule.addSommet(atome2);
		liaison0.setGraphe(molecule);
//		liaison0.setGraphe(graphe1);
//		liaison0.setSommet1(sommet12);
		liaison0.setSommet1(atome1);
		liaison0.setSommet2(atome2);
		molecule.addArete(liaison1);
		molecule.addArete(liaison2);
//		molecule.addArete(arete11);
//		molecule.removeSommet(sommet1);
//		molecule.removeArete(arete1);
		//molecule.removeSommet(atome3);
		//molecule.removeSommet(atome2);
		molecule.removeArete(liaison1); // désactiver removesommet
		molecule.invGraphe;
		liaison0.invArrete;
		
		
		System.out.println(" ");
		System.out.println("------Test de Informatique---------");
		System.out.println(" ");
		
		val reseau = new Reseau();
		val lien0 = new Lien();
		val noeud1 = new Noeud(reseau,"10","11");
		val noeud2 = new Noeud(reseau,"5","6");
		val noeud3 = new Noeud(reseau,"7","9");
		noeud2.setGraphe(reseau);
		noeud3.setGraphe(reseau);
		val lien1 = new Lien(noeud2,noeud3);
		val lien2 = new Lien(noeud1,noeud2);
		
		noeud3.setGraphe(reseau);
		reseau.addSommet(noeud3);
//		reseau.addSommet(sommet3);
		reseau.addSommet(noeud1);
		reseau.addSommet(noeud2);
		lien0.setGraphe(reseau);
//		lien0.setGraphe(graphe1);
//		lien0.setSommet1(sommet12);
		lien0.setSommet1(noeud1);
		lien0.setSommet2(noeud2);
		reseau.addArete(lien1);
		reseau.addArete(lien2);
//		reseau.addArete(arete11);
//		reseau.removeSommet(sommet1);
//		reseau.removeArete(arete1);
		//molecule.removeSommet(atome3);
		//molecule.removeSommet(noeud3);
		reseau.removeArete(lien1); // désactiver removesommet
		reseau.invGraphe;
		lien0.invArrete;
    
    
    
    /*
    
    
			val graphe = new Graphe;
			val reseau = new Reseau;
			val molecule = new Molecule;
			val sommet1 = new Sommet(graphe,"1","2");
			val sommet2 = new Sommet(graphe,"4","4");
			// val noeud1 = new Noed(molecule,"1","3"); //ne focntionne pas
			val noeud1 = new Noed(reseau,"1","3");
			val noeud2 = new Noed(reseau,"1","3");

			val arete = new Arete(sommet1,sommet2);
			val lien = new Lien(noeud1,noeud2);
			
			graphe.addSommet(sommet1);
			graphe.addSommet(sommet2);
			// graphe.addSommet(sommet3);
			//molecule.addSommet(sommet1); // erreur
			reseau.addSommet(noeud1);
			reseau.addSommet(noeud2);

			graphe.addArete(arete);
			
			reseau.addArete(lien);
     
     */
  }

}

