#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIW"倚天屠龙秘籍"NOR, ({ "mi ji", "miji" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本倚天剑和屠龙刀里的秘籍。\n"); 
         }
    set("owner", "周芷若"); 
    setup();
}
