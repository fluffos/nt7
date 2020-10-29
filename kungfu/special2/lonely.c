
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "天煞孤星" NOR; }

int perform(object me, string skill, string arg)
{
      return notify_fail("这项技能不需要使用。\n");
}
