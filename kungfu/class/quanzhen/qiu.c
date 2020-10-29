// This program is a part of NT MudLIB

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

string ask_job();
void reward_dest(object obj, object ob);
void thank_dest(object obj, object ob);

void create()
{
        set_name("丘处机", ({"qiu chuji", "qiu"}));
        set("gender", "男性");
        set("age", 36);
        set("class", "taoist");
        set("nickname",HIM"长春子"NOR);
        set("long",
                "他就是江湖上人称‘长春子’的丘处机丘真人，他方面大耳，\n"
                "满面红光，剑目圆睁，双眉如刀，相貌威严，平生疾恶如仇。\n");
        set("attitude", "heroism");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("title","全真七子之四");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "strike.ju" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.ding" :),
        }));

        set("qi", 4800);
        set("max_qi", 4800);
        set("jing", 2400);
        set("max_jing", 2400);
        set("neili", 5100);
        set("max_neili", 5100);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 1400000);
        set("no_get", 1);

        set_skill("force", 185);
        set_skill("quanzhen-xinfa", 185);
        set_skill("sword", 185);
        set_skill("quanzhen-jian",185);
        set_skill("dodge", 180);
        set_skill("jinyan-gong", 180);
        set_skill("parry", 185);
        set_skill("strike", 185);
        set_skill("chongyang-shenzhang", 185);
        set_skill("haotian-zhang", 185);
        set_skill("literate", 150);
        set_skill("finger",170);
        set_skill("zhongnan-zhi", 170);
        set_skill("taoism",190);
        set_skill("medical", 180);
        set_skill("liandan-shu", 180);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("array","beidou-zhenfa");
        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("coagents", ({
                ([ "startroom" : "/d/quanzhen/shiweishi",
                   "id"        : "ma yu" ]),
                ([ "startroom" : "/d/quanzhen/wanwutang",
                   "id"        : "wang chuyi" ]),
        }));

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
                "纯阳神通功": "纯阳神通功是本门第一绝技，可惜我辈愚昧不堪，都没有练成。",
                "任务" : (: ask_job :),
                "job" : (: ask_job :),
        ]) );

        set("master_ob",4);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();

}

void init()
{
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
}


void greeting(object ob)
{
        mapping fam;
        int i ;
        object me;

        me = this_object();
        if (! ob || environment(ob) != environment() || ! living(me))
                return;

        if (interactive(ob) && base_name(environment()) == query("startroom"))
        {
                if( !(fam=query("family", ob)) || fam["family_name"] != "全真教" )
                {
                        if (ob->is_not_bad())
                                command("say 这里是本教重地，你走动小心些。");
                        else
                        {
                                command("say 你这魔头，竟敢闯入我全真重地，我一定要杀了你！");
                                kill_ob(ob);
                        }
                } else
                        command("smile"+query("id", ob));
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 120 )
        {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<12000 )
        {
                command("say 你目前表现太差！多做点行侠仗义的是再来找我！\n");
                return;
        }
        command("say 好吧，我就收下你这个徒弟了，可别坏了我们全真七子得名头！");
        command("recruit "+query("id", ob));
}

string ask_job()
{
        mapping job_stat;
        object ob = this_player();
        object me = this_object();
        int good_skill;
        object yaochu;
        object ob2;

        job_stat=query_temp("qz/caiyao", ob);

        if( query("family/family_name", ob) != "全真教" )
                return "这位" + RANK_D->query_respect(ob) + "非我全真教弟子，岂敢劳烦。\n";

        if( query("combat_exp", ob)>2000000 )
                return "这位"+RANK_D->query_respect(ob)+"实战经验已经颇高，岂敢劳烦大架。\n";

        if (job_stat)
        {
                command("hmm "+query("id", ob));
                return "你还没完成任务，就又想要新的？\n";
        }

        command("nod");
        command("say 好，最近炼丹用的草药都用完了，你去山下树林里去采一些回来。");

        if (objectp(yaochu = present("yao chu", ob)))
                destruct(yaochu);

        ob2 = new("/d/quanzhen/obj/yaochu");
        ob2->move(me);
        set_temp("qz/caiyao", 1, ob);
        command("give yao chu to "+query("id", ob));

        return "早去早回，路上要小心一些！\n";
}

int accept_object(object me, object obj)
{
        object ob = this_player();
        int r;
        if (r = ::accept_object(me, obj))
                return r;

        command("say " + obj->name() + "?");

        if( query("id", obj) == "chuanbei" || 
            query("id", obj) == "fuling" || 
            query("id", obj) == "gouzhizi" || 
            query("id", obj) == "heshouwu" || 
            query("id", obj) == "huanglian" || 
            query("id", obj) == "jugeng" || 
            query("id", obj) == "jinyinhua" || 
            query("id", obj) == "shengdi" )
        {

                if( (query("family/family_name", ob) == "全真教") && 
                    (query("id", ob) == query("player", obj)) )
                {
                        call_out("reward_dest", 1, obj, ob);
                } else
                {
                        call_out("thank_dest", 1, obj, ob);
                }

                return 1;
        }

        command( "hmm" );
        command( "say 你给我这东西做什麽？" );
        return 0;
}

void reward_dest(object obj, object ob)
{
        int time;
        object yaochu;

        if (! objectp(ob))
                return;

        if (objectp(yaochu = present("yao chu", ob)))
                destruct(yaochu);

        command("pat "+query("id", ob));
        command("say "+query("name", ob)+"干的不错，下去休息一下吧！\n");

        if( query_temp("qz/caiyao", ob) )
        {
                delete_temp("qz/caiyao", ob);
        }
        if (objectp(obj))
        destruct(obj);
}


void thank_dest(object obj, object ob)
{
        command( "jump");
        command( "say 我们很需要这些药材，多谢啦！\n");
        destruct(obj);
}
