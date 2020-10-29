// banruo-zhang.c 般若掌

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
int is_pbsk() { return 1; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N前腿踢出，后腿脚尖点地，一式"HIC"「横空出世」"NOR"，二掌直出，攻向$n的上中下三路",
        "lvl" : 0,
        "skill_name" : "横空出世"
]),
([      "action" : "$N左掌划一半圆，一式"HIR"「长虹贯日」"NOR"，右掌斜穿而出，疾拍$n的胸前大穴",
        "lvl" : 12,
        "skill_name" : "长虹贯日"
]),
([      "action" : "$N使一式"HIB"「云断秦岭」"NOR"，右掌上引，左掌由后而上一个甩劈，斩向$n的$l",
        "lvl" : 18,
        "skill_name" : "云断秦岭"
]),
([      "action" : "$N左掌护胸，右拳凝劲后发，一式"HIM"「铁索拦江」"NOR"，缓缓推向$n的$l",
        "lvl" : 24,
        "skill_name" : "铁索拦江"
]),
([      "action" : "$N使一式"HIY"「狂风卷地」"NOR"，全身飞速旋转，双掌一前一后，猛地拍向$n的胸口",
        "lvl" : 30,
        "skill_name" : "狂风卷地"
]),
([      "action" : "$N合掌抱球，猛吸一口气，一式"HIW"「怀中抱月」"NOR"，双掌疾推向$n的肩头",
        "lvl" : 36,
        "skill_name" : "怀中抱月"
]),
([      "action" : "$N向上高高跃起，一式"HIG"「高山流水」"NOR"，居高临下，掌力笼罩$n的全身",
        "lvl" : 42,
        "skill_name" : "高山流水"
]),
([      "action" : "$N使一式"CYN"「摘星换斗」"NOR"，劲气弥漫，双掌如轮，一环环向$n的$l斫去",
        "lvl" : 48,
        "skill_name" : "摘星换斗"
]),
([      "action" : "$N两掌上下护胸，一式"HIW"「翻江搅海」"NOR"，骤然化为满天掌雨，攻向$n",
        "lvl" : 54,
        "skill_name" : "翻江搅海"
]),
([      "action" : "$N一式"HIY"「金刚伏魔」"NOR"，双手合十，对着$n微微一揖，全身内劲如巨浪般汹涌而出",
        "lvl" : 60,
        "skill_name" : "金刚伏魔"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="yizhi-chan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练般若掌必须空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的内功火候不够，无法练般若掌。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的内力太弱，无法练般若掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("banruo-zhang", 1))
                return notify_fail("你的基本掌法火候水平有限，无法领会更高深的般若功。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手练习！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练般若掌。\n");

        me->receive_damage("qi", 65);
        addn("neili", -64, me);
        return 1;
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
        int d_e1 = -50;
        int d_e2 = -30;
        int p_e1 = -10;
        int p_e2 = 20;
        int f_e1 = 250;
        int f_e2 = 350;
        int i, lvl, seq, ttl = sizeof(action);
        string *msg = ({
                "喝道：“吃我一掌！”",
                "双手合什，说道：“阿弥陀佛！”",
                "说道：“罪过罪过！”这四字一出口，忽地",
                "",
        });

        lvl = (int) me->query_skill("banruo-zhang", 1);
        if( query_temp("sl_perform/san", me) )
        {
                i = me->query_skill("force") + lvl;
                return([
                        "action": HIW"$N"+ msg[random(sizeof(msg))] +"双掌自外向里转了个圆圈，缓缓向$n推了过来。\n"
                                        "$P掌力未到，$n已感胸口呼吸不畅，顷刻之间，$N的掌力如怒潮般汹涌而至！"NOR,
                        "force" : i + random(i),
                        "damage": 300,
                        "dodge" : -100,
                        "parry" : -100,
                        "damage_type" : "瘀伤", ]);
        }
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

void skill_improved(object me)
{
        int level = (int)me->query_skill("banruo-zhang", 1);

        if (level >= 180
        &&  (int)me->query_skill("yizhi-chan", 1) >= 180
         && !query("sl_gift/yzc", me)){
                addn("con", 1, me);
                set("sl_gift/yzc", 1, me);
                tell_object(me, "\n你的一指禅和般若掌学有所成，提高了你的根骨。\n");
        }

        if( !(level % 10) && level >= (int)me->query_skill("force", 1) ) {
                me->improve_skill("force", (level - 5), 1);
                tell_object(me, "\n你在般若掌方面的造诣增进了你的基本内功修为。\n");
        }

       if(me->query_skill("yijinjing",1)>1800 && me->query_skill("banruo-zhang",1)>1800
       && !query("can_perform/banruo-zhang/yipai",me))
       {
          tell_object(me,HIY"你通晓了般若掌「" HIR "一拍两散" HIY "」的奥秘。\n"NOR);
           set("can_perform/banruo-zhang/yipai",1,me);
         }
        /*
        if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) ) {
                me->improve_skill("hunyuan-yiqi", (level - 5)/2, 1);
                tell_object(me, "\n你在般若掌方面的造诣增进了你的混元一气功修为。\n");
        }
        */
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"banruo-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n般若掌："NOR"\n");
        write(@HELP

    少林七十二绝技之一。
    可与一指禅互备。
    般若掌有一招凶猛的绝招，唤做“一拍两散”。所谓“两散”，是
指拍在石上，石屑四“散”、拍在人身，魂飞魄“散”。这路掌法就只
这么一招，只因掌力太过雄浑，临敌时用不着使第二招，敌人便已毙命，
而这一掌以如此排山倒海般的内力为根基，要想变招换式，亦非人力之
所能。

        学习要求：
                混元一气功20级
                内力100
HELP
        );
        return 1;
}
