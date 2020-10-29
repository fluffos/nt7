// boss_good.h

#define MAX_BUNCH_EXP        5000000000
#define WAIT_TIME 120

void init()
{

        add_action("do_join","join");
        add_action("do_disengage","disengage");
        add_action("do_choose","choose");
        add_action("do_giveup","giveup");
}

int do_join()
{
        string msg, bname;
        object me, ob;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (good_bunch(me))
        {
                bname=query("bunch/bunch_name", me);
                if (bname == bunch_good["bunch_name"])
                {
                        if( query("shen", me)<0 )
                        {
                                message_vision("$N对着$n勃然大怒：我们无极帮都是正义之士，岂能容得了你这种邪恶之徒？\n", ob, me);
                                delete("bunch", me);
                                set("last_leave_bunch", time(), me);
                                msg = "听说" + me->name(1) + "被" + ob->name(1) + "逐出了" + bname;
                                CHANNEL_D->channel_broadcast("rumor", msg);
                                return notify_fail("你被" + ob->name() + "开除出了" + bname + "。\n");
                        }
                        return notify_fail("你已经是我" + bname + "的成员了，昏头了？\n");
                }
                return notify_fail("你现在是" + bname + "的成员，要加入我" + bunch_good["bunch_name"] + "，得先脱离(disengage)原来的帮会。\n");
        }

        if( bad_bunch(me) || query("shen", me)<0 )
        {
                message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n", ob, me);
                command("say " + "我们" + bunch_good["bunch_name"] + "都是正义之士，岂能容得了你这种邪恶之徒？");
                return notify_fail("看来" + ob->name() + "并不欢迎你！\n");
        }

        if( query("combat_exp", me)<100000 )
        {
                command("joke "+query("id", me));
                command("say 这位" + RANK_D->query_respect(me) + "，江湖险恶，您现在这样的身手，还不适合闯荡啊。");
                return notify_fail("看来" + ob->name() + "觉得你的身手太低了点。\n");
        }

        if( query("combat_exp", me) >= MAX_BUNCH_EXP )
        {
                command("joke "+query("id", me));
                command("say 这位" + RANK_D->query_respect(me) + "，您身手已经很不错，应该把志向放的更高远一些了。");
                return notify_fail("看来" + ob->name() + "觉得你身手太高了。\n");
        }

        if( time()-query("last_leave_bunch", me)<300 )
                return notify_fail(ob->name() + "看着你说：听说你是刚脱离了别的帮会过来的吧？我得再观察观察你，过五分钟再来吧！\n");

        set("bunch", bunch_good, me);
        delete("last_leave_bunch", me);
        message_vision("$N单膝跪下，对着$n恭恭敬敬的喊了声：帮主！\n", me, ob);
        message_vision("$N微微一笑，对着$n点了点头，摆手让$n站起身来。\n", ob, me);
        tell_object(me, "恭喜你成为" + bunch_good["bunch_name"] + "的一员！\n");
        msg = "听说" + me->name(1) + "加入了" + bunch_good["bunch_name"]+"。";
        CHANNEL_D->channel_broadcast("rumor", msg);
        return 1;
}

int do_disengage()
{
        string msg;
        object me, ob;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
        {
                command("yi "+query("id", me));
                command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bunch_good["bunch_name"] + "的成员啊！");
                return notify_fail("看来" + ob->name() + "给你搞的满头雾水。\n");
        }

        if( query("bunch/boss", me) != bunch_good["boss"] )
                return notify_fail("想脱离我"+bunch_good["bunch_name"]+"？找你的介绍人"+query("bunch/boss", me)+"去吧。\n");

        delete("bunch", me);
        set("last_leave_bunch", time(), me);

        if( query("shen", me)<0 )
        {
                message_vision("$N对着$n勃然大怒：你怎么这么不争气，我帮中没有你这样的兄弟！\n",ob,me);
                tell_object(me,"你被" + ob->name() + "开除出了" + bunch_good["bunch_name"] + "。\n");
                msg = "听说" + me->name(1) + "被" + ob->name(1) + "逐出了" + bunch_good["bunch_name"]+"。";
                CHANNEL_D->channel_broadcast("rumor", msg);
        } else
        {
                message_vision("$N对着$n叹气道：那好罢，你自己保重！\n",ob,me);
                tell_object(me,"你决定脱离" + bunch_good["bunch_name"] + "。\n");
        }
        return 1;
}

