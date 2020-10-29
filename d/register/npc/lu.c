// lu

inherit NPC;

void greeting(object me);

void create()
{
        set_name("陆天抒", ({ "lu tianshu", "lu"}));
        set("long", "他一脸正气，眉宇之间乃显侠义雄风。\n");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);

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

        command("hi"+query("id", me));
        command("say 这位" + RANK_D->query_respect(me) +
                "，此处前去，你就能做一个光明磊落的人，想\n"
                "那郭靖、萧峰，皆是我辈中人！");
}

void check_leave(object me, string dir)
{
        if (dir == "out")
        {
                message_vision("$N对$n笑道：去吧！去吧！\n", this_object(), me);
                command("chat 哈哈！江湖上又多了一位光明磊落的人物。");
                set("character", "光明磊落", me);
        } else
        if (dir == "west")
        {
                command("sigh");
                command("say 可惜啊可惜，光明大道岂能不走？");
        }
}