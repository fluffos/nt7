// longzhua-gong.c 龙爪功

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
        "劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
        "幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
});

int next_hit(object me, object victim, object weapon, int damage);
mapping *action = ({
([      "action": "在呼呼风声中，$N使一招「捕风式」，双手如钩如戢，插向$n的$l",
        "force" : 100,
        "attack": 30,
        "dodge" : 25,
        "parry" : 5,
        "damage": 10,
        "lvl"   : 0,
        "post_action": (: next_hit :),
        "skill_name" : "捕风式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N猛地向前跃出，一招「捉影式」，两腿踢出，双手抓向$n的面门",
        "force" : 110,
        "attack": 41,
        "dodge" : 30,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 10,
        "post_action": (: next_hit :),
        "skill_name" : "捉影式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N双手平伸，十指微微上下抖动，一招「抚琴式」打向$n的$l",
        "force" : 120,
        "attack": 49,
        "dodge" : 35,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 20,
        "post_action": (: next_hit :),
        "skill_name" : "抚琴式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N左手上拦，右手内挥，一招「击鼓式」击向$n胸口",
        "force" : 140,
        "attack": 54,
        "dodge" : 36,
        "parry" : 11,
        "damage": 30,
        "lvl"   : 30,
        "post_action": (: next_hit :),
        "skill_name" : "击鼓式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N右手虚握，左手掌立如山，一招「批亢式」，猛地击向$n的$l",
        "force" : 160,
        "attack": 57,
        "dodge" : 38,
        "parry" : 15,
        "damage": 40,
        "lvl"   : 40,
        "post_action": (: next_hit :),
        "skill_name" : "批亢式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N腾步上前，左手护胸，右手探出，一招「掏虚式」击向$n的裆部",
        "force" : 190,
        "attack": 60,
        "dodge" : 42,
        "parry" : 19,
        "damage": 45,
        "lvl"   : 50,
        "post_action": (: next_hit :),
        "skill_name" : "掏虚式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N双手平提胸前，左手护住面门，一招「抱残式」右手推向$n的$l",
        "force" : 220,
        "attack": 65,
        "dodge" : 47,
        "parry" : 21,
        "damage": 51,
        "lvl"   : 60,
        "post_action": (: next_hit :),
        "skill_name" : "抱残式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N两手胸前环抱，腋下含空，五指如钩，一招「守缺式」插向$n的顶门",
        "force" : 260,
        "attack": 71,
        "dodge" : 52,
        "parry" : 22,
        "damage": 54,
        "lvl"   : 80,
        "post_action": (: next_hit :),
        "skill_name" : "守缺式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N右腿斜插$n二腿之间，一招「抢珠式」，上手取目，下手反勾$n的裆部",
        "force" : 300,
        "attack": 76,
        "dodge" : 55,
        "parry" : 25,
        "damage": 57,
        "lvl"   : 100,
        "post_action": (: next_hit :),
        "skill_name" : "抢珠式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N一手虚指$n的剑诀，一招「夺剑式」，一手劈空抓向$n手中的长剑",
        "force" : 320,
        "attack": 82,
        "dodge" : 61,
        "parry" : 31,
        "damage": 62,
        "lvl"   : 120,
        "post_action": (: next_hit :),
        "skill_name" : "夺剑式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N左手指向$n胸前的五道大穴，右手斜指太阳穴，一招「拿云式」使"
                  "$n进退两难",
        "force" : 340,
        "attack": 85,
        "dodge" : 62,
        "parry" : 35,
        "damage": 65,
        "lvl"   : 140,
        "post_action": (: next_hit :),
        "skill_name" : "拿云式" ,
        "damage_type" : "内伤"
]),
([      "action": "$N前脚着地，一手顶天成爪，一手指地，一招「追日式」劲气笼罩$n"
                  "的全身",
        "force" : 360,
        "attack": 90,
        "dodge" : 65,
        "parry" : 38,
        "damage": 70,
        "lvl"   : 160,
        "post_action": (: next_hit :),
        "skill_name" : "追日式" ,
        "damage_type" : "内伤"
])
});
int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="qianye-shou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练龙爪功必须空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候不够，无法学龙爪功。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的内力太弱，无法练龙爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("longzhua-gong", 1))
                return notify_fail("你的基本爪法火候水平有限，无法领会更高深的龙爪功。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手练习！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的内力不够练龙爪功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}
int next_hit(object me, object victim, object weapon, int damage)
{
        string *msg;
        msg = ({
                HIR"\n$N一抓不中，次抓随至，来势更加迅捷刚猛！" NOR,
                HIR"\n$N龙爪手源源而出，一招落空，又即连续急攻！" NOR,
                HIR"\n$n才躲过这招，$N次招又至，抓法快极狠极！"NOR,
        });

        if ((int)me->query_skill("longzhua-gong", 1) > 100
         && !query_temp("next_hit", me) )
        {
                message_combatd(msg[random(sizeof(msg))] , me, victim );
                addn("neili", -20, me);
                addn_temp("next_hit", 1, me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                delete_temp("next_hit", me);
        }

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
        int d_e1 = 30;
        int d_e2 = 10;
        int p_e1 = -15;
        int p_e2 = -50;
        int f_e1 = 300;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);
        lvl = (int)me->query_skill("longzhua-gong", 1);
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
                "post_action" : (: next_hit :),
                "damage_type" : random(2) ? "内伤" : "抓伤",
        ]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        int j;
        string name;
        j = me->query_skill("longzhua-gong", 1);
        name = xue_name[random(sizeof(xue_name))];

        if (damage_bonus < 50) return 0;

        if( (query("neili", me)>200) && random(j)>120 )
        {
                result = ([ "damage" : damage_bonus ]);
                if( !victim->is_busy() )
                        victim->start_busy(2);
                addn("neili", -30, me);

                result += ([ "msg" : HIY "突然人影闪动，$N迫到$n身后，袖中伸出手，五根手指向$n"
                                     RED + name + HIY "插了下去！\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action) 
{
        return __DIR__"longzhua-gong/" + action; 
}

int learn_bonus() { return 10; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point() { return 1; }

int help(object me)
{
        write(HIC"\n龙爪功："NOR"\n");
        write(@HELP

    龙爪功只有三十六招，要旨端在凌厉狠辣，不求变化繁多。为
少林七十二绝技之一。
    可与如来千叶手互备。

        学习要求：
                混元一气功20级
                内力100
HELP
        );
        return 1;
}
