// shizhe.h for fight and get letter from ShiZhe
int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query("id", obj) == "tuijian xin5"
         && query_temp("have_letter", ob )
        && ob_fam["generation"] == my_fam["generation"] + 2)
        {
                set_temp("apprentice_ok", 1, ob);
                command("say 好，"+query("name", ob)+"，你愿意拜我为师吗？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say 这东西给我可没有什麽用。");
        command("give "+query("id", obj)+" to "+query("id", me));
        return 0;

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

#include "mingjiao.h"

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "与本教素无来往，不知此话从何谈起？");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，小使哪里敢当 !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) )
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎麽跑到我这儿来了，哈哈哈 !");
                command("recruit "+query("id", ob));
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);

                        command("say 是" + ob_fam["master_name"] + "叫你来找我的吧，哈哈哈 !");
                        command("say 本使者又得一可塑之才，真是可喜可贺 !");

                        command("say 恭喜你荣升为明教护教法王！");
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

