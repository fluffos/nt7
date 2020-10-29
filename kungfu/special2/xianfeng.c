
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "仙风道骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail("这项技能能够使你更快地学习技能和研究技能。\n"
                       HIC "可提高每次学习次数上限50次，提高每次研究次数上限50次。\n" NOR);
}

