/*! * * * * * * * * * * * * * * * * * *
 * @file extsched_proc_types.h
 * @brief Extended Sheduler process \n
 *        types defined.
 * @date 2011-04-26
 * @author Taher Odeh
 * @version 1.0
 * * * * * * * * * * * * * * * * * * * */
typedef enum proc_type{
  proc_cam = 1, /* camera */
  proc_ui = 2,  /* ui */
  proc_nav = 3  /* navigation */
} proc_type ; 

#define PROC_CAM 1
#define PROC_UI 2
#define PROC_NAV 3
