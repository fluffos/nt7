// xiaozei.c

inherit NPC;

void create()
{
        set_name("小贼", ({ "xiao zei","xiao","zei" }) );
        set("gender", "男性" );
        set("age", 15);
        set("long", "一个笑嘻嘻看着你的小孩。\n");

        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);

        set("max_qi", 500);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);
        set("shen_type", 0);

        set_temp("apply/attack",  20);
        set_temp("apply/defense", 20);
        set_temp("apply/damage",  20);

        set("combat_exp", 20000);
        set("str", 27);
        set("kar", 100);
        set("thief", 0);
        set("force", 200);

        set("max_force", 200);
        set("force_factor", 2);

        set_skill("unarmed", 50);
        set_skill("sword", 50);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("stealing", 100);
        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "小贼说道: 好心的大爷哪～ 赏我要饭的几个铜板吧～\n",
                "小贼懒洋洋地打了个哈欠。\n",
                "小贼伸手捉住了身上的虱子，骂道: 小爷身上没几两肉，叫你们还咬! \n",
                (: random_move :)
        }) );
        carry_object("/clone/food/jitui");
        carry_object("/clone/food/jiudai");
        add_money("silver", 10);
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) ) {
                remove_call_out("stealing");
                call_out("stealing", 1, ob);
        }
}

void stealing(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( ob->present("gold_money")) command("hi");
        switch( random(5) )
        {
                case 0:
                       command("hehe"+query("id", ob));
                       command("stealcoinfrom"+query("id", ob));
                       command("buy jitui");
                       break;
                case 1:
                       command("grin"+query("id", ob));
                       command("stealsilverfrom"+query("id", ob));
                       command("eat jitui");
                       break;
                case 2:
                       command("hi"+query("id", ob));
                       command("stealgoldfrom"+query("id", ob));
                       command("drink jiudai");
                       break;
                case 3:
                       command("pat"+query("id", ob));
                       command("stealchangjianfrom"+query("id", ob));
                       command("wield changjian");        
                       command("drink jiudai");
                       break;
                case 4:
                       command("walkby"+query("id", ob));
                       command("stealjituifrom"+query("id", ob));
                       command("eat jitui");
                       break;
        }
}


int accept_object(object me, object obj)
{
        if( query("money_id", obj) && obj->value() >= 1){
                command("smile");
                command("say 多谢啦 ! 其实我还是有点钱的，这次只不过试试你罢了 !");
                command("give10silverto"+query("id", me));
        }
        else {
                command("shake");
                command("say 这种东西鬼才要 ! 滚一边去 !");
                command("give"+query("id", obj)+"to"+query("id", me));
//                obj->move(this_player());
        }
        return 1;
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "饶命ⅵ小的这就离开ⅵ\n");
        return 0;
}