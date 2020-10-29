// dingjia-qinnashou.c 丁家擒拿手


inherit SKILL;

string *action_msg = ({
        "$N使出一招「凤尾手」，右手绕个半圈，欺上去抓住了$n的手腕一扭。",
        "$N随手使出一招「鹤翔手」，左手肘横过，右手便去抓$n的肩头。",
        "$N突然一招「龙腾抓」，双手一前一后，直取$n的左肩。",
        "$N右手一招「虎爪手」，抓向$n背心后的「灵台穴」。",
        "$N左手使出一招「玉女拈针」，内力直透中指指尖，拿向$n的后腰。",
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练丁家擒拿手必须空手。\n");
                
        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练丁家擒拿手。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 260 + random(50), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "damage_type" : random(2)?"内伤":"瘀伤", 
        ]); 
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的内力不够练丁家擒拿手。\n");
        me->receive_damage("qi", 40);
        addn("shen", -10, me);
        addn("neili", -40, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"dingjia-shou/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("dingjia-shou", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
