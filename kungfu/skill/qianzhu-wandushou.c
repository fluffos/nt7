// qianzhu-wandushou.c 千蛛万毒手
// Last Modified by Lonely on May. 17 2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N身形一晃而至，一招"HIB"「小鬼勾魂」"NOR"，双掌带着一缕腥风拍向$n的前心",
        "lvl"    : 0,
        "skill_name" : "小鬼勾魂"
]),
([        "action" : "$N身形化做一缕轻烟绕着$n急转，一招"MAG"「天网恢恢」"NOR"，双掌幻出无数掌影罩向$n",
        "lvl"    : 20,
        "skill_name" : "天网恢恢"
]),
([        "action" : "$N大喝一声，一招"BLU"「恶鬼推门」"NOR"，单掌如巨斧开山带着一股腥风猛劈向$n的面门",
        "lvl"    : 30,
        "skill_name" : "恶鬼推门"
]),
([        "action" : "$N一声冷笑，一招"HIR"「灵蛇九转」"NOR"，身形一闪而至，一掌轻轻拍出，手臂宛若无骨，掌到中途竟连变九变，如鬼魅般印向$n的$l",
        "lvl"    : 40,
        "skill_name" : "灵蛇九转"
]),
([        "action" : "$N侧身向前，一招"BLU"「地府阴风」"NOR"，双掌连环拍出，一缕缕彻骨的寒气从掌心透出，将$n周围的空气都凝结了",
        "lvl"    : 50,
        "skill_name" : "地府阴风"
]),
([        "action" : "$N厉叫一声，身形忽的蜷缩如球，飞身撞向$n，一招"YEL "「黄蜂吐刺」"NOR"单掌如剑，直刺$n的心窝",
        "lvl"    : 60,
        "skill_name" : "黄蜂吐刺"
]),
([        "action" : "$N一个急旋，飞身纵起，半空中一式"HIB"「毒龙摆尾」"NOR"，反手击向$n的$l",
        "lvl"    : 70,
        "skill_name" : "毒龙摆尾"
]),
([        "action" : "$N大喝一声，运起五毒神功，一招"RED"「毒火焚身」"NOR"，刹那间全身毛发尽绿，一对碧绿的双爪闪电般的朝$n的$l抓去",
        "lvl"    : 80,
        "skill_name" : "毒火焚身"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="wudu-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练千蛛万毒手必须空手。\n");

        if( !query("family/family_name", me) || me->query_family() != "五毒教" )
                return notify_fail("练千蛛万毒手必须是五毒教的人才可以修炼。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练千蛛万毒手");
        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练千蛛万毒手。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int lvl2;
        int flvl;

        lvl  = me->query_skill("qianzhu-wandushou", 1);
        lvl2 = me->query_skill("duji", 1);
        flvl=query("jiali", me);
        if (lvl + random(flvl) > victim->query_skill("dodge")
                         &&victim->affect_by("qzhu_poison",
                                  ([ "level" : lvl2 + lvl*3 + random(flvl),
                                     "id":query("id", me),
                                    "duration" : lvl / 50 + flvl/50 + random(lvl2 / 50) ])))
        {
                return HIW "$n" HIW "突然面孔扭曲,痛苦不堪,看来是中了千蛛万毒功的巨毒。\n" NOR;
        }
}
void skill_improved(object me)
{
        if( random(15)<1 && query("per", me)>5 )
        {
                tell_object(me, HIR"你忽然觉得体内毒气狂窜，面上顿时罩着一层黑气！\n" NOR );
                addn("per", -1, me);
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
        int d_e1 = -55;
        int d_e2 = -20;
        int p_e1 = 10;
        int p_e2 = 35;
        int f_e1 = 190;
        int f_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qianzhu-wandushou", 1);
        if (random(me->query_skill("finger")) > 120 &&
            me->query_skill("force") > 100 &&
            me->query_skill("dodge") > 100 &&
            query("neili", me)>1500){
                addn("neili", -200, me);
                return ([
                "action": HIR "$N眉间黑气笼罩，牙关紧咬，突然喷出一股香气，十指又快如鬼魅般点向$n膻中穴！"NOR,
                "force": 560,
                "damage" : 100,
                "damage_type": "瘀伤"]);
        }
           if (random(me->query_skill("finger")) > 80 &&
            me->query_skill("force") > 100 &&
            query("neili", me)>1000){
                addn("qi", -15, me);
                addn("neili", -100, me);
                return ([
                "action": HIR "$N忽然咬破食指，潜用内力将毒素逼入指尖，轻轻弹出，一股内劲直袭$n胸口！"NOR,
                "force": 420,
                 "damage" : 80,
                "damage_type": "瘀伤"]);
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
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qianzhu-wandushou", 1) >= 50 )
                return __DIR__"qianzhu-wandushou/" + action;
}

int help(object me)
{
        write(HIC"\n千蛛万毒手："NOR"\n");
        write(@HELP

    千蛛万毒手是五毒教的独门功夫，有独门修炼方法。靠吸取毒
虫身上的毒气来练成毒功，虽然厉害，但毒气会损坏自己的容貌，
使自己变的丑陋无比。

        学习要求：
                五毒神功20级
                内力100
HELP
        );
        return 1;
}
