#include <ansi.h> 
inherit TASK; 
void create()  
{
    set_name(MAG"武林绝学"NOR, ({ "wulin juexue" }) );  
    set_weight(10);  
        set_weight(10);  
         if( clonep() )  
                 destruct(this_object());  
   else {  
             set("unit", "本");  
             set("material", "book");
             set("long", "一本武林绝学。\n");  
      } 
      set("owner", "北丑");  
      setup(); 
}
