Tate Larsen
gamearch-final
==============

KeyBoard Shortcuts :
====================
                ESC - Exit
                  D - Switch Between Panda and Emitters
              A & S - Switch Emitters (I had 9 or so)
 Left & Right Arrow - Switch Control Functions (There are a lot)
              1 & 2 - Switch Spawner Function (0 is a Box, 1 on a sphere, bunch more past that that can have some strange behavior)
              - & = - Change Particle Size
                  P - Disable the fade in and out ( Need to switch controller to see effect)
                  F - Does something weird I don't remember
        Tab & Tilde - Switch between various camera position
               Home - Set camera to a viewpoint on the Z-axis
           RControl - Cycle zoom levels
          BackSlash - Cycle another set of zoom levels (for further zooming)
          
===================================================================================================================================


State :
=======
Titlebar is of the format:
    "FUN FUN FUN" (<camera_position>) - <emitter_index> - <controller_name> - <spawner_index>"

===================================================================================================================================


Build :
=========
Requires:
    Cmake
    SFML 2.0
    glm
    
Pretty standard cmake then make.
Might currently demand the static SFML libraries (Commenting out line 10 of CMakeLists.txt might fix that)

Standard policy of email if there are issues

===================================================================================================================================


Comments :
=========
Don't mind the stupid number of lines in src/emitter/emitter.cpp and src/emitter/controller_functions.cpp, that's just due to the horrible way I'm switching the control functions currently.

Noticed a lack of grades on LMS for Uberlight and Subspace Skeletal Deformation (I think I included Uberlight in the same submission as SSD, it would be in the readme)