#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIC "青天甲" NOR, ({ "qingtian jia" }) );
        set_weight(1000);
                set("long", HIW "这是一张普普通通的护甲，护甲周围散发出淡淡的雾气将其周身笼罩"
                        "什么也看不清。\n" HIC
                    HIC "有效招架修正：+ 100        有效轻功修正：+ 100\n" NOR
                    HIC "抗毒效果修正：+ 30%        防御效果等级：  300\n" NOR
                    HIC "抗毒回避修正：+ 30%\n" NOR);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 300);
                        set("armor_prop/dodge", 100);
                                set("armor_prop/parry", 100);
                        set("armor_prop/reduce_poison", 30);
                                set("armor_prop/avoid_poison", 30);
                }
                set("material", "tian jing");
                set("wear_msg", HIC "青天甲破空而响，阵阵雾气随之而出，却早已与$N" HIC "合而为一。[2;37;0m\n" NOR);
                set("remove_msg", HIC "$N" HIC "仰天长啸，青天甲叮呤做响，刹那间周围雾气渐散，但青天甲早已"
                                                        "消失于天际。\n" NOR);

        setup();
}

int query_autoload()
{
        return 1;
}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "轻轻一叹，身上" HIC "青天甲" HIR "叮呤"
                                            "做响，$N" HIR "只觉心头一阵凄苦。这一招居然打不下去。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "只见$n" HIM "身上" HIC "青天甲" HIM "一颤，有"
                                            "若龙吟。" HIM "$N" HIM "你只感头晕目眩，居然一招打在空处。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "一招打中$n" HIW "，顿觉毫不受力。定睛一看，原来是"
                                            "的" HIC "青天甲" HIW "幻化出来的幻象。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "身上" HIC "青天甲" HIY "一阵金光闪过，$N" HIY "这一"
                                            "招被金光牢牢挡住，伤不了$n" HIY "分毫。\n" NOR]);
                        break;
                }
                return result;
        }
}
*/