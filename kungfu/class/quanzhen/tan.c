// This program is a part of NT MudLIB
// tan.c 谭处端

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
string ask_me();

void create()
{
        set_name("谭处端", ({"tan chuduan", "tan"}));
        set("gender", "男性");
        set("age", 40);
        set("class", "taoist");
        set("nickname",HIY"长真子"NOR);
        set("long",
                "他就是全真次徒谭处端谭真人，他身材魁梧，浓眉大眼，嗓音\n"
                "洪亮，拜重阳真人为师前本是铁匠出身。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 34);
        set("int", 28);
        set("con", 28);
        set("dex", 28);

        set("title","全真七子之二");
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

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 100);
        set("level", 20);
        set("combat_exp", 1200000);

        set_skill("force", 150);
        set_skill("quanzhen-xinfa", 160);
        set_skill("sword", 150);
        set_skill("quanzhen-jian",160);
        set_skill("dodge", 140);
        set_skill("jinyan-gong", 140);
        set_skill("parry", 150);
        set_skill("strike", 150);
        set_skill("chongyang-shenzhang", 150);
        set_skill("haotian-zhang", 150);
        set_skill("literate",80);
        set_skill("finger",140);
        set_skill("zhongnan-zhi", 140);
        set_skill("taoism",100);
        set_skill("cuff",150);
        set_skill("chunyang-quan",150);
        set_skill("array",150);
        set_skill("beidou-zhenfa", 150);

        map_skill("force", "quanzhen-xinfa");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jian");
        map_skill("finger", "zhongnan-zhi");
        map_skill("strike", "haotian-zhang");
        prepare_skill("finger", "zhongnan-zhi");
        prepare_skill("strike","haotian-zhang");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教"   :  "我全真教是天下道家玄门正宗。\n",
                "三花聚顶" : (: ask_skill1 :),
                "秘籍" : (: ask_me :),
        ]) );
        set("book_count", 1);
        set("master_ob",3);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/greenrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("quanzhen-xinfa",1) < 80 )
        {
                command("say 你的本门内功心法火候不足,难以领略更高深的武功。");
                return;
        }
        if( query("shen", ob)<8000 )
        {
                command("say 我看你还是多做一些侠义之事吧。\n");
                return;
        }
        command("say 好吧，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/haotian-zhang/ju", me) )
                return "这招我不是已经教会你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "阁下与贫道素不相识，不知此话从何说起？";

        if (me->query_skill("haotian-zhang", 1) < 1)
                return "你连昊天掌都没学，何谈绝招可言？";

        if( query("family/gongji", me)<250 )
                return "你在我全真教内甚无作为，这招我暂时还不能传你。";

        if( query("shen", me)<30000 )
                return "你的侠义正事还做得不够，这招我暂时还不能传你。";

        if (me->query_skill("haotian-zhang", 1) < 120)
                return "你的昊天掌不够娴熟，练高点再来吧。";

        if (me->query_skill("force") < 180)
                return "你的内功修为不够，修炼高后再来找我吧。";

        message_sort(HIY "\n$n" HIY "眉头一皱，上下打量了$N" HIY "一番"
                     "，当下更不答话，衣袖轻轻一抖，猛然大喝一声，顿时"
                     "双掌纷飞，掌劲朝四面八方云贯而出，气势恢弘之极。"
                     "\n\n" NOR, me, this_object());

        command("say 看懂了么？");
        tell_object(me, HIC "你学会了「三花聚顶」。\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("haotian-zhang"))
                me->improve_skill("haotian-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/haotian-zhang/ju", 1, me);
        addn("family/gongji", -250, me);

        return 1;
}

string ask_me()
{
        mapping fam;
        object ob, *obs,ob2 ;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "全真教" )
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";

        if (query("book_count") < 1)
                return "你来晚了，本派的内功心法不在此处。";
           obs = filter_array(children("/d/quanzhen/obj/qz_force"), (: clonep :));
                  if (sizeof(obs) > 20)
                return "你来晚了，本派的内功心法不在此处。";

        ob=new("/d/quanzhen/obj/qz_force");
        ob->move(this_player());
        addn("book_count", -1);
        command("rumor"+query("name", this_player())+"弄到了一册玄门内功心法。");
        return "好吧，这本「玄门内功心法」你拿回去好好钻研。";
}
int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "浩然一击" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_perform/haotian-zhang/ji", 
                                "name"    : "浩然一击",
                                "sk1"     : "haotian-zhang", 
                                "lv1"     : 120, 
                                "sk2"     : "strike", 
                                "lv2"     : 120, 
                                "gongxian": 600, ])); 
               break; 
         default: 
               return 0; 
         } 
} 

