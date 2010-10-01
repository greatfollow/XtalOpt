/**********************************************************************
  Cluster - Implementation of an atomic cluster

  Copyright (C) 2010 by David C. Lonie

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 ***********************************************************************/

#include <gapc/structures/cluster.h>

#include <globalsearch/macros.h>

#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

namespace GAPC {

  Cluster::Cluster(QObject *parent) :
    Structure(parent)
  {
  }

  Cluster::~Cluster()
  {
  }

  void Cluster::constructRandomCluster(const QHash<unsigned int, unsigned int> &comp,
                                       float minIAD,
                                       float maxIAD)
  {
    INIT_RANDOM_GENERATOR();
    // Get atomic numbers
    QList<unsigned int> atomicnums = comp.keys();
    unsigned int totalSpecies = atomicnums.size();

    // Get total number of atoms
    unsigned int totalAtoms = 0;
    for (int i = 0; i < totalSpecies; i++) {
      totalAtoms += comp.value(atomicnums.at(i));
    }

    // Use this queue to determine the order to add the atoms. Value
    // is atomic number
    deque<unsigned int> q;

    // Populate queue
    // - Fill queue
    for (int i = 0; i < totalSpecies; i++) {
      unsigned int atomicnum = atomicnums.at(i);
      for (int j = 0; j < comp[atomicnum]; j++) {
        q.push_back(atomicnum);
      }
    }
    // - Randomize
    random_shuffle(q.begin(), q.end());

    // Populate cluster
    clear();
    while (!q.empty()) {
      // Center the molecule at the origin
      centerAtoms();
      // Upper limit for new position distance
      double max = radius() + maxIAD;
      double x, y, z;
      double shortest;
      // Set first atom to origin
      if (numAtoms() == 0) {
        x = y = z = 0.0;
      }
      // Randomly generate other atoms
      else {
        do {
          // Randomly generate coordinates
          x = RANDDOUBLE() * max;
          y = RANDDOUBLE() * max;
          z = RANDDOUBLE() * max;
          getNearestNeighborDistance(x, y, z, shortest);
        } while (shortest > maxIAD || shortest < minIAD);
      }
      Atom *atm = addAtom();
      Eigen::Vector3d pos (x, y, z);
      atm->setPos(pos);
      atm->setAtomicNumber(q.front());
      q.pop_front();
    }

    resetEnergy();
    resetEnthalpy();
    emit moleculeChanged();
  }

  void Cluster::centerAtoms()
  {
    translate(-center());
  }

  QHash<QString, QVariant> Cluster::getFingerprint() const
  {
    QHash<QString, QVariant> fp = Structure::getFingerprint();
    fp.insert("IADFreq", QVariant(m_histogramFreq));
    fp.insert("IADDist", QVariant(m_histogramDist));
    return fp;
  }


} // end namespace GAPC

//#include "scene.moc"
