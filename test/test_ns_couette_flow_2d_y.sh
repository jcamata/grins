#!/bin/bash

PROG="./test_ns_couette_flow_2d_y"

INPUT="./input_files/couette_flow_input_2d_y.in"

PETSC_OPTIONS="-pc_type lu -pc_factor_mat_solver_package mumps"
$PROG $INPUT
