// 天涯明月刀 written by tiandi。 
/*　　傅红雪已拔刀。 
　　天下无双的刀，不可思仪的刀法。 
　　无论多恶毒的暗器，无论多复杂的诡计，遇见了这把刀，就像是冰雪到了阳光下。 
　　刀光闪，一连串金铃般的轻响，满天暗器落地，每一件暗器都被削断了，都是从正中间断的，就算巧手匠人用小刀一件件停细分割也未必能如此精确。 
　　刀光消失后，才看见血，血是从脸上流下的 
　　屠青的脸。 
　　一道刀口从他眉毛间刻下来，划过鼻尖，这一刀只要多用三分力，他的头 
　　刀已人鞘。 
　　鲜血从鼻尖流落，流入嘴唇，又热又咸又苦。屠青脸上每一根肌肉都已因痛苦而抽搐他的人却没有动
*/
inherit SKILL;

mapping *action = ({
        ([      "action":               
"就在这时，$N飘飞倏忽的，呼地斗然翻出，纵刀斜削，金刀耀日，一刹那间，下了七记杀手",
                "dodge":                -120,
                "damage":               230,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"就在这时忽然有刀光一闪，这就是$N的$w，天上地下，独一无二的刀",
                "dodge":                -120,
                "damage":               330,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"就在这刻不容缓的一瞬问，$N的$w突然自肋下穿出，“叮”的一响，$w迸出火花，激向$n的$l处",
                "dodge":                -130,
                "damage":               220,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"刀光又一斩，屋檐破裂。$w的威力，如雷霆霹雳，横刀再斩$n，眨眼间已斩下了七刀",
                "dodge":                -140,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"骤然间，一片刀光，一道血影，左右直扑$n！\n这一下变生时腋，刀光凌厉，而且绝，除了一刀致命的人体部位外，别的地方都不打",
                "dodge":                -240,
                "damage_type":  "割伤"
        ]),
 
});

int valid_learn(object me)
{
        object ob;
	if ( me->query("gender") != "男性")
		return notify_fail("你好象不是男的吧。\n");
	  if( me->query("TASK") < 1000  || !me->query("marks/kuaihuo") ) 
    		return notify_fail("以你目前的状况，还没有资格练此功夫。\n");
	if ( (int)me->query_skill("moshen-force",1) < 50)
		   return notify_fail("你的魔神诀不够。\n");        

	  if( (int)me->query("max_force") < 200 )
                return notify_fail("你的内力不够，没有办法练天涯明月刀。\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
                return notify_fail("刀呢？\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="blade" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return 
notify_fail("你的内力或气不够，没有办法练习天涯明月刀。\n");
        me->receive_damage("kee", 30);
        me->add("force", -3);
        write("你按著所学练了一遍天涯明月刀。\n");
        return 1;
}

string perform_action_file(string action)
{
        return CLASS_D("moon") + "/tianya-blade/" + action;
}
 
int effective_level() { return 35;}

string *parry_msg = ({
        "$n没有闪避，没有动，动的是$n的刀，“盯”的一响，火星四激，一道刀光冲天面起，看来就像是已种破云层飞至天外。\n",
        "$n的身子忽然斜斜飞出，恰巧从边缘掠过。\n",
});

string *unarmed_parry_msg = ({
        "$n没有闪避，没有动，动的是$n的刀，“盯”的一响，火星四激，一道刀光冲天面起，看来就像是已种破云层飞至天外。\n",
        "$n的身子忽然斜斜飞出，恰巧从边缘掠过。\n",
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
	return -30;
}
int black_white_ness()
{
	return 15;
}

