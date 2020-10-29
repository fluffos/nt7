#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不动，一招「对台梳妆」，手中$w抖得笔直，对准$n$l直刺而去",
        "force" : 80,
        "attack": 30,
        "dodge" :-35,
        "parry" :-25,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "对台梳妆",
        "damage_type": "刺伤"
]),
([      "action": "$N身形一转，一招「云龙白鹤」，手中$w如矫龙般腾空一卷，猛地向$n劈头打下",
        "force" : 130,
        "attack": 38,
        "dodge" :-43,
        "parry" :-27,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "云龙白鹤",
        "damage_type": "抽伤"
]),
([      "action": "$N力贯鞭梢，一招「明月千里」，手中$w舞出满天鞭影，铺天盖地袭向$n全身",
        "force" : 160,
        "attack": 45,
        "dodge" :-63,
        "parry" :-29,
        "damage": 61,
        "lvl"   : 80,
        "skill_name" : "明月千里",
        "damage_type": "抽伤"
]),
([      "action":"$N一声娇喝，一招「映月无声」，手中$w变换莫测，从意想不到的方位扫向$n",
        "force" : 180,
        "attack": 50,
        "dodge" :-65,
        "parry" :-33,
        "damage": 68,
        "lvl"   : 120,
        "skill_name" : "映月无声",
        "damage_type": "抽伤"
]),
([      "action":"$N飞身一跃而起，凌空一招「影玉徵辉」，$w宛如蛟龙通天，携着飕飕破空之声袭向$n",
        "force" : 210,
        "attack": 53,
        "dodge" :-76,
        "parry" :-36,
        "damage": 73,
        "lvl"   : 160,
        "skill_name" : "影玉徵辉",
        "damage_type": "抽伤"
]),
([      "action":"$N身形飘逸无定，一招「金光泻地」，手中$w幻出无数鞭影，笼罩$n全身",
        "force" : 230,
        "attack": 65,
        "dodge" :-92,
        "parry" :-35,
        "damage": 91,
        "lvl"   : 180,
        "skill_name":  "金光泻地",
        "damage_type": "抽伤"
]),
([      "action":"$N身形飘逸无定，一招「蜃楼银沙」，手中$w幻出无数鞭影，笼罩$n全身",
        "force" : 251,
        "attack": 66,
        "dodge" :-117,
        "parry" :-40,
        "damage": 120,
        "lvl"   : 200,
        "skill_name" : "蜃楼银沙",
        "damage_type": "抽伤"
]),
});

int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( query("gender", me) != "女性" )
                return notify_fail("银索金铃只有女性能练。\n");

        if ((int)me->query_dex()  < 40)
                return notify_fail("你的后天身法不够，无法练银索金铃。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你必须先找一条鞭子才能练银索金铃。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的内力不足，没有办法练银索金铃。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候太浅，没有办法练银索金铃。\n");

        if ((int)me->query_skill("whip", 1) < 30)
                return notify_fail("你的基本鞭法火候太浅，没有办法练银索金铃。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yinsuo-jinling", 1))
                return notify_fail("你的基本鞭法水平还不够，无法领会更高深的银索金铃。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("yinsuo-jinling", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不对。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的体力不够练银索金铃。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的内力不够练银索金铃。\n");

        me->receive_damage("qi", 45);
        addn("neili", -55, me);
        return 1;
}

void skill_improved(object me)
{
       int level = (int)me->query_skill("yinsuo-jinling", 1);
       if(level>1800 && !query("can_perform/yinsuo-jinling/chan",me))
       {
          tell_object(me,HIY"你通晓了银索金铃「" HIR "缠字诀" HIY "」的奥秘。\n"NOR);
          set("can_perform/yinsuo-jinling/chan",1,me);
        }
}
string perform_action_file(string action)
{
        return __DIR__"yinsuo-jinling/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        weap=query_temp("weapon", victim);
        weap1=query_temp("weapon", me);

        if( (me->query_skill("yinsuo-jinling") > 150)
             && (query("neili", me)>700 )
             && (query_temp("weapon", victim) )
            && random(10) > 7)
        {
                message_combatd(HIW "只见$N挥舞" + weap1->name() + "，转出无数个大小圈子，以阴柔之劲缠住了$n的" + weap->name() + "！\n" NOR,
                                me, victim  );
                if (! victim->is_busy())
                        victim->start_busy(1);

                if (random(me->query_str() + me->query_dex()) > victim->query_str() + me->query_dex())
                {
                        message_combatd(HIY "\n$N气运手臂用力一拽，" + weap->name() + "却无法从" + weap1->name() +
                                        "的缠绕中脱开，情急之下只好放弃了手中的" + weap->name() + "。\n" NOR, victim );
                        weap->unequip();
                        weap->move(environment(me));
                        victim->reset_action();
                }

                else
                {
                        message_combatd(HIY "\n$N暗运巧劲，" + weap->name() + "顺着方向快速旋转数下，解开了" + weap1->name() +
                                        "的缠绕。\n" NOR, victim );
                        addn("neili", -50, victim);
                }

                addn("neili", -(20+random(30)), me);
        }
        return 1;
}
