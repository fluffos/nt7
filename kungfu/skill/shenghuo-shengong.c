inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenghuo-shengong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
        return (force == "shenghuo-xinfa");
}

int valid_learn(object me)
{
        if (query("int", me) < 32)
                return notify_fail("你先天悟性不够，无法领悟圣火神功。\n");

        if ((int)me->query_skill("force", 1) < 180)
                return notify_fail("你的基本内功火候还不够，还不能学习圣火神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("圣火神功只能用学(learn)的来增加熟练度。\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, i;
        int flvl, attack_time;
        object weapon;

        lvl  = me->query_skill("shenghuo-shengong", 1);
        flvl = me->query_skill("shenghuo-ling");

        if (lvl < 140
        ||  ! damage_bonus
        ||  me->query_skill_mapped("force") != "shenghuo-shengong"
        ||  me->query_skill_mapped("sword") != "shenghuo-ling"
        ||  ! objectp(weapon = query_temp("weapon", me))
        ||  (string)query("skill_type", weapon) != "sword"
        ||  flvl < 140
        ||  query_temp("shenghuo-ling/hit", me)
        ||  query("neili") < 200, me)
                return 0;

        attack_time = (int)(me->query_skill("shenghuo-ling", 1) / 40);

        if (attack_time > 8)
                attack_time = 8;


        if (lvl / 2 + random(lvl) > victim->query_skill("force", 1) &&
            ! query_temp("shenghuo-ling/max_hit", me) ) {
                 message_vision(HIR "\n刹那间$N" HIR "身法陡然加快，剑招连绵而出，招式诡异无比"
                                "，令$n" HIR "难以琢磨。\n" NOR, me, victim);


                 me->start_busy(1+ random(attack_time));
                 addn("neili", -attack_time * 20, me);
                 addn_temp("shenghuo-ling/hit", 1, me);
                 for (i = 0; i < attack_time; i++)
                 {
                        if (! me->is_fighting(victim))
                                break;

                        COMBAT_D->do_attack(me, victim, weapon, 0);
                 }
                 delete_temp("shenghuo-ling/hit", me);

                 return 1;
        }

}

string exert_function_file(string func)
{
        return __DIR__"shenghuo-shengong/" + func;
}
