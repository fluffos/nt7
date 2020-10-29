#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIC "膏药" NOR, ({ "gaoyao" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "张"); 
                set("material", "paper"); 
                set("long", "这是一张特制的膏药，弥漫着淡淡的草药气味。\n"); 
        } 
        set("owner", "徐天川"); 
        setup(); 
} 
