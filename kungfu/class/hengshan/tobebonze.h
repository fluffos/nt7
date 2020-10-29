string ask_for_join()
{
        object me = this_player();
        mapping myfam;

        myfam=query("family", me);
        if (!myfam || (myfam["family_name"] != "恒山派"))
                return ("你和恒山没有渊源，贫尼不敢给你剃度。\n");
        if( query("class", me) == "bonze" )
                return "阿弥陀佛！出家人不打诳语。你已经不是俗家人了。\n";
        if( query("gender", me) != "女性" )
                return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，可去少林寺受戒。\n";
        set_temp("pending/join_bonze", 1, me);
        command("say 阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请跪下(kneel)受戒。\n");
        return "记住，一旦出了家，是不能还俗的，否则将会受到惩罚。\n";
}

int do_kneel()
{
        object me = this_player();

        string name, new_name;
        if( !query_temp("pending/join_bonze", me) )
                return 0;
        message_vision("$N你双手合十，恭恭敬敬地跪了下来。\n\n$n看着$N说道：好吧，你就在本庵修行吧。\n\n$n伸出手掌，在$N头顶轻轻地摩挲了几下，将$N的头发尽数剃去。\n\n", me, this_object() );
        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = "容" + name[0..0];;
        command("say 从今以后你的法名叫做" + new_name + "。");
        command("chat "+name+"削发为尼，在恒山修行，取法名"+new_name+"。");
        command("smile");
        set("marks/old_name", name, me);
        delete_temp("pending/join_bonze", me);
        set("name", new_name, me);
        set("class", "bonze", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}
