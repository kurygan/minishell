# Fonctions Externes Autorisées – Minishell

## 📁 Partie 1 : Tableau des fonctions par bibliothèque


| Bibliothèque  | Fonctions autorisées                       			    |
|---------------|-----------------------------------------------------------|
| `unistd.h`    | `write`, `read`, `close`, `access`, `fork`, `pipe`, `dup` |
|			    | `dup2`, `getcwd`, `chdir`, `isatty`, `ttyname`, `ttyslot` |
|---------------|-----------------------------------------------------------|
| `stdlib.h`    | `malloc`, `free`, `exit`, `getenv`      				    |
|---------------|-----------------------------------------------------------|
| `stdio.h`     | `printf`, `perror`					   		   	        |
|---------------|-----------------------------------------------------------|
| `string.h`    | `strerror`					         		    	    |
|---------------|-----------------------------------------------------------|
| `sys/types.h` | Définitions de types (`mode_t`, `pid_t`, etc.) utilisés   |
|			    | par d’autres headers									    |
|---------------|-----------------------------------------------------------|
| `sys/stat.h`  | `stat`, `lstat`, `fstat`					  	    	    |
|---------------|-----------------------------------------------------------|
| `sys/wait.h`  | `wait`, `waitpid`					         	    	    |
|---------------|-----------------------------------------------------------|
| `sys/ioctl.h` | `ioctl`					         		  		  	    |
|---------------|-----------------------------------------------------------|
| `errno.h`     | Déclaration de `errno` (utile pour `perror`/`strerror`)   |
|---------------|-----------------------------------------------------------|
| `signal.h`    | `signal`, `sigaction`, `kill`, `sigemptyset`, `sigaddset` |
|---------------|-----------------------------------------------------------|
| `dirent.h`    | `opendir`, `readdir`, `closedir`				    	    |
|---------------|-----------------------------------------------------------|
| `termios.h`   | `tcsetattr`, `tcgetattr`					           	    |
|---------------|-----------------------------------------------------------|
| `fcntl.h`     | `open`					 	         		    	    |
|---------------|-----------------------------------------------------------|


## 📘 Partie 2 : Description des fonctions


### GNU Readline :

* Fonctions qui facilitent la saisie et l’historique des lignes de commande

`printf` -> Affiche du texte formaté dans le terminal. Principalement utilisé pour afficher des messages ou des résultats.

`readline(prompt)` -> Affiche `prompt`, lit une ligne avec édition (déplacement, suppression, insertion).

`add_history(line)` -> Ajoute `line` à l’historique des commandes.

`rl_clear_history()` -> Vide complètement l’historique.

`rl_on_new_line()` -> Indique à Readline qu’on passe sur une nouvelle ligne (après un \n).

`rl_replace_line(text, clear_undo)` -> Remplace le contenu courant de la ligne par `text`.

`rl_redisplay()` -> Force la réaffichage de la ligne courante (utile après modification du buffer).


### Termcap / ncurses / terminfo :

* Fonctions qui donnent accès aux capacités du terminal (Positionnement du curseur, couleurs, etc)

`tgetent(bp, term)` -> Charge dans `bp` les informations du terminal identifié par `term`.

`tgetflag("capname")` -> Récupère un indicateur booléen (true/false) de la capacité nommée "capname".

`tgetnum("capname")` -> Récupère une valeur numérique associée à la capacité "capname".

`tgetstr("capname", &area)` -> Renvoie la séquence de contrôle (string) pour la capacité "capname".

`tgoto(cm_string, col, row)` -> Génère la séquence pour déplacer le curseur à la ligne "row" et la colonne "col".

`tputs(string, affcnt, putcfunc)` -> Affiche "string" en gérant le timing (padding) pour l’impression.


### Entrée / Sortie & fichiers :

* Fonctions pour ouvrir, lire, écrire et gérer les fichiers

`open(path, flags, mode)` -> Ouvre ou crée le fichier "path", renvoie un descripteur de fichier.

`read(fd, buf, count)` -> Lit jusqu’à "count" octets depuis "fd" dans le buffer "buf".

`write(fd, buf, count)` -> Écrit jusqu’à "count" octets depuis le buffer "buf" sur "fd".

