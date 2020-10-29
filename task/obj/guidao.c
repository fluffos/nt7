#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIB "鬼刀" NOR, ({ "gui dao" }) ); 
        set_weight(40); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "这是一把诡异的弯刀，刀身细长，刀背宽厚，刀柄怪异。\n"); 
        } 
        set("owner", "王五"); 
        setup(); 
} 
