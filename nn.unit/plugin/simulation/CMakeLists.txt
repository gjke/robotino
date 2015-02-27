cmake_minimum_required( VERSION 2.6 )
SET( NAME unit_robview_myfunctionblocks_nn_simulation )

IF( WIN32 )
	INCLUDE( $ENV{ROBOTINOVIEW2_API_DIR}/cmake/unit_plugin_simulation.cmake )
ELSE( WIN32 )
	INCLUDE( /usr/local/RobotinoView2/api/cmake/unit_plugin_simulation.cmake )
ENDIF( WIN32 )
