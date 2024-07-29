/**
 * \file GyotoFitsRW.h
 * \brief Class to read/write jnu and anu in FITS File
 *
 */

/*
    Copyright 2019 Frederic Vincent, Thibaut Paumard, Nicolas Aimar

    This file is part of Gyoto.

    Gyoto is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Gyoto is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Gyoto.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GyotoFitsRW_H_
#define __GyotoFitsRW_H_ 

#include <iostream>
#include <fstream>
#include <iomanip>
#ifdef GYOTO_USE_CFITSIO
#include <fitsio.h>
#endif

namespace Gyoto {
  class FitsRW;
}

#ifdef GYOTO_USE_XERCES
#include <GyotoRegister.h>
#endif

/**
 * \class Gyoto::FitsRW
 * \brief Class for reading or writing data in FITS file.
 * The data stored should be 1D array(s).
 *        
 *        
 */
class Gyoto::FitsRW
{
 public:
  FitsRW(); ///< Constructor
  FitsRW(const FitsRW&); ///< Copy constructor
  virtual FitsRW* clone() const ;
  virtual ~FitsRW() ;        ///< Destructor

#ifdef GYOTO_USE_CFITSIO

  /**
   * \brief Creates a FITS file with dummy primary HDU
   *
   *
   * Opens a new fits file referred to by a fitsfile pointer
   * and fills the primary HDU by a single pixel equal to 0.
   * Returns the fitsfile pointer to the new FITS file.
   *
   * \param filename Name of fits file to be created
   *
   */
  fitsfile* fitsCreate(std::string const filename) const;
  /**
   * \brief Open a fits file 
   *
   *
   * \param filename name of the FITS file to be open
   *
   */
  fitsfile* fitsOpen(std::string const filename) const;

  /**
   * \brief Closes a fits file referred to by a fitsfile pointer
   *
   *
   * \param fptr fitsfile pointer to FITS file to be closed
   *
   */
  void fitsClose(fitsfile* fptr) const;

  /**
   * \brief Writes 1D array in FITS files
   *
   *
   * \param fptr fitsfile pointer to FITS file
   * \param extname Name of extension to be written
   * \param src Data to be written in extension
   * \param ndim numer of axes of src
   * \param len of each axes
   */
  void fitsWriteHDUData(fitsfile* const fptr, std::string const extname, double* const src, long const nelements) const;

  /**
   * \brief Writes a key in the header of a given HDU (by default "PRIMARY")
   *
   *
   * \param fptr fitsfile pointer to FITS file
   * \param key Name of the key to be stored
   * \param value Value of the key to be stored
   * \param hdu HDU where to store the key, by default "PRIMARY"
   */
  void fitsWriteKey(fitsfile* const fptr, std::string const key, double value, std::string const hdu="PRIMARY") const;

  /**
   * \brief Read 1D array in FITS files
   *
   *
   * \param fptr fitsfile pointer to FITS file
   * \param extname Name of extension to be read
   */
  double* fitsReadHDUData(fitsfile* const fptr, std::string const extname) const;

  /**
   * \brief Read a specific key of the HDU with a specific 'extname'
   *
   *
   * \param fptr fitsfile pointer to FITS file
   * \param key Name of the key to be read
   * \param hdu HDU extname where to search for the key
   */
  double fitsReadKey(fitsfile* const fptr, std::string const key, std::string const hdu) const;
  
  /**
   * \brief Read a specific key of the HDU defined by its number (by default 1 equivalent ot the "PRIMARY" HDU)
   *
   *
   * \param fptr fitsfile pointer to FITS file
   * \param key Name of the key to be read
   * \param hdu_num HDU number where to search for the key
   */
  double fitsReadKey(fitsfile* const fptr, std::string const key, int const hdu_num=1) const;

  #endif

};


#endif