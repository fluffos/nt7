#include <ansi.h>   
inherit TASK;  
void create()   
{ 
    set_name(HIW"太极剑经"NOR, ({ "tjjj" }) );   
    set_weight(1);  
         if( clonep() ) 
            destruct(this_object());   
    else { 
        set("unit", "本");  
        set("material", "book"); 
        set("long", "张三丰自创武功太极剑的心法。\n");   
     } 
     set("owner", "张三丰"); 
        setup();  
}
