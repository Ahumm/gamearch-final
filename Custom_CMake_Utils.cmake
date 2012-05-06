# CMAKE UTILS

# VERBOSE FLAG
SET(_VERBOSE TRUE)

#### GHETTO MAPS START ####

#################################################################################
## ADD AN EXECUTABLE TO BUILD                                                   #
## FORMAT :                                                                     #
##   SET(PROGRAM_NAMES <executable_name>)                                       #
##   INSERT_INTO_MAP(<executable_name> <source_file_1> <source_file_2> ... )    #
#################################################################################

#################################################################################################################################
##  USAGE  ######################################################################################################################
#################################################################################################################################
## set(PROGRAM_NAMES "final" "final2")                                                                                           #
## set(final "src/final.cpp" "src/model/model.cpp" "src/emitter/emitter.cpp")                                                    #
## set(final "src/final.cpp" "src/model/model.cpp" "src/utils/utils.cpp" "src/emitter/emitter.cpp" "src/emitter/particle.cpp")   #
#################################################################################################################################



## SET MAP PREFIX
SET(_MAP_PREFIX "_MY_MAP")

## CREATE A VARIABLE NAMED _KEY STORING _VALUE (GHETTO MAPING, WOO)
MACRO(INSERT_INTO_MAP _KEY _VALUE)
    SET("${_MAP_PREFIX}_${_KEY}" "${_VALUE}")
ENDMACRO(INSERT_INTO_MAP)

## CREATE A VARIABLE NAMED _DESTINATION_VAR AND STORING THE VALUE OF _KEY (GHETTO MAPING, WOO)
MACRO(GET_FROM_MAP _KEY _DESTINATION_VAR)
    SET("${_DESTINATION_VAR}" "${${_MAP_PREFIX}_${_KEY}}")
ENDMACRO(GET_FROM_MAP)

#### GHETTO  MAPS  END ####