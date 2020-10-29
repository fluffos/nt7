#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIR"浑天宝鉴"NOR, ({ "book", "book" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本写着浑天宝鉴内功的秘籍。\n"); 
         }
    set("owner", "南贤"); 
    setup();
}
