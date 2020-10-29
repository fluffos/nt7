// hit.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj/*, old_target*/;

        if( me->is_chatter() )
                return 0;

        if( query("no_fight", environment(me)) )
                return notify_fail("这里禁止战斗。\n");

        if( !arg || !objectp(obj = present(arg, environment(me))) )
                return notify_fail("你想攻击谁？\n");

        if( !obj->is_character() )
                return notify_fail("看清楚一点，那并不是你能招呼的对象。\n");

        if( query_temp("apply/name", me) && playerp(obj) )
                return notify_fail("你还是先取下面具吧!\n");

        if( !living(obj) )
                return notify_fail("你还要打？不如杀了算了。\n");

        if( obj->is_fighting(me) )
                return notify_fail("加油！加油！加油！\n");

        if( obj == me)
                return notify_fail("打自己？别这么想不开。\n");

        if( query("age", obj) <= 17 && userp(obj) )
                return notify_fail("为了世界更美好，放过小孩子吧.\n");

        if( query("qi", me)<query("max_qi", me)*3/10 )
                return notify_fail("你现在没有力气战斗了。\n");

        if( query("can_speak", obj) )
                message_vision("\n$N对著$n大喝一声：看招！\n\n", me, obj);
        else
                message_vision("\n$N大喝一声，开始对$n发动攻击！\n\n", me, obj);

        notify_fail("你无从下手。\n");
        switch( obj->accept_hit(me) )
        {
        case 0:
                return 0;
        case -1:
                return 1;
        default:
        }

        me->fight_ob(obj);
        if( query("can_speak", obj)){
                if( userp(obj) ) {
                        if( query("age", me)<18 )
                                me->want_kill(obj);
                        obj->fight_ob(me);
                        remove_call_out("do_hit");
                        call_out("do_hit", 1, me, obj);
                } else {
                        if( query("shen", obj)<-3000 )
                                obj->kill_ob(me);
                        else
                                obj->fight_ob(me);
                }
        } else
                obj->kill_ob(me);

        return 1;
}

void do_hit(object me, object obj)
{
        if( objectp(present(obj, environment(me))) ) {
                COMBAT_D->do_attack(me,obj,query_temp("weapon", me));
                COMBAT_D->do_attack(obj,me,query_temp("weapon", obj));
        }
        return;
}

int help(object me)
{
        write(@HELP
指令格式 : hit <人物>

这个指令让你直接向一个人物「进招」。这种形式的战斗是即时的，只要玩家一
敲这个命令，战斗就会开始，直到某一方受伤50% 以上为止。这个指令对那些不
喜欢fight的NPC很有用，因为很多时候你的比武要求会被拒绝。不过使用这个命
令有可能遭到NPC 的强烈反应，所以要小心使用。

其他相关指令: fight, kill

HELP );
        return 1;
}
