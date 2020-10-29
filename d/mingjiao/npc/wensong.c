// WenSong.c
// pal 1997.05.11

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();

void create()
{
        set_name("闻苍松", ({ "wen cangsong", "wen", "cangsong", }));
        set("long",
        "他是一位高大魁伟的中年男子，身穿一件白布长袍。\n"
        "他天生神力，手中的两头狼牙棒有万夫不当之勇，真是一条威风凛凛的汉子。\n"
        );

        set("title", HIG "明教" HIC "巨木旗" NOR "掌旗使");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 48);
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

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("cuff", 120);
        set_skill("strike", 120);
        set_skill("throwing", 200);
        set_skill("literate", 100);

        set_skill("shenghuo-xinfa", 120);
        set_skill("shenghuo-bu", 120);
        set_skill("shenghuo-quan", 120);
        set_skill("guangming-zhang", 120);
        set_skill("liehuo-jian", 120);
        set_skill("wuxing-jueji", 200);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");
        map_skill("throwing", "wuxing-jueji");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        create_family("明教", 37, "巨木旗掌旗使");
        set("inherit_title",HIG"明教"NOR"巨木旗教众"NOR);

        set("inquiry", ([
                "name" : "在下就是明教巨木旗掌旗使闻苍松，不知阁下有何指教。",
                "任务" : (: ask_job :),
                "job"  : (: ask_job :),
                "放弃" : (: ask_abandon :),
                "abandon" : (: ask_abandon :),
        ]));

        setup();

        carry_object("/d/mingjiao/obj/qimeigun")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object ling,axe,shugan;

    if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
        return "这位"+RANK_D->query_respect(player)+"并非我教弟兄，那敢在下那敢分派阁下什么任务呢。\n";

        if( query("combat_exp", player)>400000 )
                 return "这位"+RANK_D->query_respect(player)+"实战经验已经颇高，岂敢劳烦大架。\n";
        if (fam["generation"] <37)
                 return "这位"+RANK_D->query_respect(player)+"在我明教地位颇高，岂敢劳烦大架。\n";

        if( query("mingjiao/job", player) == "mu_kanshu" && shugan=present("shugan",player) )
        {
                if( query("owner", shugan) == query("id", player) )
                {
                        command("pat "+query("id", player));
                        if (axe=present("axe",player))
                                destruct(axe);
                        message_vision("闻苍松叫来一名教众，把$N的树干接了过去。\n",player);
                        destruct(shugan);
                        delete_temp("apply/short", player);
                        remove_call_out("reward");
                        call_out("reward",1,this_player(),"砍树");
               return query("name", player)+"干得不错！下去好好休息休息。\n"; 
                }
                else
                        return "这好象不是你砍的吧。想偷懒？\n";
        }

        if( query("mingjiao/job", player) )
                return judge_jobmsg(player,0);

        command("nod"+query("id", player));

        set("mingjiao/job", "mu_kanshu", player);

        axe=new(OBJ_PATH"/axe");
        axe->move(player);
        tell_object(player,"闻苍松给你一把斧头。\n");

        return "你来的正好，兄弟们演练阵法，巨木不够了，你去树林里砍些树干扛回来。\n";

}

#include "zhangqishi.h"
