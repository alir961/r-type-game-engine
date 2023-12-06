# Pratiques GitHub

## Convention de nommage des commits

Les messages de commit suivent une convention de préfixe pour indiquer la nature des changements apportés. Utilisez les préfixes suivants dans vos messages de commit :

- **feat:** ➞ Pour les nouvelles fonctionnalités.
- **fix:** ➞ Pour les corrections de bugs.
- **refacto:** ➞ Pour les refontes du code existant sans ajouter de fonctionnalité ni résoudre de bug.
- **doc:** ➞ Pour la documentation du code ou du projet.
- **ci:** ➞ Pour les modifications liées aux configurations de l'intégration continue.

## Exemples de messages de commit

#### Ajout d'une nouvelle fonctionnalité
```plaintext
feat: Player can customize is starship
```

#### Correction d'un bug

```plaintext
fix: Remove infinite bullets glitch
```

#### Refonte du code existant

```plaintext
refacto: Improve binary encoding algorithm
```

#### Mise à jour de la documentation

```plaintext
doc: Update game entities schema
```

#### Modification de la configuration de l'intégration continue

```plaintext
ci: Run tests on push and merge
```
