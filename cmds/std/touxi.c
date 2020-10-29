// touxi.c 偷袭
// by King 97.05

#include <ansi.h>

int main(object me, string arg)
{
        object obj;
        int skill, count;

        if( query("no_fight", environment(me)) )
                return notify_fail("这里禁止战斗。\n");

        if (! arg || !objectp(obj = present(arg, environment(me))) || !me->visible(obj) )
                return notify_fail("你想偷袭谁？\n");

        if (me->is_chatter())
                return notify_fail("你这个样子有什么好偷袭的？\n");

        if (! obj->is_character())
                return notify_fail("看清楚一点，那并不是生物。\n");

        if (obj->is_fighting(me))
                return notify_fail("你已经在战斗中了，还想偷袭？\n");

        if (! living(obj))
                return notify_fail(obj->name() + "都已经这样了，你还用"
                                   "得着偷袭吗？\n"); 

        if (obj == me)
                return notify_fail("偷袭自己？别这么想不开。\n");

        if (me->is_busy())
                return notify_fail("你的动作还没有完成，不能偷袭。\n");

        if (obj->query_competitor())
                return notify_fail("人家比武你要偷袭？真是太不要脸了。\n");

        tell_object(me, "你飞身纵起，扑向" + obj->name() +"！\n\n");
        tell_object(obj, CYN + me->name() + "忽然向你扑来！\n\n" NOR);
        message("vision", CYN + me->name() + "忽然向" + obj->name() +
                          "扑去！\n\n" NOR, environment(me), ({me, obj}));

        switch (obj->accept_touxi(me))
        {
        case 0:
                return 0;
        case -1:
                return 1;
        }

        count = me->query_str();

/*
        if( query("id", userp(me) && userp(obj) && !obj->is_want_kill(me)) )
                me->want_kill(obj);
        me->kill_ob(obj);
*/

        if( random(query("combat_exp", me))<query("combat_exp", obj)/2 )
        {
                addn_temp("str", count*4, me);
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                addn_temp("str", -count*4, me);
        } else
        {
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
        }

   //me->start_busy(3);
        obj->kill_ob(me);

        return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : touxi <人物>
 
这个指令用来向敌人偷袭。偷袭不成时，则会招至反击。特别适合于
经验低的玩家向经验高的玩家拚命。:)

其他相关指令: fight, kill, hit
HELP
    );
    return 1;
}