int do_choose(string bh)
{
        string msg;
        mapping bunch_quest;
        object me, obj, ob;

        me = this_player();
        obj = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

       //如果是黑道的，就赶走
        if (bad_bunch(me))
        {
                message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n", obj, me);
                command("say " + "我们" + bunch_good["bunch_name"] + "都是正义之士，岂能容得了你这种邪恶之徒？");
                return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
        }

        //如果不是本帮会的，不给领取任务
        if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
        {
                command("yi "+query("id", me));
                command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bunch_good["bunch_name"] + "的成员啊！");
                return notify_fail("看来" + obj->name() + "给你搞的满头雾水。\n");
        }


        //如果是本帮会，但是变成了-神，那么如果是本人收录的成员，将其开除；否则，将其赶走
        if( query("shen", me)<0 )
        {
                message_vision("$N对着$n勃然大怒：你怎么这么不争气，我帮中没有你这样的兄弟！\n",obj,me);
                if( query("bunch/boss", me) == bunch_good["boss"] )
                {
                        message_vision("$N对着$n怒喝道：留你在我" + bunch_good["bunch_name"] + "岂非叫人笑话！\n",obj,me);
                        delete("bunch_quest", me);
                        delete("bunch", me);
                        set("last_leave_bunch", time(), me);
                        msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bunch_good["bunch_name"];
                        CHANNEL_D->do_channel(this_object(), "rumor", msg);
                        return notify_fail("你被" + obj->name() + "开除出了" + bunch_good["bunch_name"] + "。\n");
                } else
                {
                        message_vision("$N对着$n怒喝：还不给我快滚！\n",obj,me);
                        return notify_fail("你没有从" + obj->name() + "那里领取到任何任务，反而挨了一顿臭骂。\n");
                }
        }

        //如果已经有任务在身，就痛骂一顿
        if( query("bunch_quest", me) )
                return notify_fail(obj->name() + "生气的看着你说：你刚才领的任务还没有完成，急什么？\n");

        if( query("combat_exp", me) >= MAX_BUNCH_EXP )
        {
                command("joke "+query("id", me));
                command("say 这位" + RANK_D->query_respect(me) + "，您身手这么高了，我怎么还好意思让你做这种小事情。");
                return notify_fail("看来" + obj->name() + "觉得你等级太高了。\n");
        }

        //如果没有输入编号，则提示指令
        if (! bh)
               return notify_fail(obj->name() + "奇怪的看着你，你想领取什么任务？指令是：choose <编号>。\n");

        //如果是追杀任务，则不需要领取任务
        if (bh[0..1] == "zs")
                return notify_fail(obj->name() + "微微一笑，既然是追杀令，还用领取任务？赶紧去完成吧！\n");

        //如果是巡城，则看玩家是否加入的本地帮会
        if( bh == "xc" && query("bunch/place", me) != bunch_good["place"] )
                return notify_fail(obj->name() + "对你摆了摆手说：巡城这种事情，我本城的兄弟就可以胜任，不劳你大驾了！\n");

        //如果这个NPC正BUSY，则不给任务
        if (obj->is_busy())
                return notify_fail(obj->name() + "正忙着呢，你稍微等一下。\n");

        //如果这个玩家刚放弃过任务，需要等待
       if( time()-query("last_bunch_quest", me)<query("need_wait_time", me) )
                return notify_fail("完成不了任务，先好好反省一下，然后再来领取任务！\n");

        me->start_busy(1);

        //检查该编号的任务是否存在
        bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE, TYPE, bh);

        if (! bunch_quest)
                return notify_fail(obj->name() + "翻开簿子看了看，对你说：目前没有" + bh + "这个任务。\n");

        //如果是巡城任务，则检查当天是否已经有人在巡城
        if (bunch_quest["id"] == "xc" && ! bunch_quest["enable"])
                return notify_fail(obj->name() + "微微笑着说：今天已经有兄弟去巡城了，你就等改天吧！\n");

        //给任务，并且将该任务从列表中删除
        obj->start_busy(1);
        PARTY_QUEST_D->delete_city_quest(PLACE,TYPE,bh);
        set("bunch_quest", bunch_quest, me);
        message_vision("$N对着$n点了点头：那么这个任务就交给你了，好好去干！\n",obj,me);
        if (bunch_quest["id"] == "xc")
        {
                ob = new("/d/city/npc/obj/yaopai");
                ob->move(me);
                message_vision("$N将一块" + ob->name() + "递给了$n。\n",obj,me);

        }
        tell_object(me,"你接的任务是：\n" + bunch_quest["msg"] + "\n");
        return 1;
}

