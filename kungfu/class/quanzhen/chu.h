// chu.h 处字辈收徒

int accept_object(object ob, object obj)
{
        object me = this_object();

        if( query("id", obj) == "quanzhenxin2" && query_temp("have_letter", ob) )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say好，"+query("name", ob)+"，你愿意拜我为师吗？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say 这东西给我可没有什么用。");
        command("give"+query("id", obj)+"to"+query("id", me));
        return 0;

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);
        string name, new_name;
        name=query("name", ob);

        if ((int)ob->query_skill("xiantian-qigong",1) < 70 ) {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<10000){
                command( "say 行侠仗义是我辈本份，你若能多做些侠义之事，我一定收你为徒。\n");
                return;
        }
        if( query("gender", ob) == "男性" && query("gender", me) == "女性"){
                command("say 我不收男徒，你还是去拜我几位师兄为师吧。\n");
                return;
        }
        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "全真教" )
        {
                command("say 我教为玄门正宗，" + RANK_D->query_respect(ob) + "若要学艺，还是先找本门四代弟子吧。");
                return;
        }
        if ( ob_fam["generation"] == 0 )
        {
                command("say 无量寿佛！你还是先找四代弟子学点基本功吧。");
                return;
        }
        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say "+RANK_D->query_respect(ob)+"，贫道哪里敢当！");
                return;
        }
        if ( ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say 我和"+ob_fam["master_name"]+"抢徒弟，哈哈哈！");
                command("recruit "+query("id", ob));
        }
        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);

                        command("say 是"+ob_fam["master_name"]+"叫你来找我的？好，好。");
                        command("say 贫道看你是可塑之才，你就安心学艺吧！");
                        if( query("class", ob) == "quanzhen" )
                        {
                                new_name = name[0..0] + "志" + name[2..2];
                                set("name", new_name, ob);
                                command("say 从今以后你的道号叫做"+new_name+ "，你现在是全真教志字辈弟子了。");
                        }
                        else command("say 你没有出家，我虽可以收你，以后你可别后悔了。");
                        command("recruit "+query("id", ob));
                }
                else
                {
                        command("say " + RANK_D->query_respect(ob) + "，你没有推荐信，不能越级拜师。");
                        return;
                }
        }
        return;
}
