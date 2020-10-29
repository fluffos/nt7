#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "天生奇骨" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你拥有天生超强疗伤和逼毒能力，且内力上限破格提升5%，不需要运用。\n");
}

