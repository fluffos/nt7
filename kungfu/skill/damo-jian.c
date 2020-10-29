// damo-jian.c 达摩剑

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
int is_pbsk() { return 1; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N使一式"MAG"「万事随缘往」"NOR"，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
        "lvl" : 0,
        "skill_name" : "万事随缘往"
]),
([        "action":"$N错步上前，使出"HIC"「来去若梦行」"NOR"，剑意若有若无，$w淡淡地向$n的$l挥去",
        "lvl" : 10,
        "skill_name" : "来去若梦行"
]),
([        "action":"$N一式"YEL"「浮世沧桑远」"NOR"，纵身飘开数尺，运发剑气，手中$w遥摇指向$n的$l",
        "lvl" : 20,
        "skill_name" : "浮世沧桑远"
]),
([        "action":"$N纵身轻轻跃起，一式"BLU"「轮回法舟轻」"NOR"，剑光如轮疾转，霍霍斩向$n的$l",
        "lvl" : 30,
        "skill_name" : "轮回法舟轻"
]),
([        "action":"$N手中$w中宫直进，一式"HIW"「水月通禅寂」"NOR"，无声无息地对准$n的$l刺出一剑",
        "lvl" : 40,
        "skill_name" : "水月通禅寂"
]),
([        "action":"$N手中$w斜指苍天，剑芒吞吐，一式"HIM"「鱼龙听梵音」"NOR"，对准$n的$l斜斜击出",
        "lvl" : 50,
        "skill_name" : "鱼龙听梵音"
]),
([        "action":"$N左指凌空虚点，右手$w逼出丈许雪亮剑芒，一式"GRN "「千里一苇去」"NOR"刺向$n的$l",
        "lvl" : 60,
        "skill_name" : "千里一苇去"
]),
([        "action":"$N合掌跌坐，一式"HIG"「禅心顿自明」"NOR"，$w自怀中跃出，如疾电般射向$n的胸口",
        "lvl" : 70,
        "skill_name" : "禅心顿自明"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("damo-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的达摩剑法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力不够练达摩剑。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练达摩剑。\n");

        me->receive_damage("qi", 62);
        addn("neili", -69, me);
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
        int d_e1 = -30;
        int d_e2 = -50;
        int p_e1 = -20;
        int p_e2 = -40;
        int f_e1 = 200;
        int f_e2 = 350;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);
        int j, wt;
        object target;
        string *msg;

        wt=query_temp("sl_weituo", me);
        target = me->select_opponent();
        weapon=query_temp("weapon", me);

        msg = ({
                HIR"\n$N剑招越攻越急，出剑突快，顷刻之间，$n" +HIR"上全是进手招数。\n"NOR,
                HIY"\n$N身随剑转，回剑横掠，一剑跟著一剑，绵绵不尽，剑招连环进击，紧密无比。\n"NOR,
                HIC"\n原本达摩剑走的均是刚猛路子，此刻却带了三分灵动之气，剑势更加厉害！\n"NOR,
                HIW"\n这时$N心剑合一，势成自然，将「韦陀伏魔剑」发挥到了淋漓尽致。\n"NOR,
        });

        if( wt>1 && wt<6 && !query_temp("weituo_attack", me)){

                message_combatd( msg[wt-2] , me, weapon);
                set_temp("weituo_attack", 1, me);
                for( j=0; j < wt-1; j++ )
                {
                        if (! me->is_fighting(target)) break;
                        addn("neili", -50, me);
                        COMBAT_D->do_attack(me, target, weapon);
                }
                delete_temp("weituo_attack", me);
                addn_temp("sl_weituo", 1, me);

        }
        lvl = (int) me->query_skill("damo-jian", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割伤" : "刺伤",
        ]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon;
        int i;

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "damo-jian"
        ||  me->query_skill_mapped("parry") != "damo-jian"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return 0;

        if( query_temp("damo-jian/lian", me) ||
            random(2) == 0 ||
            me->is_busy())
                return 0;

        message_combatd(HIY "\n$N" HIY "身随剑转，回剑横掠，一剑跟著一剑，绵绵不尽，"
                        "剑招连环进击，紧密无比。\n" NOR,
                        me, victim);

        addn("neili", -270, me);

        set_temp("damo-jian/lian", 1, me);

        for (i = 0; i < 3; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2) == 1)
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 3);
        }
        delete_temp("damo-jian/lian", me);

}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point() { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"damo-jian/" + action;
}

int help(object me)
{
        write(HIC"\n达摩剑："NOR"\n");
        write(@HELP

    达摩剑为少林七十二绝技之一。

        学习要求：
                混元一气功20级
                内力100
HELP
        );
        return 1;
}
