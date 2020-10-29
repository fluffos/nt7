#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( RED "赤龙令" NOR, ({ "chilong ling" }) ); 
        set_weight(50); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "把"); 
                set("material", "iron"); 
                set("long", "这就是名震江湖的赤龙令，令牌隐隐透出血红色的光芒，看上去煞是吓人。\n"); 
        } 
        set("owner", "无根道长"); 
        setup(); 
} 
