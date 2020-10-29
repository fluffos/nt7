#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(MAG"道德经"NOR, ({ "daode jing" }) ); 
    set_weight(10); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本道德经书。\n"); 
        }
    set("owner", "谷虚道长"); 
    setup(); 
}
