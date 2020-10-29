#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIG "剑灵之魂" NOR, ({ "jianling zhihun2", "zhihun2" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIG "这是一件由蓝蝶仙子幻化而成并附身在爱人身上的宝衣，淡淡的蓝色光芒中隐现一只蝴蝶。\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/parry", 300);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【剑灵套装】部件之一（剑灵之怒、剑灵之痕、剑灵之力、剑灵之魂）。\n"
                                    "                  关于剑灵套装的传说参见 help boss\n"
                                    "                  有效招架提高300级。\n");
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