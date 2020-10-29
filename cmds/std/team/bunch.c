// team command: bunch

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        object env;
        object tob;
        string msg;
        object bei;

        string pure_name, id;

        // 查验队伍的合法性
        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("你现在并不在队伍中啊。\n");

        if (! me->is_team_leader())
                return notify_fail("只有队伍的领袖才能发话，你先闭嘴。\n");

        if (! arg || sscanf(arg, "%s %s", arg, id) != 2)
                return notify_fail("建帮前先想好一个名字以及代表这个名字的英文ID吧！\n");

        if (stringp(msg = BUNCH_D->valid_new_build(me, id, arg)))
                return notify_fail(msg);

        t -= ({ 0 });

        if (sizeof(t) < 5)
                return notify_fail("你这个队伍中现在没有多少人，创建什么帮派？\n");

        if( query_temp("pending/team_doing", me) && 
            query_temp("pending/team_doing", me) != "bunch" )
                return notify_fail("你还是等目前队伍中的提议结束了再说吧。\n");

        // 判断命令的合法性
        if (arg == "cancel")
        {
                if( arrayp(t=query_temp("pending/team_bunch/member", me)) )
                {
                        delete_temp("pending/team_bunch", me);
                        write("你取消和大家创建帮派的念头。\n");
                        t -= ({ 0 });
                        message("vision", YEL + me->name(1) +
                                "取消了大家一同创建帮派的倡议。\n", t, me);
                } else
                        write("你现在并没有倡议大家创建帮派啊！\n");

                delete_temp("pending/team_doing", me);
                return 1;
        }

        if( mapp(query_temp("pending/team_bunch", me)) )
        {
                write("你正倡议大家创建帮派呢！还是等大家回应吧。\n");
                return 1;
        }

        if( query("balance", me)<100000000 )
        {
                write("开帮立会需要很多钱的，你银行中的这点积蓄可不够啊！\n");
                return 1;
        }

        if( query("weiwang", me)<10000 )
        {
                write("你在江湖上无籍籍之名，也来附这风雅？\n");
                return 1;
        } else
        if( query("weiwang", me)<50000 )
        {
                write("你这点名望还不够振臂一呼，聚帮结众，还是以后再说吧。\n");
                return 1;
        } else
        if( query("weiwang", me)<80000 )
        {
                write("你现在在江湖上也算是有些名头了，可惜还是不够。\n");
                return 1;
        } else
        if( query("weiwang", me)<100000 )
        {
                write("你再努力努力提升自己的威望，能"
                      "够创建帮派的日子也不远了。\n");
                return 1;
        }

        // 判断名字的合法性
        pure_name = arg;
        if (strlen(pure_name) > 10)
                return notify_fail("你这个名字太长了。\n");

        if (strlen(pure_name) < 4)
                return notify_fail("你这个名字太短了。\n");

        if (! is_chinese(pure_name))
                return notify_fail("请你用中文起名字。\n");

        if (stringp(msg = BUNCH_D->valid_new_bunch(pure_name)))
                return notify_fail(msg);

        if (strlen(pure_name) != strlen(arg))
                arg += NOR;

        // 判断队伍中所有人的合法性
        env = environment(me);
        foreach (tob in t)
        {
                if (environment(tob) != env)
                        return notify_fail("现在你队伍中的人还没有到齐呢。\n");

                if (! living(tob))
                        return notify_fail("现在你队伍中" + tob->name(1) + "昏迷不醒呢。\n");

                if (! playerp(tob))
                        return notify_fail("你想结义，只怕" + tob->name(1) + "不答应。\n");

                if (tob->is_fighting())
                        return notify_fail("现在你队伍中" + tob->name(1) + "正忙着打架呢。\n");

                if( mapp(query("league", tob)) || mapp(query("bunch", tob)) )
                        return notify_fail("现在你队伍中"+ tob->name(1) + "已经加入别的组织了。\n");

                if( query("weiwang", tob)<10000 )
                        return notify_fail("现在你队伍中" + tob->name(1) + "的江湖威望不够，光你们威望很难振臂一呼，聚帮结众。\n");
        }

        set_temp("pending/team_bunch/member", t, me);

        message_vision("$N大声提议道：“我们众兄弟情"
                       "投意合，今日为何不创建帮派，共创" +
                       "『" + arg + "』”？\n", me);
        set_temp("pending/team_bunch/name", pure_name, me);
        set_temp("pending/team_bunch/id", id, me);
        set_temp("pending/team_bunch/accept", ({me}), me);
        set_temp("pending/team_doing", "bunch", me);
        foreach (tob in t)
        {
                if (tob == me)
                        continue;

                tell_object(tob, YEL + me->name(1) + "(" +
                            query("id", me)+")想让大家一"
                            "同创建帮派，创立『" + arg + "』，"
                            "你是否同意(right/refuse)？\n" + NOR);
                set_temp("pending/answer/"+query("id", me)+"/right",
                              bind((: call_other, __FILE__, "do_right", tob, me :), tob), tob);
                set_temp("pending/answer/"+query("id", me)+"/refuse",
                              bind((: call_other, __FILE__, "do_refuse", tob, me :), tob), tob);
        }

        return 1;
}

