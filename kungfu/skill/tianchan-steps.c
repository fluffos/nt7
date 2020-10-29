// tianchan-steps.c
// by Find.
// 天蝉步法

inherit SKILL;

string *dodge_msg = ({
	"$n双足轻轻点地，身形若隐若现，$N的招式完全落空。\n",
	"$n一式「风里避风」，瞬间人已不见了踪影。\n",
	"$n双足一蹬，人以落在了丈许开外，$N的招式对$n丝毫无损。\n",
	"只见$n腰身东躲西闪，$N的招法尽数落空。\n"
});

int valid_enable(string usage) 
{ 
	return (usage == "dodge"); 
}

string perform_action_file(string action)
{
        return CLASS_D("tangmen") + "/tianchan-steps/" + action;
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
       return dodge_msg[random(sizeof(dodge_msg))];
}

int effective_level() { return 12;}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 40 )
                return notify_fail("你的体力太差了，不能练习天蝉步法。\n");
        me->receive_damage("kee", 30, "tire");
        return 1;
}

/* 此函数返回值越小越难练，越大越好练，0 为正常难度。*/
int practice_bonus()
{
	return -10;
}


/* 此函数返回值越小越难学，越大越好学，0 为正常难度。*/
int learn_bonus()
{
	return -10;
}

/* 当这项武功小于 75 级时，此函数返回值越小学的越快。
 * 当这项武功大于 75 级时，此函数返回值越大学的越快。
 * 当这项武功等于 75 级时，此函数返回值没有意义。
 * 也就是说此函数返回值小，利于初期学习，但越学越难
 * 函数返回值大，初期学习很难，但越学越快
 * 函数返回值为零正常，前后阶段难度没有变化
 */
int black_white_ness()
{
	return 0;
}

