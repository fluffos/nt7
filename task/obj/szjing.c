#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIY"三字经"NOR, ({ "san zi jing" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "cloth");
            set("long", "一本字迹不清的经文\n");
          } 
    set("owner", "朱丹臣");
        setup();
}      
