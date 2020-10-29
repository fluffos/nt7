#include <ansi.h> 
inherit TASK; 
void create()
{ 
    set_name(HIY"黄布" NOR, ({ "huangbu"}) ); 
    set_weight(1); 
    if( clonep() )
            destruct(this_object()); 
    else { 
            set("unit", "块"); 
            set("material", "paper");
            set("long", "一块黄色的布上面绣了几个黑色的字。\n打遍天下无敌手。\n"); 
         } 
    set("owner", "苗人凤"); 
    setup(); 
}
