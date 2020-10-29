// Code of JHSH

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();
int get_jingtie_num();
string ask_jingtie();
string ask_jingtie_num();
void dest_ob(object);

void create()
{
        set_name("吴劲草", ({ "wu jincao","wu"}) );
        set("long",
        "他是一位看上去很精干的中年男子，身穿一件白布长袍。\n"
        "他天生神力，手中的两头狼牙棒有万夫不当之勇，真是一条威风凛凛的汉子。\n"
        );
        set("title", HIG "明教" HIW "锐金旗" NOR "掌旗副使");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 42);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 85);
        set_skill("hunyuan-yiqi", 85);
        set_skill("dodge", 85);
        set_skill("shaolin-shenfa", 85);
        set_skill("cuff", 95);
        set_skill("jingang-quan", 95);
        set_skill("parry", 85);
        set_skill("buddhism", 85);
        set_skill("literate", 85);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");
        create_family("明教", 37, "锐金旗掌旗副使");


        set("inquiry", ([
                "name" : "在下就是明教锐金旗掌旗副使吴劲草，不知阁下有何指教。",
                "打铁" : (: ask_job :),
                "datie": (: ask_job :),
                "精铁储藏" : (: ask_jingtie_num :),
                "reserve"  : (: ask_jingtie_num :),
                "精铁" : (: ask_jingtie :),
                "jingtie" : (: ask_jingtie :),
        ]));

        setup();

        carry_object("/d/mingjiao/obj/langyabang")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();

}

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object /*ling,*/chui,qiao;

    if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
        return "这位"+RANK_D->query_respect(player)+"并非我教弟兄，那敢在下那敢分派阁下什么任务呢。\n";

        if( query("combat_exp", player)>400000 )
                 return "这位"+RANK_D->query_respect(player)+"实战经验已经颇高，岂敢劳烦大架。\n";

        if (fam["generation"] <37)
                 return "这位"+RANK_D->query_respect(player)+"在我明教中地位颇高，岂敢劳烦大架。\n";

        if( query("mingjiao/job", player) != "jin_caikuang" )
                return judge_jobmsg(player,0);

        if( !present("wujin kuangshi",player ) )
                return "你并未采来矿石，如何打铁？\n";

        qiao=present("tie qiao",player );
        if (qiao) destruct(qiao);
        tell_object(player,"你把铁锹交给吴劲草。\n\n");

        command("nod"+query("id", player));

        chui=new(OBJ_PATH"/tiechui");
        chui->move(player);
        tell_object(player,"吴劲草给你一把铁锤。\n");

        return "好！快去把采来的矿石炼成精铁吧。\n";
}

int accept_object(object me, object ob)
{
        string name;
        string job_flg;
        object room,tool;


        name=query("id", ob);
        if ( name != "jing tie")
                return 0;

        job_flg = judge_jobmsg(me,1);

        if ( job_flg !=  "采集铁矿" )
        {
                command("hmm"+query("id", me));
                command("say 没有这项工作，就不要胡乱开采！");
                return 0;
        }
        else
        {
                command("thumb"+query("id", this_player()));
                command("say 这位兄弟辛苦了!下去好好休息休息！");
                tool=present("tie chui",me );
                if (tool) destruct(tool);
                remove_call_out("dest_ob");
                call_out("dest_ob",1,ob);
                if (!(room = find_object("/d/mingjiao/mj_center.c")))
                        room = load_object("/d/mingjiao/mj_center.c");
                addn("jingtie", 1, room);
                call_out("reward",0,this_player(),job_flg);
                return 1;
        }

        return 0;

}


int get_jingtie_num()
{
        int num;
        object room;

        if (!(room = find_object("/d/mingjiao/mj_center.c")))
                room = load_object("/d/mingjiao/mj_center.c");
        num=query("jingtie", room);

        return num;

}

string ask_jingtie_num()
{
        return "现在还有"+chinese_number(get_jingtie_num())+"块精铁。\n";
}

string ask_jingtie()
{
//      int num;
        object me=this_player();
        object jingtie,room;
        string job_flg;

        job_flg = judge_jobmsg(me,1);
        if (job_flg != "打造火枪")
                return "这位"+RANK_D->query_respect(me)+"好象没有造火枪的任务吧。\n";

        if (present("jing tie",me) )
        {
                command("hmm"+query("id", me));
                return "你不是已经有一块了吗？还想要，真是贪得无厌。\n";
        }

        if ( get_jingtie_num() <= 0 )
                return "对不起，我这里已经没有精铁了。\n";

        command("nod"+query("id", me));
        message_vision("吴劲草拿了一块精铁给$N\n",me);
        if (!(room = find_object("/d/mingjiao/mj_center.c")))
                room = load_object("/d/mingjiao/mj_center.c");
        addn("jingtie", -1, room);

        jingtie=new(OBJ_PATH"/jingtie");
        jingtie->move(me);

        return "这是兄弟们辛辛苦苦炼出来的精铁，你要用它好好打造兵器。\n";
}

void dest_ob(object ob) { destruct(ob);}