#include <ansi.h>
inherit KNOWER;

inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("武敦儒", ({ "wu dunru", "wu", "dunru" }));
        set("title", HIY "郭靖大弟子" NOR);
        set("gender", "男性");
        set("age", 23);
        set("long", "他是郭靖大弟子，相貌和蔼，一天到晚笑呵呵的。\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 24);
        set("str", 20);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 2500);
        set("neili", 2800);
        set("max_neili", 2800);
        set("jiali", 50);
        set("combat_exp", 400000);
        set("score", 20000);
         
        set_skill("force", 160);
        set_skill("yijin-duangu", 160);
        set_skill("dodge", 160);
        set_skill("shexing-lifan", 160);
        set_skill("finger", 160);
        set_skill("sun-finger", 160);
        set_skill("sword", 160);
        set_skill("yuenv-jian", 160);
        set_skill("parry", 160);
        set_skill("literate", 140);
        set_skill("jingluo-xue", 160);
        set_skill("martial-cognize", 140);

        map_skill("force", "yijin-duangu");
        map_skill("dodge", "shexing-lifan");
        map_skill("finger", "sun-finger");
        map_skill("sword", "yuenv-jian");
        map_skill("parry", "jinyuan-gun");

        prepare_skill("finger", "sun-finger");

        create_family("郭府", 2, "弟子");

        set("inquiry", ([
                "黄蓉" : "那是我师母。",
                "郭靖" : "那是我师父。",
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/wuguan/guofu_dating",
                   "id"        : "guo jing", ]),
        }));

        set("guarder", ([
                "refuse_carry": CYN "$N" CYN "对$n" CYN "喝道：你背上"
                                "背的是什么人？还不给我放下来。\n" NOR,
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qian" :),
                (: perform_action, "finger.dian" :),
                (: perform_action, "dodge.gui" :),
                (: perform_action, "powerup" :),
                (: exert_function, "recover" :),
        }));

        setup();
        if (clonep()) keep_heart_beat();
        carry_object("/clone/misc/cloth")->wear();
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom"))
           && find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character()
                           || interactive(ob)
                           || playerp(ob)
                            || query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob) )
                           && find_object(start_room) == environment())
                                continue;

                        if( query("id", ob) == "guojing"
                           || base_name(ob) == CORPSE_OB)
                                continue;

                        message_vision(CYN "$N" CYN "环顾四周，摇了摇头，转身"
                                       "向南离去。\n" NOR, ob);
                        ob->move("/d/xiangyang/westjie1");
                }
        }
        ::heart_beat();
}

void init()
{
        object ob;
        int exp, pot, sc;

        ::init();

        exp = 3000 + random(500);
        pot = 1000 + random(100);
        sc = 50 + random(30);

        if (interactive(ob = this_player())
           && ! is_fighting())
	{
        	if (! ob || environment(ob) != environment())
			return;

        	if( query("combat_exp", ob)<5000
           	 && !query("mark/guofu_ok", ob )
           	 && !query("mark/guofu_over", ob )
           	 && !query("mark/guofu_out", ob) )
		{
        		command("say 这位" + RANK_D->query_respect(ob) +
                        	"，武功这么差，怎么闯江湖呢？\n");
        		command("whisper"+query("id", ob)+"现在正"
                        	"值兵荒马乱，这里正遭蒙\n古人的围攻，你"
                        	"还是别乱走动的好。我们郭府内正缺少人手"
                        	"打\n杂，你若有兴趣倒是可以进来 (" HIY
                        	"join 郭府" NOR + WHT ")帮帮忙，顺便学"
                        	"点\n基本功夫防身。不知" + RANK_D->query_respect(ob) +
                        	"意下如何？\n");
		} else
        	if( query("combat_exp", ob) >= 20000
           	 && query("mark/guofu_ok", ob) )
		{
        		command("look"+query("id", ob));
        		command("haha");
        		command("whisper"+query("id", ob)+"不错，"
                                "不错。想不到你的进展如\n此神速，再留在"
                                "郭府已无多大用处，今后还是多去闯荡闯荡吧。\n");

delete("mark/guofu_ok", 			ob);
set("mark/guofu_out", 1, 			ob);

addn("combat_exp", exp, 	ob);
        addn("potential", pot, 	ob);
                addn("score", sc, 	ob);
                        tell_object(ob, HIC "通过在郭府内的锻炼，你获得"
                                        "了" + chinese_number(exp) + "点"
                                        "经验、" + chinese_number(pot) +
                                        "点潜能\n以及" + chinese_number(sc)
                                        + "点江湖阅历，武技得到了提升。"
                                        "\n\n" NOR);
		} else
        	if( query("mark/guofu_over", ob) )
		{
        		command("sneer"+query("id", ob));
		} else
        	if( query("mark/guofu_out", ob) )
		{
        		command("nod"+query("id", ob));
		} else
        	if( query("combat_exp", ob)>20000
           	 && !query("mark/guofu_ok", ob )
           	 && !query("mark/guofu_over", ob )
           	 && !query("mark/guofu_out", ob) )
		{
        		command("hi"+query("id", ob));
        		command("say 现襄阳正值动乱时期，不及招呼，还请恕罪。");
		} else
        	if( query("combat_exp", ob)<20000
           	 && query("mark/guofu_ok", ob) )
		{
        		command("look"+query("id", ob));
        		command("hmm");
        		command("say 赶快干活去，没事瞎溜达什么？");
		}
        }
        add_action("do_join", "join");
        add_action("do_kill", "hit");
        add_action("do_kill", "kill");
        add_action("do_kill", "touxi");
        add_action("do_kill", "fight");
        add_action("do_yun", "yun");
        add_action("do_yun", "exert");
}

