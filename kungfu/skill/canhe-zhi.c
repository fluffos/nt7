// 基本指法及特殊指法数种。
// 少林武功秘籍藏于慕容世家：    天竺佛指、多罗叶指、修罗指法
// 杭州灵隐寺住持「大悲尊者」：  莲花指
// 南海「孙玉溪」：              七星指
// 关东「大天龙」：              大天龙指
// 祁连山「无洞上人」：          祁连五绝指
// 岭南「幽冥道人」              幽冥指
// 演练为：
// canhe-zhi.c 参合指神功

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
//inherit F_SSERVER;
inherit SKILL;

string martialtype() { return "skill"; }

string *xue_name = ({
        "劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
        "幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
});

string *xue2_name = ({
        MAG "$N默运神元神功，将内力聚于手指，平平淡淡毫无花俏地点向$n的膻中穴" NOR,
        YEL "$N两掌竖合，掌心微虚，如莲花之开放，接着双手食指轻轻一弹，两股指风同时袭向$n" NOR,
        WHT "$N凌空虚点数指，数道指风合成一股剑气，直向$n攻去"NOR,
        RED "$N缓缓举手，五指先是箕张，再缓缓拢指合拳，霎时生出气凝河岳般的剑气狂扬" NOR,
        HIR "$N指风犀利，似一道无形剑气，将$n笼罩于内，$n只觉胸口一痛，全身真气狂泻而出" NOR
});
mapping *action = ({
([      "action": "$N双指并拢虚点而出，合「"NOR + MAG "天竺佛指" NOR "」及"
                  "「" NOR + MAG "修罗指" NOR "」为一式，顿时一股罡风直射$n",
        "force" : 480,
        "attack": 110,
        "parry" :-90,
        "dodge" :-95,
        "damage": 160,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "$N双指齐点而出，合「" HIG "莲花指" NOR "」及「" HIG "多罗叶"
                  "指" NOR "」为一式，顿时剑气已笼罩$n全身各处",
        "force" : 460,
        "attack": 100,
        "parry" :-90,
        "dodge" :-115,
        "damage": 180,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
]),
([
        "action": "只见$N十指箕张，随手指指点点，将「" HIY "祁连五绝指" NOR "」及"
                  "「" HIY "大天龙指" NOR "」的精髓招式同时使出，\n顿时剑气纵横，尘"
                  "砂四起，逼向$n而去",
        "force" : 460,
        "attack": 100,
        "parry" :-135,
        "dodge" :-125,
        "damage": 180,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
]),
([
        "action": "只见$N纵身跃起，长啸一声，凌空而下，「" HIM "七星剑气" NOR "」已射"
                  "向$n全身各处",
        "force" : 460,
        "attack": 100,
        "parry" :-115,
        "dodge" :-145,
        "damage": 200,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "$N伸出两指，弹指无声，陡见两缕紫气由指尖透出，「" HIW "幽冥剑气" NOR
                  "」射向$n周身大穴",
        "force" : 460,
        "attack": 120,
        "parry" :-130,
        "dodge" :-125,
        "damage": 200,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
]),
([      "action": "遥见$N伸出一指轻轻拂向$n，指未到，「" HIR "参合剑气" NOR "」已将$n压"
                  "得透不过气来",
        "force" : 480,
        "attack": 120,
        "parry" :-150,
        "dodge" :-165,
        "damage": 240,
        "weapon" : HIR "参合破体剑气" NOR,
        "damage_type" : "刺伤"
])
});

string main_skill() { return "canhe-zhi"; }

