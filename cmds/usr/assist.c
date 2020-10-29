// assist.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        object *team;
        object *assistors;
        mapping q;

        if (! arg)
        {
                if( objectp(ob=query_temp("quest/assist", me)) )
                        write("你现在正帮助" CYN + ob->name(1) +
                              NOR "完成门派的任务。\n");
                else
                        write("你现在并没有帮助任何人完成门派的任务。\n");
                return 1;
        }

        if (arg == "cancel" || arg == "none")
        {
                if( objectp(ob=query_temp("pending/assist", me)) )
                {
                        write("你打消了帮助" + ob->name(1) + "的念头。\n");
                        delete_temp("pending/assist", me);
                        return 1;
                }

                if( !objectp(ob=query_temp("quest/assist", me)) )
                {
                        write("你现在并没有去帮助别人啊！\n");
                        return 1;
                }

                if (environment(ob) == environment(me))
                        message_vision("$N挥了一挥手，对$n道：“我还有"
                                       "事，先不帮你了，改日再见！”\n",
                                       me, ob);

                // 解除帮助状态
                delete_temp("quest/assist", me);
                team = me->query_team();
                if (arrayp(team) && team[0] == ob)
                {
                        // 我在帮助对象的队伍中，自动解除
                        me->dismiss_team();
                        message_vision("$N离开了$n的队伍。\n",
                                       me, ob);
                }
                return 1;
        }

        if( objectp(ob=query_temp("quest/assist", me)) )
        {
                write("你现在不是正打算帮助" + ob->name(1) +
                      "完成任务么？是不是想取消(assist cancel)了？\n");
                return 1;
        }

        // 帮助某人完成任务
        ob = present(arg, environment(me));
        if (! objectp(ob))
        {
                write("你想帮助谁？\n");
                return 1;
        }

        if( !stringp(query("family/family_name", ob)) || 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                write("你和" + ob->name() + "并不是同一个门派"
                      "的呀，看来这份好意只能让对方心领了。\n");
                return 1;
        }

        if (! living(ob))
        {
                write("看来" + ob->name() + "现在没法接受你得好意了。\n");
                return 1;
        }

        if( ob == query_temp("pending/assist", me) )
        {
                write("你想帮助" + ob->name(1) + "，可是人家还没有答应你呢。\n");
                return 1;
        }

        if( query("quest", me) )
        {
                write("你现在正有任务在身，还是先忙完自己的"
                      "事情再说吧！\n");
                return 1;
        }

        write("你决定开始帮助" + ob->name(1) + "完成任务。\n");
        message_vision("$N对$n道：“" + ob->name() +
                       "，我和你一起去吧！”\n", me, ob);
        set_temp("pending/assist", ob, me);
        if (! playerp(ob))
        {
                message_vision("$n对$N说：“我还有别的事情哦，"
                               "不用你帮忙啦！”\n", me, ob);
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + YEL "决定帮助你一"
                    "同完成任务，你是否同意(right|refuse " +
                    query("id", me)+")？\n"NOR);

        ob->set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
        ob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));

        return 1;
}

// 允诺对方加入
int do_right(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // 对方还没有说愿意你帮助你呢
                write(ob->name() + "现在没打算帮助你呀，你还是再问问吧！\n");
                return 1;
        }

        delete_temp("pending/assist", ob);

        // 对方愿意你帮助你
        message_vision("$N爽快的对$n说：“好吧！多谢了！”\n",
                       me, ob);
        tell_object(ob, me->name(1) + "愿意接受你的帮助。\n");
        set_temp("quest/assist", me, ob);

        if (! pointerp(me->query_team()) || me->is_team_leader())
        {
                if (sizeof(me->query_team()) >= 12)
                {
                        write("你这个队伍中的人太多了，没法邀请" +
                              ob->name(1) + "加入，这样让他帮助"
                              "就不方便了。\n");
                        return 1;
                }

                // 我不在队伍中或是我就是队伍的领袖，则让帮手加入队伍
                if (pointerp(ob_team = ob->query_team()))
                {
                        // 帮手也在一个队伍中，看看是哪个队伍
                        if (ob_team[0] == me)
                                // 帮手已经在我的队伍中了
                                return 1;

                        // 帮手在其它队伍中，先退出来
                        ob->dismiss_team();
                }

                // 帮手加入我的队伍
                me->add_team_member(ob);
                message_vision("$n加入了$N的队伍，一同行走江湖。\n",
                               me, ob);
        } else
                tell_object(me, "让" + ob->name() + "帮助你最"
                            "好是和你在一个队伍中，如果可以的"
                            "话，就邀请对方组队吧！\n");

        return 1;
}

// 拒绝对方加入
int do_refuse(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // 对方还没有说愿意你帮助你呢，你干什么呢？
                write(ob->name() + "现在没打算帮助你呀，你拒绝什么？\n");
                return 1;
        }

        delete_temp("pending/assist", ob);
        message_vision("$N摇摇头，对道：“你的好意我心领了，"
                       "不过现在还不需要劳动大驾。”\n", me, ob);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : assist <玩家ID>

这个指令表示你想帮助另一个人一同完成掌门或是世家长老分配给他
的杀人任务。当然你必须和他是同门，而且你当时没有任务。如果对
方同意接受你的帮助，那么你会自动加入到对方的队伍中（除非对方
在另外一个队伍中并且不是队长）。
HELP );
        return 1;
}