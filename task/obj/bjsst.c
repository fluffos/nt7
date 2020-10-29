#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"白金丝手套"NOR, ({ "shou tao", "shoutao" }) ); 
    set_weight(1);
    if( clonep() )
       destruct(this_object());
    else {
       set("unit", "双"); 
       set("material", "steel");
       set("long", "这是一双白金丝手套，手套乃质地轻薄柔软，以极细极韧的白金丝织成。\n"); 
    }
    set("owner", "小龙女"); 
    setup();
}
