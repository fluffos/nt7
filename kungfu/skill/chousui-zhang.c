// chousui-zhang.c 抽髓掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": ""HIB"$N脸上露出诡异的笑容，隐隐泛出绿色的双掌扫向$n的$l"NOR"",
        "lvl"   : 0,
        "skill_name" : "抽髓掌"
]),
([        "action": ""BLU"$N突然身形旋转起来扑向$n，双掌飞舞着拍向$n的$l"NOR"",
        "lvl"   : 10,
        "skill_name" : "抽髓掌"
]),
([        "action": ""HIB"$N将毒质运至右手，一招「腐尸毒」阴毒无比地抓向$n的$l"NOR"",
        "lvl"   : 20,
        "skill_name" : "抽髓掌"
]),
([        "action": ""BLU"$N双掌挟着一股腥臭之气拍向$n的$l"NOR"",
        "lvl"   : 30,
        "skill_name" : "抽髓掌"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo)
{
        return combo == "sanyin-zhua";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("poison", 1) < 50)
                return notify_fail("你的基本毒技不足，无法练抽髓掌。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法练抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的掌法根基不足，无法练抽髓掌。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为太弱，无法练抽髓掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("choushui-zhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的抽髓掌法。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必须空手才能练习。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的体力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的内力不够练抽髓掌。\n");
        if (me->query_skill("chousui-zhang", 1) < 50)
                me->receive_damage("qi", 45);
        else
                me->receive_damage("qi", 40);
        addn("neili", -25, me);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("chousui-zhang", 1);
        flvl=query("jiali", me);

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("xx_poison",
                              ([ "level" : flvl*2 + random(flvl*2),
                                 "id":query("id", me),
                                 "duration" : lvl / 50 + random(lvl / 10) ])))
        {
                // 以下是抽髓掌的 perform sandu 中的散毒功能转到这里。
                if (me->query_skill("poison", 1) < 101)
                        set("body_poison", me->query_skill("poison",1)+1, me);
                if (me->query_skill("poison", 1) > 100)
                        set("body_poison", me->query_skill("poison",1)+10, me);
                //  散毒结束
                return HIW "$n" HIW "只感一阵极寒从心底升起，看来是中了$N" HIW "掌上的剧毒。\n" NOR;
        }
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -45;
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 25;
        int f_e1 = 210;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        if (present("huo yan", environment(me)))
        {
                if( random(me->query_skill("strike"))>250 && query("neili", me)>1000 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": BLU "$N神色惨淡，伸手打开发髻，长发下垂，覆在脸上，跟着力咬舌尖，" HIR "一口鲜"
                                "血向火焰中喷去。\n那火焰忽地一暗，" HIW "随即大为明亮，$N猛地身子急旋，如陀"
                                "螺般连转了十多个圈子，\n" HIR "大袖拂动，整个火焰堆陡地拨起，便如一座火墙般向$n压过去" NOR,
                                "force" : 450,
                                "dodge" : -100,
                                "parry" : -100,
                                "weapon": "火焰",
                                "damage_type": "烧伤"]);
                }
                if (random(me->query_skill("strike")) > 215 &&
                    query("neili", me)>800 )
                    {
                        addn("neili", -75, me);
                        return ([
                                "action": HIG "$N厉声大喝，掌力加盛，绿火突然化作一个"
                                          HIR "斗大的火球，向$n疾冲过来。\n使力极猛，去势奇快，"
                                          HIG "只见一碧绿的火球在空中骨碌碌的迅速转动" NOR,
                                "force" : 420,
                                "dodge" : -90,
                                "parry" : -90,
                                "weapon": "火球",
                                "damage_type": "烧伤"]);
                }
                if (random(me->query_skill("strike")) > 180 &&
                    query("neili", me)>600 )
                {
                        addn("neili", -50, me);
                        return ([
                                "action": HIR "$N衣袖一拂，一股劲气直射入火焰之中，"+HIG+"火焰中又分出一道细细的绿火，便如一根水线般，\n"
                                          HIW "$N衣袖挥动，两股劲风分袭$n左右" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG "绿火" NOR,
                                "damage_type": "烧伤"]);
                }
                if (random(me->query_skill("strike")) > 150 &&
                    query("neili", me)>500 )
                {
                        addn("neili", -20, me);
                        return ([
                                "action": HIR "$N随即左掌斜拍出一道"+HIG+"绿火"+HIR+"向$n射去，声势汹汹，"+HIG+"便似一条绿色长蛇横卧空际，轻轻摆动，\n"
                                          HIR "颜色又是鲜艳，"+BLU+"又是诡异，光芒闪烁不定"+HIG+"照映得$n头脸皆碧"NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": HIG"绿火"NOR,
                                "damage_type": "烧伤"]);
                }

                if (random(me->query_skill("strike")) > 120 &&
                        query("neili", me)>400){
                        addn("neili", -10, me);
                        return ([
                                "action": HIR "$N突然间双眉往上一竖，右手食指点两点，火焰堆中嗤嗤两声轻响，"+HIG+"爆出几朵火花，犹如流星一般，\n"
                                          "在$N内力摧迫下，分从左右袭向$n，来势迅速之极" NOR,
                                "force" : 400,
                                "dodge" : -80,
                                "parry" : -80,
                                "weapon": "火花",
                                "damage_type": "烧伤"]);
                }
        }
        lvl = (int) me->query_skill("chousui-zhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 获得招数序号上限 */
                        break;
                }
        seq = random(seq);       /* 选择出手招数序号 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "内伤" : "瘀伤",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n抽髓掌："NOR"\n");
        write(@HELP

    星宿派掌法，以腐尸毒名慑天下。
    可与三阴蜈蚣爪互备。

        学习要求：
                化功大法10级
                内力60
HELP
        );
        return 1;
}
