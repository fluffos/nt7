#include <ansi.h>  
inherit TASK;  
void create()  
{
    set_name(HIG"云龙心法"NOR, ({ "ylxf" }) );  
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object());  
    else {
            set("unit", "本");  
            set("material", "paper");  
            set("long", "云龙门的内功心法。\n");  
      } 
      set("owner", "陈近南"); 
        setup();
}
