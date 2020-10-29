// fight.h
// 丐帮升袋

void attempt_apprentice(object ob)
{
        if( query("detach/丐帮", ob) || query("betrayer/丐帮", ob) )
        {
                command("say 嘿嘿，你当初走的时候是怎么说的？");
                return;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 我们丐帮行事堂堂正正，绝不接纳判师之徒。");
                return;
        }

        if( query("family/family_name", ob )
            && query("family/family_name", ob) != "丐帮" )
        {
                command("say 你既然已经有了名师指点，还来我们丐帮干什么？");
                return;
        }
        command("say 你去找本帮长老吧，我不收徒。");
}

int accept_object(object ob, object obj)
{
        object me = this_object();

//      mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query("id", obj) != "qingzhu ling" )
        {
                command("say 啥玩艺？还是自个留着吧。");
                return 0;
        }

        if (! ob_fam || ob_fam["family_name"] != "丐帮")
        {
                command("say 你是从哪里搞来的青竹令？");
                return 0;
        }

        if( query("combat_exp", ob)<10000 )
        {
                command("say 你这种水平简长老怎么会给你青竹令？");
                return 0;
        }

        if( query_temp("have_cloth", ob) && present("pobu",ob) )
        {
                command("say 你不是已经有破布么？回去找简长老吧。");
                return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("combat_exp", ob) <= 10000 )
            || (query("family/beggarlvl", ob) == 1
            && query("combat_exp", ob) <= 20000 )
            || (query("family/beggarlvl", ob) == 2
            && query("combat_exp", ob) <= 50000 )
            || (query("family/beggarlvl", ob) == 3
            && query("combat_exp", ob) <= 100000 )
            || (query("family/beggarlvl", ob) == 4
            && query("combat_exp", ob) <= 200000 )
            || (query("family/beggarlvl", ob) == 5
            && query("combat_exp", ob) <= 300000 )
            || (query("family/beggarlvl", ob) == 6
            && query("combat_exp", ob) <= 500000 )
            || (query("family/beggarlvl", ob) >= 7
            && query("combat_exp", ob) <= 800000) )
        {
             command("say 就你那点脓水？我看就算了吧。");
             return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("title", me) == "丐帮一袋弟子" )
            || (query("family/beggarlvl", ob) == 1
            && query("title", me) == "丐帮二袋弟子" )
            || (query("family/beggarlvl", ob) == 2
            && query("title", me) == "丐帮三袋弟子" )
            || (query("family/beggarlvl", ob) == 3
            && query("title", me) == "丐帮四袋弟子" )
            || (query("family/beggarlvl", ob) == 4
            && query("title", me) == "丐帮五袋弟子" )
            || (query("family/beggarlvl", ob) == 5
            && query("title", me) == "丐帮六袋弟子" )
            || (query("family/beggarlvl", ob) == 6
            && query("title", me) == "丐帮七袋弟子" )
            || (query("family/beggarlvl", ob) == 7
            && query("title", me) == "丐帮八袋弟子" )
            || (query("family/beggarlvl", ob) == 8
            && query("title", me) == "丐帮九袋长老") )
        {
                set_temp("fight_ok",query("id",  me), ob);
                command("say 好吧。既然已有青竹令，那就看你的运气了。");
                destruct(obj);
                return 1;
        }

        command("hmm");
        command("say 你到底懂不懂我们丐帮升袋的规矩？");
        return 0;
}

int accept_fight(object ob)
{
        if (query_competitor() == ob)
                return 1;

        if (is_fighting())
        {
                command("say 你等会，让我把面前的这个家伙放倒再说。");
                return 0;
        }

        if (query("qi") < query("eff_qi") * 2 / 3
           || query("jing") < query("eff_jing") * 2 / 3
           || query("neili") < query("max_neili") * 2 / 3)
        {
                command("say 我现在有点疲倦，待我歇会儿再说。");
                return 0;
        }

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say 免了，我可没兴趣和你动手。");
                return 0;
        }

        if( query_temp("fight_ok", ob) != query("id") )
        {
                command("say 你去向简长老要了青竹令再来找我。");
                return 0;
        }

        delete_temp("fight_ok", ob);

        command("nod");
        command("say 就让我试一试你的身手，看看你究竟有啥水平？");
        competition_with(ob);
        return 1;
}

void lost()
{
        object me, ob;

        me = query_competitor();
        set_temp("newtitle", query("title"), me);
        set_temp("have_cloth", 1, me);

        ob = new("/d/gaibang/npc/obj/po-bu");
        set("owner", me->name(1), ob);
        set("from", this_object()->name(1), ob);
        ob->move(this_object());

        command("say 厉害，厉害。既然你胜过了我，这块破布就拿去吧。");
        command("give po bu to "+query("id", me));
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        command("say 就你这点水平也想升袋？下去练练再来吧。");
        ::win();
}
