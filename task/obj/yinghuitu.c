#include <ansi.h>
inherit TASK; 
void create()
{
    set_name(HIR"淫秽图"NOR, ({ "yinhui tu", "tu" }) ); 
    set_weight(1);
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "张"); 
            set("material", "paper"); 
              set("long", "一张画满美女裸体的图。\n"); 
       }
       set("owner", "血刀老祖"); 
       setup(); 
}
