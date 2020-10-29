#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIG "碧水剑" NOR, ({ "bishui sword" }) ); 
        set_weight(1); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "这是一把碧水剑。\n"); 
        } 
        set("owner", "岳灵珊"); 
        setup(); 
} 
