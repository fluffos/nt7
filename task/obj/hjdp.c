#include <ansi.h>  
inherit TASK;  
void create()  
{ 
    set_name(HIW"胡家刀谱"NOR, ({ "daopu" }) );  
    set_weight(10);
       if( clonep() ) 
            destruct(this_object());  
    else { 
            set("unit", "本");
            set("material", "book");  
            set("long", "胡家刀谱丢失掉的一页。\n");
        }
       set("owner", "胡斐"); 
        setup();  
}
