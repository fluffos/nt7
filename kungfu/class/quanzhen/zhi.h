// zhi.h 志字辈收徒和推荐给处字辈

int accept_object(object ob, object obj)
{
        object me = this_object();

        mappingmy_fam=query("family", me);
        mappingob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("quanzhenxin2",ob) )
        {
                command("say 怎麽样，你拿我的推荐信去拜师了吗 ?");
                return 0;
        }

        if( (query("id", obj) == "quanzhenling" )
        && ob_fam["family_name"] == "全真教"
        && ob_fam["generation"] == my_fam["generation"] + 1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已有掌门真人许可，我们就来验证一下武功。");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        if( query("id", obj) == "quanzhenxin1" && query_temp("have_letter", ob) )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say好，"+query("name", ob)+"，你愿意拜我为师吗？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say 这东西给我可没有什麽用。");
        command("give"+query("id", obj)+"to"+query("id", me));
        return 0;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

int accept_fight(object ob)
{
        object me  = this_object();

        if( !query_temp("fight_ok", ob))return 0;

        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("fight_ok", ob);

        return 1;
}

int checking(object me, object ob)
{
        object obj;
        int my_max_qi, his_max_qi;

        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if (me->is_fighting())
        {
                call_out("checking",2, me, ob);
                return 1;
        }

        if ( !present(ob, environment()) ) return 1;

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                command("say 青出於蓝胜於蓝，不愧是全真门下弟子！恭喜你了！\n");
                message_vision("$N交给$n一封推荐信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/quanzhen/obj/tuijianxin-2");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看来" + RANK_D->query_respect(ob) +
                        "还得多加练习，方能在本教诸多弟子中出人头地！\n");
                return 1;
        }

        return 1;
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);
        string name, new_name;
        name=query("name", ob);

        if ((int)ob->query_skill("xiantian-qigong",1) < 30 ) {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<1000){
                command( "say 行侠仗义是我辈学武人的基本品质，你若能多做些侠义之事，我一定收你为徒。\n");
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
                                new_name = name[0..0] + "清" + name[2..2];
                                set("name", new_name, ob);
                                command("say 从今以后你的道号叫做"+new_name+ "，你现在是全真教清字辈弟子了。");
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
