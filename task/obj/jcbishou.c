#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( HIB "家传匕首" NOR, ({ "bishou" }) ); 
        set_weight(20); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "这是一把短小锋利的匕首，匕首柄上刻着一个”康“字，令人难以捉摸。\n"); 
        } 
        set("owner", "杨过"); 
        setup(); 
} 
