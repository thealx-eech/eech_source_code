class LwsExport
{

 private:

struct sub_object_key
{
 unsigned short int sub_object_index;
 unsigned char number_of_keyframes, number_of_object_dissolve_keyframes;
 unsigned char default_visibility:1, collision_contribution:1;
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
 struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *object_dissolve_keyframes;
 float object_dissolve, relative_heading_minimum, relative_heading_maximum, relative_pitch_minimum, relative_pitch_maximum, relative_roll_minimum, relative_roll_maximum;
};

struct sub_object_lod
{
 unsigned short int index;
 unsigned char sub_object_approximation_in_level, sub_object_approximation_out_level;
};

struct sub_object
{
 static const int max_lods = 16;
 static const int max_sub_objects = 100;

 sub_object_key key;
 int number_of_lods;
 sub_object_lod lods[max_lods + 1];
 int number_of_sub_objects;
 sub_object* sub_objects[max_sub_objects];

 sub_object(void) : number_of_lods(0), number_of_sub_objects(0) {}
 ~sub_object(void) { for (int i = 0; i < number_of_sub_objects; i++) delete sub_objects[i]; }
};


int sub_object_suits(sub_object* subo, struct OBJECT_3D_DATABASE_ENTRY* sub, int sub_object_index)
{
 if (sub->sub_object_approximation_out_level < sub->sub_object_approximation_in_level)
  error("Error in aproximation levels");

#define CH_EQ(x) if (sub->x != subo->key.x) return 0;

 for (int i = 0; i < subo->number_of_lods; i++)
  if (sub->sub_object_approximation_out_level >= subo->lods[i].sub_object_approximation_in_level &&
      sub->sub_object_approximation_in_level <= subo->lods[i].sub_object_approximation_out_level &&
      sub->index != subo->lods[i].index)
   return 0;

 if (sub_object_index != subo->key.sub_object_index)
  return 0;
 CH_EQ(number_of_keyframes)
 CH_EQ(number_of_object_dissolve_keyframes)
 CH_EQ(default_visibility)
 CH_EQ(collision_contribution)
 CH_EQ(object_dissolve)
 CH_EQ(relative_heading_minimum)
 CH_EQ(relative_heading_maximum)
 CH_EQ(relative_pitch_minimum)
 CH_EQ(relative_pitch_maximum)
 CH_EQ(relative_roll_minimum)
 CH_EQ(relative_roll_maximum)

 for (int i = 0; i < sub->number_of_keyframes; i++)
  {
   CH_EQ(keyframes[i].index)
   CH_EQ(keyframes[i].linear)
   CH_EQ(keyframes[i].x)
   CH_EQ(keyframes[i].y)
   CH_EQ(keyframes[i].z)
   CH_EQ(keyframes[i].heading)
   CH_EQ(keyframes[i].pitch)
   CH_EQ(keyframes[i].roll)
   CH_EQ(keyframes[i].scale_x)
   CH_EQ(keyframes[i].scale_y)
   CH_EQ(keyframes[i].scale_z)
   CH_EQ(keyframes[i].tension)
   CH_EQ(keyframes[i].continuity)
   CH_EQ(keyframes[i].bias)
  }

 for (int i = 0; i < sub->number_of_object_dissolve_keyframes; i++)
  {
   CH_EQ(object_dissolve_keyframes[i].index)
   CH_EQ(object_dissolve_keyframes[i].linear)
   CH_EQ(object_dissolve_keyframes[i].value)
   CH_EQ(object_dissolve_keyframes[i].tension)
   CH_EQ(object_dissolve_keyframes[i].continuity)
   CH_EQ(object_dissolve_keyframes[i].bias)
  }

 return 1;

#undef CH_EQ
}

const OBJECT_3D_SCENE_DATABASE_ENTRY* G_scene;

void sub_object_add(sub_object* subo, int number_of_sub_objects, struct OBJECT_3D_DATABASE_ENTRY* sub)
{
 for (int i = 0; i < number_of_sub_objects; i++)
  {
   int sub_object_index = 0;
   for (int j = 0; j < G_scene->number_of_sub_object_table_entries && !sub_object_index; j++)
   {
    struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY* t = &G_scene->sub_object_indices_table[j];
    for (int k = 0; k < t->number_of_sub_objects; k++)
     if (t->sub_objects[k] == &sub[i])
      {
       sub_object_index = t->sub_object_index;
       break;
      }
   }

   sub_object* added = NULL;
   for (int j = 0; j < subo->number_of_sub_objects; j++)
    if (sub_object_suits(subo->sub_objects[j], &sub[i], sub_object_index))
     {
      added = subo->sub_objects[j];
      break;
     }
   if (!added)
   {
    if (subo->number_of_sub_objects >= sub_object::max_sub_objects)
     error("Too many subobjects");
    added = subo->sub_objects[subo->number_of_sub_objects++] = new sub_object;

#define AS(x) added->key.x = sub[i].x;

    added->key.sub_object_index = sub_object_index;
    AS(number_of_keyframes)
    AS(number_of_object_dissolve_keyframes)
    AS(default_visibility)
    AS(collision_contribution)
    AS(keyframes)
    AS(object_dissolve_keyframes)
    AS(object_dissolve)
    AS(relative_heading_minimum)
    AS(relative_heading_maximum)
    AS(relative_pitch_minimum)
    AS(relative_pitch_maximum)
    AS(relative_roll_minimum)
    AS(relative_roll_maximum)

#undef AS
   }

   if (added->number_of_lods >= sub_object::max_lods)
    error("Too many lods");

#define AS(x) added->lods[added->number_of_lods].x = sub[i].x;

   AS(index)
   AS(sub_object_approximation_in_level)
   AS(sub_object_approximation_out_level)

#undef AS

   added->number_of_lods++;

   sub_object_add(added, sub[i].number_of_sub_objects, sub[i].sub_objects);
  }
}

int current;
void ExportObject(FILE* fp, int index, int sub_object_index)
{
 current++;
 if (index)
  if (sub_object_index)
   fprintf(fp, "LoadObject %04X_%s.LWO\n", index, names.SubObjects[sub_object_index]);
  else
   fprintf(fp, "LoadObject %04X.LWO\n", index);
 else
  {
   if (sub_object_index)
    fprintf(fp, "AddNullObject NullObject (%s)\n", names.SubObjects[sub_object_index]);
   else
    fprintf(fp, "AddNullObject NullObject\n");
  }
}
void ExportKeyFrames(FILE* fp, const char* type, int number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes)
{
 fprintf(fp, "Show%s 7 3\n%sMotion (unnamed)\n9\n", type, type);
 fprintf(fp, "%i\n", number_of_keyframes);
 for (int i = 0; i < number_of_keyframes; i++)
  {
   struct OBJECT_3D_SUB_OBJECT_KEYFRAME* f = &keyframes[i];
   fprintf(fp, "%f %f %f %f %f %f %f %f %f\n%i %i %f %f %f\n",
           f->x, f->y, f->z, deg(f->heading), deg(f->pitch), deg(f->roll),
           f->scale_x, f->scale_y, f->scale_z, f->index, f->linear,
           f->tension, f->continuity, f->bias);
  }
 fprintf(fp, "EndBehavior 2\n");
}

void ExportLimits(FILE* fp, const char* l, double min, double max)
{
 if (fabs(min) > 1E-2 || fabs(max) > 1E-2)
  fprintf(fp, "%sLimits %f %f\n", l, deg(min), deg(max));
}

int target_sub_object_index[OBJECT_3D_SUB_OBJECT_LAST];

void sub_object_export(FILE* fp, sub_object* subo, int parent)
{
 fprintf(fp, "\n");

 if (subo->key.sub_object_index)
  {
   for (int i = 0; i < subo->number_of_lods; i++)
    {
     int index = subo->lods[i].index;
     if (objs[index].surfaces)
      {
       bool found = false;
       for (unsigned j = 0; j < !object_sub_object[index]; j++)
        if (object_sub_object[index][j] == subo->key.sub_object_index)
         {
          found = true;
          break;
         }
       if (found)
        break;

       char filename[1024];
       LWO_File lwofile;
       sprintf(filename, "_OBJECTS/%04X_%s.LWO", index, names.SubObjects[subo->key.sub_object_index]);
       ExportLWO(eet, filename, objs[index]);
       object_sub_object[index].Append(subo->key.sub_object_index);
      }
    }
  }

 for (int i = 0; i < subo->number_of_lods - 1; i++)
  {
   int k = i;
   for (int j = i + 1; j < subo->number_of_lods; j++)
    if (subo->lods[j].sub_object_approximation_in_level < subo->lods[k].sub_object_approximation_in_level)
     k = j;
   if (k != i)
    {
     sub_object_lod lod = subo->lods[i];
     subo->lods[i] = subo->lods[k];
     subo->lods[k] = lod;
    }
  }

 //FIXME
 for (int i = 0; i < subo->number_of_lods; i++)
  if (subo->lods[i].sub_object_approximation_in_level > G_scene->number_of_approximations + 1)
   subo->lods[i].sub_object_approximation_in_level = G_scene->number_of_approximations + 1;

 {
  int i = 1;
  for (int j = 1; j < subo->number_of_lods; j++)
   {
    if (subo->lods[j].index == subo->lods[i - 1].index &&
        subo->lods[j].sub_object_approximation_in_level <= subo->lods[i - 1].sub_object_approximation_out_level)
     {
      if (subo->lods[j].sub_object_approximation_out_level > subo->lods[i - 1].sub_object_approximation_out_level)
       subo->lods[i - 1].sub_object_approximation_out_level = subo->lods[j].sub_object_approximation_out_level;
     }
    else
     {
      if (i != j)
       subo->lods[i] = subo->lods[j];
      i++;
     }
   }
  subo->number_of_lods = i;
 }

 while (subo->number_of_lods > 1 && subo->lods[subo->number_of_lods - 1].index == 0)
  subo->number_of_lods--;
  //if (subo->lods[subo->number_of_lods - 1].sub_object_approximation_in_level > G_scene->number_of_approximations + 1)
  // error("Too great lod distance");

 if (subo->lods[subo->number_of_lods - 1].index && subo->lods[subo->number_of_lods - 1].sub_object_approximation_out_level < G_scene->number_of_approximations + 1)
  {
   subo->lods[subo->number_of_lods].index = 0;
   subo->lods[subo->number_of_lods].sub_object_approximation_in_level = subo->lods[subo->number_of_lods - 1].sub_object_approximation_out_level + 1;
   subo->lods[subo->number_of_lods].sub_object_approximation_out_level = G_scene->number_of_approximations + 1;
   subo->number_of_lods++;
  }


 int i = 0;
 if (subo->lods[0].sub_object_approximation_in_level == 1)
  {
   ExportObject(fp, subo->lods[0].index, subo->key.sub_object_index);
   i = 1;
  }
 else
  ExportObject(fp, 0, subo->key.sub_object_index);

 if (subo->key.sub_object_index)
  {
   bool found = false;
   for (int i = 0; i < G_scene->number_of_cameras; i++)
    {
     struct OBJECT_3D_SCENE_CAMERA_INFO* s = &G_scene->cameras[i];
     if (s->camera_name_index < 0 || (unsigned)s->camera_name_index >= !names.Cameras || s->camera_index >= scenes.total_number_of_cameras)
      error("Invalid camera index\n");
     struct OBJECT_3D_SCENE_CAMERA* c = &scenes.objects_3d_camera_database[s->camera_index];
     if (c->target_sub_object_id == subo->key.sub_object_index)
      {
       found = true;
       break;
      }
   }
   if (found)
    {
     if (!target_sub_object_index[subo->key.sub_object_index])
      target_sub_object_index[subo->key.sub_object_index] = current;
    }
  }

 if (subo->number_of_lods > 1)
  {
   fprintf(fp, "Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n1\n");
   fprintf(fp, "%i\n", subo->number_of_lods - i);

   for (; i < subo->number_of_lods; i++)
    {
     fprintf(fp, "%f\n", G_scene->approximations[subo->lods[i].sub_object_approximation_in_level - 2].distance);
     if (subo->lods[i].index)
      fprintf(fp, "\"%04X.LWO\"\n", subo->lods[i].index);
     else
      fprintf(fp, "NullObject\n");
    }

   fprintf(fp, "EndPlugin\n");
  }

 ExportKeyFrames(fp, "Object", subo->key.number_of_keyframes, subo->key.keyframes);
 fprintf(fp, "ParentObject %i\n", parent);
 ExportLimits(fp, "H", subo->key.relative_heading_minimum, subo->key.relative_heading_maximum);
 ExportLimits(fp, "P", subo->key.relative_pitch_minimum, subo->key.relative_pitch_maximum);
 ExportLimits(fp, "B", subo->key.relative_roll_minimum, subo->key.relative_roll_maximum);

 sub_objects_export(fp, subo, current);
}

void sub_objects_export(FILE* fp, sub_object* subo, int parent)
{
  for (int i = 0; i < subo->number_of_sub_objects; i++)
   sub_object_export(fp, subo->sub_objects[i], parent);
}

void ExportScene(FILE* fp, const OBJECT_3D_SCENE_DATABASE_ENTRY* scene)
{
 current = 0;
 fprintf(fp, "LWSC\n1\n\nFirstFrame 1\nLastFrame 600\nFramesPerSecond 30\n\n"); //FIXME

 ExportObject(fp, scene->index, 0);
 ExportKeyFrames(fp, "Object", scene->number_of_keyframes, scene->keyframes);
 if (scene->number_of_approximations)
  {
   struct OBJECT_3D_APPROXIMATION_INFO* last = &scene->approximations[scene->number_of_approximations - 1];
   while (last > scene->approximations && last->object_number == last[-1].object_number)
    last--;
   if (last->object_number != scene->index)
    {
     last++;
     fprintf(fp, "Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n1\n");
     fprintf(fp, "%i\n", last - scene->approximations);
     for (OBJECT_3D_APPROXIMATION_INFO* ap = scene->approximations; ap < last; ap++)
      {
       fprintf(fp, "%f\n", ap->distance);
       if (ap->object_number)
        fprintf(fp, "\"%04X.LWO\"\n", ap->object_number);
       else
        fprintf(fp, "NullObject\n");
      }
     fprintf(fp, "EndPlugin\n");
    }
  }
 /*if (scene->object_dissolve > 1E-2)
  fprintf(fp, "ObjDissolve %f\n", scene->object_dissolve);*/

 memset(target_sub_object_index, 0, sizeof(target_sub_object_index));
 {
  G_scene = scene;
  sub_object sub;
  sub_object_add(&sub, scene->number_of_sub_objects, scene->sub_objects);
  sub_objects_export(fp, &sub, current);
  G_scene = NULL;
 }

 fprintf(fp, "\nAmbientColor 255 255 255\nAmbIntensity 0.500000\n\n");
 for (int i = 0; i < scene->number_of_sprite_lights; i++)
  {
   struct OBJECT_3D_SPRITE_LIGHT* s = &scene->sprite_lights[i];
   fprintf(fp, "AddLight\nShowLight 0 7\nLightMotion (unnamed)\n9\n1\n");
   fprintf(fp, "%f %f %f 0 0 0 %f %f %f\n0 0 0 0 0\n", s->position.x, s->position.y, s->position.z, s->scale.x, s->scale.y, s->scale.z);
   fprintf(fp, "EndBehavior 1\nLightColor %i %i %i\nLgtIntensity 1\nLightType 1\n\n", s->colour.r, s->colour.g, s->colour.b);
  }

 for (int i = 0; i < scene->number_of_cameras; i++)
  {
   struct OBJECT_3D_SCENE_CAMERA_INFO* s = &scene->cameras[i];
   if (s->camera_name_index < 0 || (unsigned)s->camera_name_index >= !names.Cameras || s->camera_index >= scenes.total_number_of_cameras)
    error("Invalid camera index\n");
   struct OBJECT_3D_SCENE_CAMERA* c = &scenes.objects_3d_camera_database[s->camera_index];
   fprintf(fp, "\nAddCamera\nCameraName %s\n", names.Cameras[s->camera_name_index]);
   ExportKeyFrames(fp, "Camera", c->number_of_keyframes, c->keyframes);
   int locked = (c->heading_locked ? 8 : 0) | (c->pitch_locked ? 16 : 0) | (c->roll_locked ? 32 : 0);
   if (locked)
    fprintf(fp, "LockedChannels %i\n", locked);
   fprintf(fp, "ParentObject 1\n");
   if (c->target_sub_object_id)
    {
     int object = target_sub_object_index[c->target_sub_object_id];
     if (object)
      fprintf(fp, "TargetObject %i\n", object);
    }
  }
}


 EET& eet;
 const AllNames& names;
 const Objects& objs;
 const Scenes& scenes;
 typedef Array<int> ObjectSubobject;
 ObjectSubobject* object_sub_object;

 public:

 LwsExport(EET& eet, const AllNames& names, const Objects& objects, const Scenes& scenes)
  : eet(eet), names(names), objs(objects), scenes(scenes)
 {
  object_sub_object = new ObjectSubobject[objs.GetNumberOfObjects()];
 }

 ~LwsExport(void)
 {
  delete [] object_sub_object;
 }

 void ExportScene(const char* filename, const OBJECT_3D_SCENE_DATABASE_ENTRY& scene)
 {
  printf("Exporting scene '%s'\n", filename);
  FILE* fp = safe_fopen(filename, "w");
  ExportScene(fp, &scene);
  fclose(fp);
 }
};