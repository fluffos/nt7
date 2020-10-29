#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "号令八方" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv;
        object *t;
        object tob;
        int attack, damage;

        joblv = me->query_joblv();

        t = me->query_team(); // 必须要组队才能施展

        if (me->query_temp("special2/haoling"))
                return notify_fail("「号令八方」的功效还未消失，无法施展。\n");

        if (me->query("yhjob/job") != "魔师")
                return notify_fail("你的职业错误，无法施展。\n");
                
        if (me->query("neili") < 1200)
                return notify_fail("你的内力不足，无法施展。\n");

        if (joblv < 30)
                return notify_fail("你的职业等级不足，无法施展。\n");                

        if (! arrayp(t))
                return notify_fail("该技能只能在组队的时候施展。\n");

        t -= ({ 0 });
        if (sizeof(t) <= 1)
                return notify_fail("该技能只能在多人组队的时候施展。\n");
                        
        if (me->is_busy())return notify_fail("等你忙完再说吧！\n");

        message_vision(HIR "$N" HIR "双目发光，振臂高呼，“魔由心生，号令八方！” ，声音激荡四周，令人生畏。\n" NOR, me);

        foreach (tob in t)
        {
                if (1)
                {                        
                        tell_object(tob, HIW + me->name() + "施展出绝招「号令八方」，提高所有队友的命中及伤害力。\n" NOR);
                        attack = 100 + me->query_joblv() * 20 + me->query("lhpoint/special/haoling") * 60;
                        damage = 100 + me->query_joblv() * 30 + me->query("lhpoint/special/haoling") * 80;

                              // 不能重复施展
                        if (! tob->query_temp("special2/haoling"))
                        {
                                tob->set_temp("special2/haoling", joblv);
                                tob->add_temp("apply/attack", attack);
                                tob->add_temp("apply/damage", damage);
                                tob->add_temp("apply/unarmed_damage", damage);
                                tob->start_call_out( (: call_other, __FILE__, "remove_effect", tob, attack, damage :), 
                                                    60 + joblv * 10);
                        }
                }
        }
 
        me->add("neili", -1200);
        me->start_busy(1);

        return 1;
}

void remove_effect(object me, int attack, int damage)
{
        if ((int)me->query_temp("special2/haoling"))
        {
                me->add_temp("apply/attack", -1 * attack);
                me->add_temp("apply/damage", -1 * damage);
                me->add_temp("apply/unarmed_damage", -1 * damage);
                me->delete_temp("special2/haoling");
                tell_object(me, "「号令八方」的功效已经消失。\n");
        }
}