mapping sub_skills = ([
        "lianhua-zhi"    : 120,
        "tianlong-zhi"   : 120,
        "qilian-zhi"     : 120,
        "tianzhu-fuzhi"  : 120,
        "qixing-zhi"     : 120,
        "youming-zhi"    : 120,
        "xiuluo-zhi"     : 120,
        "duoluoye-zhi"   : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
//      object ob;

        if( query("int", me)<30 )
        {
                tell_object(me, "你只觉依自己的悟性，无法合成参合指神功。\n");
                return 0;
        }

        if( query("dex", me)<30 )
        {
                tell_object(me, "你只觉依自己的身法灵动性，根本无法合成参合指神功。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "你觉得参合指神功极其深奥，看来多研究一下学问可能更有帮"
                                "助。\n");
                return 0;
        }

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
        {
                tell_object(me, "你演练完毕，发现如果通晓经络学应该更有所帮助。\n");
                return 0;
        }
        */

        if (me->query_skill("martial-cognize", 1) < 200)
        {
                tell_object(me, "你发现自己的武学修养尚待提高，暂且无法演练成功。\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 240)
        {
                tell_object(me, "你发现自己的内功根基不够，暂且无法演练成功。\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你觉得自己真气不继，无法合成参合指神功。\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "你觉得有所感悟，或许再演练一次就能融会贯通。\n");
                return 0;
        }

        tell_object(me, HIY "\n霎那间，你只觉自身所修炼的数种指法不断在脑海中交替呈\n"
                            "现，最后又如百川归海，终于融会贯通，合为本家绝学参合\n"
                            "指神功。你终于通晓了参合指的诀窍。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

int double_attack()
{
        return 1;
}

int valid_combine(string combo)
{
        /*
         object me = this_player();
         mappingmyfam=query("family", me);
         if (myfam["master_name"] == "慕容博")
        */
        return combo == "xingyi-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练参合指必须空手。\n");

        if( query("int", me)<30 )
                return notify_fail("你的先天悟性太低，无法领会参合指。\n");

        if( query("dex", me)<30 )
                return notify_fail("你的先天身法孱弱，无法修炼参合指。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的内功火候不够，无法修炼合指。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的内力太弱，无法修炼参合指。\n");

        if ((int)me->query_skill("finger", 1) < 160)
                return notify_fail("你的基本指法火候不够，无法修炼参合指。\n");

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("你发现这里面有很多奥妙都和人体的经络构造有关，难以理解。\n");
        */

        if (me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("你的武学修养尚待提高，暂且无法修炼参合指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的参合指。\n");

        return 1;
}

int practice_skill(object me)
{
        int cost;

        if (me->query_skill("canhe-zhi", 1) > 120
            && me->query_skill("zihui-xinfa", 1) < 120)
                return notify_fail("你紫徽心法修为不够，这样下去恐怕会走火入魔！\n");

        if( query("qi", me)<130 )
                return notify_fail("你的体力太低了。\n");

        cost = me->query_skill("canhe-zhi", 1) / 2 + 60;

        if( query("neili", me)<cost )
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("qi", 100);
        addn("neili", -cost, me);
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

        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 280;
        int f_e2 = 380;
        int i, lvl, seq, ttl = sizeof(action);

        // if (! undefinedp(me->query_temp("canhe-action")))
        //        return action[me->query_temp("canhe-action")];

        if( random(10) == 1 && query("neili", me)>1000 )
        {
                addn("neili", -300, me);
                return ([       "action": HIC "$N" HIC "凝神聚气，双指连续点出，指风凌"
                                          "厉，破空而出的「参合剑气」已经逼向$n",
                                "dodge" :-140,
                                "parry" :-140,
                                "damage": 320,
                                "force" : 560,
                                "weapon" : HIR "参合破体剑气" NOR,
                                "damage_type": "刺伤"
                        ]);
        }

        lvl = (int) me->query_skill("canhe-finger", 1);
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
                "damage_type" : random(2) ? "刺伤" : "瘀伤",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.0; }

string query_parry_msg(object victim_weapon)
{
        switch (random(3))
        {
        case 0:
                return NOR + WHT "$n" NOR + WHT"不退反进，右手食指径直指向$N" NOR + WHT
                       "胸前大穴，$N一惊，连忙回身自救。\n" NOR;
        case 1:
                return NOR + WHT "$n" NOR + WHT"双指连连点出，迅捷有力，无数道钢劲的参"
                       "合剑气护出周身，令$N" NOR + WHT"无从下手。\n" NOR;
        default:
                return NOR + WHT "$n" NOR + WHT"长啸一声，但见无数剑气自$N" NOR + WHT
                       "双指而出，笼罩在$P周围，犹如一张网一般，毫无破绽。\n";
        }
}

/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, slv, p;
        object target;
        string msg;

        if (! target) target = offensive_target(me);
        if (! target) {return "";}
        lvl = me->query_skill("canhe-zhi", 1);

        // 身负六脉神剑绝技可以将参合剑气折回
        if (slv = target->query_skill("six-finger", 1) > 200
            && target->query_skill_prepared("finger") == "six-finger"
            && slv >= me->query_skill("canhe-zhi", 1) - 60
            && random(10) == 0)
        {
                msg = action[random(sizeof(action))]["action"];
                msg += HIY "\n但见$n" HIY "斜斜一指点出，指出如风，剑气纵横，嗤然"
                       "作响，竟将$N" HIY "的剑气全部折回，反向自己射去！\n" NOR;

                me->receive_wound("qi", slv / 4 + random(slv / 6), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";
                return msg;
        }

        if (damage_bonus < 120 || lvl < 140) return 0;

        if (random(damage_bonus) > victim->query_dex()/10
            && query("neili", me)>200)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                        return HIR "你只听「嗤嗤嗤」破空声骤响，脸上竟溅到一些血滴！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"canhe-zhi/" + action;
}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy() || damage_bonus < 100) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>200) && random(me->query_skill("canhe-zhi",1))>60 )
                {
                        victim->start_busy(2);
                        addn("neili", -30, me);
                        if( query("neili", victim) <= (damage_bonus/2+30) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/2+30, victim);

                        return HIW "$N默运神元神功，指风轻飘飘地点向$n，一股内劲无声无息的绕向$n周身大穴！\n"
                               HIW "$n只觉全身一麻，已被一招点中「" HIR + name + HIW "」！\n" NOR;
                }
        }
}
*/

int help(object me)
{
        write(HIC"\n参合指："NOR"\n");
        write(@HELP

    参合指为姑苏慕容家指法绝技。慕容氏家学渊源，参合指威力
亦不逊于少林派大力金刚指。
    可与星移掌互备。

        学习要求：
                神元功15级
                内力100
HELP
        );
        return 1;
}