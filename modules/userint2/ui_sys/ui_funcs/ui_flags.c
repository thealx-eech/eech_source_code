// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_ui_object_state [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_state [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_drawable [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_drawable [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_autosize [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_autosize [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_redraw [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_redraw [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_redraw_all [NUM_UI_TYPES]) (ui_object *obj, int flag);


void (*fn_set_ui_object_moveable [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_moveable [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_resizeable [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_resizeable [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_list_item [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_list_item [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_item_number [NUM_UI_TYPES]) (ui_object *obj, int number);

int (*fn_get_ui_object_item_number [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_item_number2 [NUM_UI_TYPES]) (ui_object *obj, int number);

int (*fn_get_ui_object_item_number2 [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_clear [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_clear [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_global [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_global [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_user_flag1 [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_user_flag1 [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_user_flag2 [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_user_flag2 [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_user_flag3 [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_user_flag3 [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_user_flag4 [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_user_flag4 [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_list_box_y_space [NUM_UI_TYPES]) (ui_object *obj, float y_space);

float (*fn_get_ui_object_list_box_y_space [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_virtual_coords [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_virtual_coords [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_tool_tips_timer [NUM_UI_TYPES]) (ui_object *obj, int timer);

int (*fn_get_ui_object_tool_tips_timer [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_highlightable [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_highlightable [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_highlighted [NUM_UI_TYPES]) (ui_object *obj, int flag);

int (*fn_get_ui_object_highlighted [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_start_real_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, unsigned char alpha);

void (*fn_get_ui_object_start_real_colour [NUM_UI_TYPES]) (ui_object *obj, char *red, char *green, char *blue, unsigned char *alpha);


void (*fn_set_ui_object_end_real_colour [NUM_UI_TYPES]) (ui_object *obj, char red, char green, char blue, unsigned char alpha);

void (*fn_get_ui_object_end_real_colour [NUM_UI_TYPES]) (ui_object *obj, char *red, char *green, char *blue, unsigned char *alpha);


void (*fn_set_ui_object_t_value [NUM_UI_TYPES]) (ui_object *obj, float t);

float (*fn_get_ui_object_t_value [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_time_length [NUM_UI_TYPES]) (ui_object *obj, int time);

int (*fn_get_ui_object_time_length [NUM_UI_TYPES]) (ui_object *obj);



void (*fn_set_ui_object_start_time [NUM_UI_TYPES]) (ui_object *obj, int start_time);

int (*fn_get_ui_object_start_time [NUM_UI_TYPES]) (ui_object *obj);


void (*fn_set_ui_object_offset_time [NUM_UI_TYPES]) (ui_object *obj, int offset_time);

int (*fn_get_ui_object_offset_time [NUM_UI_TYPES]) (ui_object *obj);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_flag (ui_object *obj, int flag)
{

   obj;
   flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int default_get_ui_object_flag (ui_object *obj)
{

   obj;

   return (0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_float_flag (ui_object *obj, float flag)
{

   obj;
   flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float default_get_ui_object_float_flag (ui_object *obj)
{

   obj;

   return (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_set_ui_object_real_colour (ui_object *obj, char blue, char green, char red, unsigned char alpha)
{

   obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void default_get_ui_object_real_colour (ui_object *obj, char *blue, char *green, char *red, unsigned char *alpha)
{

   obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ui_object_flags_default_functions (void)
{

   int
      i;

   for (i = 0; i < NUM_UI_TYPES; i ++)
   {

      fn_set_ui_object_state [i]          = default_set_ui_object_flag;

      fn_get_ui_object_state [i]          = default_get_ui_object_flag;


      fn_set_ui_object_drawable [i]       = default_set_ui_object_flag;

      fn_get_ui_object_drawable [i]       = default_get_ui_object_flag;


      fn_set_ui_object_autosize [i]       = default_set_ui_object_flag;

      fn_get_ui_object_autosize [i]       = default_get_ui_object_flag;


      fn_set_ui_object_redraw [i]         = default_set_ui_object_flag;

      fn_get_ui_object_redraw [i]         = default_get_ui_object_flag;


      fn_set_ui_object_redraw_all [i]     = default_set_ui_object_flag;


      fn_set_ui_object_moveable [i]       = default_set_ui_object_flag;

      fn_get_ui_object_moveable [i]       = default_get_ui_object_flag;


      fn_set_ui_object_resizeable [i]     = default_set_ui_object_flag;
      
      fn_get_ui_object_resizeable [i]     = default_get_ui_object_flag;


      fn_set_ui_object_list_item [i]      = default_set_ui_object_flag;
      
      fn_get_ui_object_list_item [i]      = default_get_ui_object_flag;


      fn_set_ui_object_item_number [i]    = default_set_ui_object_flag;
      
      fn_get_ui_object_item_number [i]    = default_get_ui_object_flag;


      fn_set_ui_object_item_number2 [i]   = default_set_ui_object_flag;
      
      fn_get_ui_object_item_number2 [i]   = default_get_ui_object_flag;


      fn_set_ui_object_clear [i]          = default_set_ui_object_flag;
      
      fn_get_ui_object_clear [i]          = default_get_ui_object_flag;


      fn_set_ui_object_global [i]         = default_set_ui_object_flag;
      
      fn_get_ui_object_global [i]         = default_get_ui_object_flag;


      fn_set_ui_object_user_flag1 [i]     = default_set_ui_object_flag;
      
      fn_get_ui_object_user_flag1 [i]     = default_get_ui_object_flag;


      fn_set_ui_object_user_flag2 [i]     = default_set_ui_object_flag;
      
      fn_get_ui_object_user_flag2 [i]     = default_get_ui_object_flag;
		

      fn_set_ui_object_user_flag3 [i]     = default_set_ui_object_flag;
      
      fn_get_ui_object_user_flag3 [i]     = default_get_ui_object_flag;


      fn_set_ui_object_user_flag4 [i]     = default_set_ui_object_flag;
      
      fn_get_ui_object_user_flag4 [i]     = default_get_ui_object_flag;


      fn_set_ui_object_list_box_y_space [i] = default_set_ui_object_float_flag;
      
      fn_get_ui_object_list_box_y_space [i] = default_get_ui_object_float_flag;


      fn_set_ui_object_virtual_coords [i]  = default_set_ui_object_flag;
      
      fn_get_ui_object_virtual_coords [i]  = default_get_ui_object_flag;


      fn_set_ui_object_tool_tips_timer [i]  = default_set_ui_object_flag;
      
      fn_get_ui_object_tool_tips_timer [i]  = default_get_ui_object_flag;


      fn_set_ui_object_highlightable [i]  = default_set_ui_object_flag;
      
      fn_get_ui_object_highlightable [i]  = default_get_ui_object_flag;


      fn_set_ui_object_highlighted [i]  = default_set_ui_object_flag;
      
      fn_get_ui_object_highlighted [i]  = default_get_ui_object_flag;


		fn_set_ui_object_start_real_colour [i] = default_set_ui_object_real_colour;

		fn_get_ui_object_start_real_colour [i] = default_get_ui_object_real_colour;


		fn_set_ui_object_end_real_colour [i] = default_set_ui_object_real_colour;

		fn_get_ui_object_end_real_colour [i] = default_get_ui_object_real_colour;


		fn_set_ui_object_t_value [i] = default_set_ui_object_float_flag;

		fn_get_ui_object_t_value [i] = default_get_ui_object_float_flag;


		fn_set_ui_object_time_length [i] = default_set_ui_object_flag;

		fn_get_ui_object_time_length [i] = default_get_ui_object_flag;


		fn_set_ui_object_start_time [i] = default_set_ui_object_flag;

		fn_get_ui_object_start_time [i] = default_get_ui_object_flag;


		fn_set_ui_object_offset_time [i] = default_set_ui_object_flag;

		fn_get_ui_object_offset_time [i] = default_get_ui_object_flag;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
