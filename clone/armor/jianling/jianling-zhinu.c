#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIG "剑灵之怒" NOR, ({ "jianling zhinu", "zhinu", }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "顶");
                set("long", HIG "这是由黑曜石和剑灵的怒气结晶而成的头箍，阵阵光芒令人生畏。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 45);
                set("armor_prop/str", 45);
                set("armor_prop/con", 45);
                set("armor_prop/damage", 4300);
                set("armor_prop/sword", 200);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【剑灵套装】部件之一（剑灵之怒、剑灵之痕、剑灵之力、剑灵之魂）。\n"
                                    "                  关于剑灵套装的传说参见 help boss\n"
                                    "                  有效剑法提高300级。\n");
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