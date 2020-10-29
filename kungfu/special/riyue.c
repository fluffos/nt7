#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY"日月齐辉" NOR; }

int perform(object me, string skill)
{
        return notify_fail("二转时你受到日月之辉的照耀而感悟，对武学的领悟更上一层，此技能可提升练习次数50次。\n");
}

