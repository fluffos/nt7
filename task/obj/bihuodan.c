#include <ansi.h>  
inherit TASK; 
void create()  
{
   set_name(HIR"碧火弹" NOR, ({ "bihuo dan" }) );  
   set_weight(10); 
   if( clonep() ) 
           destruct(this_object());  
   else { 
        set("unit", "颗");  
        set("material", "stone");
        set("long", "看起这么阴险的东西，肯定是星宿摘星子的碧火弹了。。。\n");  
         }
         set("owner", "摘星子");  
         setup();
}
