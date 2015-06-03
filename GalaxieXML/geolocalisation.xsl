<?xml version="1.0" encoding="utf8" ?>
    <xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" >
     
            <xsl:output method="html" encoding="utf8"/>
            <xsl:strip-space elements="*"/>
            <xsl:template match="*">
                    <html>
                            <head>
                                    <title>Géolocalisation</title>
                            </head>
                            <body>
                                <style type="text/css">
                                    body {
                                    color: purple;
                                    background-color: #F5F5F5 }
                                    h1 {
                                    font-family: Helvetica, Geneva, Arial,
                                    SunSans-Regular, sans-serif;
                                    text-align:center }
                                    #corps {
                                    width:700px;
                                    margin-left:auto;
                                    margin-right:auto;
                                    height:800px;
                                    background-color: #d8da3d}
                                    #pres {
                                    text-align:center }
                                </style>
                            <div id="pre">
                            <h1>
                                Librairie 2000
                            </h1>
                            <i>
                                Bienvenue sur le site de la librairie 2000!!

                                Veuillez utiliser le formulaire ci-dessous pour effectuer une recherche.

                                Bonne visite.
                            </i>

                            <h3>
                                Formulaire de recherche
                            </h3>

                            <form action="relais.php" method="GET">
                                <select name="geolocalisation/Secteur-idSecteur">
                                    <option value="Any" selected="selected"> Tous les secteurs </option>
                                    <xsl:for-each select="Secteur">
                                        <option value="{./@idSecteur}"> <xsl:value-of select="Informations/nom/@nomCourant" /></option>
                                    </xsl:for-each>
                                </select>

                                <select name="Salle-idSalle">
                                    <option value="Any" selected="selected"> Toutes les salles </option>
                                    <xsl:for-each select="Secteur">
                                        <xsl:for-each select="Salle">
                                            <option value="{./@idSalle}"> <xsl:value-of select="Informations/nom/@nomCourant" /> </option>
                                        </xsl:for-each>
                                    </xsl:for-each>
                                </select>

                                <br />
                                <table>
                                    <tr>
                                        <td>Nom du livre recherché</td> 
                                        <td>
                                            <select name="Livre-idLivre">
                                            <option value="Any" selected="selected"> Tous les livres </option>
                                            <xsl:for-each select="Secteur">
                                                <xsl:for-each select="Salle">
                                                    <xsl:for-each select="Livre">
                                                        <option value="{./@idLivre}"> <xsl:value-of select="titre/@nomCourant" /> </option>
                                                    </xsl:for-each>
                                                </xsl:for-each>
                                            </xsl:for-each>
                                        </select>
                                        </td> 
                                    </tr>

                                     <tr>
                                        <td>Types de livre</td> 
                                        <td>
                                        <select name="Livre-type">
                                            <option value="Any" selected="selected"> Tous les types </option>
                                            <xsl:for-each select="typeLivres/typeL">
                                                <option value="{@type}"> <xsl:value-of select="@type" /> </option>    
                                            </xsl:for-each>
                                        </select>
                                        </td> 
                                    </tr>
                                    
                                    <tr>
                                        <td>Auteurs</td> 
                                        <td>
                                        <select name="Livre-auteur">
                                            <option value="Any" selected="selected"> Tous les auteurs </option>
                                            <xsl:for-each select="auteurs/auteur">
                                                <option value="{@nom}"> <xsl:value-of select="@nom" /> </option>    
                                            </xsl:for-each>
                                        </select>
                                        </td> 
                                    </tr>

                                   
                                <br />
                            </table>
                                <input type="submit" value="Envoyer" />
                            </form>
                                </div>
                            </body>


                    </html>
            </xsl:template>
     
        
     
    </xsl:stylesheet>

