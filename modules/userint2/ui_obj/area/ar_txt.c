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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "userint2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_text (ui_object *obj, const char *text)
{

	int
		length;

	area_ui_object
		*area;

	ui_object
		*parent;

	area = (area_ui_object *) obj->data;

	if (area->text)
	{

		safe_free (area->text);
	}

	area->text = NULL;

	if (text)
	{

		length = strlen (text);
	
		area->text = (char *) safe_malloc ((sizeof (char) * length) + 1);
	
		strcpy (area->text, text);
	}
			
	parent = get_ui_object_parent (obj);

	if (parent)
	{

		set_ui_object_redraw (parent, TRUE);

		while ((parent) && (get_ui_object_clear (parent)))
		{

			parent = get_ui_object_parent (parent);

			if (parent)
			{

				set_ui_object_redraw (parent, TRUE);
			}
		}
	}
	else
	{

		set_ui_object_redraw (obj, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char *get_area_ui_object_text (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_add_text (ui_object *obj, const char *text)
{

	char
		*temp_text;

	int
		new_length,
		old_length;

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	if ((!area->text) || (strlen (area->text) == 0))
	{

		set_ui_object_text (obj, text);

		return;
	}

	new_length = strlen (text);

	old_length = strlen (area->text);

	temp_text = (char *) safe_malloc (old_length + new_length + 1);

	strcpy (temp_text, area->text);

	strcat (temp_text, text);

	set_ui_object_text (obj, temp_text);

	safe_free (temp_text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_text_justify (ui_object *obj, text_justify_types justify)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->text_justify = justify;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static text_justify_types get_area_ui_object_text_justify (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (text_justify_types) (area->text_justify);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_font_type (ui_object *obj, font_types font_id)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->font_type = font_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static font_types get_area_ui_object_font_type (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (font_types) (area->font_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_font_colour (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->font_colour_end.r = red;
	area->font_colour_end.g = green;
	area->font_colour_end.b = blue;
	area->font_colour_end.a = alpha;

	area->font_colour_start.r = red;
	area->font_colour_start.g = green;
	area->font_colour_start.b = blue;
	area->font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->font_colour_end.r = red;
	area->font_colour_end.g = green;
	area->font_colour_end.b = blue;
	area->font_colour_end.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->font_colour_start.r = red;
	area->font_colour_start.g = green;
	area->font_colour_start.b = blue;
	area->font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_font_colour (ui_object *obj)
{

	area_ui_object
		*area;

	rgb_colour
		col;

	int
		dr,
		dg,
		db,
		da;

	float
		t;

	area = (area_ui_object *) obj->data;

	t = get_ui_object_bounded_t_value (obj);

	//
	// Interpolate the colour values
	//

	dr = ( int ) area->font_colour_end.r - ( int ) area->font_colour_start.r;
	dg = ( int ) area->font_colour_end.g - ( int ) area->font_colour_start.g;
	db = ( int ) area->font_colour_end.b - ( int ) area->font_colour_start.b;
	da = ( int ) area->font_colour_end.a - ( int ) area->font_colour_start.a;

	dr *= t;
	dg *= t;
	db *= t;
	da *= t;

	col.r = ( ( int ) area->font_colour_start.r + dr );
	col.g = ( ( int ) area->font_colour_start.g + dg );
	col.b = ( ( int ) area->font_colour_start.b + db );
	col.a = ( ( int ) area->font_colour_start.a + da );

	return (col);
//	return (&(area->font_colour_start));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_font_colour_end (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->font_colour_end);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_font_colour_start (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->font_colour_start);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlighted_font_type (ui_object *obj, font_types font_id)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->highlighted_font_type = font_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static font_types get_area_ui_object_highlighted_font_type (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (font_types) (area->highlighted_font_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlighted_font_colour (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->highlighted_font_colour_end.r = red;
	area->highlighted_font_colour_end.g = green;
	area->highlighted_font_colour_end.b = blue;
	area->highlighted_font_colour_end.a = alpha;

	area->highlighted_font_colour_start.r = red;
	area->highlighted_font_colour_start.g = green;
	area->highlighted_font_colour_start.b = blue;
	area->highlighted_font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlighted_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->highlighted_font_colour_end.r = red;
	area->highlighted_font_colour_end.g = green;
	area->highlighted_font_colour_end.b = blue;
	area->highlighted_font_colour_end.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_highlighted_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->highlighted_font_colour_start.r = red;
	area->highlighted_font_colour_start.g = green;
	area->highlighted_font_colour_start.b = blue;
	area->highlighted_font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_highlighted_font_colour (ui_object *obj)
{

	area_ui_object
		*area;

	rgb_colour
		col;

	int
		dr,
		dg,
		db,
		da;

	float
		t;

	area = (area_ui_object *) obj->data;

	t = get_ui_object_bounded_t_value (obj);

	//
	// Interpolate the colour values
	//

	dr = ( int ) area->highlighted_font_colour_end.r - ( int ) area->highlighted_font_colour_start.r;
	dg = ( int ) area->highlighted_font_colour_end.g - ( int ) area->highlighted_font_colour_start.g;
	db = ( int ) area->highlighted_font_colour_end.b - ( int ) area->highlighted_font_colour_start.b;
	da = ( int ) area->highlighted_font_colour_end.a - ( int ) area->highlighted_font_colour_start.a;

	dr *= t;
	dg *= t;
	db *= t;
	da *= t;

	col.r = ( ( int ) area->highlighted_font_colour_start.r + dr );
	col.g = ( ( int ) area->highlighted_font_colour_start.g + dg );
	col.b = ( ( int ) area->highlighted_font_colour_start.b + db );
	col.a = ( ( int ) area->highlighted_font_colour_start.a + da );

	return (col);
	/*(
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->highlighted_font_colour_start);
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_highlighted_font_colour_end (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->highlighted_font_colour_end);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_highlighted_font_colour_start (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->highlighted_font_colour_start);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_selected_font_type (ui_object *obj, font_types font_id)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->selected_font_type = font_id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static font_types get_area_ui_object_selected_font_type (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (font_types) (area->selected_font_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_selected_font_colour (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->selected_font_colour_end.r = red;
	area->selected_font_colour_end.g = green;
	area->selected_font_colour_end.b = blue;
	area->selected_font_colour_end.a = alpha;

	area->selected_font_colour_start.r = red;
	area->selected_font_colour_start.g = green;
	area->selected_font_colour_start.b = blue;
	area->selected_font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_selected_font_colour_end (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->selected_font_colour_end.r = red;
	area->selected_font_colour_end.g = green;
	area->selected_font_colour_end.b = blue;
	area->selected_font_colour_end.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_selected_font_colour_start (ui_object *obj, char red, char green, char blue, char alpha)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	area->selected_font_colour_start.r = red;
	area->selected_font_colour_start.g = green;
	area->selected_font_colour_start.b = blue;
	area->selected_font_colour_start.a = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_selected_font_colour (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->selected_font_colour_start);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_selected_font_colour_end (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->selected_font_colour_end);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour get_area_ui_object_selected_font_colour_start (ui_object *obj)
{

	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->selected_font_colour_start);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_area_ui_object_tool_tips (ui_object *obj, const char *tool_tips)
{

	int
		length;

	area_ui_object
		*area;

	ui_object
		*parent;

	area = (area_ui_object *) obj->data;

	if (area->tool_tips)
	{

		safe_free (area->tool_tips);
	}

	area->tool_tips = NULL;

	if (tool_tips)
	{

		length = strlen (tool_tips);
	
		area->tool_tips = (char *) safe_malloc ((sizeof (char) * length) + 1);
	
		strcpy (area->tool_tips, tool_tips);
	}
			
	parent = get_ui_object_parent (obj);

	if (parent)
	{

		set_ui_object_redraw (parent, TRUE);

		while ((parent) && (get_ui_object_clear (parent)))
		{

			parent = get_ui_object_parent (parent);

			if (parent)
			{

				set_ui_object_redraw (parent, TRUE);
			}
		}
	}
	else
	{

		set_ui_object_redraw (obj, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char *get_area_ui_object_tool_tips (ui_object *obj)
{
	
	area_ui_object
		*area;

	area = (area_ui_object *) obj->data;

	return (area->tool_tips);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_area_ui_object_text_functions (ui_object_types type)
{

	fn_set_ui_object_text [type] 				= set_area_ui_object_text;

	fn_get_ui_object_text [type] 				= get_area_ui_object_text;

	fn_set_ui_object_add_text [type] 		= set_area_ui_object_add_text;

	fn_set_ui_object_text_justify [type] 	= set_area_ui_object_text_justify;

	fn_get_ui_object_text_justify [type] 	= get_area_ui_object_text_justify;

	fn_set_ui_object_font_type [type] 		= set_area_ui_object_font_type;

	fn_get_ui_object_font_type [type] 		= get_area_ui_object_font_type;

	fn_set_ui_object_font_colour [type] 	= set_area_ui_object_font_colour;
	fn_set_ui_object_font_colour_end [type] 	= set_area_ui_object_font_colour_end;
	fn_set_ui_object_font_colour_start [type] 	= set_area_ui_object_font_colour_start;

	fn_get_ui_object_font_colour [type] 	= get_area_ui_object_font_colour;
	fn_get_ui_object_font_colour_end [type] 	= get_area_ui_object_font_colour_end;
	fn_get_ui_object_font_colour_start [type] 	= get_area_ui_object_font_colour_start;

	fn_set_ui_object_highlighted_font_type [type] 	= set_area_ui_object_highlighted_font_type;

	fn_get_ui_object_highlighted_font_type [type] 	= get_area_ui_object_highlighted_font_type;

	fn_set_ui_object_highlighted_font_colour [type] 	= set_area_ui_object_highlighted_font_colour;
	fn_set_ui_object_highlighted_font_colour_end [type] 	= set_area_ui_object_highlighted_font_colour_end;
	fn_set_ui_object_highlighted_font_colour_start [type] 	= set_area_ui_object_highlighted_font_colour_start;

	fn_get_ui_object_highlighted_font_colour[type] 	= get_area_ui_object_highlighted_font_colour;
	fn_get_ui_object_highlighted_font_colour_end [type] 	= get_area_ui_object_highlighted_font_colour_end;
	fn_get_ui_object_highlighted_font_colour_start [type] 	= get_area_ui_object_highlighted_font_colour_start;

	fn_set_ui_object_selected_font_type [type] 	= set_area_ui_object_selected_font_type;

	fn_get_ui_object_selected_font_type [type] 	= get_area_ui_object_selected_font_type;

	fn_set_ui_object_selected_font_colour [type] 	= set_area_ui_object_selected_font_colour;
	fn_set_ui_object_selected_font_colour_end [type] 	= set_area_ui_object_selected_font_colour_end;
	fn_set_ui_object_selected_font_colour_start [type] 	= set_area_ui_object_selected_font_colour_start;

	fn_get_ui_object_selected_font_colour [type] 	= get_area_ui_object_selected_font_colour;
	fn_get_ui_object_selected_font_colour_end [type] 	= get_area_ui_object_selected_font_colour_end;
	fn_get_ui_object_selected_font_colour_start [type] 	= get_area_ui_object_selected_font_colour_start;

	fn_set_ui_object_tool_tips [type] 				= set_area_ui_object_tool_tips;

	fn_get_ui_object_tool_tips [type] 				= get_area_ui_object_tool_tips;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
