// linji-zhuang.c 临济十二庄

#include <ansi.h>
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        if( query("sex", me) )
                return 0;

        lvl = (int)me->query_skill("linji-zhuang", 1);
        return lvl / 100 * lvl * 24 * 15 / 200;
}

string *skill_name = ({
        "天字庄",
        "地字庄",
        "之字庄",
        "心字庄",
        "游龙庄",
        "鹤翔庄",
        "旋风庄",
        "飘云庄",
        "大字庄",
        "小字庄",
        "幽字庄",
        "冥字庄",
        "临济十二庄",
});

string *combo_name = ({
        "天地",
        "之心",
        "龙鹤",
        "风云",
        "大小",
        "幽冥",
});
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        int /*i,*/ np, nf, nh/*, ns, ts*/;
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);
        np = (int)me->query_skill("mahayana", 1);

        if( query("gender", me) != "女性" )
                return notify_fail("你非女子，不能练习临济十二庄。\n");

        if (np <= nh && np < 200)
                return notify_fail("你的大乘涅磐功修为不够，无法领会更高深的临济十二庄。\n");

        if (nf < 40)
                return notify_fail("你的基本内功火候还不够，无法领会临济十二庄。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("临济十二庄只能用学(learn)的来增加熟练度。\n");
}

void skill_improved(object me)
{
        int level = me->query_skill("linji-zhuang",1);
        int o_lvl=query("linji_lvl", me);
        int i;

        if ( level > 180 ) return;

        if ( level/15*15 == level ) {
                tell_object(me, HIG "你对「" + skill_name[level/15-1] + "」已豁然贯通。\n"NOR);
                if (o_lvl < level) {
                        tell_object(me, HIG"顿时你对基本内功的领悟也大大提高。\n"NOR);
                        for (i=0; i< level; i++)
                        me->improve_skill("force", level);
                }
        }

        if ( level/30*30 == level )
        if (o_lvl < level) {
                tell_object(me, HIY"此时你" + combo_name[level/30-1] +
                        "二庄融会贯通，一股柔和的真气周游全身，内力修为更精深了一层。\n"NOR);
                addn("max_neili", level, me);
        }


        if( o_lvl<level)set("linji_lvl", level, me);

}
/*
void skill_improved(object me)
{
        switch (me->query_skill("linji-zhuang",1))
        {
                case 30:
                        tell_object(me, HIG "你天地庄练成了! \n" NOR );
                        break;
                case 60:
                        tell_object(me, HIG "你之心庄练成了! \n" NOR );
                        break;
                case 90:
                        tell_object(me, HIG "你龙鹤庄练成了! \n" NOR );
                        break;
                case 120:
                        tell_object(me, HIG "你风云庄练成了! \n" NOR );
                        break;
                case 150:
                        tell_object(me, HIG "你大小庄练成了! \n" NOR );
                        break;
                case 180:
                        tell_object(me, HIG "你幽冥庄练成了! \n" NOR );
                        break;
        }
        return;
}
*/
string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

int help(object me)
{
        write(HIC"\n临济十二庄："NOR"\n");
        write(@HELP

    临济十二庄，讲动静功修练，其排列顺序是：天地之心、龙鹤
风云、大小幽冥。练功的入手途径，始于道家而归于佛家的四智如
来境界。十二庄分别以十二个字标名，又可分别称为天字庄、地字
庄、之字庄、心字庄、游龙庄、鹤翔庄、旋风庄、飘云庄、大字庄、
小字庄、幽字庄、冥字庄。每练成一庄都有对自身有莫大好处，特
别是当将十二庄互为反正融会贯通时，（指天地、之心、大小、龙
鹤、风云、幽冥），对内力修为会有助益，并可增加可以使用的内
功特异功能。若能贯通幽冥二庄（１８０级）更可到达武林人士梦
寐以求的龙虎交会、水火既济的境界、并熟通采制灵丹之妙法。
    临济十二庄可用于为他人疗伤，有效程度比其他内功高，但不
可用于自疗。

        学习要求：
                处女纯阴之体
                出家人才能修习30级以上的临济十二庄
                相应级别的大乘涅磐功
                基本内功10级
                不犯戒
HELP
        );
        return 1;
}