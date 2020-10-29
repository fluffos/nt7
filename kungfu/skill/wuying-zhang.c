// wuying-zhang.c
// 唐门 无影穿心掌

inherit SKILL;

mapping *action = ({
([      "action" : "$N连续上步，一式「五毒穿心」，右手抓向$n的$l",
        "force" : 10,
        "dodge" : 20,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N纵身一跃，一招「无影摄魂」，双掌扑向$n的$l",
        "force" : 20,
        "dodge" : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N移身挪步，一式「掖底偷桃」，单拳向$n的$l打去",
        "force" : 30,
        "dodge" : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N将全身内力聚在手掌之上，双掌慢慢飘向$n的$l",
        "force" : 40,
        "dodge" : 40,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身子平平向前，单手飞向$n的$l",
        "force" : 50,
        "dodge" : 50,
        "damage_type" : "瘀伤"
]),

});

int valid_learn(object me)
{
        return 1;
}

int valid_enable(string usage)
{
	return (usage=="unarmed") || (usage=="throwing");
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30 )
		return notify_fail("你的体力不够了，休息一下再练吧。\n");
	me->receive_damage("kee", 30, "tire");
	return 1;
}

int effective_level() { return 11;}

string *parry_msg = ({
	"$n双手一引，$N手中的$w略偏了一分，从$n的身旁飞了过去。\n",
});
string *unarmed_parry_msg = ({
	"$n一招「灵蛇出洞」，轻巧的挡开了$N的招式。\n",
});

string query_parry_msg(object weapon)
{
	if( weapon )
		return parry_msg[random(sizeof(parry_msg))];
	else
		return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
int learn_bonus()
{
	return 0;
}
int practice_bonus()
{
	return 0;
}
int black_white_ness()
{
	return 0;
}

string perform_action_file(string action)
{
	return __DIR__ + "/wuying-zhang/" + action;
}

