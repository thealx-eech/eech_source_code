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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_instance
	*virtual_pilot_cockpit_inst3d,

	*virtual_cockpit_hud_glass_inst3d,
	*virtual_cockpit_hud_display_inst3d,
	*virtual_cockpit_main_rotor_inst3d,
	*virtual_cockpit_adi_inst3d,
	*virtual_cockpit_hsi_inst3d,
	*virtual_cockpit_ekran_display_inst3d,
	*virtual_cockpit_compass_inst3d;

static object_3d_sub_instance
	*pilot_head_object;

// crew position in first dimension, min/max limit in second
static vec3d head_limits[2][2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_sub_instance* find_sub_object(object_3d_instance* parent_object, unsigned sub_obj_id)
{
	object_3d_sub_object_index_numbers
		index;
	object_3d_sub_object_search_data
		search;

	search.search_depth = 0;
	search.search_object = parent_object;
	search.sub_object_index = sub_obj_id;

	if (find_object_3d_sub_object(&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		debug_fatal ("Failed to locate sub object: %d", sub_obj_id);

	return search.result_sub_object;
}

void initialise_hind_3d_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_pilot_cockpit_inst3d = construct_3d_object (OBJECT_3D_MI24V_PILOT_COCKPIT);

	pilot_head_pitch_datum = 0.0;

	co_pilot_head_pitch_datum = 0.0;

	virtual_cockpit_hud_glass_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_GLASS_LEVEL1);
	virtual_cockpit_hud_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_DISPLAY);
	virtual_cockpit_main_rotor_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_MAIN_ROTOR);
	virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_ADI);

	virtual_cockpit_hsi_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_LEVEL1);
	virtual_cockpit_ekran_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_DISPLAYS_EKRAN);
	virtual_cockpit_compass_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS_LEVEL1);

	//
	// wipers and rain
	//

	initialise_hind_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

	pilot_head_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_HEAD);

#ifdef DEBUG  // don't limit in debug (for all practical purposes
	// pilot limits
	head_limits[0][0].x = -10;
	head_limits[0][1].x =  10;
	head_limits[0][0].y = -10;
	head_limits[0][1].y =  10;
	head_limits[0][0].z = -10;
	head_limits[0][1].z =  10;

	// co-pilot limits
	head_limits[1][0].x = -10;
	head_limits[1][1].x =  10;
	head_limits[1][0].y = -10;
	head_limits[1][1].y =  10;
	head_limits[1][0].z = -10;
	head_limits[1][1].z =  10;
#else
	// pilot limits
	head_limits[0][0].x = -0.25;
	head_limits[0][1].x =  0.25;
	head_limits[0][0].y = -0.3;
	head_limits[0][1].y =  0.3;
	head_limits[0][0].z = -0.10;
	head_limits[0][1].z =  0.50;

	// co-pilot limits
	head_limits[1][0].x = -0.2;
	head_limits[1][1].x =  0.2;
	head_limits[1][0].y = -0.2;
	head_limits[1][1].y =  0.2;
	head_limits[1][0].z = -0.05;
	head_limits[1][1].z =  0.3;
#endif
	
//VJ 050208 cleaing up wideview
	wide_cockpit_nr = WIDEVIEW_HIND_PILOT;
//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read	
	set_global_wide_cockpit(TRUE);	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_3d_cockpit (void)
{
	//
	// 3D instances
	//

	destruct_3d_object (virtual_pilot_cockpit_inst3d);

	destruct_3d_object (virtual_cockpit_hud_glass_inst3d);
	destruct_3d_object (virtual_cockpit_hud_display_inst3d);
	destruct_3d_object (virtual_cockpit_main_rotor_inst3d);
	destruct_3d_object (virtual_cockpit_adi_inst3d);
	destruct_3d_object (virtual_cockpit_hsi_inst3d);
	destruct_3d_object (virtual_cockpit_ekran_display_inst3d);
	destruct_3d_object (virtual_cockpit_compass_inst3d);

	pilot_head_object = NULL;

	//
	// wipers and rain
	//

	deinitialise_hind_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hind_3d_cockpit (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_cockpit_white_lighting (matrix3x3 attitude)
{
	matrix3x3
		directional_light_rotation,
		result;

	vec3d
		directional_light_direction;

	light_colour
		ambient_light_colour,
		directional_light_colour;

	float
		directional_light_heading,
		directional_light_pitch,
		directional_light_roll;

	directional_light_colour.red		= 0.3;
	directional_light_colour.green	= 0.3;
	directional_light_colour.blue		= 0.3;

	directional_light_heading 			= rad (0.0);
	directional_light_pitch 			= rad (0.0);
	directional_light_roll 				= rad (0.0);

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.70;
			ambient_light_colour.green		  		= 0.70;
			ambient_light_colour.blue		  		= 0.70;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.85;
			ambient_light_colour.green		  		= 0.85;
			ambient_light_colour.blue		  		= 0.85;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-40.0);
			directional_light_roll 					= rad (0.0);

			directional_light_pitch 				= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.65;
			ambient_light_colour.green		  		= 0.50;
			ambient_light_colour.blue		  		= 0.50;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.45;
			ambient_light_colour.green		  		= 0.45;
			ambient_light_colour.blue		  		= 0.55;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);

	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
}

