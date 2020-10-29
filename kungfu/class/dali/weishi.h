// weishi.h 升级到卫士, 拜师
int ask_me()
{
        object ob, me;
        me = this_object();
        ob = this_player();
        if ((int)ob->query_skill("kurong-changong",1) < 60)
        {
                command("say 你想当卫士，再练几年功吧。\n");
                return 1;
        }
        
        if( query("guard", ob) == "镇南王府家臣" )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然如此想切磋，那就看你的本事如何了。\n");
                return 1;
        }
        else
        {
                command("say 只有家臣才能升卫士。\n");
                return 1;
        }
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
                command("say 青出於蓝胜於蓝，不愧是大理段家的好弟子！恭喜你了！\n");
                command("say 你的已经可以胜任大理卫士！\n");
                upgrade_title(ob, "镇南王府卫士");
                return 1;
        }
        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看来" + RANK_D->query_respect(ob) + 
                        "还得多加练习，方能在大理段家诸多弟子中出人头地！\n");
                return 1;
        }
        return 1;  
}
void upgrade_title(object ob,string arg)
{
//        string title;
//        title=arg+clear_title(ob->query("title"));
        set("guard", arg, ob);
}
/*
string clear_title(string arg)
{
        if (strsrch(arg, "大理镇南王府家臣") >= 0)
        {
                arg = replace_string(arg, "大理镇南王府家臣","");
        }
        return arg;
}
*/
void attempt_apprentice(object ob)
{
        if( (query("guard", ob) != "镇南王府家奴") && 
            (query("family/family_name", ob) != "大理段家") )
        {
                command("shake"+query("id", this_player()));
                command("say 我早已投身大理为臣，不再涉足江湖俗务，不能收徒了。\n");
                return;
        }
        if( query("shen", ob)<0 )
        {
                command("say 我大理段氏向来不与您这种黑道人物打交道，您请回吧！");
                return;
        }
        if( query("combat_exp", ob)>10000 || query("age", ob)>17 )
        {
                command("say 镇南王府收了大侠您，也让你太屈尊了吧！");
                return;
        }
        command("say 很好，很好。既已入府，便当尽忠报主，这条性命也就不是自己的了。\n");
        command("recruit "+query("id", ob));
        if( query("gender", ob) == "男性" )
                set("guard", "镇南王府家丁", ob);
        else
                set("guard", "镇南王府婢女", ob);
}
