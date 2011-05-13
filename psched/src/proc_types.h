/*! * * * * * * * * * * * * * * * * * *
 * @file extsched_proc_types.h
 * @brief Extended Sheduler process \n
 *        types defined.
 * @date 2011-04-26
 * @author Taher Odeh
 * * * * * * * * * * * * * * * * * * * */

#define PROC_CAM 1
#define PROC_UI 2
#define PROC_NAV 3

typedef enum proc_type{
  proc_cam = PROC_CAM, /* camera */
  proc_ui = PROC_UI,  /* ui */
  proc_nav = PROC_NAV  /* navigation */
} proc_type ; 


