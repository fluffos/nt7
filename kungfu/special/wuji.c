#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "横行无忌" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在门派中倍受尊崇，完成师门任务可获得额外多5%的奖励，不需要运用。\n");
}

