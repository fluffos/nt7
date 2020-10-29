
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "妙手药王" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你对所有药理及毒物运用出神入化，带毒类攻击对手，可使对手中毒程度加深20%；\n"
                           "同时，具有本草知识技能的特效，且效果提升10%。不需要运用。\n");
}

