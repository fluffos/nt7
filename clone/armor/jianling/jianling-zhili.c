#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIG "剑灵之力" NOR, ({ "jianling zhili", "zhili"}) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", HIG "这是一张淡蓝色的护符，其外形有如蝴蝶翅膀一般。\n" NOR);
                set("value", 10000000);
                set("limit", ([
                        "exp"    :   50000000,
                ]));
                set("armor_prop/int", 50);              
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);

                set("armor_prop/T_jianling", 1);
                set("special/desc", "【剑灵套装】部件之一（剑灵之怒、剑灵之痕、剑灵之力、剑灵之魂）。\n"
                                    "                  关于剑灵套装的传说参见 help boss\n");

                set("limit", ([
                         "exp" : 100000000,
                         "thborn" : 1,
                         "jianling": 1, // equip.c里限制，必须要调整成功剑灵1次后才能装备
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}