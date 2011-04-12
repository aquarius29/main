/* Author: Jarryd Hall
 * Purpose: A number of listener functions to be run on seperate 
 * pthreads to handle input data via protocol_read...
 *
 */ 

// listener functions

// ui input such as destination changes, new collision tiles etc.
void uilistener()
{
	data = protocol_read_ui_input;
	
	if (data == null)
	{
		printf("No UI input data\n");
	}
	else 
		// set the tilemap data e.g. call a fucntion and send the data received.
}

// movement report from the movement group
void movementlistener()
{
	data = protocol_read_movement;
	
	if (data == null)
	{
		printf("No movement input data\n");
	}
	else
		// send the command to the positioning system
}

// commands via the UI, user/manual commands
void commandslistener()
{
	data = protocol_read_command;
	
	if (data == null)
	{
		printf("No command input data\n");
	}
	else
		// send the command to the movement group using protocol_write
}