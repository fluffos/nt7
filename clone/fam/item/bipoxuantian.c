#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "碧魄玄天" NOR, ({ "bipo xuantian", "bipo", "xuantian" }));
        set_weight(20000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIG "世间极为罕见的宝石，从万年冰川中取得。\n" NOR);
                set("unit", "块");
                set("value", 300000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", HIG "碧魄玄天" NOR);
                set("can_make", "all");
                set("power_point", 150);
        }
}

int query_autoload()
{
        return 1;
}
