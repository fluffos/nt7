#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( YEL "竹棒" NOR, ({ "zhu bang" }) ); 
        set_weight(20); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "根"); 
                set("material", "bamboo"); 
                set("long", "一根看上去很不起眼的竹棒，上面痕迹斑斑，摸上去却光滑至极。\n"); 
        } 
        set("owner", "越女"); 
        setup(); 
} 