`close(fd)` -> Ferme le descripteur de fichier "fd".

`access(path, mode)` -> Teste les permissions (lecture/écriture/exécution) sur "path".

`stat(path, statbuf)` -> Remplit "statbuf" avec les méta-infos (taille, permissions, type) sur le fichier "path".

`lstat(path, statbuf)` -> Comme `stat()`, mais ne suit pas les liens symboliques.

`fstat(fd, statbuf)` -> Comme `stat()`, mais prend un descripteur "fd" au lieu d’un chemin.

`unlink(path)` -> Supprime le nom de fichier "path" (et son contenu si plus aucun lien).


### Partitionnement mémoire & chaînes :

* Fonctions pour l’allocation/libération mémoire et la gestion des chaînes de caractères

`malloc(size)` -> Alloue un bloc mémoire de "size" octets, retourne un pointeur vers ce bloc.

`free(ptr)` -> Libère le bloc mémoire pointé par "ptr".

`printf(format, ...)` -> Écrit sur la sortie standard selon le format "format".

`perror(msg)` -> Affiche "msg" suivi de la description textuelle de l’erreur courante (`errno`).

`strerror(errnum)` -> Retourne la description textuelle de l’erreur identifiée par "errnum".


### Processus & communication :

* Fonctions pour création de processus et échanges inter-processus

`fork()` -> Crée un processus fils identique au processus parent.

`execve(path, argv, envp)` -> Remplace le processus courant par le programme "path" avec les arguments "argv" et l’environnement "envp".

`wait(status)` -> Attend la terminaison d’un fils, stocke son code de retour dans "status".

`waitpid(pid, status, options)` -> Attend la terminaison du fils identifié par "pid".

`wait3(status, options, rusage)` -> Variante de `wait()` récupérant aussi des infos d’usage de ressources.

`wait4(pid, status, options, rusage)` -> Variante de `waitpid()` avec infos d’usage de ressources.

`pipe(fds)` -> Crée un pipe : "fds[0]" pour lecture et "fds[1]" pour écriture.

`dup(oldfd)` -> Duplique le descripteur "oldfd", renvoie un nouveau descripteur libre.

`dup2(oldfd, newfd)` -> Duplique "oldfd" vers "newfd", en fermant "newfd" si nécessaire.


### Signaux :

* Fonctions pour gérer les signaux POSIX

`signal(sig, handler)` -> Associe le gestionnaire simple "handler" au signal "sig".

`sigaction(sig, act, oldact)` -> Configure finement le comportement du signal "sig".

`sigemptyset(set)` -> Initialise le masque de signaux "set" à vide.

`sigaddset(set, sig)` -> Ajoute le signal "sig" au masque "set".

`kill(pid, sig)` -> Envoie le signal "sig" au processus identifié par "pid".


### Répertoires :

* Fonctions pour parcourir le contenu d’un répertoire

`opendir(path)` -> Ouvre le répertoire "path" en vue de sa lecture.

`readdir(dirp)` -> Lit l’entrée suivante du répertoire pointé par "dirp".

`closedir(dirp)` -> Ferme le flux de répertoire "dirp".


### Terminal & environnement :

* Fonctions pour interagir avec le terminal et les variables d’environnement

`getcwd(buf, size)` -> Copie le chemin du répertoire courant dans "buf" (taille "size").

`chdir(path)` -> Change le répertoire courant pour "path".

`isatty(fd)` -> Retourne true si "fd" est associé à un terminal.

`ttyname(fd)` -> Retourne le nom du terminal associé à "fd".

`ttyslot()` -> Renvoie l’indice du terminal dans /etc/ttys.

`ioctl(fd, request, argp)` -> Effectue une opération de contrôle sur l’appareil ou terminal "fd".

`tcgetattr(fd, termios_p)` -> Lit les attributs du terminal dans la structure "termios_p".

`tcsetattr(fd, optional_actions, termios_p)` -> Applique les attributs de terminal définis dans "termios_p".

`getenv(name)` -> Retourne la valeur de la variable d’environnement "name".

`exit(status)` -> Termine le processus avec le code de retour "status".