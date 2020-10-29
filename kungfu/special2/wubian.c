
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "浩月无边" NOR; }

int perform(object me, string skill)
{
        return notify_fail("由于你在转世的过程中感应到浩月的无穷智慧，使你的学习能力大大提高。\n"
                       HIY "可提高每次学习次数上限100次，提高每次研究次数上限100次。\n" NOR);
}