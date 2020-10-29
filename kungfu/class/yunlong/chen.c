// chen.c 陈近南

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "yunlong.h"
int ask_tuihui();
mixed ask_me();
string ask_me1();

void create()
{
        set_name("陈近南", ({ "chen jinnan", "chen","jinnan" }));
        set("title", HIR "天地会"HIM"总舵主"NOR );
        set("nickname", HIC "英雄无敌" NOR);
        set("long",
                "\n这是一个文士打扮的中年书生，神色和蔼。\n"
                "他就是天下闻名的天地会总舵主陈近南，\n"
                "据说十八般武艺，样样精通。\n"
                "偶尔向这边看过来，顿觉他目光如电，英气逼人。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 120);
        set("combat_exp", 2000000);
        set("score", 500000);
        set_skill("literate", 600);

        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("parry", 600);
        set_skill("claw", 600);
        set_skill("blade", 600);
        set_skill("wuhu-duanmendao", 600);
        set_skill("sword", 600);
        set_skill("yunlong-jian", 600);
        set_skill("whip", 600);
        set_skill("yunlong-bian", 600);
        set_skill("houquan", 600);
        set_skill("yunlong-xinfa", 600);
        set_skill("yunlong-shengong", 600);
        set_skill("yunlong-shenfa", 600);
        set_skill("ningxue-shenzhao", 600);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("unarmed", "houquan");
        map_skill("parry", "ningxue-shenzhao");
        map_skill("claw", "ningxue-shenzhao");

        prepare_skill("claw","ningxue-shenzhao");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "claw.ji" :),
                (: exert_function, "recover" :),
        }) );

        create_family("云龙门",1, "开山祖师");
        set("book_count", 1);
        set("inquiry", ([
                "天地会" :  "只要是英雄好汉，都可以入我天地会(join tiandihui)。",
                "入会" :  "还不快快如天地会一同反清复明。",
                "反清复明" : "去棺材店和回春堂仔细瞧瞧吧！\n",
                "暗号"     : "敲三下！\n",
                "切口"     : "敲三下！\n",
                "绝招" : (: ask_me :),
                "绝技" : (: ask_me :),
                "疾电" : (: ask_me :),
                "凝血神爪" : (: ask_me :),
                "云龙剑谱" : (: ask_me1 :),
                "退会" : (: ask_tuihui :),
                "tuihui"   : (: ask_tuihui :),
        ]) );

        set("master_ob", 5);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_join","join");
}

int ask_tuihui()
{
        object ob;
        ob=this_player();

        if( query("party/party_name", ob) != "天地会" )
        {
                message_vision("陈近南笑了笑，对$N说道：你还没"
                               "加入我天地会呢，退什么退？\n", ob);
                return 1;
        }
        command("look "+query("id", ob));
        command("sigh ");
        command("say 反清复明，就要坚贞志士，你去吧! ");
        delete("party", ob);
        delete("rank", ob);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/ningxue-shenzhao/ji", me) )
                return "你真会开玩笑，会了还来找我。";

/*
        if( !query("story/shenzhao", me) )
                return "你打听这个干嘛？";
*/

        if( query("shen", me)<1000000 )
                return "习武之人最重一个“侠”字，侠义方面你还做得不够！";

        if (me->query_skill("ningxue-shenzhao", 1) < 250)
                return "你的凝血神爪还不到家，要多练练！";

        message_vision(HIY "$n" HIY "点了点头，变掌为爪，"
                       "随意挥洒而出，双爪顿时幻出漫天爪影，"
                       "气势恢弘无比。\n" NOR,
                       me, this_object());
        command("nod");
        command("say 你可明白了？");
        tell_object(me, HIC "你学会了「疾电」这一招。\n" NOR);
        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 500000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 500000);
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 500000);
        if (me->can_improve_skill("ningxue-shenzhao"))
                me->improve_skill("ningxue-shenzhao", 500000);
        set("can_perform/ningxue-shenzhao/ji", 1, me);
        return 1;
}

string ask_me1()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "云龙门")
                return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的云龙真经不在此处。";
        addn("book_count", -1);
        ob = new("/clone/book/yljianpu");
        ob->move(this_player());
        return "好吧，这本「云龙剑谱」你拿回去好好钻研。";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_skill("yunlong-shengong", 1) < 50)
        {
                command("say 我云龙神功乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在云龙神功上多下点功夫？");
                return;
        }
        if( query("weiwang", ob)<60 )
        {
                command("say 我云龙门武功天下无敌，凡入我门，\n必闯荡江湖，行侠仗义，为天下苍生谋福利。\n");
                command("say " + RANK_D->query_respect(ob) +
                        "是否应该先出去闯一闯，做几件惊天动地的大事？");
                return ;
        }
        if( query("shen", ob)>0 && query("shen", ob)<5000){
                command("say 学武之人，德义为先，功夫的高低倒还在其次，未练武，要先学做人。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否还做得不够？");
                return ;
        }
        if( query("weiwang", ob)<80 )
        {
                if( query("shen", ob)<0 )
                command("say "+ RANK_D->query_respect(ob) +"虽然是邪派中人，但也还做了些好事。\n");
                command("chat 我天地会所作所为，无一不是前人所未行之事。\n");
                command("chat 万事开创在我，骇人听闻，物议沸然，又何足论？\n");
                command("chat 今天就收了你吧！！\n");
                command("chat 想不到我一身惊人艺业，今日终于有了传人，哈哈哈哈！！！！\n");
                message_vision(HIC "$N的江湖威望提高了！\n" NOR,this_player());
                set("weiwang", 80, ob);
        }
        command("recruit "+query("id", ob));
        if( (!query("class", ob)) || (query("class", ob) != "fighter") )
                set("class", "fighter", ob);
}

#include "/kungfu/class/yunlong/tiandihui.h"
