// jinkuai.c 金块

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "金锭" NOR, ({ "jin ding", "jin", "ding" }));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "一锭黄澄澄的金锭。\n");
                set("value", 800000);
                set("unit", "锭");
        }
}

int query_autoload() { return 1; }