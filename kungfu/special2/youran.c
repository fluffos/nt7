
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "天地幽然" NOR; }

int perform(object me, string skill)
{
        return notify_fail("被动技能，不需要施展，能大幅度提高内力上限和加"
                           "力上限，提高内力恢复速度。\n");
}