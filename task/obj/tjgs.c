#include <ansi.h>  
inherit TASK;
void create()
{
    set_name(RED"通缉告示"NOR, ({ "tongji gaoshi", "gaoshi"}) );  
    set_weight(10);  
    if( clonep() )  
            destruct(this_object());  
    else { 
            set("unit", "张");
            set("material", "paper");  
            set("long", "一张通缉告示。\n"); 
       }
       set("owner", "衙役");  
       setup();  
}
