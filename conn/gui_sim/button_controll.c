/*! 
    @author Michal Musialik
*/

/*
Commands that are used by the frame.c that allow wireless 
communication to the drone.

*/

/*GTK widget*/
GtkLabel *label;


void right_controll(){

  gtk_label_set_text(label,"Going right");
  send_right();
}

void back_controll(){

  gtk_label_set_text(label,"Going down");
  send_back();
}

void foward_controll(){

  gtk_label_set_text(label,"Going up");
  send_foward();
}

void left_controll(){

  gtk_label_set_text(label,"Going left");
  send_left();
}


void command_quit(){
  
  send_exit();
  gtk_main_quit ();
  
}

void auto_controll(){

  gtk_label_set_text(label,"Auto enabled");
  send_auto();
}

void info_pressed(){

  printf("Pressing dirrection button\n");

}

void hover(){

  gtk_label_set_text(label,"Hovering");
  send_hover();
}


void alt_up(){

  gtk_label_set_text(label,"Alt up");
  send_alt_up();
}


void alt_down(){

  gtk_label_set_text(label,"Alt down");
  send_alt_down();
}

void drone_connect(){

  gtk_label_set_text(label,"Connecting");
  setup();
 
}

void landing(void){

  gtk_label_set_text(label,"landing");
  send_landing();
}


void camera_connect(){

   gtk_label_set_text(label,"Starting camera");
   send_camera();
}

