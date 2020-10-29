//      炎黄-玩家自创武功系统
//      Made at 2007-12-19 20:43:21 by Rcwiz
//      /kungfu/skill/xigua-blade.c  西瓜刀

inherit SKILL;
#include <ansi.h>

#define PMSKILLS_D        "/adm/daemons/pmskillsd"

string *parry_msg = ({
HIG "西瓜刀\n" NOR,
HIG "西瓜刀\n" NOR,
HIG "西瓜刀\n" NOR,
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int playermake(){ return 1; }
string who_make(){ return "zilin"; }

//####actions start####
mapping *action = ({
([        "action"     :  "西瓜刀",
          "force"      :  334,
          "attack"     :  254,
          "parry"      :  222,
          "dodge"      :  234,
          "damage"     :  234,
          "skill_name" :  "西瓜刀",
          "damage_type":  "砍伤",
]),
([        "action"     :  "西瓜刀",
          "force"      :  334,
          "attack"     :  254,
          "parry"      :  222,
          "dodge"      :  234,
          "damage"     :  234,
          "skill_name" :  "西瓜刀",
          "damage_type":  "砍伤",
]),
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
        return usage == "blade" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        object ob;
        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "blade" )
                return notify_fail("你使用的武器不对。\n");
        if (me->query_skill("blade", 1) < me->query_skill("xigua-blade", 1))
                return notify_fail("你的基本刀法火候有限，无法领会更高深的西瓜刀。\n");
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
        int i, attack_time;

        object weapon;

        weapon=query_temp("weapon", me);

        attack_time = (int)(me->query_skill("xigua-blade", 1) / 40);

        if (attack_time > 13)attack_time = 13;

        if( query("pmskills/point", me)<PMSKILLS_D->get_max_point() )
                addn("pmskills/point", 1, me);

        victim->receive_wound("qi",damage_bonus*PMSKILLS_D->get_point2(query("pmskills/point", me))/3,me);

        if (damage_bonus < 160 || ! living(victim))return 0;

        if( random(3) || me->is_busy() || query_temp("pmskill/lian", me) || query("neili", me)<100)return 0;
        message_vision(HIR "\n西瓜刀\n" NOR, me, victim);

        me->start_busy(1 + random(attack_time));

        addn("neili", -50, me);

        set_temp("pmskill/lian", 1, me);
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, weapon, 0);
        }

        delete_temp("pmskill/lian", me);

        return 1;

        
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("xigua-blade", 1) < 300
         || !(m_weapon=query_temp("weapon", me) )
        || ! living(me)
         || query("skill_type", m_weapon) != "blade" )
                return;

        ap = me->query_skill("xigua-blade", 1);

        dp = ob->query_skill("force", 1) + ob->query_dex() / 2;

        if (ob->query_skill("count", 1) > 100)return;

        if (random(100) == 1)
        {
                result = ([ "damage": -damage ]);
                switch (random(3))
                {
                case 0:
                   result += (["msg" : HIC "西瓜刀\n" NOR]);
                break;
                case 1:
                   result += (["msg" : HIC "西瓜刀\n" NOR]);
                break;
                default:
                   result += (["msg" : HIC "西瓜刀\n" NOR]);
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
        return __DIR__"xigua-blade/" + action;
}
