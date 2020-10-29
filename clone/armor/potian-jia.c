#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIR "破天甲" NOR, ({ "potian jia" }) );
        set_weight(1000);
                set("long", HIW "这是一张普普通通的护甲，护甲周围散发出淡淡的雾气将其周身笼罩"
                        "什么也看不清。\n" HIC
                    HIC "有效招架修正：+ 100        有效轻功修正：+ 100\n" NOR
                    HIC "抗毒效果修正：+ 20%        防御效果等级：  300\n" NOR
                    HIC "抗毒回避修正：+ 40%\n" NOR);
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
                        set("armor_prop/reduce_poison", 20);
                                set("armor_prop/avoid_poison", 40);
                }
                set("material", "tian jing");
                set("wear_msg", HIR "破天甲破空而响，阵阵雾气随之而出，却早已与$N" HIC "合而为一。[2;37;0m\n" NOR);
                set("remove_msg", HIR "$N" HIC "仰天长啸，破天甲叮呤做响，刹那间周围雾气渐散，但破天甲早已"
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
                        result += (["msg" : HIR "$n" HIR "平静地看着$N" HIR "，$N" HIR "脑"
                                            "子一片茫然，心想：难道这小子是老千？\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$n" HIR "平静地看着$N" HIR "，$N" HIR "脑"
                                            "子一片茫然，心想：难道这小子是老千？\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "平静地看着$N" HIR "，$N" HIR "脑"
                                            "子一片茫然，心想：难道这小子是老千？\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "平静地看着$N" HIR "，$N" HIR "脑"
                                            "子一片茫然，心想：难道这小子是老千？\n" NOR]);
                        break;
                }
                return result;
        }
}
*/