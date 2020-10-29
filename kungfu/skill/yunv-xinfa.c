// yunv-xinfa.c 玉女心法
// Last Modified by Lonely on Mar. 10 2000

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yunv-xinfa", 1);
        return lvl * lvl * 15 * 12 / 100 / 200;
}

int valid_force(string force)
{
        // return (force == "minggu-xinfa");
        return 1;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if( (!me->query_family() ||
            me->query_family() != "古墓派") && !query("yuanshen", me) )
                return notify_fail("你不是古墓派中人，无法修习！\n");

        if( query("gender", me) == "无性" )
                return notify_fail("你无根无性，阴阳难调，不能修习玉女心法。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的基本内功火候还不够，不能修习玉女心法。\n");

        if ((int)me->query_int() < 42)
                return notify_fail("你的后天悟性不足，无法领悟玉女心法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不足，难以领会玉女心法。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("玉女心法只能用学(learn)来增加熟练度。\n");
}
mixed hit_ob(object me, object victim)
{
        int lvl;
        int damage_bonus;
        string wn;
        object weapon;

        lvl = me->query_skill("yunv-xinfa", 1);

        if (lvl < 150
             || query("neili", me)<300
             || !objectp(weapon=query_temp("weapon", me) )
            || random(me->query_skill("force") / 6) < victim->query_con()
            || random(3) > 1
             || !query("can_learn/yunv-xinfa/wall", me) )
                return 0;

        wn = weapon->name();

        if( query("skill_type", weapon) == "sword"
              && me->query_skill_mapped("sword") == "yunv-jian") 
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 5 + random(lvl / 5);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "手中" + wn + HIW "忽的一振，将玉"
                       "女心经功力运于剑端，漫出无边寒意。\n" NOR;
        } else
        if( query("skill_type", weapon) == "whip"
            && me->query_skill_mapped("whip") == "yinsuo-jinling")
        {
                addn("neili", -50, me);
                damage_bonus = lvl / 4 + random(lvl / 4);

                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus * 2 / 3, me);

                return HIW "$N" HIW "一声娇喝，将玉女心法功力运至" + wn +
                       HIW "之上，姿势妙曼，令人肃然起敬。\n" NOR;
        }
}
int difficult_level()
{
             return 10;
}

string exert_function_file(string func)
{
        return __DIR__"yunv-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n玉女心法："NOR"\n");
        write(@HELP

    古墓内功讲究一个“静”字，唯有平心静气、摆脱世俗之扰才
能修习上乘武功。玉女心经修炼难度很大，学习者要不急不躁，循
序渐进方有成功之望。可以寻觅本门秘籍《玉女心经》上下册研读。

        学习要求：
                基本内功10级
                不能做太监
HELP
        );
        return 1;
}
