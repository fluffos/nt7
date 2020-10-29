// shanzheng.c 单正

#include <ansi.h>
#include <quest.h>

inherit NPC;

void create()
{
        set_name("单正", ({ "shan zheng", "shan" }));

        set("gender", "男性");
        set("age", 62);
        set("long", "他体态魁梧，相貌威严，长的一副童颜鹤发。\n");
        set("attitude", "peaceful");
        
        set("nickname", HIR "铁面判官" NOR);

        set("str", 35);
        set("int", 36);
        set("con", 31);
        set("dex", 30);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.duan" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "铁面判官" : "这是江湖好友给在下的称号，见笑了。",
                "单正" : "没错，就是我了，怎么，找我有事？",
                "审案" : "哪里的案子？",
                "判案" : "哪里的案子？",
        ]));

        set("shen_type", 1);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 50);

        set("combat_exp", 800000);
        set("score", 5000000);

        set_skill("force", 150);
        set_skill("huntian-qigong", 150);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 150);
        set_skill("blade", 150);
        set_skill("unarmed", 150);
        set_skill("taiji-quan", 150);
        set_skill("wuhu-duanmendao", 150);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 80);
        set_temp("apply/unarmed_damage", 80);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

varargs int move(mixed dest, int raw)
{
        int r;

        // 执行原本的MOVE函数
        r = ::move(dest, raw);

        if (objectp(query_temp("run_ob")))
        {
                // 正在执行任务，察看是否到了地点
                remove_call_out("give_intercession");
                call_out("give_intercession", 2);
        }

        return r;
}

mixed accept_ask(object who, string topic)
{
        object *obs;
        object follow;
        object run_ob;

        obs = filter_array(children("/clone/quest/judge"),
                           (: $1->name() == $(topic) :));
        if (sizeof(obs) > 0)
        {
                if( query("weiwang", who)<5000 )
                        return "你算哪一号人物，居然也管起江湖上的事情来了？";

                follow = query_leader();
                if (objectp(follow) && environment(follow) == environment())
                {
                        // 正在跟随另外一个人，察看当前执行
                        // 的任务。
                        run_ob = query_temp("run_ob");

                        if (follow == who)
                        {
                                // 跟随的就是目前发问的人
                                if (! objectp(run_ob))
                                {
                                        // 由于原先的事情取消了，所以
                                        // 可以更换一件事情
                                        set_temp("run_ob", obs[0]);

                                        // 取消返回或是调解的定时呼叫
                                        remove_call_out("do_back");
                                        remove_call_out("give_intersession");

                                        // 四分钟以后解除跟随状态
                                        remove_call_out("cancel_follow");
                                        call_out("cancel_follow", 240);
                                        return "好吧，刚才那件事情听说也了了，咱们就换换吧！";
                                }

                                // 跟随的就是发话的人
                                return "咱们快走吧！不是要办" +
                                       run_ob->name() + "么？别磨蹭了。";
                        }

                        if (run_ob == obs[0])
                                // 其他人询问相同的事情
                                return "我现在正是和" + follow->name() +
                                       "去办这件事的，不劳你费心了。";

                        if (objectp(run_ob))
                                // 其他人询问不同的事情
                                return "我现在要和" + follow->name() +
                                       "去办" + run_ob->name() + "，你先等等吧。";

                        message_vision("$N回头对$n道：“我听说你那件事情"
                                       "已经了了，我先走了。”\n",
                                       this_object(), follow);
                }

                // 我现在没有跟谁人
                message_vision("$N点点头，对$n道：“这事我也"
                               "略有耳闻，就和你走一趟吧！”\n",
                               this_object(), who);
                set_temp("run_ob", obs[0]);
                command("follow"+query("id", who));

                // 取消返回或是调解的定时呼叫
                remove_call_out("do_back");
                remove_call_out("give_intersession");

                // 四分钟以后解除跟随状态
                remove_call_out("cancel_follow");
                call_out("cancel_follow", 240);
                return 1;
        }

        switch (random(3))
        {
        case 0:
                return "要是听说哪儿有不公之事，尽可以告诉我，"
                       "不过你说的这个我实在不太清楚。";
        case 1:
                return RANK_D->query_respect(who) + "，你说的"
                       "这个事我不太清楚啊。";
        default:
                return "我只帮人断案排忧，你说的这个究竟是啥事情？";
        }
}

