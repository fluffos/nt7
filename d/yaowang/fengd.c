inherit ROOM;

protected int nut = 3;
protected string ll = "这里是一片低矮的灌木丛，空气中有一种淡淡的幽香，身临
空谷，闻着淡淡的芬芳之气，让人心旷神怡。";

string query_long();
string query_item_desc();

string query_long()
{
        if(nut <= 0)
                return ll+"\n";
        return ll+"丛中还结着几颗棕\n色的[小果子]。\n";
}

string query_item_desc()
{
        if(nut > 0)
                return "这是一颗小指甲盖大的棕色果子，可爱
的样子只想让人摘(pick)下来看看。\n";

        return 0;
}

void reset()
{
        if(nut < 3)
                nut = 3;
        ::reset();
}

void init()
{
        add_action("do_pick", "pick");
}

int do_pick(string arg)
{
        object ob, me = this_player();
        mapping q;

        if(arg != "果子" && arg != "小果子")
                return notify_fail("你要摘什么？\n");

        if(nut <= 0)
                return notify_fail(sprintf("这里没有%s。\n", arg));

        if( !mapp(q=query("quest/yaowang_quest", me)) || (q["name"] != "海松子") || q["get_nut"] )
                return notify_fail("你没小心被灌木上的小刺扎了一下，疼得赶紧缩回了手。\n");

        nut--;
        message_vision("$N小心翼翼的摘下了一颗小果子。\n", me);

        ob = new(__DIR__"obj/nut");

        if(!ob->move(me) && !ob->move(this_object()))
                destruct(ob);

        q["get_nut"] = 1;
        return 1;
}
