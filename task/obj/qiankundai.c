#include <ansi.h> 
inherit TASK; 
void create() 
{ 
        set_name( MAG "乾坤袋" NOR, ({ "qiankun dai" }) ); 
        set_weight(20); 
        if( clonep() ) 
                destruct(this_object()); 
        else { 
                set("unit", "个"); 
                set("material", "paper"); 
                set("long", "一个普普通通甚至有些破旧不堪的布袋，知道究竟有何用的人少之甚少。\n"); 
        } 
        set("owner", "说不得"); 
        setup(); 
} 