int do_right(object me, object ob)
{
        object *t;
        object *r;
        string msg;
        object tob;
        int base, shen;
        string bunch_name, type, id;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已经不在这儿了。\n");

        if (! living(ob))
                return notify_fail("人家现在听不到你说的话，还是算了吧。\n");

        t=query_temp("pending/team_bunch/member", ob);
        if (! arrayp(t))
                return notify_fail("人家现在已经不打算创建帮派了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你现在已经不在人家的创建帮派考虑范围之内了。\n");

        switch (random(8))
        {
        case 0:
                msg = "$N点点头，看了看大家，郑重道：“我没有意见，我同意！”\n";
                break;
        case 1:
                msg = "$N大喜，拍掌大笑道：“正合我意！来！来来！”\n";
                break;
        case 2:
                msg = "$N哈哈大笑，大声道：“很好！很好！真是不错！”\n";
                break;
        case 3:
                msg = "$N只是热泪盈眶，道：“甚好！他日行走江湖，那是何等的威风？”\n";
                break;
        case 4:
                msg = "$N点头颔首，伸出一指点点大家，道：“天下豪杰，尽皆于此，可喜啊！”\n";
                break;
        case 5:
                msg = "$N一声长叹，道：“$l此言极是，道出我心中多年之愿！”\n";
                break;
        case 6:
                msg = "$N环顾四方，豪气顿发，道：“$l之言我谨随无异！”\n";
                break;
        case 7:
                msg = "$N喝道：“早有今日之事，江湖怎会忒多争端？此举甚妙！”\n";
                break;
        default:
                msg = "$N连道：“妙！妙！妙不可言！今日良辰，更待合适？”\n";
                break;
        }
        msg = replace_string(msg, "$l", ob->name(1));
        message_vision(msg, me, ob);

        r=query_temp("pending/team_bunch/accept", ob);
        if (! arrayp(r) || sizeof(r) < 1)
                r = ({ me });
        else
                r += ({ me });

        if (sizeof(t) == sizeof(r) && ! sizeof(t - r) && ! sizeof(r - t))
        {
                string fail = 0;

                // 全部同意，检查是否能够完成的条件，同时计算
                // 帮派的名望。
                base = 10000;
                foreach (tob in t)
                {
                        if (! objectp(tob) || environment(tob) != environment(me))
                        {
                                fail = "虽然大家都同意"
                                       "了，可惜现在有人不在，$N";
                                       "的提议只好作罢。\n";
                                break;
                        }

                        if (! living(tob) || tob->is_fighting())
                        {
                                fail = "虽然大家都同意"
                                       "了，可惜现在有人没法和大"
                                       "家一同创建帮派，$N的提议只好作罢。\n";
                                break;
                        }

                        if( mapp(query("league", tob)) || mapp(query("bunch", tob)) )
                        {
                                fail = "虽然大家都同意"
                                       "了，可惜" + tob->name() +
                                       "已经加入了别的组织了，$N的提议只好作罢。\n";
                                break;
                        }

                        base+=query("weiwang", tob);
                        shen+=query("shen", tob);
                }

                // 失败了，无法结义
                if (stringp(fail))
                {
                        delete_temp("pending/team_bunch", ob);
                        message_vision(fail, ob);
                        return 1;
                }

                // 完成结义
                if (shen < 0)
                        type = "bad";
                else
                        type = "good";

                bunch_name=query_temp("pending/team_bunch/name", ob);
                id=query_temp("pending/team_bunch/id", ob);
                BUNCH_D->create_bunch(bunch_name, id, type, base, t);
                addn("balance", -100000000, ob);
                switch (random(3))
                {
                case 0:
                        msg = "听说" + implode(t->name(1), "、") + "创建『" +
                              bunch_name + "』，纵横江湖。";
                        break;
                case 1:
                        msg = "据闻" + implode(t->name(1), "、") + "创建帮派，" +
                              "组成了『" + bunch_name + "』，震动江湖。";
                        break;
                default:
                        msg = "传说" + implode(t->name(1), "、") + "情投意合，" +
                              "创建帮派，共创『" + bunch_name + "』。";
                        break;
                }

                msg = sort_string(msg, 100, strlen("【泥潭帮派】某人："))[0..<2];
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                delete_temp("pending/team_bunch", ob);
        } else
                set_temp("pending/team_bunch/accept", r, ob);

        return 1;
}

int do_refuse(object me, object ob)
{
        object *t;
        string msg;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已经不在这儿了。\n");

        if (! living(ob))
                return notify_fail("人家现在听不到你说的话，还是算了吧。\n");

        t=query_temp("pending/team_bunch/member", ob);
        if (! arrayp(t))
                return notify_fail("人家现在已经不打算创建帮派了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你现在已经不在人家的创建帮派考虑范围之内了。\n");

        delete_temp("pending/team_bunch", ob);
        message_vision("$N摇了摇头，对$n道：“你们的事情我不管，但是我没有兴趣。”\n",
                       me, ob);
        t -= ({ 0 });
        message("vision", YEL + me->name(1) + "拒绝了" + ob->name(1) +
                "的创建帮派提议。\n" NOR, t, me);
        return 1;
}
