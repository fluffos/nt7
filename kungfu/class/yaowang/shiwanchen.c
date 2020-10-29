#include <ansi.h>
#include "yaowang.h"

#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;


void create()
{
        set_name("石万嗔", ({ "shi wanchen", "shi", "wanchen" }));
        set("nickname", HIR "毒手神枭" NOR);
        set("long",@LONG
这是一位身着朴素的老者，双目失明，他便是号称
「毒手神枭」的石万嗔。数次和无嗔斗法，每一回
均是屈居下风。在最后一次斗毒之际，石万嗔终于
被“断肠草”熏瞎了双目，逃往缅甸野人山。但在
野人山中花了数十年功夫，不但解除了“断肠草”
的毒性，而且练出了更多毒药。
LONG );
        set("title", HIG "药王门掌门" NOR);
        set("gender", "男性");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 60000);
        set("max_jing", 50000);
        set("neili", 60000);
        set("max_neili", 60000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 350);
        set_skill("yaogu-xinfa", 350);
        set_skill("shennong-xinjing", 350);
        set_skill("dodge", 350);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 300);
        set_skill("shennong-zhang", 300);
        set_skill("throwing", 300);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 300);
        set_skill("literate", 280);
        set_skill("poison", 600);
        set_skill("dispel-poison", 600 );
        set_skill("yaowang-shenxin", 600 );
        set_skill("medical", 400);
        set_skill("yaowang-miaoshu", 400 );
        set_skill("baicao-jue", 500 );
        set_skill("bencao-changshi", 500);
        set_skill("hunting", 300);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("药王谷", 1, "掌门");
        set("class", "bonze");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.tengshe" :),
                (: perform_action, "whip.panying" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suolong" :),
                (: perform_action, "claw.lianhuan" :),
                (: perform_action, "strike.duchan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        set("inquiry", ([
                "七星海棠" : "七星海棠乃天下第一毒，无药可治！但据说程灵素哪个小丫头到是有点办法。",
                "碧蚕毒蛊" : "碧蚕毒蛊乃苗人的三大蛊毒之一，无药可治！",
                "苗人凤"   : "呵呵，当年他和胡一刀比武，就是用的我的毒陷害的。",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
        
        if( query("character", ob) == "光明磊落" )
        {
                command("say 你性格不适合学毒，我不能收你。");
                return;
        }
        if( query("shen", ob)>-100000 )
        {
                command("say 欲习我毒技医术，必须心狠手辣。");
                return;
        }
        
        if( query("combat_exp", ob)<300000 )
        {
                command("say 你现在经验尚浅，领会不了什么，还是先去增长点经验吧。");
                return;
        }
        if( !query_temp("yaowang_give", ob) )
        {
                command("say 你先把本门的《药王神篇》找来给我!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 100)
        {
                command("say 你本门的心法还学的不够啊。");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 120)
        {
                command("say 你连最基本的学问都没学好，我如何传授你高深的毒技医术。");
                return;
        }

        if ((int)ob->query_skill("yaowang-miaoshu", 1) < 120)
        {
                command("say 你先把药王妙术钻研透彻了再来找我吧。");
                return;
        }

        if ((int)ob->query_skill("dispel-poison", 1) < 120)
        {
                command("say 你的妙手驱毒研究透彻了吗？");
                return;
        }

        command("pat"+query("id", ob));
        command("say 不错，不错！既然你如此有心，老夫就收下你这个徒弟。");
        command("say “本门中人不能放蛊，又有九种没解药的毒药决计不能使用”的规矩在我这儿就取消了!");
        command("say 凡是对己不利者直接用毒，越毒越好!");
        command("recruit "+query("id", ob));
        set("title", "毒手神枭亲传弟子", ob);
        return;
}


int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != SHENPIAN)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
        {
                command("say 多谢这位" + RANK_D->query_respect(me) + "将本门宝物交给我。");
                set_temp("yaowang_give", 1, me);
        }
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}

