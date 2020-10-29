// li

inherit NPC;

void greeting(object me);

void create()
{
        set_name("李自成", ({ "li zicheng", "li"}));
        set("long", "他面透煞气，暴戾异常，看得你心里毛毛的。\n");
        set("gender", "男性");
        set("age", 49);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 20);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        remove_call_out("greeting");
        call_out("greeting", 0, me);
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        command("nod"+query("id", me));
        command("say 这位" + RANK_D->query_respect(me) +
                "，哈哈，你来得正好！咱们讲究的就是心狠手辣\n"
                "什么正派人士，全是伪君子，我们要把他们统统杀光！");
}

void check_leave(object me, string dir)
{
        if (dir == "out")
        {
                message_vision("$N对$n狂笑道：上啊！杀光那帮伪君子！\n",
                               this_object(), me);
                command("chat 哈哈！你们这些伪君子小心了！");
                set("character", "心狠手辣", me);
        } else
        if (dir == "south")
        {
                command("heng");
                command("say 胆小鬼！");
        }
}