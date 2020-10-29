//      炎黄-玩家自创武功系统
//      Made at 2007-03-19 12:27:42 by Rcwiz
//      /kungfu/skill/guafu-zhongzhi.c  寡妇的中指

inherit SKILL;
#include <ansi.h>

#define PMSKILLS_D        "/adm/daemons/pmskillsd"

string *parry_msg = ({
HIG "$N中指斜伸，一招$NM，反身一顿，一指向$n的$l戳去。\n" NOR,
HIG "$N食指斜伸，一招$NM，反身一顿，一指向$n的$l戳去。\n" NOR,
HIG "$N拇指斜伸，一招$NM，反身一顿，一指向$n的$l戳去。\n" NOR,
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int playermake(){ return 1; }
string who_make(){ return "thess"; }

//####actions start####
mapping *action = ({
([        "action"     :  "$N中指斜伸，一招「直指花心」，反身一顿，一指向$n的$l戳去。",
          "force"      :  320,
          "attack"     :  74,
          "parry"      :  58,
          "dodge"      :  64,
          "damage"     :  107,
          "skill_name" :  "直指花心",
          "damage_type":  "刺伤",
])
});
//####actions end####

mixed get_actions(){ return action;}

mixed get_actnames()
{
        int i;

        string *names;

        names = ({});

        for (i = sizeof(action) - 1; i >= 0; i--)
                names += ({action[i]["skill_name"]});

        return names;
}

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        object ob;
        if( query_temp("weapon", me )
         || query("secondary_weapon", me) )
                return notify_fail("你必须空手练习。\n");
        if (me->query_skill("finger", 1) < me->query_skill("guafu-zhongzhi", 1))
                return notify_fail("你的基本指法火候有限，无法领会更高深的寡妇的中指。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int double_attack(){ return 1; }

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int ap, dp;
        object weapon;

        weapon=query_temp("weapon", me);

        if( query("pmskills/point", me)<PMSKILLS_D->get_max_point() )
                addn("pmskills/point", 1, me);

        victim->receive_wound("qi",damage_bonus*PMSKILLS_D->get_point2(query("pmskills/point", me))/3,me);

        ap = me->query_skill("finger");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) <= dp)return 0;

        if (! living(victim) || victim->is_busy() || random(4))return 0;

        message_vision(HIR "\n$N一招攻出，竟卷起千层气浪，太玄内劲顿时源源不绝涌入$n体内！\n" NOR, me, victim);

        addn("neili", -50, me);

        victim->start_busy(2 + random(ap / 80));

        return 0;
}

int query_effect_parry(object attacker, object me)
{
        return (100+150*PMSKILLS_D->get_point(query("pmskills/point", me)));
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int)me->query_skill("guafu-zhongzhi", 1) < 300
         || random(2)
         || ! living(me))
                return;

        ap=me->query_skill("guafu-zhongzhi",1)+100*PMSKILLS_D->get_point(query("pmskills/point", me));

        dp = ob->query_skill("force", 1) + ob->query_dex() / 2;

        if (random(100) == 1)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                   result += (["msg" : HIC "可是$n不闪不避，闪电般伸出「中指」反戳$N手腕，挡开了此招。\n" NOR]);
                break;
                case 1:
                   result += (["msg" : HIC "可是$n不闪不避，闪电般伸出「食指」反戳$N手腕，挡开了此招。\n" NOR]);
                break;
                default:
                   result += (["msg" : HIC "可是$n不闪不避，闪电般伸出「拇指」反戳$N手腕，挡开了此招。\n" NOR]);
                break;
                }
                return result;
        }

}

int practice_skill(object me)
{
        if( !query("scborn", me))return notify_fail("自创武学只能用学(learn)的来提升等级。\n");
}

int difficult_level(){ return 2000;}

string perform_action_file(string action)
{
        return __DIR__"guafu-zhongzhi/" + action;
}
