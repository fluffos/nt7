void init()
{
        add_action("do_kneel", "kneel");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( query("class", me) == "bonze" )
                return "你已经是出家人了，还跟我罗嗦些什么？";

        if( query("gender", me) != "男性" )
                return "我们雪山寺历来只收男徒，你还是走吧。";

        set_temp("pending/join_bonze", 1, me);

        return "甚好，甚好！你若真心皈依我佛，请跪下(kneel)受戒。";
}

int do_kneel()
{
        object me = this_player();

        if( !query_temp("pending/join_bonze", me) )
                return 0;

        message_vision(HIC "\n$N" HIC "你双手合十，恭恭敬敬地跪了下来。\n\n"
                       NOR + CYN "$n" CYN "看着$N" CYN "说道：好吧，以后你就"
                       "在本寺修行吧。\n\n" HIY "$n" HIY "伸出手掌，在$N" HIY
                       "头顶轻轻地摩挲了几下，随即便将$N" HIY "的头发尽数剃"
                       "去。\n\n" NOR, me, this_object());

        set("class", "bonze", me);
        set("title", "雪山寺喇嘛", me);

        command("nod");
        command("say 既然出了家，就得一心向佛，再不能还俗。");

        return 1;
}
