// apprentice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old_app;
        mapping family, ob_family/*, skills*/;
//      int i;
//      string *skname;

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (! arg)
                return notify_fail("指令格式：apprentice | bai [cancel]|<对象>\n");

        if (query("reborn_offer", me))
                return notify_fail("转世过程中无法拜师。\n");

        if ( query("berrayer/times", me) )
                return notify_fail("你已经得罪过一个门派了，想找死啊？\n");

        if (arg == "cancel")
        {
                old_app=query_temp("pending/apprentice", me);
                if( !objectp(old_app) )
                        return notify_fail("你现在并没有拜任何人为师的意思。\n");
                write("你改变主意不想拜" + old_app->name() + "为师了。\n");
                tell_object(old_app, me->name() + "改变主意不想拜你为师了。\n");
                delete_temp("pending/apprentice", me);
                return 1;
        }

        if( query_temp("apply/name", me) ) 
                return notify_fail("你解开你的面具再拜师。。\n");

        if (! (ob = present(arg, environment(me))) ||
            ! ob->is_character())
                return notify_fail("你想拜谁为师？\n");

        if (! living(ob))
                return notify_fail("你必须先把" + ob->name() + "弄醒。\n");

        if (ob == me)
                return notify_fail("拜自己为师？好主意....不过没有用。\n");

        if (ob->is_baby())
                return notify_fail("拜孩子为师？好主意....不过没有用。\n");

        if (me->is_apprentice_of(ob))
        {
                message_vision("$N恭恭敬敬地向$n磕头请安，叫道：「师父！」\n", me, ob);
                return 1;
        }

        if( !mapp(ob_family=query("family", ob)) )
                return notify_fail(ob->name() + "既不属於任何"
                                   "门派，也没有开山立派，不能拜师。\n");

        if (playerp(ob))
                return notify_fail("... 现在不能拜玩家为师 :)\n");

        family=query("family", me);
        if (mapp(family) && stringp(family["master_name"]) &&
            ob_family["family_name"] == family["family_name"] &&
            ob_family["generation"] >= family["generation"])
                return notify_fail(ob->name() + "吓了一跳，忙道：“这可不敢当，不敢当。”\n");

        // betrayer ?
        if (mapp(family) && stringp(family["family_name"]) &&
            family["family_name"] != ob_family["family_name"] &&
            query_temp("pending/betrayer", me) != ob )
        {
                if( query("reborn_offer", me) )
                        return notify_fail("转世进程中不可以判师。\n");

                if( family["family_name"] != "华山剑宗" || ob_family["family_name"] == "华山派" )
                write(HIR "你是打算判师嘛？这很可能遭到严厉惩罚的哦。\n" NOR
                      "如果你下了决心，就再输入一次这条命令。\n");

                set_temp("pending/betrayer", ob, me);
                return 1;
        }

        // If the target is willing to recruit us already, we do it.
        if ((object)query_temp("pending/recruit", ob) == me)
        {
                if (mapp(family) && stringp(family["family_name"]) &&
                    family["family_name"] != ob_family["family_name"])
                {
                        message_vision(
                                "$N决定背叛师门，改投入$n门下！！\n\n"
                                "$N跪了下来向$n恭恭敬敬地磕了四个响头，叫道：「师父！」\n\n",
                                me, ob);
                        set("weiwang", 0, me);
                        addn("betrayer/times", 1, me);
                        delete("quest", me);
                        delete_temp("quest", me);
                        if (stringp(family["family_name"]))
                                addn("betrayer/"+family["family_name"], 1, me);
                } else
                        message_vision(
                                "$N决定拜$n为师。\n\n"
                                "$N跪了下来向$n恭恭敬敬地磕了四个响头，叫道：「师父！」\n\n",
                                me, ob);
                ob->recruit_apprentice(me);
                delete_temp("pending/recruit", ob);

                tell_object(ob, "恭喜你新收了一名弟子！\n");
                printf("恭喜您成为%s的第%s代弟子。\n",
                        query("family/family_name", me),
                        chinese_number(query("family/generation", me)));
                return 1;

        } else
        {
                old_app=query_temp("pending/apprentice", me);
                if (ob == old_app)
                        return notify_fail("你想拜" + ob->name() +
                                           "为师，但是对方还没有答应。\n");
                else
                if (objectp(old_app))
                {
                        write("你改变主意不想拜" + old_app->name() + "为师了。\n");
                        tell_object(old_app, me->name() + "改变主意不想拜你为师了。\n");
                }

                message_vision("$N想要拜$n为师。\n", me, ob);
                set_temp("pending/apprentice", ob, me);
                if (userp(ob))
                {
                        tell_object(ob, YEL "如果你愿意收" + me->name() +
                                    "为弟子，用 recruit 指令。\n" NOR);
                } else
                        ob->attempt_apprentice(me);
                return 1;
        }
}


int help(object me)
{
        write(@HELP
指令格式 : apprentice|bai [cancel]|<对象>

这个指令能让你拜某人为师，如果对方也答应要收你为徒的话，就会
立即行拜师之礼， 否则要等到对方用 recruit 指令收你为弟子才能
正式拜师。

请注意你已经有了师父，又背叛师门投入别人门下，则很有可能导致
原有门派的人的追杀，一旦失手，则所有的特殊武功都将被别人废掉，
基本武功减半。

如果对你的师父使用这个指令，会变成向师父请安。

拜同门的师父不能拜比自己辈分低的或是和自己辈分相同的人。

请参考相关指令 expell、recruit
HELP );
        return 1;
}