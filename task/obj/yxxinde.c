#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( WHT "医仙心得" NOR, ({ "yixian xinde" }) ); 
        set_weight(2); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "本"); 
                set("material", "paper"); 
                set("long", "这是一本医书，其中收录了各家医术之所长，被视为医之珍宝。\n"); 
        } 
        set("owner", "胡青牛"); 
        setup(); 
} 
