/**
 * \file bv.js
 * \author Brice VICO & Eymard MAMENE
 * \date 13/05/2015
 *
 * \brief Fichier contenant une multitude fonction JavaScript permettant de gérer les intéractions, l'affichage D3JS et 3D
 */

$(document).ready(function()
{
    var jsonObj = []; /**< collection d'objet Json correspondant chacun aux informations sur les éléments trouvé aprés la recherche */
    var listeMur = []; /**< Collection des murs */

    var grille = $("#grille").html();
    console.log(grille);

    /**
     * Cette fonction permet d'ajouter une action sur les cercle SVG permettant d'afficher les informations de cet élément.
     */
    $("circle").on("mouseover", function()
    {
        $("#titreLivre").text($(this).data("titre"));
        $("#auteurLivre").text($(this).data("auteur"));
        $("#isbnLivre").text($(this).data("isbn"));
        $("#editeurLivre").text($(this).data("editeur"));
    });


    /**
     * Cette fonction permet de créer les collections d'objet json "jsonObj" et "listeMur" en fonction des informations contenu dans les
     * champs "data" des cercles svg.
     */
    $("#creerJSON").on("click", function()
    {
        $("circle").each(function()
        {
            var titre = $(this).data("titre");
            var auteur = $(this).data("auteur");
            var isbn = $(this).data("isbn");
            var editeur = $(this).data("editeur");
            var posX = $(this).attr("cx");
            var posY = $(this).attr("cy");
            var posZ = $(this).attr("data-posZ");

            var element = {};
            element["titre"] = titre;
            element["auteur"] = auteur;
            element["isbn"] = isbn;
            element["editeur"] = editeur;
            element["posX"] = posX;
            element["posY"] = posY;
            element["posZ"] = posZ;

            jsonObj.push(element);
        });

        $(this).data("make", "1");
        console.log(jsonObj);

        listeMur.push(
            {
                id : "mur",
                x1 : 10, y1 : 10,
                x2 : 10, y2 :500
            });

        listeMur.push(
            {
                id : "mur",
                x1 : 250, y1 : 500,
                x2 : 250, y2 :10
            });

        listeMur.push(
            {
                id : "mur",
                x1 : 10, y1 : 10,
                x2 : 500, y2 :10
            });

        listeMur.push(
            {
                id : "mur",
                x1 : 500, y1 : 10,
                x2 : 500, y2 :500
            });

        listeMur.push(
            {
                id : "mur",
                x1 : 10, y1 : 500,
                x2 : 500, y2 :500
            });

        listeMur.push(
            {
                id : "mur",
                x1 : 10, y1 : 250,
                x2 : 500, y2 :250
            });
        listeMur.push();

        console.log(listeMur);
    });

    /**
     * Cette fonction permet l'affichage D3JS en fonction des collection d'objet JSON.
     */
    $("#affichageD3js").on("click", function()
    {
        if ($("#creerJSON").data("make") == 0)
        {
            alert("Veuillez d'abords créer le json !");
        }
        else
        {
            $("#grille").html("");

            var zone = [];
            var nbPas = 50;
            var pas = 10;

            for (var i = 0; i < nbPas; i++)
            {
                for (var j = 0; j < nbPas; j++)
                {
                    var objet = {'id' : 'c'+ i + '' + j, 'x' : pas + i * pas, 'y' : pas + j * pas};
                    zone.push(objet);
                }
            }

            window.svg = d3.select("#grille")
                .append('svg')
                .attr("width", pas * (nbPas + 2) + 'px')
                .attr("height", pas * (nbPas + 2) + 'px');

            svg.selectAll()
                .data(zone)
                .enter()
                .append("circle")
                .attr(
                {
                    id : function(data) {return data.id},
                    class : 'point',
                    r : pas / 2,
                    cx : function(data) {return data.x},
                    cy : function(data) {return data.y},
                    fill : 'white',
                    stroke : 'black'
                });

            console.log(listeMur);

            svg.selectAll()
                .data(listeMur)
                .enter()
                .append("line")
                .attr(
                {
                    id : function(data) {return data.id},
                    class : 'mur',
                    x1 : function(data) {return data.x1},
                    x2 : function(data) {return data.x2},
                    y1 : function(data) {return data.y1},
                    y2 : function(data) {return data.y2},
                    stroke : 'black',
                    'stroke-width' : '5px'
                }

            );

            svg.selectAll()
                .data(jsonObj)
                .enter()
                .append("circle")
                .attr(
                {
                    id : "myCircle",
                    class : 'point',
                    r : pas / 2,
                    cx : function(data) {return calculerPointProche(data.posX, pas)},
                    cy : function(data) {return calculerPointProche(data.posY, pas)},
                    fill : 'red',
                    stroke : 'black',
                    "data-titre" : function(data) {return data.titre},
                    "data-isbn" : function(data) {return data.isbn},
                    "data-editeur" : function(data) {return data.editeur},
                    "data-auteur" : function(data) {return data.auteur}
                });
        }
    });

    /**
     * Fonction lancé lors d'un clic sur le bouton d'affichage 3D.
     */
    $("#affichage3D").on("click", function()
    {
        if ($("#creerJSON").data("make") == 0)
        {
            alert("Veuillez d'abords créer le json !");
        }
        else
        {
            $("section").html("");

            init();
        }
    });

    /**
     * \fn calculerPointProche
     * \param pos Une position
     * \param pas Un pas
     * \return int
     *
     * \brief Permet de calculer le point le plus proche de la position exacte d'une élément.
     */
    function calculerPointProche(pos, pas)
    {
        var tmp = Math.floor(parseInt(pos) / parseInt(pas)) * 10;

        if (tmp == 0)
        {
            return parseInt(tmp) + 10;
        }
        else
        {
            return parseInt(tmp);
        }
    }

    /**
     * \fn init
     *
     * \brief Permet de créer le rendu 3D d'une scène en utilisant les données des collection d'objets JSON.
     */
    function init()
    {
        var scene = new THREE.Scene();
        var largeur = window.innerWidth;
        var hauteur = window.innerHeight;

        var cameraH = new THREE.PerspectiveCamera(75, largeur/hauteur, 0.1, 20000);
        scene.add(cameraH);
        cameraH.position.set(0,150,400);
        cameraH.lookAt(scene.position);

        var renderer = new THREE.WebGLRenderer({antialias : true});
        renderer.setSize(largeur, hauteur);
        renderer.setClearColor(0xFFFFFF, 1.0);

        var onKeyDown = function(event)
        {
            onKeyDownBis(event, cameraH);
        };
        document.addEventListener('keydown', onKeyDown, false);

        var controls = new THREE.OrbitControls( cameraH, renderer.domElement );

        $("body").html(renderer.domElement);

        ajouterElementExterne(cameraH);

        /**
         * Plaçage des élements graphiques !
         */

        var material = new THREE.MeshBasicMaterial( { color : 0x1C1C1C, side: THREE.DoubleSide} );
        var geometry = new THREE.BoxGeometry( 500, 1, 500 );
        var sol = new THREE.Mesh(geometry, material);
        scene.add(sol);

        genererMur(scene);
        genererElement(scene);

        /**
         * Création du rendu.
         */
        var animate = function()
        {
            requestAnimationFrame(animate);
            renderer.render(scene, cameraH);

            if ($("#sourisActive").data("active") == "1")
            {
                controls.update();
            }

            $("#maCam").attr("cx", cameraH.position.x);
            $("#maCam").attr("cy", cameraH.position.z);
        };

        animate();
    }

    /**
     * \fn genererMur
     * \param scene
     *
     * \brief Génère les mur dans la scéne "scéne" en fonction de "listeMur"
     */
    function genererMur(scene)
    {
        for (var i = 0; i < listeMur.length; i++)
        {
            var x1 = listeMur[i].x1;
            var x2 = listeMur[i].x2;
            var y1 = listeMur[i].y1;
            var y2 = listeMur[i].y2;
            var longueur = Math.sqrt(((x2-x1) * (x2-x1)) + ((y2-y1) * (y2-y1)))
            var material = new THREE.MeshBasicMaterial( { color : 0xFF0000} );
            var geometry = new THREE.BoxGeometry( longueur, 50, 1);
            var mur = new THREE.Mesh(geometry, material);
            mur.position.set(-250 + (x1 + x2) / 2, 25, -250 + (y1 + y2) /2 );
            mur.rotation.y = Math.atan(Math.abs(y2 - y1) / Math.abs(x2 - x1));
            scene.add(mur);
            console.log(i);
        }
    }

    /**
     * \fn genererElement
     * \param scene
     *
     * \brief Génère les éléments dans la scéne "scéne" en fonction de "jsonObj"
     */
    function genererElement(scene)
    {
        for (var i = 0; i < jsonObj.length; i++)
        {
            var x1 = jsonObj[i].posX;
            var y1 = jsonObj[i].posY;
            var z = jsonObj[i].posZ;

            var material = new THREE.MeshBasicMaterial( { color : 0x0000FF} );
            var geometry = new THREE.BoxGeometry( 15, 10, 15);
            var element = new THREE.Mesh(geometry, material);
            element.position.set(x1 - 250 + 15 , z, y1 -250 + 15 );
            scene.add(element);
            console.log(z);
        }
    }

    /**
     * \fn ajouterElementExterne
     * \param camera
     *
     * \brief permet d'ajouter des élément externes par dessus l'affichage 3D.
     */
    function ajouterElementExterne(camera)
    {
        $("body").append("<button class=\"btn btn-success\" id=\"sourisActive\" data-active=\"0\">Activer ou Désactiver la souris</button>");
        $("body").append(grille);

        $("#sourisActive")
            .css(
            { "z-index":"3",
                "position":"absolute", "top":"4px", "left":"550px"
            });

        $("#sourisActive")
            .on("click",
            function()
            {
                if ($(this).data("active") == "0")
                {
                    $(this).data("active", "1");
                }
                else
                {
                    $(this).data("active", "0");
                }
                console.log($(this).data("active"));
            });

        $("#svgGrille").css(
            {
                "z-index": "2",
                "position": "absolute",
                "top": "4px",
                "left": "4px"
            }
        );

        $("#svgGrille").append("<circle id=\"maCam\" cx=\"" + camera.position.y + 5 + "\" cy=\"" + camera.position.z + "\" r=\"5\" fill=\"green\" stroke=\"black\"/>");
    }

    /**
     * \fn onKeyDownBis
     * \param event
     * \param camera
     *
     * \brief Cette fonction est appelée par "onKeyDown", qui est dans "init" est permet de rajouter des paramètres supplémentaire à la fonction : camera.
     */
    function onKeyDownBis(event, camera)
    {
        var matrix = camera.projectionMatric;


        switch (event.keyCode)
        {
            case 90 :
                console.log('On avance !');
                camera.position.z -= 2;
                break;
            case 83 :
                console.log('On recule !');
                camera.position.z += 2;
                break;
            case 80 :
                camera.position.y -= 2;
                console.log(camera.position.z);
                break;
            case 77 :
                camera.position.y += 2;
                console.log(camera.position.z);
                break;
            case 81 :
                console.log("On tourne à gauche !");
                camera.rotation.y += 2 * Math.PI / 180;
                break;
            case 68 :
                camera.rotation.y -= 2 * Math.PI / 180;
                console.log("On tourne à droite !");
                break;
        }
    }
});