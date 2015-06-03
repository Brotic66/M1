<?php

/**
 * \file formulaire.php
 * \author Brice VICO
 * \date 13/05/2015
 *
 * \brief Ce fichier permet de transférer les données de formulaire passées dans l'URL vers le fichier XSLT plan.xsl
 */

$parametres = urldecode($_SERVER['QUERY_STRING']);

$docXml = new DOMDocument();
$docXml->load('BDD.xml');

$docXsl = new DOMDocument();
$docXsl->load('plan.xsl');

$proc = new XsltProcessor();
$proc ->importStylesheet($docXsl);
$proc->setParameter(null, 'criteres', $parametres);

echo $proc->transformToXML($docXml);

?>
