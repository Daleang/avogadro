/**********************************************************************
  Atom - Atom class derived from the base Primitive class

  Copyright (C) 2007 Donald Ephraim Curtis
  Copyright (C) 2008 Marcus D. Hanwell

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.sourceforge.net/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#ifndef ATOM_H
#define ATOM_H

#include <avogadro/primitive.h>

namespace OpenBabel {
  class OBAtom;
}

namespace Avogadro {

  class Molecule;
  /**
   * @class Atom atom.h <avogadro/atom.h>
   * @brief Atom Class
   * @author Marcus D. Hanwell
   *
   * The Atom class is a Primitive subclass that provides an atom object. All
   * atoms must be owned by a Molecule and should also be deleted by the
   * Molecule that owns it.
   */
  class Bond;
  class AtomPrivate;
  class A_EXPORT Atom : public Primitive
  {
    Q_OBJECT

    public:
      /**
       * Constructor
       *
       * @param parent the object parent.
       */
      Atom(QObject *parent=0);

      /**
        * @return The position of the atom.
        */
      const Eigen::Vector3d * pos() const;

      /**
       * Sets the position of the atom.
       * @param vec Position of the atom.
       */
      void setPos(const Eigen::Vector3d &vec);

      /**
       * Sets the position of the atom.
       * @param vec Position of the atom.
       */
      void setPos(const Eigen::Vector3d *vec) { setPos(*vec); }

      /**
       * @return Atomic number of the atom.
       * @note Replaces GetAtomicNum()
       */
      inline int atomicNumber() const { return m_atomicNumber; }

      /**
       * Set the atomic number of the atom.
       */
      inline void setAtomicNumber(int num) { m_atomicNumber = num; }

      /**
       * Adds a reference to a bond to the atom.
       */
      void addBond(Bond* bond);

      /**
       * Deletes the reference of the bond to the atom.
       */
      void deleteBond(Bond* bond);

      /**
       * @return List of bond ids to the atom.
       */
      QList<unsigned long int> bonds() { return m_bonds; }

      /**
       * @return List of neighbor ids to the atom (atoms bonded to that atom).
       */
      QList<unsigned long int> neighbors() { return m_neighbors; }

      /**
       * The valence of the atom. FIXME - don't think this will cut it...
       */
      double valence() { return static_cast<double>(m_neighbors.size()); }

      /**
       * @return True if the atom is a hydrogen.
       */
      bool isHydrogen() const { return m_atomicNumber == 1; }

      /**
       * Set the partial charge of the atom.
       * @note This is not calculated at the moment!
       */
      inline void setPartialCharge(double charge) const
      {
        m_partialCharge = charge;
      }

      /**
       * @return Partial charge of the atom.
       */
      double partialCharge() const;

      /// Our OpenBabel conversion functions
      /**
       * @return An OpenBabel::OBAtom copy of the atom.
       */
      OpenBabel::OBAtom OBAtom();

      /**
       * Copies an OpenBabel::OBAtom to the atom.
       */
      bool setOBAtom(OpenBabel::OBAtom *obatom);

      Atom& operator=(const Atom& other);

    private:
      /* shared d_ptr with Primitive */
      Molecule *m_molecule; /** Parent molecule - should always be valid. **/
      int m_pos;
      int m_atomicNumber;
      QList<unsigned long int> m_bonds, m_neighbors;
      mutable double m_partialCharge;
      Q_DECLARE_PRIVATE(Atom)
  };

} // End namespace Avoagdro

#endif