static void set_cockpit_lighting (matrix3x3 attitude)
{
	matrix3x3
		directional_light_rotation,
		result;

	vec3d
		directional_light_direction;

	light_colour
		ambient_light_colour,
		directional_light_colour;

	float
		directional_light_heading,
		directional_light_pitch,
		directional_light_roll;

/*
	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.574;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 1.0;
			directional_light_colour.blue			= 1.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-30.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.574;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.703;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

	#if DEMO_VERSION

	ambient_light_colour.red		 		= 0.0;
	ambient_light_colour.green		  		= 0.0;
	ambient_light_colour.blue		  		= 0.0;

	directional_light_colour.red			= 1.0;
	directional_light_colour.green		= 1.0;
	directional_light_colour.blue			= 1.0;

	directional_light_heading 				= rad (0.0);
	directional_light_pitch 				= rad (-30.0);
	directional_light_roll 					= rad (0.0);

	#endif
*/

/*	ambient_light_colour.red = 0.6;
	ambient_light_colour.green = 0.6;
	ambient_light_colour.blue = 0.6;
*/
//	debug_log("%.2f, %.2f, %.2f", ambient_3d_light.colour.red, ambient_3d_light.colour.green, ambient_3d_light.colour.blue);

	ambient_light_colour.red = 0.35 + ambient_3d_light.colour.red;
	ambient_light_colour.green = 0.35 + ambient_3d_light.colour.green;
	ambient_light_colour.blue = 0.35 + ambient_3d_light.colour.blue;

/*
	ambient_light_colour.red = -0.4 + ambient_3d_light.colour.red;
	ambient_light_colour.green = -0.4 + ambient_3d_light.colour.green;
	ambient_light_colour.blue = -0.4 + ambient_3d_light.colour.blue;
*/
	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

/*
	directional_light_heading 				= rad (debug_var_x * 10.0);
	directional_light_pitch 				= rad (debug_var_y * 10.0);
	directional_light_roll 					= 0.0;

//	debug_log("heading %.2f, pitch %.2f", deg(directional_light_heading), deg(directional_light_pitch));

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);
	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];
/*
	directional_light_direction = current_3d_sun->light_direction;

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
*/

//	set_3d_main_light_source (main_3d_single_light_env, &current_3d_sun->colour, &directional_light_direction, FALSE);
	directional_light_colour.red = bound(current_3d_sun->colour.red * 1.2, 0.0, 1.0);
	directional_light_colour.green = bound(current_3d_sun->colour.green * 1.2, 0.0, 1.0);
	directional_light_colour.blue = bound(current_3d_sun->colour.blue * 1.2, 0.0, 1.0);

//	set_3d_main_light_source (main_3d_single_light_env, &current_3d_sun->colour, &current_3d_sun->light_direction, FALSE);
	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &current_3d_sun->light_direction, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_crew_viewpoint (viewpoint *crew_viewpoint)
{
	int is_copilot = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT;

	viewpoint
		vp;

	object_3d_sub_instance*
		head_object;
	
	ASSERT (crew_viewpoint);

	// TODO: add co-pilot
	virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;
	head_object = pilot_head_object;
	
#if 0
	switch (get_view_mode())
		{
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
			index = is_copilot
				? OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_2
				: OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_1;
			break;

		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
			index = is_copilot
				? OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_2
				: OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_1;
			break;

		default:
			index = OBJECT_3D_SUB_OBJECT_PILOT_VIEWPOINT;
			break;
		}
#endif

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	switch (get_view_mode())
	{
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		break;

	default:
		// adjust pitch according to user preferance
		if (edit_wide_cockpit)
			pilot_head_pitch = rad ( wide_cockpit_position[wide_cockpit_nr].p );

		// rotate head
		head_object->relative_heading = -pilot_head_heading;
		head_object->relative_pitch = -pilot_head_pitch;

		// adjust position according to user preferance
		head_object->relative_position.x = wide_cockpit_position[wide_cockpit_nr].x;
		head_object->relative_position.y = wide_cockpit_position[wide_cockpit_nr].y;
		head_object->relative_position.z = wide_cockpit_position[wide_cockpit_nr].z;

		// adjust for track-IR position
		if (query_TIR_active())
		{
			head_object->relative_position.x -= current_custom_cockpit_viewpoint.x;
			head_object->relative_position.y -= current_custom_cockpit_viewpoint.y;
			head_object->relative_position.z -= current_custom_cockpit_viewpoint.z;
		}

		// keep head inside reasonable limimts
		head_object->relative_position.x = bound(head_object->relative_position.x, head_limits[is_copilot][0].x, head_limits[is_copilot][1].x);
		head_object->relative_position.y = bound(head_object->relative_position.y, head_limits[is_copilot][0].y, head_limits[is_copilot][1].y);
		head_object->relative_position.z = bound(head_object->relative_position.z, head_limits[is_copilot][0].z, head_limits[is_copilot][1].z);

#if 0
		if (is_copilot)
		{
			// adjust for offset of co-pilot's cockpit compared to pilot's
			head_object->relative_position.y += -0.30;
			head_object->relative_position.z += 1.32;
		}
#endif
	}

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);
	get_3d_sub_object_world_viewpoint (head_object, &vp);
	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	*crew_viewpoint = virtual_cockpit_inst3d->vp;
}


