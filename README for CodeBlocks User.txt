Pour les utilisateurs de CodeBlocks, verifier que vous avez installé cmake et MinGW et que vos variables d'environnement sont bien configurées.
Excétcutez la commande 'cmake . -G "CodeBlocks - MinGW Makefiles"'.
Cette commande va générer un makefile et un .cbp (codeblocks project) que vous pourrez ouvrir sous codeblocks.
Un fichier bin sera crée, c'est là que les fichier une fois compiler iront.
Copiez le fichier SDL2.dll se trouvant dans lib/x86 dans bin/. Ensuite essayez de compiler avec codeblocks.