//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2015 Paul T. Bauman, Roy H. Stogner
// Copyright (C) 2010-2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-


// This class
#include "grins/turbulence_models_base.h"

// GRINS
#include "grins/assembly_context.h"
#include "grins/constant_viscosity.h"
#include "grins/parsed_viscosity.h"
#include "grins/spalart_allmaras_viscosity.h"
#include "grins/grins_physics_names.h"
#include "grins/turbulence_models_macro.h"

// libMesh
#include "libmesh/utility.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/getpot.h"
#include "libmesh/fem_system.h"

namespace GRINS
{
  template<class Mu>
  TurbulenceModelsBase<Mu>::TurbulenceModelsBase(const std::string& physics_name, const GetPot& input )
    : Physics(physics_name, input),
      _rho(input("Physics/"+incompressible_navier_stokes+"/rho", 1.0)),
      _mu(input)
  {
    return;
  }

  template<class Mu>
  void TurbulenceModelsBase<Mu>::init_variables( libMesh::FEMSystem* system )
  {
    this->_dim = system->get_mesh().mesh_dimension();
        
    this->_mu.init(system); 
   
    return;
  }

  template<class Mu>
  TurbulenceModelsBase<Mu>::~TurbulenceModelsBase()
  {
    return;
  }  
     
} // namespace GRINS

// Instantiate
INSTANTIATE_TURBULENCE_MODELS_SUBCLASS(TurbulenceModelsBase);
