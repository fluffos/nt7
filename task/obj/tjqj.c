#include <ansi.h>  
inherit TASK;  
void create()  
{
    set_name(HIW"太极拳经"NOR, ({ "tjqj" }) );  
    set_weight(1); 
    if( clonep() )
            destruct(this_object());  
    else {  
            set("unit", "本"); 
            set("material", "book");  
            set("long", "张三丰自创武功太极拳的心法。\n");  
      } 
      set("owner", "张三丰");  
        setup();  
}
