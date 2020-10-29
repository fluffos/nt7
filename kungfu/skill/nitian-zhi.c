//      炎黄-玩家自创武功系统
//      Made at 2004-03-05 00:44:35 by Rcwiz
//      /kungfu/skill/nitian-zhi.c  含情脉脉指

inherit SKILL;
#include <ansi.h>

#define PMSKILLS_D        "/adm/daemons/pmskillsd"

string *parry_msg = ({
HIG "我爱你个叉~~~!\n" NOR,
HIG "我爱你个叉叉~~~!\n" NOR,
HIG "我爱你个叉叉叉~~~!\n" NOR,
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int playermake(){ return 1; }
string who_make(){ return "lala"; }

//####actions start####
mapping *action = ({
([        "action"     :  "我爱你~~~!",
          "force"      :  320,
          "attack"     :  100,
          "parry"      :  64,
          "dodge"      :  60,
          "damage"     :  294,
          "skill_name" :  "含情脉脉",
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
        if (me->query_skill("finger", 1) < me->query_skill("nitian-zhi", 1))
                return notify_fail("你的基本指法火候有限，无法领会更高深的含情脉脉指。\n");
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
        object weapon;

        weapon=query_temp("weapon", me);
        if( query("pmskills/point", me)<PMSKILLS_D->get_max_point() )
                addn("pmskills/point", 1, me);

        victim->receive_wound("qi",damage_bonus*2*PMSKILLS_D->get_point2(query("pmskills/point", me)),me);

        if (damage_bonus < 160)return 0;

        if( random(3) || me->is_busy() || query("neili", me)<100)return 0;
        victim->receive_wound("qi",damage_bonus/2+damage_bonus*PMSKILLS_D->get_point2(query("pmskills/point", me))*2,me);
        addn("neili", -50, me);

        return HIR "$n说道:好爽啊!\n" NOR;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int)me->query_skill("nitian-zhi", 1) < 300
         || random(2)
         || ! living(me))
                return;

        ap = me->query_skill("nitian-zhi", 1);

        dp = ob->query_skill("force", 1) + ob->query_dex() / 2;

        if (ob->query_skill("count", 1) > 100)return;

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                   result += (["msg" : HIC "$n躲过了$N的诱惑\n" NOR]);
                break;
                case 1:
                   result += (["msg" : HIC "$n躲过了$N的诱惑\n" NOR]);
                break;
                default:
                   result += (["msg" : HIC "$n躲过了$N的诱惑\n" NOR]);
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
        return __DIR__"nitian-zhi/" + action;
}
