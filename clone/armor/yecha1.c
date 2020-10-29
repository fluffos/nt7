#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIY "夜叉" NOR, ({ "yecha fu", "yecha", "fu" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", HIY "这是一张道符，上面画着一个奇特的鬼怪，名曰：夜叉。\n" NOR);
                set("value", 95000);
                set("limit", ([
                        "exp"    :   500000,
                ]));

                set("apply_prop/damage", 100);
                set("armor_prop/unarmed_damage", 100);
                set("armor_prop/int", 2);
                set("armor_prop/str", 2);
        }
        setup();
}

int query_autoload()
{
        return 1;
}