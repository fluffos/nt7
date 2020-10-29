#include <ansi.h>
inherit ITEM;
void create()
{
        set_name("树干", ({ "shu gan", "tree", "shu", "gan" }));
        set("weight", 130000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "巨大的树干，比一个人还要粗。\n" NOR);
                set("value", 10);                
        }
        setup();
}