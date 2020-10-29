// xuanzhen.c 玄贞道长

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "yunlong.h"

int ask_weiwang();
string ask_me();

void create()
{
        set_name("玄贞道长", ({ "xuan zhen", "xuan", "zhen" }));
        set("gender", "男性");
        set("title", HIR "天地会"HIG"青木堂"NOR"会众");
        set("long", "\n这位沉默寡言的道人，便是天地会青木堂护法。\n"+
                "他是青木堂数一数二的好手，一柄长剑使得出神入化。\n");
        set("age", 55);
        set("class", "taoist");
        set("int", 30);

        set("qi", 2800);
        set("max_qi", 2800);
        set("jing", 1200);
        set("max_jing", 1200);
        set("shen_type", 1);

        set("combat_exp", 100000);
        set("attitude", "friendly");

        set_skill("force", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("sword", 100);
        set_skill("whip", 80);
        set_skill("hand", 70);
        set_skill("claw", 70);
        set_skill("yunlong-shengong", 70);
        set_skill("yunlong-shenfa", 70);
        set_skill("yunlong-xinfa", 70);
        set_skill("yunlong-bian", 70);
        set_skill("yunlong-jian", 80);
        set_skill("yunlong-shou", 50);
        set_skill("yunlong-zhua", 50);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 60);

        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "yunlong-jian");
        map_skill("sword", "yunlong-jian");
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("whip", "yunlong-bian");

        prepare_skill("hand", "yunlong-shou");
        prepare_skill("claw", "yunlong-zhua");
        create_family("云龙门",2, "弟子");
        set("book_count", 1);
        set("inquiry", ([
                "陈近南" :  "这是我们的总舵主。",
                "天地会" :  "只要是英雄好汉，都可以入我天地会(join tiandihui)。\n",
                "入会" :  "加入了我们天地会吧！\n",
                "反清复明" : "去药铺和棺材店仔细瞧瞧吧！\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
                "云龙经" : (: ask_me :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat 这位" + RANK_D->query_respect(this_player())+",你我无冤无仇，何必如此?\n") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "whip.chan" :),
                (: perform_action, "whip.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                      }) );
        set("master_ob", 4);
        setup();
        carry_object(CLOTH_DIR"daopao")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        carry_object(WEAPON_DIR"changbian")->wield();
        carry_object(WEAPON_DIR"changjian");
        add_money("gold", 1);
}
string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "云龙门")
                return RANK_D->query_respect(this_player()) +
                "与本派素无来往，不知此话从何谈起？";
        if (query("book_count") < 1)
                return "你来晚了，本派的云龙真经不在此处。";
        addn("book_count", -1);
        ob = new("/clone/book/yljing2");
        ob->move(this_player());
        return "好吧，这本「云龙经」你拿回去好好钻研。";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

//      if ((int)ob->query("weiwang") < 50) {
//              command("say 我云龙门武功盖世，对弟子要求也是极高。");
//              command("say " + RANK_D->query_respect(ob) + "若能先" +
//                      "加入我天地会，或许我可以考虑收你为徒。");
//              return;
//      }
        if( query("party/party_name", ob) != "天地会" ){
                command("say 我云龙门武功盖世，对弟子要求也是极高。");
                command("say " + RANK_D->query_respect(ob) + "若能先" +
                        "加入我天地会，或许我可以考虑收你为徒。");
                command("say 你不是本会弟兄，我不能收你！");
                return;
        }
        command("say 好吧，既然" + RANK_D->query_respect(ob) + "也是" +
                "我辈中人，今天就收下你吧。");
        command("recruit "+query("id", ob));
}
void init()
{
        ::init();
        add_action("do_join","join");
/*
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
*/
}

int ask_weiwang()
{
        command("tell "+query("id", this_player())+"你现在的江湖威望是"+(query("weiwang", this_player())));
        say("\n玄贞说道：如果你威望值很高，有些人见了你不但不会杀你，还会教你武功，送你宝贝。\n"
        +"而且你还可以加入帮会，率领会众去攻打目标，就连去钱庄取钱也会有利息 。。。。。\n");
        say("玄贞又说：杀某些坏人或救某些好人可以提高江湖威望。\n");
        return 1;
}

/*
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ||
                file_name(environment(ob))!="/d/beijing/andao1") return;
        if( query("weiwang", ob) >= 50 )
        switch( random(3))
        {
                case 1:
                        say("玄贞笑道：这位"+RANK_D->query_respect(ob)+"，我带你去香堂吧。\n");
                        ob->move("/d/beijing/dating");
                        message_vision("$N来到了大厅。\n",ob);
                        break;
                default:
                        say("玄贞说道：这位" + RANK_D->query_respect(ob) + "，请自便。\n");
                        break;
        }
        else say( "玄贞笑道：这位" + RANK_D->query_respect(ob)
                                + "，到这儿来干什么？\n");
}
*/

int recognize_apprentice(object ob)
{
        if( query("party/party_name", ob) != "天地会" ){
                message_vision("$N摇了摇头。\n",this_object());
                command("tell"+query("id", ob)+"不是天地会弟子我不教。\n");
                return 0;
        }
        return 1;
}
#include "/kungfu/class/yunlong/tiandihui.h";