int do_yun(string arg)
{
        object ob = this_object();

        if (arg == "roar")
        {
                message_vision(CYN "\n武敦儒喝道：什么人？郭府门"
                               "前可由不得你嚣张！\n" NOR, ob);
                return 1;
        }
        return 0;
}

int do_kill(string arg)
{
        object ob = this_object();

        if (arg != "wu dunru"
           && arg != "wu"
           && arg != "dunru" )
        {
                message_vision(CYN "\n武敦儒喝道：什么人？郭府门"
                               "前可由不得你放肆！\n" NOR, ob);
                return 1;
        }
        return 0;
}

int do_join(string arg)
{
        object ob = this_player();

        if (! arg
           && arg != "guofu"
           && arg != "郭府")
                return notify_fail(CYN "武敦儒眉头一皱，道：你到"
                                   "底要干什么？怎么说话吞吞吐吐"
                                   "的？\n" NOR);

	if( query("mark/guofu_over", ob) )
                return notify_fail(CYN "武敦儒冷笑道：师父让你走"
                                   "开，你还赖在这里干嘛？\n" NOR);

	if( query("mark/guofu_ok", ob) )
                return notify_fail(CYN "武敦儒皱眉道：你不是已经"
                                   "进来了吗？赶快干活去，罗嗦什"
                                   "么？\n" NOR);

	if( query("mark/guofu_out", ob) )
                return notify_fail(CYN "武敦儒微笑道：你现在的武"
                                   "功已经有一定的底子了，还是多"
                                   "闯荡闯荡吧。\n" NOR);

        if( query("combat_exp", ob)>5000 )
                return notify_fail(CYN "武敦儒微笑道：让你来打杂"
                                   "可太委屈你了，你还是另谋出路"
                                   "吧。\n" NOR);

	if( query_temp("mark/guofu_join", ob) )
	{
        	message_vision(HIC "\n$N" HIC "对$n" HIC "点了点"
                               "头，说道：甚好，甚好。入了郭府一"
                               "切就要\n按规矩办事，你现在去耶律"
                               "帮主那里，他会帮你安排事情的。\n"
                               "\n", this_object(), ob);
set("mark/guofu_ok", 1, 		ob);
                set("startroom", "/d/wuguan/guofu_dayuan", ob);
delete_temp("mark/guofu_join", 		ob);
	} else
	{
        	command("nod");
        	command("whisper"+query("id", ob)+"你进郭"
                        "府之后我们会确保你的安\n全，但是经验在"
                        HIW "两万" NOR + WHT "前不能离开郭府。如"
                        "果你决定下来了，请\n再输入一次此命令。"
                        "\n" NOR);
set_temp("mark/guofu_join", 1, 		ob);
	}
        return 1;
}

int accept_fight(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say 给我滚进去，跑到这里来瞎胡闹什么！");
        	return 0;
	} else
	{
	        command("say 我现在没空。\n");
        	return 0;
	}
}

int accept_hit(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say 给我滚进去，跑到这里来瞎胡闹什么！");
        	return 0;
	} else
	{
	        command("say 找死。\n");
        	kill_ob(ob);
        	return 1;
	}
}

int accept_kill(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say 给我滚进去，跑到这里来瞎胡闹什么！");
                return notify_fail("你还是不要轻举妄动为好。\n");
	} else
	{
	        command("say 找死。\n");
        	kill_ob(ob);
        	return 1;
	}
}

int accept_touxi(object who)
{
        object ob = this_player();

	if( query("mark/guofu_ok", ob) )
	{
        	command("say 给我滚进去，跑到这里来瞎胡闹什么！");
                return notify_fail("你还是不要轻举妄动为好。\n");

	} else
	{
	        command("say 找死。\n");
        	kill_ob(ob);
        	return 1;
	}
}

void recover()
{
        mapping p;

        clear_condition(0);
        p = query_entire_dbase();
        p["eff_qi"] = p["max_qi"];
        p["qi" ] = p["max_qi"];
        p["eff_jing"] = p["max_jing"];
        p["jing" ] = p["max_jing"];
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}

void unconcious()
{
        die();
}

void die()
{
        message_vision(HIW "\n$N" HIW "深深吸了几口气，脸色看起来"
                       "好多了。\n" NOR, this_object());
        recover();
}