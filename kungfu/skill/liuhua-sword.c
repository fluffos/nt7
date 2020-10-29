// liuhua-sword.c
// 流花掠影剑

inherit SKILL;

mapping *action = ({
([      "action":"$N的$w斜斜的升出，一招「不紧不慢」刺向$n的$l",
        "dodge" : -10,
        "damage": 45,
        "damage_type":  "刺伤"
]),
([      "action":"$N手中的$w一闪，一式「你情我愿」罩向$n的$l",
        "dodge" : -10,
        "damage": 60,
        "damage_type":  "割伤"
]),
([      "action":"$N身形一闪，从$n的视线里消失，$w却飞向$n的$l",
        "dodge" : 45,
        "damage": 130,
        "damage_type":  "割伤"
]),
([      "action":"$N一个转身，$w在身边一闪一闪，刹那间斩向$n的$l",
        "dodge" : 10,
        "damage": 55,
        "damage_type":  "割伤"
]),
([      "action":"$N手中$w中宫直进，无声无息地对准$n的$l刺出一剑",
        "dodge" : 35,
        "damage": 160,
        "damage_type":  "刺伤"
]),
([      "action":"$N手中的$w发出丈许剑芒，内力从剑削发出，直逼$n的$l而去",
        "dodge" : 60,
        "damage": 155,
        "damage_type":  "刺伤"
]),
([      "action":"$N双手握紧$w，剑锋透出寒气，看似极平凡的一招向$n的$l逼去",
        "dodge" : 70,
        "damage": 180,
        "damage_type":  "割伤"
]),

});

int valid_learn(object me)
{
	object ob;

	if( !(ob = me->query_temp("weapon"))
	|| (string)ob->query("skill_type") != "sword" )
		return notify_fail("你必须先找一把剑才能练剑法。\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30 || (int)me->query("force") < 3 )
		return notify_fail("你的内力或气不够，没有办法练习流花掠影剑。\n");
	me->receive_damage("kee", 30, "tire");
	me->add("force", -3);
	write("你按著所学练了一遍流花掠影剑。\n");
	return 1;
}

int effective_level() { return 11;}

int learn_bonus()
{
	return -10;
}

int practice_bonus()
{
	return -10;
}

int black_white_ness()
{
	return -10;
}

string *parry_msg = ({
	"$v从$n手中闪出格开了$N的$w。\n",
});

string *unarmed_parry_msg = ({
	"$n手中的$v形成了一道网，死死的封住了$N的攻势。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string perform_action_file(string action)
{
	return __DIR__ + "/liuhua-sword/" + action;
}

