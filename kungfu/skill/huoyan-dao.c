// huoyan-dao.c 火焰刀

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使出一招"RED"「钻木取火」"NOR"，飞身急转，双掌向前平平拍向$n",
        "skill_name" : "钻木取火",
        "lvl" : 0
]),
([        "action" : "$N使出一招"HIR"「祝融怀焰」"NOR"，手掌如刀，斜斜劈向$n的$l",
        "skill_name" : "祝融怀焰",
        "lvl" : 10
]),
([        "action" : "$N使出一招"HIR"「风火无边」"NOR"，双掌一拍，一道内力自掌中攻向$n的$l",
        "skill_name" : "风火无边",
        "lvl" : 20
]),
([        "action" : "$N使出一招"RED"「六道轮回」"NOR"，双手合十，当头劈向$n",
        "skill_name" : "六道轮回",
        "lvl" : 30
]),
([        "action" : "$N使出一招"HIR"「双龙吐焰」"NOR"，双掌一错，两道内力交叉攻向$n的$l",
        "skill_name" : "双龙吐焰",
        "lvl" : 40
]),
([        "action" : "$N使出一招"HIB"「刀山火海」"NOR"，双掌向下斜拍，顿时万千道内力从四面八方攻向$n",
        "skill_name" : "刀山火海",
        "lvl" : 60
]),
([        "action" : "$N使出一招"RED"「白佛光度」"NOR"，左臂回收，右掌引内力直刺$n的$l",
        "skill_name" : "白佛光度",
        "lvl" : 80
]),
([        "action" : "$N使出一招"RED"「火内莲花」"NOR"，双掌微并，两臂前伸，一道内劲如排山倒海般攻向$n",
        "skill_name" : "火内莲花",
        "lvl" : 100
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }
int valid_combine(string combo)
{
        return combo == "dashou-yin" ||
               combo == "yujiamu-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练火焰刀必须空手。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅。\n");

        if (me->query_skill("strike", 1) < me->query_skill("huoyan-dao", 1))
                return notify_fail("你的基本掌法火候有限，无法领会更高深的火焰刀法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练火焰刀必须空手。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的体力不够，练不了火焰刀。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的内力不够，练不了火焰刀。\n");
        me->receive_damage("qi", 55);
        addn("neili", -35, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -55;
        int d_e2 = -35;
        int p_e1 = -15;
        int p_e2 = 15;
        int f_e1 = 310;
        int f_e2 = 460;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huoyan-dao", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : "割伤",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
void skill_improved(object me)
{
        int skill = me->query_skill("huoyan-dao", 1);
        if( skill == 200 && !query("sl_gift/huoyandao", me) )
        {
                tell_object(me, HIW"\n忽然，你感道体内内息越转越快，瞬时间功力已经上升到了一个新的境界！\n"
                                "你的内力增加了！\n你的根骨增加了！\n" NOR);
                addn("max_neili", skill+random(skill), me);
                addn("con", 1, me);
                set("sl_gift/huoyandao", 1, me);
         }
}

string perform_action_file(string action)
{
        return __DIR__"huoyan-dao/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        string msg;

        if (damage_bonus < 100) return 0;

        if (random(damage_bonus / 2) > victim->query_str()/10
         && query("neili", me)>query("neili", victim)*2/3 )
        {
                result = ([ "damage" : damage_bonus]);

                switch(random(3))
                {
                case 0:
                        msg = HIR"$n的经脉被一丝丝狂燥的火劲给侵入，全身痛苦无比！\n"NOR;
                case 1:
                        msg = HIR"只听见“碰”的一声，$n身上的火劲爆发了！\n"NOR;
                case 2:
                        msg = HIR"$n只闻到一阵阵烧焦的味道，完全不知道自己已经被烧地体无完肤了！\n"NOR;
                }
                result += ([ "msg" : msg ]);
                return result;
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("huoyan-dao", 1) < 100 ||
            !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("huoyan-dao", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage / 2 ]);
                result += ([ "msg" : HIR "$n展开火焰刀法，封住了一些$N的攻击！\n" NOR ]);
                return result;
       }
}

int help(object me)
{
        write(HIR"\n火焰刀："NOR"\n");
        write(@HELP

    火焰刀为雪山大轮寺住持鸠摩智的独门绝技。
    原为少林七十二绝技之一，后鸠摩智得慕容博相助，得窥少林
绝艺，并辅以小无相功，另创新招。

        学习要求：
                小无相功60级
                内力800
HELP
        );
        return 1;
}
