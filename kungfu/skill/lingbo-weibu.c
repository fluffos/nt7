#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n轻轻巧巧地往前一步，衣袂飘忽，一式"HIW"「轻云蔽月」"NOR"身影恍惚如浮云，\n$N只觉眼花缭乱。\n",
        "$n袍袖轻拂，拔地而起，在空中转了一圈，一式"HIW"「流风回雪」"NOR"有如漫天\n琼花飞舞，$N目眩神迷，辨不清方向。\n",
        "$n抬手掩面，嫣然一笑，左一步，右二步，斜刺里又三步，一式"MAG"「罗袜生尘」"NOR"\n轻捷婀娜，只见地上纤尘纷扬，$N呆立半晌，浑忘了如何出招。\n",
        "$n待$N攻近面门，突然身形后仰，后退几步，一式"MAG"「轻裾曳雾」"NOR"施施然\n躲过了$N这一招。\n",
        "$n一式"HIM"「惊鸿回眸」"NOR"，一个侧身飘然掠起，转眼已在$N身后。\n",
        "$n舒展身体，抖擞精神，一式"HIY"「游龙翩飞」"NOR"迅捷如电，侧身让过了$N这招。\n",
        "$n回眸粲然，一式"HIG"「清流弄履」"NOR"有如流水溅湿文履，刹那间滑出丈余许，\n$N这一招扑了个空。\n",
        "$n泰然自若，左足上挑，右足力蹬，一式"HIG"「神渚濯足」"NOR"纵跃于几丈开外。\n",
        "$n气定神闲，笼袖不动，足下却是风生水起，一式"HIB"「屏翳收风」"NOR"飘然避过\n$N这招。\n",
        "$n身形将倾未倾，若往若还，一式"HIC"「川后静波」"NOR"如微风轻掠水面，倏忽已\n不见人影。\n",
});

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl > 300) lvl = 300;

        if( !me->query_family() || me->query_family() != "逍遥派" )
               return notify_fail("你研究了一会儿，只觉的不是逍遥派的根本无法理解其中奥妙\n"); 

       if( query("dex", me)<21 )
                return notify_fail("你先天身法太差，无法学习凌波微步。\n");

        if( query("max_neili", me)<3000+lvl*20 )
                return notify_fail("你试着走了两步，顿觉胸"
                                   "口烦恶之极，看来是内力不济。\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("lingbo-weibu", 1);

        if( query_temp("immortal", me) )
        {
                me->stop_busy(); 
                me->clear_weak(); 
        }

        if( ap/3+random(ap)<dp || query_temp("immortal", me) )
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "身子轻轻晃动，$N" HIW
                                            "眼前顿时出现了无数个$n" HIW "的幻影，令$N"
                                            HIW "完全无法辨出虚实。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "往旁边歪歪斜斜的迈出一步，却恰"
                                            "好令$N" HIW "的攻击失之毫厘。\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "这一招来的好快，然后$n"
                                            HIW "一闪，似乎不费半点力气，却将$N"
                                            HIW "这一招刚好避开。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "轻轻一跃，已不见了踪影，$N"
                                            HIW "心中大骇，却又见$n" HIW "擦肩奔过，"
                                            "当真令人思索菲仪。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "只见$n" HIY "微微一笑，身子轻轻晃动，"
                                 "顿时出现了无数个$n" HIY "的幻影，可是$N"
                                 HIY "精通易理，将其中虚实辨得清清楚楚。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "往旁边歪歪斜斜的迈出一步，然而$N"
                                 HIY "错步跟随，方位毫厘不差。\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "一闪，似乎不费半点力气，却将$N"
                                 HIY "这一招刚好避开，可是$N"
                                 HIY "招中有招，进攻却是不止。\n" NOR;
                        break;
                default:
                        result = HIY "但见$n" HIY "轻轻一跃，已不见了踪影，$N"
                                 HIY "不假思索，反身出招，更是巧妙无方。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的体力太差了，难以练习凌波微步。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够了，无法练习凌波微步。\n");

        me->receive_damage("qi", 65);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}

/*
void skill_improved(object me)
{
        if( me->query_skill("lingboweibu",1) == 80 && !query("lbwb", me )
        &&  me->query_skill("literate", 1) > 80)
        {
                tell_object(me, HIY "$N一步步走下来，只觉的心情舒畅，不知不觉内力有所积累。\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 120 && query("lbwb", me) == 1
        &&  me->query_skill("literate", 1) > 100)
        {
                tell_object(me, HIM "$N六十四卦走完，刚好绕了一个大圈，回到原地，精神大振。\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 160 && query("lbwb", me) == 2
        &&  me->query_skill("literate", 1) > 120)
        {
                tell_object(me, CYN "$N越走越快，内息随着步法不住运转，隐隐然自己的内力已经有了提高！\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 200 && query("lbwb", me) == 3
        &&  me->query_skill("literate", 1) > 140)
        {
                message_vision(RED "$N步法娴熟，随意踏出，脚步成圆，只感神清气爽，全身精力弥漫！\n" NOR, me);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
}

*/

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) {
        if (me->query_family() =="xiaoyao")        return 1.5;
        return 1.0;
}

int help(object me)
{
        write(HIC"\n凌波微步："NOR"\n");
        write(@HELP

    洛神赋：“凌波微步，罗袜生尘……转盼流精，光润玉颜。含
辞未吐，气若幽兰。华容婀娜，令我忘餐。［禾农］纤得衷，修短
合度，肩若削成，腰如红素，延颈秀项，皓质呈露，芳泽无加，铅
华弗御。云髻峨峨，修眉连娟。丹唇外朗，皓齿内鲜。明眸善睐，
辅薜承权。环姿艳逸，仪静体闲。柔情绰态，媚于语言……皎若太
阳升朝霞，灼若芙蓉出绿波”。
    凌波微步原载于北冥神功帛卷卷末，按伏羲六十四卦而排，内
劲行遍一周天，脚步亦踏遍六十四卦一周天。步法轻灵迅捷，有如
凌波而行，罗袜生尘，巧妙已极。
    凌波微步乃逃命之妙法，非害人之本领也，练之有百利而无一
害。

        学习要求：
          北冥神功10级
HELP
        );
        return 1;
}
