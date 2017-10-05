/* -*- mode: c++ -*- */

#pragma once

#include <string>

/**
   Read the file pointed to by `filename` into the output.

   @param filename The input filename.
   @return         The data contained in the file pointed to by `filename`.
 **/
std::string readFile(std::string filename);
