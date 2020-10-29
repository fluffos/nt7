#include "herb.h" 
void create() 
  {
      set_name(NOR + HIY "七星海棠" NOR, ({ "qixing haitang", "qixing", "haitang","herb_qixing-haitang" })); 
          /*if (clonep())      
                 set_default_object(__FILE__); 
          else*/ { 
                  set("long", NOR + HIG "这株花的叶子也和寻常海棠无异，花瓣紧贴枝干而生，花枝如铁，花瓣上有七个小小的黄点。\n" NOR); 
                  set("base_unit", "株");
                  set("base_value", 5000); 
                  set("base_weight", 20);
               }
               setup();
  }