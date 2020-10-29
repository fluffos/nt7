// This program is a part of NT MudLIB
// ab_crystal.c 能力水晶

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC"强化水晶"NOR, ({ "qianghua crystal", "qianghua", "crystal" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIC "表面泛着青色光芒的强化水晶，装备在6星之前使用（不包括6星），可以100%强化成功。\n" NOR);
                set("value", 50000);
                set("unit", "块");
        }
        //set("set_data", 1);
        set("autoload", 1);
        setup();
}
