#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name(HIG "剑灵之痕" NOR, ({ "jianling zhihen2", "zhihen2" }) );
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "双");
                set("long", HIG "这是由剑灵的真气结晶而成的宝靴，看上去异常奇特。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60);
                set("armor_prop/dodge", 300);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【剑灵套装】部件之一（剑灵之怒、剑灵之痕、剑灵之力、剑灵之魂）。\n"
                                    "                  关于剑灵套装的传说参见 help boss\n"
                                    "                  有效轻功等级提高300级。\n");
                set("material", "boots");
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