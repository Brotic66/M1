<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"
                xmlns:dyn="http://exslt.org/dynamic">
    <xsl:output method="html" encoding="UTF-8" />
    <xsl:strip-space elements="*" />

<xsl:param name="criteres" />

    <xsl:template name="xpathFactory">
        <xsl:param name="criteres" />
        <xsl:param name="balisePrecedente" />

        <xsl:variable name="tmp" select="substring-before($criteres, '&amp;')" />
        <xsl:variable name="valeur" select="substring-after($tmp, '=')" />
        <xsl:variable name="partieGauche" select="substring-before($tmp, '=')" />
        <xsl:variable name="balise" select="substring-before($partieGauche, '-')" />
        <xsl:variable name="attr" select="substring-after($partieGauche, '-')" />

        <xsl:if test="$balisePrecedente = $balise">

            <xsl:if test="$valeur != 'Any'">
                <xsl:variable name="complementXPathBalise" select="concat('[@',$attr,'=&quot;',$valeur,'&quot;]')" />
                <xsl:value-of select="$complementXPathBalise" />
            </xsl:if>

            <xsl:if test="$valeur = 'Any'">
                <xsl:variable name="complementXPathBalise" />
                <xsl:value-of select="$complementXPathBalise" />
            </xsl:if>

        </xsl:if>

        <xsl:if test="$balise != $balisePrecedente" >

            <xsl:if test="$valeur != 'Any'">
                <xsl:variable name="sousRequette" select="concat('/',$balise,'[@',$attr,'=&quot;',$valeur,'&quot;]')" />
                <xsl:value-of select="$sousRequette" />
            </xsl:if>

            <xsl:if test="$valeur = 'Any'">
                <xsl:variable name="sousRequette" select="concat('/',$balise)" />
                <xsl:value-of select="$sousRequette" />
            </xsl:if>

        </xsl:if>

        <xsl:variable name="reste" select="substring-after($criteres,'&amp;')" />
        <xsl:variable name="resteTaille" select="string-length($reste)"/>

        <xsl:if test="$resteTaille > 0">

            <xsl:variable name="return">
                <xsl:call-template name="xpathFactory">
                    <xsl:with-param name="criteres" select="substring-after($criteres,'&amp;')"/>
                    <xsl:with-param name="balisePrecedente" select="$balise" />
                </xsl:call-template>
            </xsl:variable>

            <xsl:value-of select="$return" />

        </xsl:if>

    </xsl:template>

<xsl:template match="/">

      <xsl:variable name="return">
            <xsl:call-template name="xpathFactory">
                <xsl:with-param name="criteres" select="concat($criteres,'&amp;')"/>
            </xsl:call-template>
        </xsl:variable>

        <html>
            <head>
                <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css" />
                <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
                <script src="http://d3js.org/d3.v3.min.js" charset="utf-8"></script>
                <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r71/three.min.js"></script>
                <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
                <script src="https://stemkoski.github.io/Three.js/js/OrbitControls.js"></script>
                <script src="./bv.js"></script>
            </head>
            <body>
                <header class="row">
                    <div class="container">
                        <p> Requete XPath : <xsl:value-of select="$return" /> </p>
                    </div>
                </header>
                <section class="row">
                    <div class="col-md-5 col-md-offset-1" id="grille">
                        <svg width="800px" height="540px" 
                            xmlns="http://www.w3.org/2000/svg" 
                            xmlns:xlink="http://www.w3.org/1999/xlink"
                            id="svgGrille">

                            <image xlink:href="fond.png" width="505" height="505" />

                            <xsl:for-each select="dyn:evaluate($return)">
                                <circle data-posZ="{@z}" data-titre="{titre/@nomCourant}" data-auteur="{@auteur}" data-isbn="{isbnLivre/@isbn}" data-editeur="{editeurLivre/@edit}" cx="{@x}" cy="{@y}" r="5" fill="red" stroke="black"/>
                            </xsl:for-each>
                        </svg>
                    </div>
                    <div class="col-md-3">
                        <div class="alert alert-info" style="text-align:left;">
                            <p>
                                Passez votre souris sur un point pour afficher ses informations.
                            </p>
                            <p>
                                Titre : <span id="titreLivre"></span><br />
                                Auteur : <span id="auteurLivre"></span><br />
                                ISBN : <span id="isbnLivre"></span><br />
                                Editeur : <span id="editeurLivre"></span><br />
                            </p>
                        </div>
                    </div>
                </section>
                <footer class="row">
                    <div class="col-md-offset-1">
                        <button id="creerJSON" data-make="0" class="btn btn-success">Creer JSON</button>
                        <button id="affichageD3js" class="btn btn-success">Afficher avec d3js</button>
                        <button id="affichage3D" class="btn btn-success">Afficher en 3D</button>
                        <span id="test"></span>
                    </div>
                </footer>
            </body>
        </html>

</xsl:template>


</xsl:stylesheet>
