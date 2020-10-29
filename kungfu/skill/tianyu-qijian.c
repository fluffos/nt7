// tianyu-qijian.c 天羽奇剑

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N使一式"HIC"「海天一线」"NOR"，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
        "lvl" : 0,
        "skill_name" : "海天一线"
]),
([        "action":"$N错步上前，使出"HIM"「闪电惊虹」"NOR"，手中$w划出一道剑光劈向$n的$l",
        "lvl" : 9,
        "skill_name" : "闪电惊虹"
]),
([        "action":"$N手中$w一抖，一招"HIY"「日在九天」"NOR"，斜斜一剑反腕撩出，攻向$n的$l",
        "lvl" : 18,
        "skill_name" : "日在九天"
]),
([        "action":"$N手中剑锵啷啷长吟一声，一式"HIB"「咫尺天涯」"NOR"，一道剑光飞向$n的$l",
        "lvl" : 27,
        "skill_name" : "咫尺天涯"
]),
([        "action":"$N一式"HIR"「怒剑狂花」"NOR"，手中$w舞出无数剑花，使$n难断虚实，无可躲避",
        "lvl" : 36,
        "skill_name" : "怒剑狂花"
]),
([        "action":"$N手中$w斜指苍天，剑芒吞吐，一式"BLU"「九弧震日」"NOR"，对准$n的$l斜斜击出",
        "lvl" : 44,
        "skill_name" : "九弧震日"
]),
([        "action":"$N一式"HIW"「漫天风雪」"NOR"，手腕急抖，挥洒出万点金光，刺向$n的$l",
        "lvl" : 52,
        "skill_name" : "漫天风雪"
]),
([        "action":"$N一式"GRN"「天河倒泻」"NOR"，$w飞斩盘旋，如疾电般射向$n的胸口",
        "lvl" : 60,
        "skill_name" : "天河倒泻"
]),
([        "action":"$N一式"HIG"「天外飞仙」"NOR"，$w突然从天而降，一片金光围掠$n全身",
        "lvl" : 70,
        "skill_name" : "天外飞仙"
])
});
string *hit_msg = ({
        HIY"\n$N前招将落，后招已至，前后两招形如一式，此起彼伏，连绵不绝！\n"NOR,
        HIC"\n对方正惊愕间，却见$N的剑光已闪至眼前，剑光闪处寒气四射，咄咄逼人！\n"NOR,
        HIR"\n只见$N人影一闪，身形已然欺近对方，手中剑光闪烁，嗡嗡做响！\n"NOR,
        HIM"\n却见$N一剑未定二剑已至，随有前后之分却同时到达，速度之快晃如两剑同时发出！\n"NOR,
        HIG"\n不见$N手臂动作，只听一声龙吟之生，这第二剑已破空而至，刺至身前！\n"NOR,
        HIB"\n紧跟着，$N又是一剑刺至，剑招虽分前后，但剑锋几乎同时到达，速度之快难以言表！\n"NOR,
        HIW"\n一眨眼间$N的身形已欺至身前，若有若无，这第二剑已于电光火石间刺至身前！\n"NOR,
});
int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if (me->query_skill("force") < 40)
                return notify_fail("你的内功火候不够，不能学习天羽奇剑。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的内力不够，不能学习天羽奇剑。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<50 || query("neili", me)<35 )
                return notify_fail("你的内力或气不够练天羽奇剑。\n");
        me->receive_damage("qi", 45);
        addn("neili", -30, me);
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
        int d_e1 = -15;
        int d_e2 = 5;
        int p_e1 = -45;
        int p_e2 = -25;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 170;
        int m_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tianyu-qijian", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) {
          return 1.4;
  return 1.0;
}

string perform_action_file(string action)
{
        return __DIR__"tianyu-qijian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weapon;
        string amsgs;

        weapon=query_temp("weapon", me);

        if( query_temp("09_pfm/zhu", me )
              && query_temp("09_pfm/zhu", me)>0
             && weapon
              && query("skill_type", weapon) == "sword"
              && !query_temp("09_pfm/zhu_hit_done", me) )
        {
                amsgs = hit_msg[random(sizeof(hit_msg))];
                addn("neili", -40, me);
                addn_temp("09_pfm/zhu", -1, me);
                message_combatd(amsgs, me);
                set_temp("09_pfm/zhu_hit_done", 1, me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
                delete_temp("09_pfm/zhu_hit_done", me);
        }
}

int help(object me)
{
        write(HIC"\n天羽奇剑："NOR"\n");
        write(@HELP

    天羽奇剑为天山灵鹫宫剑法。

        学习要求：
                八荒六合惟我独尊功20级
                内力80
HELP
        );
        return 1;
}