static void get_display_viewpoint (view_modes mode, viewpoint *display_viewpoint)
{
	object_3d_sub_object_index_numbers
		index;

	object_3d_sub_object_search_data
		search;

	viewpoint
		vp;

	ASSERT (display_viewpoint);

	if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV)
	{
		index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_CRT_CAMERA;
	}
	else if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD)
	{
		index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_HUD_CAMERA;
	}
	else
	{
		debug_fatal ("Invalid view mode = %d", mode);
	}

	virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = index;

	if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
	}

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	get_3d_sub_object_world_viewpoint (search.result_sub_object, &vp);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	memcpy (display_viewpoint, &virtual_cockpit_inst3d->vp, sizeof (viewpoint));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_internal_3d_cockpit (unsigned int flags)
{
	static float debug = 0.0;
	
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*virtual_cockpit_inst3d;

//VJ wideview mod, date: 18-mar-03	
    char buffer[128];

	flags = (unsigned)-1;
	

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	get_crew_viewpoint(&vp);
	
	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_HUD_DISPLAY)
	{
		draw_hind_hud_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_EKRAN_DISPLAY)
	{
		draw_hind_ekran_display_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_CRT_DISPLAY)
	{
		draw_hind_mfd_on_texture ();
	}

	// Casm 10SEP05 Havoc Instruments - temporary used for Hind
	if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
	{
		memcpy (&havoc_lamps, &hind_lamps, sizeof (havoc_lamps));
		draw_havoc_virtual_cockpit_instruments_on_texture ();
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

//	if (flags & (VIRTUAL_COCKPIT_COCKPIT | VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES))
	{
//		set_cockpit_white_lighting (vp.attitude);
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		debug_var_y = debug != debug_var_z;
//		debug_log("z: %.1f, y: %.1f", debug_var_z, debug_var_y);
		if (debug_var_y != 0.0)
			debug = debug_var_z;

/*		set_3d_active_environment (main_3d_env);

//VJ 050108 wideview x coord used to clip apache cockpit
		set_3d_view_distances (main_3d_env, 10.0, 0.3, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();
*/
		if (begin_3d_scene ())
		{
			//
			// virtual cockpit
			//

			if (flags & VIRTUAL_COCKPIT_COCKPIT)
			{
				/*
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level3_inst3d;

						break;
					}
				}
				*/

				virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;

				memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);
			}

			//
			// instrument needles
			//
#if 0
			if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
			{
				//
				// HSI
				//

				{
					float
						direction_finder,
						flight_path,
						drift;

					get_hind_virtual_cockpit_hsi_needle_values (&direction_finder, &flight_path, &drift);

					//
					// flight path
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_flight_path_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_DOUBLE;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = flight_path;
					}

					memcpy (&virtual_cockpit_hsi_flight_path_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_flight_path_inst3d->vp.position, virtual_cockpit_hsi_flight_path_inst3d);

					//
					// direction finder
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_direction_finder_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_LONG;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = direction_finder;
					}

					memcpy (&virtual_cockpit_hsi_direction_finder_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_direction_finder_inst3d->vp.position, virtual_cockpit_hsi_direction_finder_inst3d);

					//
					// drift
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_drift_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_SHORT;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = drift;
					}

					memcpy (&virtual_cockpit_hsi_drift_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_drift_inst3d->vp.position, virtual_cockpit_hsi_drift_inst3d);

//VJ wideview mod, date: 18-mar-03	
// re-insert compass here (internal is draw after external
					if (get_global_wide_cockpit ())
					{					
					    insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
					}
				}
			}
