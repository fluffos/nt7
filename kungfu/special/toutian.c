#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "偷天换日" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你不但智慧超群，且工于心计。在请教他人教授技能时通常可获取更多的帮助，同\n"
                           "时具有更高的领悟能力。学习技能时可提升学习效率10%。不需要运用。\n");
}

