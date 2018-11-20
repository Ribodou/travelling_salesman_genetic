# -*- coding: utf-8 -*-

# Copyright (C) 2017 Lucas Robidou
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# PS: For any question or any suggestion, please contact me at:
#luc.robidou@gmail.com

# objectif: faire des OGM

import random as rd
import numpy as np
import matplotlib.pyplot as plt
import time

def generer_villes(n, vmax) :
    """
        Return an array that contain list like [x,y] where x and y are 
        the coordinates of one city.
    
        :param a: Number of cities.
        :param b: The maximum each coordinate can take.
        :type a: integer
        :type b: integer
        :return: The coorinates of cities
        :rtype: array
    """
    villes = []
    while len(villes) < n :
        x = rd.randrange(0,vmax)
        y = rd.randrange(0,vmax)
        if not([x,y] in villes) :
            villes.append([x,y])
    return np.array(villes)


def distance(pts, i, j) :
    """Calcule la distance entre deux points."""
    return np.sqrt( (pts[i][0]-pts[j][0])**2 + (pts[i][1]-pts[j][1])**2 )


def calculer_distances(villes, origine) :
    """Calcule la matrice representant les distances entre les villes"""
    n = len(villes)
    pts = [[villes[i][j] for j in range(2)] for i in range(n)] + [origine]
    return [[distance(pts,i,j) for j in range(n+1)] for i in range(n+1)]


class Individus:

    global M
    
    def __init__(self, genes = None):
        """
            Initialise un nouvel individu en lui attribuant les gênes passés en
            paramètres.
            Si aucun génome n'est passé, on en crée un aléatoire.
        """
        if genes == None:
            self.genes = []
            self.genes = list(range(len(M) - 1))
            rd.shuffle(self.genes)
        else:
            self.genes = genes
        self.calculer_score()

    def calculer_score(self):
        """
            Renvoie le "score" d'un individu, c'est-à-dire l'efficacité avec
            laquelle il résout le problème.
            Ici, le score est la distance parcourue lors du parcour de toutes
            les villes dans l'ordre spécifié dans le génome de l'individu.
        """
        score = M[-1][self.genes[0]]
        score += sum([M[self.genes[k]][self.genes[k+1]]
            for k in range( len(self.genes) - 1) ])
        self.score = score
    
    def normaliser(self):
        """
            Permet de normaliser le génome d'un individu. S'il ne passe pas par
            toutes les villes, il faut corriger la situation.
            On veut des bébés mutants, mais pas tros monstrueux non plus.
        """
        nouveaux_genes = []
        for gene in self.genes:
            if 0 <= gene < len(M)-1 and gene not in nouveaux_genes:
                nouveaux_genes.append(gene)
        # il peut en manquer (si le test échoue)
        # complétons donc
        for i in range(len(M)-1):
            if i not in nouveaux_genes:
                nouveaux_genes.append(i)
        self.genes = nouveaux_genes
    
    def muter(self):
        """
            Permet de faire muter un individu (ici, en échangeant l'ordre de
            passage de deux villes).
        """
        i = rd.randint(0, len(self.genes) - 1)
        j = rd.randint(0, len(self.genes) - 1)
        self.genes[i], self.genes[j] = self.genes[j], self.genes[i]
        self.calculer_score()
    
    def croiser(self, other):
        """
            Fait se reproduire l'individu avec un autre dans l'espoir que son
            génôme lui permettra d'être un meilleur vendeur de carpette.
            Aldous Huxley searit fier de nous !
        """
        moitiee = len(self.genes) // 2
        genes_bebe = [self.genes[i] for i in range(moitiee)]
        for i in range(moitiee, len(other.genes)):
            genes_bebe.append(other.genes[i])
        bebe = Individus(genes_bebe)
        bebe.normaliser()
        return bebe

    
class Population:

    def __init__(self, nombre_individus):
        self.individus = []
        self.taille = nombre_individus
        for _ in range(nombre_individus):
            self.individus.append(Individus())
    
    def decimer(self, fraction):
        self.individus.sort(key=lambda individu: individu.score)
        while len(self.individus) > fraction / 100 * self.taille:
            self.individus.pop(-1)
    
    def muter(self, probabilite):
        self.individus.sort(key=lambda individu: individu.score)
        for i in range(5, len(self.individus)):
            if rd.random() < probabilite:
                self.individus[i].muter()
    
    def renouveler(self):
        taille = len(self.individus)
        for i in range(-1, taille):
            self.individus.append(self.individus[i].croiser(self.individus[i+1]))


class Afficheur:
    def __init__(self, liste):
        plt.ion()
        plt.ylabel('length of path')
        plt.xlabel('<--- faster              path            longer ----->')
        plt.title("Genetically modified travelling salesman")
        ax = plt.gca()
        ax.plot(liste, color='b', label="Génération n°0")
        plt.legend()
        plt.draw()
        plt.pause(0.001)
        print("afficher")
    
    def afficher(self, liste, numero_de_frame):
        ax = plt.gca()
        wframe = ax.plot(liste, color='g', label="Génération n°{}".format(numero_de_frame))
        plt.legend()
        plt.draw()
        plt.pause(0.001)
        frame = wframe.pop(0)
        frame.remove()


if __name__ == "__main__":
    origine = 0, 0
    M = calculer_distances(generer_villes(30, 25), origine)
    pop = Population(500)
    liste_score = sorted([individu.score for individu in pop.individus])
    afficheur = Afficheur(liste_score)
    for i in range(10000):
        pop.decimer(50)
        pop.renouveler()
        pop.muter(0.3)
        liste_score = sorted([individu.score for individu in pop.individus])
        afficheur.afficher(liste_score, i+1)
