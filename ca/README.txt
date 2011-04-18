*******************
Collision Avoidance
*******************

Sensors Involved:
4x IR
1x Sonar


Functionality:
Collision Avoidance uses the sensors to detect objects and act to avoid hitting them using a series of filters. This involves the quadrocopters
speed, the distance detected to the object, the current direction, and the directions available without objects.

Current values are hard-coded test values. If you want to change the change test values, go to ca_interface.c and change in collision_run the
variables ir1,ir2,ir3,ir4 to the desired distances.

The algorithm is set to run 5 times in a loop.

There is a main function in ca_interface that can be used. It may need to be removed for integration.


Missing Functionality:
*Collision Avoidance should write a command to protocol for movement
*Collision Avoidance should receive a command from movement through protocol about the speed and direction.
*Height is not calculated.
*The interface is not prepared for integration with movement.

