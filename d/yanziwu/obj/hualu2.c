// hualu2.c
#include <ansi.h>;
inherit ITEM;

void create()
{
        set_name(HIW"茉莉花露"NOR, ({ "hua lu" }));
        set_weight(1500);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一瓶茉莉花露，看来是花了不少心血泡制成的。\n");
                set("unit", "瓶");
                set("value", 50);
        }
}