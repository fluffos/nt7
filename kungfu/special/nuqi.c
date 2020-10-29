#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "怒气冲霄" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你前世乃是愤怒非常的饕餮神兽，转世后拥有常人无法比拟的怒气。该项技能可以使"
                           "你的加怒上限提高200%，且拥有该技能后加怒(jianu)特效不再受到天性的影响。不需要运用。\n");
}

