// ZhangQiShi.h for fight and get letter from ZhangQiShi
#include "mingjiao.h"

void init()
{
        object me,ob;
        me = this_object () ;
        ob = this_player () ;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }       
}

int accept_object(object ob, object obj)
{
        string name;
        string job_flg;
        object me = this_object();

        mapping ob_family=query("family", ob);
        name=query("id", obj);

        if( name == "huo qiang" && query("id", me) == "xin ran" )
        {
                job_flg = judge_jobmsg(ob,1);

                if ( job_flg !=  "打造火枪" ) 
                {
                        command("hmm "+query("id", ob));
                        command("say 阁下没有这项工作，哪里来的火枪？这火枪甚是危险，我先收下了。");
                        destruct(obj);
                        return 1;
                }
                else
                {
                        command("thumb "+query("id", ob));
                        command("say 这位兄弟辛苦了!下去好好休息休息！");
                        destruct(obj);
                        call_out("reward",0,ob,"打造火枪"); 
                        return 1;
                }
        }

        if( query_temp("have_letter", ob) && present("tuijian xin3",ob) )
        {
                command("say 怎麽样，你拿我的推荐信去见五散人了吗 ?");
                return 0;
        }

        if( (query("id", obj) == "tieyan ling" )
        && ob_family["family_name"] == "明教"
         && ob_family["generation"] == query("family/generation", me)+1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已得到教主许可，我们就来验证一下武功。");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        if( query("id", obj) == "tuijian xin2"
         && query_temp("have_letter", ob )
         && ob_family["generation"] == query("family/generation", me)+2 )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say 好，"+query("name", ob)+"，你愿意加入我旗吗？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

       
        command("?");
        command("say 这东西给我可没有什麽用。");
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
                command("say 青出於蓝胜於蓝，不愧是我明教的佳弟子 ! 恭喜你了 !\n");
                message_vision("$N交给$n一封推荐信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/mingjiao/obj/tuijianxin-3");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看来" + RANK_D->query_respect(ob) + 
                        "还得多加练习，方能在明教诸多弟子中出人头地 !\n");
                return 1;
        }

        return 1;  
}

void attempt_apprentice(object ob)
{
        object me;
        mapping ob_family;
//      string qi,new_rank;

        me=this_object();

        if (! permit_recruit(ob) )
                return;

        if( !mapp(ob_family=query("family", ob)) || ob_family["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此举是何用意？");
                return;
        }

        if( query("family/generation", me) >= query("family/generation", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "，在下哪里敢当 !");
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+1 )
        {
                command("say "+query("family/master_name", ob)+"的徒弟怎麽跑到我这儿来了，哈哈哈!");
                command("recruit "+query("id", ob));
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+2 )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say 哈哈哈 !");
                        command("say 本旗又得一可塑之才，真是可喜可贺 !");
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