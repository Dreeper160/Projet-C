#!/bin/bash
set -e

echo "=== 1. Téléchargement de la bibliothèque MLV dans /tmp ==="
cd /tmp
rm -rf mlv-2.0.2 mlv-2.0.2.tar.gz

# Téléchargement depuis le dépôt officiel de l'université (avec fallback Savannah)
if ! wget http://www-igm.univ-mlv.fr/~boussica/mlv/depot/mlv-2.0.2/mlv-2.0.2.tar.gz; then
    echo "Lien principal indisponible, tentative sur le miroir Savannah..."
    wget http://download.savannah.nongnu.org/releases/mlv/mlv-2.0.2.tar.gz
fi

echo "=== 2. Extraction de l'archive ==="
tar -xvzf mlv-2.0.2.tar.gz
cd mlv-2.0.2

echo "=== 3. Configuration et compilation ==="
# -fcommon et -Wno-error permettent de compiler MLV avec les versions récentes de GCC
./configure --prefix=/usr CFLAGS="-O2 -fcommon -Wno-error"
make

echo "=== 4. Installation sur le système ==="
sudo make install
sudo ldconfig

echo "=== 5. Nettoyage ==="
cd ~/Projet-C
rm -rf /tmp/mlv-2.0.2 /tmp/mlv-2.0.2.tar.gz

echo "=== Installation de MLV terminée avec succès ! ==="