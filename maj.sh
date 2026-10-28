#!/usr/bin/env bash

set -e

echo "=== MENU GIT ==="
echo "1. Créer une branche"
echo "2. Changer de branche"
echo "3. Fetch"
echo "4. Merge branche dans la branche actuelle"
echo "5. Update main depuis origin"
echo "6. Quitter"

read -p "Choix: " option

case "$option" in
  1)
    read -p "Nom de la branche: " branch
    git checkout -b "$branch"
    ;;
  2)
    git branch
    read -p "Nom de la branche: " branch
    git checkout "$branch"
    ;;
  3)
    read -p "Remote [origin]: " remote
    remote="${remote:-origin}"
    git fetch "$remote"
    ;;
  4)
    git branch
    read -p "Branche à merger (ex: main): " source
    git merge "$source"
    ;;
  5)
    git checkout main
    git fetch origin
    git merge origin/main
    ;;
  6)
    exit 0
    ;;
  *)
    echo "Choix inconnu"
    exit 1
    ;;
esac

echo "Terminé."
git status