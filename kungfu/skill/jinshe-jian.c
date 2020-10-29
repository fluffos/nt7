// jinshe-jian.c 金蛇剑法
// Last Modified by sega on Mar. 10 2000
// 拟在拿金蛇剑时提升damage属性,

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int is_pbsk() { return 1; }

mapping *action = ({
([      "skill_name" : "金光蛇影",
        "action"     : "$N使一招"HIY"「金光蛇影」"NOR"，手中的$w在一弹指间已向$n的$l连刺数剑",
        "lvl"        : 0
]),
([      "skill_name" : "蛇影万道",
        "action"     : "$N使一招"HIY"「蛇影万道」"NOR"，手中$w狂风骤雨般地向$n的$l连攻数剑",
        "lvl"        : 10
]),
([      "skill_name" : "雪地飞蛇",
        "action"     : "$N身形一转，陡地贴地跃起，手中$w灵动夭跃，一招"HIY"「雪地飞蛇」"NOR"疾刺$n的$l",
        "lvl"        : 20
]),
([      "skill_name" : "金蛇吞信",
        "action"     : "$N身形一转，一招"HIY"「金蛇吞信」"NOR"，手中的$w从左肋下向$n的$l戳了过去",
        "lvl"        : 30
]),
([      "skill_name" : "金蛇狂舞",
        "action"     : "$N手腕一抖，一招"HIY"「金蛇狂舞」"NOR"，$w挟著闪闪剑光，变幻无方逼向$n的$l",
        "lvl"        : 40
]),
([      "skill_name" : "灵蛇电闪",
        "action"     : "$N心念电闪手腕疾振处，一招"HIY"「灵蛇电闪」"NOR"，$w以无法形容的速度直射$n的$l",
        "lvl"        : 50
]),
([      "skill_name" : "蛇困愁城",
        "action"     : "$N身形一矮，一招"HIY"「蛇困愁城」"NOR"，手中的$w由下往上刺向$n的$l",
        "lvl" : 60
]),
([      "skill_name" : "金蛇化龙",
        "action"     : "$N手中$w剑光暴长，一招"HIY"「金蛇化龙」"NOR"，如千年蛇蝎往$n$l咬去",
        "lvl"        : 70
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{

        if( query("dex", me)<28 )
                return notify_fail("你研究了半天，只觉得身法有些差，始终无法理解其中的真谛。\n");

        if( query("str", me)<28 )
                return notify_fail("你研究了半天，感觉膂力有些低，始终无法随意施展。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的内力修为不够，没有办法练金蛇剑法。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不够，没有办法练金蛇剑法。\n");

        if ((int)me->query_skill("dodge", 1) < 140)
                return notify_fail("你的基本轻功火候不够，没有办法练金蛇剑法。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本剑法火候不够，没有办法练金蛇剑法。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("你的武学修养不足，没有办法领悟金蛇剑法。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想杀尽敌人，没能理解金蛇剑法。\n");

        if( query("character", me) == "阴险奸诈" )
                return notify_fail("你一心想怎么学好剑法去害人，结果没能理解金蛇剑法。\n");

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什么金蛇剑法，乱七八糟的，没有半点气势。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshe-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的金蛇剑法。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me)) || 
            query("skill_type", ob) != "sword" )
                return notify_fail("你必须先找一把剑才能练剑法。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的气不够，没有办法练习金蛇剑法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够，没有办法练习金蛇剑法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 30;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinshe-jian", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int effective_level() { return 25;}

string *parry_msg = ({
        "$n手中的$W化作千百把，护住了全身。\n",
        "$n手中的$W自上削下，几乎将$N的$w削成两段。\n",
        "$n使动$W，在身前布起了一道铜墙铁壁，封住了$N的攻势。\n",
        "$n将$W往地上一刺，$W反弹起来，刚好直刺$N的双臂。\n",
        "$n举剑静立，一股内力从剑梢透出，逼开了$N。\n",
        "$n一抖手中的$W，护住了全身。\n",
});

string *unarmed_parry_msg = ({
        "$n回招自守，架住了$N的$w。\n",
        "$n不退反进，气走周天，狠狠磕开了$N的$w。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"jinshe-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i, ap, dp;

        lvl = me->query_skill("jinshe-jian", 1);

        if( query("neili", me)<300
            || query_temp("jinshe-jian/lian", me)
           || me->query_skill_mapped("sword") != "jinshe-jian"
            || !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                     return 0;

        ap = me->query_skill("sword");
        dp = victim->query_skill("dodge");

        addn("neili", -80, me);

        switch(random(5))
        {
           case 1:
             break;

           case 2:
             break;

          case 3:
             break;

          case 4:
             if (ap / 2 + random(ap) > dp &&
                 ! me->is_busy() &&
                 ! victim->is_busy())
             {
                 message_sort(HIW "\n$N" HIW "剑锋一转，手中" + weapon->name() + HIW
                              "犹如灵蛇般地舞动着，竟将$n" HIW "周身缠绕。\n" NOR);
                 me->start_busy(1);
                 victim->start_busy(1 + random(lvl / 20));
             }
             break;

          default :
             if (ap * 3 / 5 + random(ap) > dp &&
                 ! me->is_busy() &&
                 !query_temp("jinshe-jian/lian", me) )
             {
                weapon=query_temp("weapon", me);
                message_sort(HIY "\n$N" HIY "一声长吟，手中" + weapon->name() + HIY
                             "顿时化作一条灵蛇，迅捷无比地袭向$n" HIY "。\n" NOR,
                             me, victim);

                addn("neili", -180, me);

                set_temp("jinshe-jian/lian", 1, me);
                for (i = 0; i < 9; i++)
                {
                    if (! me->is_fighting(victim))
                            break;

                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                }
                delete_temp("jinshe-jian/lian", me);

             }
             break;
       }
}
int help(object me)
{
        write(HIC"\n金蛇剑法："NOR"\n");
        write(@HELP

    金蛇剑法载于「金蛇密笈」，乃金蛇郎君夏雪宜的独门武功。
夏雪宜幼时全家不幸被温家五老劫掠灭门，立志报仇。后于苗疆得
识五毒教教主之妹何红药，并得其助获得五毒教的「三宝」──金
蛇剑、金蛇锥及藏宝图，因而练成绝世武功。
    夏雪宜性情古怪，为人阴狠，武功便正如其人般诡异难测。江
湖上人人闻其名而为之色变，乃是出名的难缠人物。夏雪宜留下的
「金蛇密笈」载有他一身武功，即金蛇剑法、金蛇锥法和金蛇游身
掌。

        学习要求：
                内力500
HELP
        );
        return 1;
}
