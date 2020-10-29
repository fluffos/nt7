inherit SKILL;
string *dodge_msg = ({
      "$n一招“月堤徘徊”，漫不经心的向左迈出一步，刚好避过$N的凌厉攻势。\n",
      "$n使一招“冷月清风”，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
      "$n施展“明月春潮”,向一旁飘然纵出，轻轻着地。\n",
      "$n身形微晃，一招“残月蝉声”，有惊无险地避开了$N这一招。\n",
      "$n使出“寒月霜天”，身形化实为虚地躲开了$N这一招。\n",
});

int valid_enable(string usage)
{
        return (usage=="dodge");
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30 )
                return notify_fail("你的体力太差了，不能练圆月步法。\n");
        me->receive_damage("kee", 30);
        return 1;
}
int effective_level() { return 20;}

int learn_bonus()
{
        return 0;
}
int practice_bonus()
{
        return 3;
}
int black_white_ness()
{
        return 0;
}

string perform_action_file(string action)
{
        return CLASS_D("moon") + "/moon-steps/" + action;
}

