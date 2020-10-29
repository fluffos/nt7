#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIY"金轮"NOR, ({ "jin lun" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "把"); 
            set("material", "stone"); 
            set("long", "金轮法王的随身兵器。\n"); 
    } 
    set("owner", "金轮法王"); 
    setup();  
}
