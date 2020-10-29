#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"枯草"NOR, ({"ku cao", "kucao"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "棵");
                set("long", "这是一棵枯萎的草药，已经没用了。\n");
                set("dig", 1);
                set("value", 0);
                set("weight", 100);
        }
        setup();
}