// 判断是否有人需要调解
void give_intercession()
{
        object run_ob;
        object npc1;
        object npc2;
        object me;
        int npc1_present, npc2_present;
        int percent;

        if (! objectp(run_ob = query_temp("run_ob")))
                // 现在没有调解任务
                return;

        npc1=query("npc1", run_ob);
        npc2=query("npc2", run_ob);
        npc1_present =  (objectp(npc1) && environment(npc1) == environment());
        npc2_present =  (objectp(npc2) && environment(npc2) == environment());
                
        if (! npc1_present || ! npc2_present)
                // 这个场景没有需要调解的人
                return;

        if (! npc1_present)
        {
                // 只有NPC2
                message_vision("$N看了看四周，摇头道：“只有" +
                               npc2->name() +"一个人了，还调"
                               "解什么？我还是走吧！”\n", this_object());
                set_leader(0);
                call_out("do_back", 1);
                return;
        }

        if (! npc2_present)
        {
                // 只有NPC1
                message_vision("$N看了看四周，摇头道：“只有" +
                               npc1->name() +"一个人了，还调"
                               "解什么？我还是走吧！”\n", this_object());
                set_leader(0);
                call_out("do_back", 1);
                return;
        }

        me = query_leader();
        message("vision", sort_msg(name() + "看了看" + npc1->name() +
                "和" + npc2->name() + "，摇摇头，喝道：“大家"
                "都是武林人士，何苦为了一些小事争执不休？没得"
                "失了颜面！”\n"), environment());
        message("vision", HIG + name() + HIG "开始劝说调解二人，听"
                "得两人连连点头，不敢放肆。\n" NOR, environment());
        if (objectp(me))
        {
                tell_object(me, CYN "你听了" + name() + CYN
                            "调解二人的话语，甚是得理，眼见"
                            "二人心服口服，不由得暗自欣慰。\n" NOR);
                CHANNEL_D->do_channel(find_object(QUEST_D), "task",
                        "听说"+me->name(1)+"("+query("id", me)+
                        ")请到铁面判官" + name() + WHT "为" +
                        npc1->name() + WHT "和" + npc2->name() +
                        WHT "成功的调解了纠纷。");
                percent=30000*100/(random(query("weiwang", me)+1)+30000);
                QUEST_D->bonus(me, ([ "exp" : 100 + random(100),
                                      "pot" : 30 + random(50),
                                      "score" : 10 + random(10),
                                      "weiwang" : 10 + random(20),
                                      "percent" : percent,
                                      "prompt" : "通过这次为人调解纠纷" ]));

                if( query("quest/freequest", me)>0 )
                        GIFT_D->delay_freequest_bonus(me);
        }

        delete_temp("run_ob");
        set_leader(0);
        run_ob->change_status(QUEST_FINISH);
        remove_call_out("cancel_follow");
        call_out("do_back", 2);
}

// 停止跟踪
void cancel_follow()
{
        object ob;

        // 去掉正在做的任务信息
        delete_temp("run_ob");

        // 现在没有领路的？直接返回
        if (! objectp(ob = query_leader()))
        {
                call_out("do_back", 1);
                return;
        }

        // 不再跟随
        set_leader(0);
        message_vision("$N叹道：“我看你也是迷迷糊糊的，算"
                       "了，我还是先走了吧！以后有事再说！”\n",
                       this_object());
        call_out("do_back", 1);
}

// 返回
void do_back()
{
        string startroom;

        if (! stringp(startroom = query("startroom")))
                return;

        if (! living(this_object()))
        {
                call_out("do_back", 10);
                return;
        }

        if (is_fighting())
        {
                message_vision("$N忽然罢手，道：“老夫不能奉陪了，走了！”\n"
                               "话音刚落，$N就急急忙忙的走了，你不由的一愣神。\n",
                               this_object());
        } else
                message_vision("$N叹了口气，头也不回的走了。\n",
                               this_object());

        // 返回故地
        move(startroom);
        message("vision", name() + "赶了过来。\n", environment());
}

void unconcious()
{
        message_vision("$N大叫一声：“气杀我也！”\n", this_object());
        die();
}

int return_home(object home)
{
        if (objectp(query_leader()))
                return 0;

        return ::return_home(home);
}
