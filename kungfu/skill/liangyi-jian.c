//liangyi-jian.c 两仪剑法
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "skill_name" : "法分玄素",
        "action"     : "$N剑尖剑芒暴长，一招"HIC"「法分玄素」"NOR"，手中$w自左下大开大阖，一剑斜上刺向$n的$l",
        "lvl"        : 0
]),
([      "skill_name" : "道尽阴阳",
        "action"     : "$N剑势圈转，手中$w如粘带连，平平展展挥出，一招" HIR"「道尽阴阳」"NOR"轻轻划过$n的$l",
        "lvl"        : 10
]),
([      "skill_name" : "渊临深浅",
        "action"     : "$N长剑轻灵跳动，剑随身长，右手$w使出一式" HIB"「渊临深浅」"NOR"刺向$n的$l",
        "lvl"        : 20
]),
([      "skill_name" : "水泛青黄",
        "action"     : "$N长剑下指，剑意流转，一招"HIG"「水泛青黄」"NOR"直取$n的$l",
        "lvl"        : 30
]),
([      "skill_name" : "云含吞吐",
        "action"     : "$N剑芒吞吐，幻若灵蛇，右手$w使出一式"HIW"「云含吞吐」"NOR"，剑势极尽曼妙，刺向$n的$l",
        "lvl"        : 40
]),
([      "skill_name" : "梦醒蝶庄",
        "action"     : "$N屈腕云剑，剑光如彩碟纷飞，幻出点点星光，右手$w使出一式"HIG"「梦醒蝶庄」"NOR"跃跃洒洒飘向$n的$l",
        "lvl"        : 50
]),
([      "skill_name" : "人在遐迩",
        "action"     : "$N挥剑分击，剑势自胸前跃出，右手$w一式"HIM"「人在遐迩」"NOR"，毫无留恋之势，刺向$n的$l",
        "lvl"        : 60
]),
([      "skill_name" : "情系短长",
        "action"     : "$N退步，左手剑指划转，腰部一扭，右手$w一记" GRN"「情系短长」"NOR"自下而上刺向$n的$l",
        "lvl"        : 80
]),
});

int valid_enable(string usage){return (usage== "sword") || (usage== "parry");}
int valid_learn(object me)
{
        if( query("max_neili", me)<200 )
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("liangyi-jian", 1) )
                return notify_fail("你的基本剑法火候太浅。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不对。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的体力不够练两仪剑法。\n");
        if( query("neili", me)<45 )
                return notify_fail("你的内力不足以练两仪剑法。\n");
        me->receive_damage("qi", 55);
        addn("neili", -40, me);
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
        int d_e1 = -25;
        int d_e2 = 0;
        int p_e1 = -50;
        int p_e2 = -35;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 200;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liangyi-jian", 1);
        if( random(lvl)>240 && me->query_skill("force")>200 && query("neili", me) >= 500 )
         {
        return ([
        "action":HIC"$N神色凝重，手中$w"NOR+HIY"一顿，气随意转，$w"+HIY"上剑芒突盛，
                   心中默念剑诀，如暴风般地刺向$n的$l！"NOR,
        "force" : 500,
        "dodge" : -140,
        "parry" : -140,
        "damage": 900,
        "weapon": HIY"剑罡"NOR,
        "damage_type":  "刺伤"
        ]);
        }
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liangyi-jian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
       string msg;
       int j, k;
       j = me->query_skill("liangyi-jian", 1);
       k = me->query_skill("qinqi-shuhua",1);
       if( random(10) >= 5
        && !me->is_busy()
        && !victim->is_busy()
        && j > 120
        && k > 120
        && me->query_skill_mapped("parry") == "liangyi-jian"
        && j > random(victim->query_skill("dodge",1))){
          switch(random(3)){
            case 0 :
               msg = HIW"$N施展开剑路，剑势浩荡起伏，犀利无比！\n"NOR;
               msg+= HIW"$n连连後退，全力招架，无力还招！\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),2);
               break;
            case 1 :
               msg = HIW"$N绕着$n飞快地旋转，一下子连刺出好几十剑！\n"NOR;
               msg+= HIW"$n根本分不清楚那一剑是虚，那一剑是实，好停下攻势，严守门户。\n"NOR;
               victim->start_busy(2);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),0);
               break;
            case 2 :
               msg = HIW"$N风驰电掣的绕著$n快跑，忽东忽西，简直像是足不点地的飞行一般！\n"NOR;
               msg+= HIW"$n随着$N转来转去，弄得眼花缭乱，摇摇欲坠。\n"NOR;
               victim->start_busy(3);
               message_vision(msg, me, victim);
               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),1);
               break;
          }
       }
}

int help(object me)
{
        write(HIC"\n两仪剑法："NOR"\n");
        write(@HELP

    太极生两仪。
    武当派两位道长，穷数十年心血，创此两仪剑法，剑法中有阴
有阳，亦刚亦柔，阴阳合一，威力无俦。

        学习要求：
                太极神功50级
                内力200
                基本剑法不低于两仪剑法
HELP
        );
        return 1;
}
