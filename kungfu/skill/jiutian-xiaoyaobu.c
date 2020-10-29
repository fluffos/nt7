// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "$n身形左闪右晃，姿势潇洒之极，一招[飞升九天]轻巧地躲开$N的进攻。\n",
        "$n宛如一屡青烟，飘忽不定，令人琢磨不定，一招[魔神无形]闪到了$N的身后。\n",
        "$n姿态幽雅之极，躲闪之中丝毫不显狼狈之态，一招[上天入地]避开了$N的攻击。\n",
        "$n身形突然连晃数下，宛如云雾中的幻灵，一招[洞彻九幽]躲开了$N的攻击。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("jiutian-xiaoyaobu", 1);
        if (lvl > 300) lvl = 300;

        if( query("max_neili", me)<3000+lvl*20 )
                return notify_fail("你试着走了两步，顿觉胸"
                                   "口烦恶之极，看来是内力不济。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("jiutian-xiaoyaobu", 1) < 100 ||
            query("family/family_name", ob) == "少林派" || 
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("jiutian-xiaoyaobu", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIW "$n" HIW "身形如同鬼魅般地晃动了几下，如流星一般躲开了$N"
                                    HIW "的攻击。\n" NOR]);

                return result;
        } else
        if (mp >= 100)
        {
                result = HIY "$n" HIY "身形如同鬼魅般地晃动了几下，可是$N"
                         HIY "反应奇快，身形一闪，拦住了$n" HIY "的去路\n" NOR;

                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jiutian-xiaoyaobu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的体力太差了，难以练习九天逍遥步。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够了，无法练习九天逍遥步。\n");

        me->receive_damage("qi", 65);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiutian-xiaoyaobu/" + action;
}