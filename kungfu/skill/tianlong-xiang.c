// tianlong-xiang.c 天龙翔
//COOL@SJ
inherit SKILL;

string *dodge_msg = ({
"$n双掌连拍，身子忽屈忽伸，犹如蛟龙飞舞，人借掌势，风吹人衫，身体突然腾上半空，划出一道曲线，远远的飘了开去。\n",    
"$n脚下猛力一登，腾空跃起，凌空一大步就跨过$N的上方，稳稳的落在$N的后面，$N禁不住喝了个彩：好一招「凌虚渡」。\n",
"但见$n身在半空，长吐一口气，”哗、哗、哗“，双袖连挥数下，使一招「龙翱九天」，身形不见下坠，反而越飘越高。\n",
"$N突然一招击出，$n见躲避不过，一掌击出，借着$N的劲道，连翻几个筋斗，远远的躲了开去。\n",
"$n双腿轮番踢出，身体顺势连续翻滚，一式「神龙降世」，跳出了$N的攻击范围。\n",
"$n一招「龙游四海」，身子一弯一扭，贴着地面平平滑开,$N眼前人影一晃，失去了$n的踪影。\n",
"$n长啸一声，使一招「神龙飞升」，腾空而起，一阵狂风吹来，$n双袖鼓起，盘旋挥舞，借着那一阵风势，越舞越高。\n",
"$n迅速解下衣衫，迎风一展，身子踏空而起，在风中飘飘然然而行，正是那招「龙行天下」。\n",
});

int valid_enable(string usage) 
{ 
	return usage == "dodge"; 
}

int valid_learn(object me)
{
	if (!me->query_skill("kurong-changong", 1))
	if ( me->query_skill("qiantian-yiyang", 1) < 10)
		return notify_fail("你的乾天一阳功等级太低了。\n");
	return 1; 
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 30 )
		return notify_fail("你的体力太差了，不能练习天龙翔。\n");
	me->receive_damage("jingli", 25);
	return 1;
}
