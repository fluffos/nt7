
#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

string name() { return HIW "移形换位" NOR; }

int perform(object me, string skill)
{
        int heal;
        int ap, dp;
        object target;

        if (me->query("jing") < 100)
                return notify_fail("你的精神不济，难以施展移形换位。\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        if (! me->is_fighting())
                return notify_fail("你又不是在打架，没事自言自语干什么？\n");

        message_vision(HIM "$N" HIM "情急生智，对着$n" HIM
                       "滔滔不绝，乱吹一通，当真是天花乱坠……迟疑间，你已施展出鬼魅般的身法逃之夭夭。\n",
                       me, target);

        me->receive_damage("jing", 30 + random(20));

        message_vision(HIM "$n" HIM "听得晕晕乎乎，似假非假，若有若无，不知所以，"
                           "手只是缓了一缓，$N" HIM "早已经溜走。\n" NOR,
                            me, target);
        me->set_temp("success_flee", HIG "你成功的逃走了！\n" NOR);
        GO_CMD->do_flee(me);

        return 1;
}
