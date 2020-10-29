// XinRan.c
// pal 1997.05.11

#include "ansi.h"
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;

string ask_job();

void create()
{
        set_name("辛然", ({ "xin ran", "xin", "ran", }));
        set("long",
        "他是一位高大魁伟的中年男子，身穿一件白布长袍。\n"
        "他天生神力，手中的两头狼牙棒有万夫不当之勇，真是一条威风凛凛的汉子。\n"
        );

        set("title", HIG "明教" HIR "烈火旗" NOR "掌旗使");
        set("level",7);

        set("gender", "男性");
        set("attitude", "friendly");

        set("age", 40);
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

        create_family("明教", 37, "烈火旗掌旗使");
        set("inherit_title",HIG"明教"NOR"烈火旗教众"NOR);

        set("inquiry", ([
                "name" : "在下就是明教烈火旗掌旗使辛然，不知阁下有何指教。",
                "任务" : (: ask_job :),
                "job"  : (: ask_job :),
                "放弃" : (: ask_abandon :),
                "abandon" : (: ask_abandon :),
        ]));

        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

#include "zhangqishi.h"

string ask_job()
{
     object player=this_player();
     mapping fam ;
//   object ling;

    if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
        return "这位"+RANK_D->query_respect(player)+"并非我教弟兄，那敢在下那敢分派阁下什么任务呢。\n";

        if( query("combat_exp", player)>400000 )
                 return "这位"+RANK_D->query_respect(player)+"实战经验已经颇高，岂敢劳烦大架。\n";

        if (fam["generation"] <37)
                 return "这位"+RANK_D->query_respect(player)+"在我明教中地位颇高，岂敢劳烦大架。\n";

        if( query("mingjiao/job", player) )
                return judge_jobmsg(player,0);

        command("nod"+query("id", player));

        set("mingjiao/job", "huo_zaoqiang", player);

        return "我烈火旗在教内负责各种武器的制造，最近需要加紧制造火枪，你去\n"
                "后山上找些硝磺，再去锐金旗要些精铁，然后到火房打造火枪。\n"
                "火枪威力巨大，乃我教抵御敌人的重要武器，你定要小心在意。\n";



}