#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "帝王符图碎片-30" NOR, ({ "diwang suipian30", "diwang", "suipian" }) );
        set_weight(100);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("long", HIM "传说乃上古黄帝，炎帝及蚩尤留下的图腾碎片，外形残缺不全，似乎看不出什么特别的。\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_drop", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}