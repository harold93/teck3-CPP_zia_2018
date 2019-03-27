ZIA

Zia est un projet réalisé en C++.

Le but est de créer un serveur en C++.

il est possible de lancer plusieurs serveurs en même temps chaque fichier xml dans le dossier config est eserveur.

Avoi installer php-cgi.

sudo apt install php-cgi

Le projet est Cross Plateforme Linux - MacOs

La commande pour le build est : 


./start.sh



le binaire se trouve dans le dossier racine

Les modules se load dans le fichier de configuration conf/server2.xml

pour créer les fichiers .so il faut compiler à l'aide des makefiles se situant dans les dossiers de modules.

Le module php empeche l'affichage correct des images et des videos, ne pas l'activer pour ces utilisations.

Les fichiers sources des affichages du serveur se situent dans le dossier ./www

Les URLs disponible sont:

/
/index.html
/images.html
/video.html
/php.html

Ainsi qu'une page 404 si l'url n'existe pas


