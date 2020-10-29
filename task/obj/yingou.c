#include <ansi.h> 
inherit TASK; 
void create() 
{ 
   set_name(HIW"银钩" NOR, ({ "yin gou" }) ); 
   set_weight(10); 
   if( clonep() ) 
           destruct(this_object()); 
   else { 
        set("unit", "把"); 
        set("material", "stone"); 
        set("long", "武当七侠中，张翠山的银钩。。。\n"); 
         } 
        set("owner", "张翠山"); 
        setup(); 
}
