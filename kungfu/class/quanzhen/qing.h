// qing.h 出家和清字辈收徒和推荐给志字辈
#include "quanzhen.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

        mappingmy_fam=query("family", me);
        mappingob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("quanzhenletter1",ob) )
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
                obj=new("/d/quanzhen/obj/tuijianxin-1");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看来" + RANK_D->query_respect(ob) + "还得多加练习，方能在本教诸多弟子中出人头地！\n");
                return 1;
        }

        return 1;
}

string ask_for_join()
{
        object me = this_player();
        mappingmy_fam=query("family", me);

        if( query("class", me) == "quanzhen" )
                return "无量寿佛！你我同属玄门，何故跟小道开这等无聊玩笑？\n";

        if( my_fam["family_name"] == "全真教" && my_fam["generation"] <= 4)
                return "无量寿佛！玄门清修之士，应自小开始修行。\n";

        if( query("betrayer", me)>0 )
                return "无量寿佛！你生性反复无常，非我玄门清修之士之所为。\n";

        set_temp("pending/join_quanzhen", 1, me);
        return "无量寿佛！施主若真心皈依我全真教门，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        string name, new_name;
        if( !query_temp("pending/join_quanzhen", me))return 0;

        message_vision(
                "$N右手捏着莲花指，恭恭敬敬地磕下头去。\n\n"
                "$n伸出双手，将$N头顶长发挽成一个道髻。\n\n",me,this_object());
        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = name[0..0] + "静" + name[1..1];
        command("say 从今以后你的道法号就叫做" + new_name + "。");
        command("smile");
        delete_temp("pending/join_quanzhen", me);
        set("name", new_name, me);
        set("marks/old_name", name, me);
        set("class", "quanzhen", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0){
                command( "say 行侠仗义是我辈学武人的基本品质，你已快入魔道，我岂能收你为徒。\n");
                return;
        }
        if( query("gender", ob) == "男性" && query("gender", me) == "女性" )
        {
                command("say 我不收男徒，你还是去拜我几位师兄为师吧。\n");
                return;
        }

        if( ob_fam=query("family", ob) )
        {
                if( ob_fam["generation"] <= my_fam["generation"] &&
                    ob_fam["family_name"] == my_fam["family_name"] )
                {
                        command("say "+RANK_D->query_respect(ob)+"，这个贫道哪敢当！");
                        return;
                }
        }
        if( query("class", ob) != "quanzhen" )
        {
                command ("say 无量寿佛！贫道就收下你做『俗家弟子』了。");
        }
        else
        {
                command ("say 无量寿佛！贫道就收你为全真教正式弟子。");
        }
        command("recruit "+query("id", ob));
}
