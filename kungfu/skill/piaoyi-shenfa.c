// piaoyi-shenfa.c 飘翼身法
// by Lonely

inherit SKILL;

string *dodge_msg = ({
        "$n身子猛然贴地向后滑出丈余，好似有人用绳缚住以快迅无纶的手法向后扯动一般。\n",
        "$n双膝不曲，腰不弯，陡然滑出，身子之僵硬怪诡，又和僵尸无异。\n",
        "不见$n提足抬脚，突然之间倒退丈余，一转身。已在数丈之外。\n",
        "只听得呼的一声，$n身子笔直的向空中飞起，直至丈余高，躲过了这一招。\n",
        "$n陡然身形拔起，在空中急速盘旋，连转四个圈子，愈转愈高，一个转折落在数丈之外。\n",
        "$n绕着圈子，东转西闪，滑如游鱼，在间不容发之际躲过了这招。\n",
        "$n大吃一惊，不及趋避，足尖使劲，拔身急起，斜飞而上，及时的躲过了这一招。\n",
        "$n有如一溜轻烟，左一闪，右一趋，正转一圈，反转一圈，已闪了开去。\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(object me)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的体力太差了，不能练飘翼身法。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的内力不够。\n");
        me->receive_damage("qi", 30);
        addn("neili", -20, me);
        return 1;
}

int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("piaoyi-shenfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