#endif

			draw_3d_scene ();

//VJ wideview mod, date: 18-mar-03	
         if (edit_wide_cockpit)
       	{
				sprintf(buffer,"HIND wide cockpit mod edit (set freelook off):");
				ui_display_text (buffer, 10, 40);
				sprintf(buffer,"Y: num 8/2; Z: num 4/6; pitch: num 7/9; Restore: num 0; Ctrl-\\ Leave");
				ui_display_text (buffer, 10, 60);
				sprintf(buffer,"x=%.3f, y=%.3f, z=%.3f, pitch=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z, wide_cockpit_position[wide_cockpit_nr].p);
				ui_display_text (buffer, 10, 100);
         }

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

#if 0
	if (flags & (VIRTUAL_COCKPIT_HUD_GLASS | VIRTUAL_COCKPIT_HUD_DISPLAY | VIRTUAL_COCKPIT_EKRAN_DISPLAY | VIRTUAL_COCKPIT_CRT_DISPLAY))
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.3, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// HUD glass
			//

			if (flags & VIRTUAL_COCKPIT_HUD_GLASS)
			{
				if (flags & VIRTUAL_COCKPIT_LARGE_HUD)
				{
					switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
					{
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAWN:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAY:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level1_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DUSK:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_NIGHT:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level3_inst3d;

							break;
						}
					}

					#if DEMO_VERSION

					virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level1_inst3d;

					#endif

					memcpy (&virtual_cockpit_large_hud_glass_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_hud_glass_inst3d->vp.position, virtual_cockpit_large_hud_glass_inst3d);
				}
				else
				{
					switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
					{
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAWN:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAY:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level1_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DUSK:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_NIGHT:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level3_inst3d;

							break;
						}
					}

					#if DEMO_VERSION

					virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level1_inst3d;

					#endif

					memcpy (&virtual_cockpit_hud_glass_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hud_glass_inst3d->vp.position, virtual_cockpit_hud_glass_inst3d);
				}
			}

			//
			// HUD display
			//

			if (flags & VIRTUAL_COCKPIT_HUD_DISPLAY)
			{
				memcpy (&virtual_cockpit_hud_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hud_display_inst3d->vp.position, virtual_cockpit_hud_display_inst3d);
			}

			//
			// EKRAN display
			//

			if (flags & VIRTUAL_COCKPIT_EKRAN_DISPLAY)
			{
				memcpy (&virtual_cockpit_ekran_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_ekran_display_inst3d->vp.position, virtual_cockpit_ekran_display_inst3d);
			}

			//
			// CRT display
			//

			if (flags & VIRTUAL_COCKPIT_CRT_DISPLAY)
			{
				memcpy (&virtual_cockpit_crt_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_crt_display_inst3d->vp.position, virtual_cockpit_crt_display_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}
#endif
	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	//
	// draw fillet to mask EO display
	//

#if 0
	if
	(
		(d3d_can_render_to_texture) &&
		(get_hind_eo_display_visible ()) &&
		(flags & (VIRTUAL_COCKPIT_COCKPIT)) &&
		(flags & (VIRTUAL_COCKPIT_CRT_DISPLAY))
	)
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
			{
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAWN:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAY:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DUSK:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_NIGHT:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level3_inst3d;

					break;
				}
			}

			#if DEMO_VERSION

			virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

			#endif

			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}
#endif
	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
	
	debug_var_y  = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_external_3d_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic)
{
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	float
		theta;

	object_3d_instance
		*inst3d;

	
	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	get_crew_viewpoint(&vp);

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

//	if (flags & (VIRTUAL_COCKPIT_MAIN_ROTOR | VIRTUAL_COCKPIT_STOWED_WIPER | VIRTUAL_COCKPIT_MOVING_WIPER))
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// main rotor
			//

//			if (flags & VIRTUAL_COCKPIT_MAIN_ROTOR)
			{
				if (!(get_helicopter_main_rotors_blurred (get_gunship_entity ()) && (!get_global_blurred_main_rotors_visible_from_cockpit ())))
				{
					if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_MAIN_ROTOR_DAMAGED))
					{
						animate_damaged_helicopter_main_rotors (get_gunship_entity (), TRUE);
					}
					else
					{
						animate_helicopter_main_rotors (get_gunship_entity (), TRUE, FALSE);
					}

					inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

					theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

					{
						set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

						animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

						memcpy (&virtual_cockpit_main_rotor_inst3d->vp, &vp, sizeof (viewpoint));

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_main_rotor_inst3d->vp.position, virtual_cockpit_main_rotor_inst3d);
					}
				}
			}