int do_giveup()
{
        string msg;
        object me, obj;

        me = this_player();
        obj = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (bad_bunch(me))
        {
                message_vision("$N上上下下的仔细打量着$n，脸色越来越难看。\n",obj,me);
                command("say " + "你这种邪派人士的到我这里来干什么？想找茬子？");
                return notify_fail("看来" + obj->name() + "并不欢迎你！\n");
        }

       //如果不是本帮会的，不理会
       if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
       {
               command("yi "+query("id", me));
               command("say 这位" + RANK_D->query_respect(me) + "，你并非我" + bunch_good["bunch_name"] + "的成员啊！");
               return notify_fail("看来" + obj->name() + "给你搞的满头雾水。\n");
       }

       //如果是本帮会，但是变成了-神，那么如果是本人收录的成员，将其开除；否则，将其赶走
       if( query("shen", me)<0 )
       {
               message_vision("$N对着$n勃然大怒：你怎么这么不争气，我帮中没有你这样的兄弟！\n",obj,me);
               if( query("bunch/boss", me) == bunch_good["boss"] )
               {
                       message_vision("$N对着$n怒喝道：留你在我" + bunch_good["bunch_name"] + "岂非叫人笑话！\n",obj,me);
                       delete("bunch_quest", me);
                       delete("bunch", me);
                       set("last_leave_bunch", time(), me);
                       msg = "听说" + me->name(1) + "被" + obj->name(1) + "逐出了" + bunch_good["bunch_name"];
                       CHANNEL_D->channel_broadcast("rumor", msg);
                       return notify_fail("你被" + obj->name() + "开除出了" + bunch_good["bunch_name"] + "。\n");
               } else
               {
                       message_vision("$N对着$n怒喝：还不给我快滚！\n",obj,me);
                       return notify_fail("你被" + obj->name() + "狠狠的痛骂了一番。\n");
               }
       }

       if( !query("bunch_quest", me) )
               return notify_fail(obj->name() + "奇怪的看着你说：你现在并没有任务在身啊，是不是闲的发慌了？\n");

       delete("bunch_quest", me);
       message_vision("$N对着$n一个劲的叹气，似乎不明白为什么$n为何如此的不成材。\n",obj,me);
       tell_object(me,obj->name() + "冲你瞪了一眼：这点小事情都完成不了，一边去好好反省反省！\n");

       //记录放弃时间
       set("last_bunch_quest", time(), me);

       //如果玩家没有连续完成任务的次数记录，则累加该玩家需要等待的时间，最多WAIT_TIME秒，否则，等待3秒
       if( !query_temp("finish_bang_times", me) )
              set("need_wait_time",query("need_wait_time", me)+3, me);
       else set("need_wait_time", 3, me);

       if( query("need_wait_time", me)>WAIT_TIME)set("need_wait_time", WAIT_TIME, me);

       //清除连续完成任务的次数
       delete_temp("finish_bang_times", me);
       return 1;
}
/*
int accept_object(object me,object ob)
{
       int exp,pot,score,weiwang;
       mapping bunch_quest,bonus;
       object who,env;
       string *place;
       string the_place,msg;

       who = this_object();
       if (base_name(ob) != "/d/city/npc/obj/yaopai")
       {
               msg=who->name()+"不屑地把"+query("name", ob)+"抛还给你：什么烂东西也给我？\n";
               tell_object(me,msg);
               return 0;
       }
       if( !query("bunch_quest", me) )
       {
               msg = who->name() + "朝你点了点头，没有说什么话。\n";
               tell_object(me,msg);
               return 1;
       }

       bunch_quest=query("bunch_quest", me);

       if (bunch_quest["id"] != "xc" || bunch_quest["bunch_name"] != "巡扬州城")
       {
               msg = who->name() + "朝你点了点头，没有说什么话。\n";
               tell_object(me,msg);
               return 1;
       }

       place = bunch_quest["place"];

       if (sizeof(place))
       {
               the_place = place[random(sizeof(place))];
               env = get_object(the_place);
               msg = who->name() + "生气的对你说：";
               msg += fail_xc_msg1[random(sizeof(fail_xc_msg1))];
               msg = replace_string(msg,"place",env->short());
               msg += fail_xc_msg2[random(sizeof(fail_xc_msg2))];
               tell_object(me,msg + "\n");
               return 0;
       }

       message_vision("$N高兴的拍了拍$n的肩膀：干的好！\n",who,me);

       addn("pk_score", -2, me);
       if( query("pk_score", me)<0)set("pk_score", 0, me);

       exp = bunch_quest["bonus"];
       pot = exp/(2+random(2));
       weiwang = 5 + random(10);
       score = 5 + random(10);
       delete("bunch_quest", me);
       addn_temp("finish_bang_times", 1, me);
       bonus = ([ "exp" : exp,
                  "pot" : pot,
                  "score" : score,
                  "weiwang" : weiwang,
                  "prompt": "在巡扬州城的过程中，经过锻炼"
               ]);
       QUEST_D->delay_bonus(me, bonus);
       destruct(ob);
       return 1;
}
*/
