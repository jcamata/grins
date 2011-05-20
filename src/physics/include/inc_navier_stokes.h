//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// GRINS - a low Mach number Navier-Stokes Finite-Element Solver
//
// Copyright (C) 2010,2011 The PECOS Development Team
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the Version 2 GNU General
// Public License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301 USA
//
//-----------------------------------------------------------------------el-
//
// Declarations for the IncompressibleNavierStokes class.
//
// $Id$
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#ifndef INC_NAVIER_STOKES_H
#define INC_NAVIER_STOKES_H

#include "config.h"

#include "libmesh.h"
#include "boundary_info.h"
#include "fe_base.h"
#include "fe_interface.h"
#include "mesh.h"
#include "quadrature.h"
#include "parameters.h"
#include "string_to_enum.h"
#include "fem_system.h"
#include "fem_context.h"

#include "physics.h"

namespace GRINS
{

  //! Physics class for Incompressible Navier-Stokes
  /*
    This physics class implements the classical Incompressible Navier-Stokes equations.
   */
  class IncompressibleNavierStokes : public Physics
  {
  public:

    IncompressibleNavierStokes()
    {};

    ~IncompressibleNavierStokes()
    {};

    //! Read options from GetPot input file.
    virtual void read_input_options( GetPot& input );

    //! Initialization Navier-Stokes variables
    /*!
      Add velocity and pressure variables to system.
     */
    virtual void init_variables( libMesh::FEMSystem* system );

    //! Register variables for coupled physics
    virtual void register_variable_indices( libMesh::FEMSystem* system );

    //! Sets velocity variables to be time-evolving
    virtual void set_time_evolving_vars( libMesh::FEMSystem* system );

    // Context initialization
    virtual void init_context( libMesh::DiffContext &context );

    // residual and jacobian calculations
    // element_*, side_* as *time_derivative, *constraint, *mass_residual

    // Time dependent part(s)
    virtual bool element_time_derivative( bool request_jacobian,
					  libMesh::DiffContext& context,
					  libMesh::FEMSystem* system );

    virtual bool side_time_derivative( bool request_jacobian,
				       libMesh::DiffContext& context,
				       libMesh::FEMSystem* system );

    // Constraint part(s)
    virtual bool element_constraint( bool request_jacobian,
				     libMesh::DiffContext& context,
				     libMesh::FEMSystem* system );

    virtual bool side_constraint( bool request_jacobian,
				  libMesh::DiffContext& context,
				  libMesh::FEMSystem* system );

    // Mass matrix part(s)
    virtual bool mass_residual( bool request_jacobian,
				libMesh::DiffContext& context,
				libMesh::FEMSystem* system );

  protected:

    //! Physical dimension of problem
    unsigned int _dim;

    //! Indices for each (owned) variable;
    VariableIndex _u_var; /* Index for velocity_x field */
    VariableIndex _v_var; /* Index for velocity_y field */
    VariableIndex _w_var; /* Index for velocity_z field */
    VariableIndex _p_var; /* Index for pressure field */

    //! Indices for each (registered) variable;
    /*!
      This depends on pre-defined set of coupling terms.
     */
    RegtdVariableIndex _T_var;  /* Index for temperature field */
    RegtdVariableIndex _E_var;  /* Index for electric field */
    RegtdVariableIndex _Bx_var; /* Index for Bx field */
    RegtdVariableIndex _By_var; /* Index for By field */
    RegtdVariableIndex _Bz_var; /* Index for Bz field */

    //! Element type, read from input
    libMeshEnums::FEFamily _FE_family;

    //! Element orders, read from input
    libMeshEnums::Order _V_order, _P_order;

    //! Material parameters, read from input
    // TODO: Is it safe to assume these are constant, or do we want
    // TODO: to create objects to allow spatial variation?
    libMesh::Number _rho, _mu;

    //! Returns the value of a forcing function at point pt_xyz.
    // This value depends on which option is set.
    // TODO: any other option to return? other than libMesh::Point?
    libMesh::Point forcing(const libMesh::Point& pt_xyz);
  };

} //End namespace block

#endif // INC_NAVIER_STOKES_H