#if 0
			//
			// wiper
			//

			if (wiper_mode == WIPER_MODE_STOWED)
			{
				if (flags & VIRTUAL_COCKPIT_STOWED_WIPER)
				{
					draw_hind_virtual_cockpit_wiper (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);
				}
			}
			else
			{
				if (flags & VIRTUAL_COCKPIT_MOVING_WIPER)
				{
					draw_hind_virtual_cockpit_wiper (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);
				}
			}
#endif
			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

#if 0
	if (flags & (VIRTUAL_COCKPIT_ADI | VIRTUAL_COCKPIT_HSI | VIRTUAL_COCKPIT_COMPASS))
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// ADI
			//

			if (flags & VIRTUAL_COCKPIT_ADI)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_adi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_ADI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						heading,
						pitch,
						roll;

					get_hind_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

//VJ wideview mod, date: 18-mar-03	
				if (get_global_wide_cockpit ())
				{
				    vp.y = wide_cockpit_position[wide_cockpit_nr].y+0.01;
				    vp.z = wide_cockpit_position[wide_cockpit_nr].z;
				}    
				
				memcpy (&virtual_cockpit_adi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_adi_inst3d->vp.position, virtual_cockpit_adi_inst3d);
			}

			//
			// HSI
			//

			if (flags & VIRTUAL_COCKPIT_HSI)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level1_inst3d;

				#endif

				search.search_depth = 0;
				search.search_object = virtual_cockpit_hsi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = current_flight_dynamics->heading.value;
				}

				memcpy (&virtual_cockpit_hsi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_inst3d->vp.position, virtual_cockpit_hsi_inst3d);
			}

			//
			// compass
			//

			if (flags & VIRTUAL_COCKPIT_COMPASS)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level1_inst3d;

				#endif

				search.search_depth = 0;
				search.search_object = virtual_cockpit_compass_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
				}

				memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	#endif

	////////////////////////////////////////
	//
	// rendered wiper
	//
	////////////////////////////////////////
#if 0
	if (flags & VIRTUAL_COCKPIT_RENDERED_WIPER)
	{
		if (wiper_mode == WIPER_MODE_STOWED)
		{
			ASSERT (wiper_rle_graphic);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (wiper_rle_graphic, ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}
		}
	}

	////////////////////////////////////////
	//
	// rain effect
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_RAIN_EFFECT)
	{
		if (rain_mode != RAIN_MODE_DRY)
		{
			set_3d_active_environment (main_3d_env);

			set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

			realise_3d_clip_extents (main_3d_env);

			recalculate_3d_environment_settings (main_3d_env);

			clear_zbuffer_screen ();

			if (begin_3d_scene ())
			{
				draw_hind_virtual_cockpit_rain_effect (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);

				draw_3d_scene ();

				end_3d_scene ();
			}
		}
	}
#endif
	//VJ wideview mod, date: 18-mar-03	
	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////
	
	if (edit_wide_cockpit)                                     
	{                                                          
		//VJ 50208 added pilot head pitch
		if (check_key(DIK_NUMPAD7))
		{
            wide_cockpit_position[wide_cockpit_nr].p += 0.5;
      }
		if (check_key(DIK_NUMPAD9))
		{
            wide_cockpit_position[wide_cockpit_nr].p -= 0.5;
      }
		if (check_key(DIK_NUMPAD6))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].z += 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD4))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].z -= 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD8))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].y += 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD2))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].y -= 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD1))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].x -= 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD3))                            
		{                                                      
            wide_cockpit_position[wide_cockpit_nr].x += 0.005; 
      }                                                      
		if (check_key(DIK_NUMPAD0))                            
		{                                       
			wide_cockpit_position[wide_cockpit_nr].x = BASE_X_HAVOC;
			wide_cockpit_position[wide_cockpit_nr].y = BASE_Y_HAVOC;
			wide_cockpit_position[wide_cockpit_nr].z = BASE_Z_HAVOC;
			wide_cockpit_position[wide_cockpit_nr].p = BASE_P_HAVOC;
      }                                                      
   }            	                                           



	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_hind_3d_cockpit_main_rotors (int seed)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	damage_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d, seed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_hind_3d_cockpit_main_rotors (void)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	restore_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////