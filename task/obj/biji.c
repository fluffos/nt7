#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( WHT "散文笔记" NOR, ({ "biji" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "一本散文笔记，你随手翻看，只觉得词藻华丽，令人仿佛身临其境。\n"); 
        } 
        set("owner", "朱熹"); 
        setup(); 
} 
