// xutianch.c 徐天川

#include <ansi.h>
inherit NPC;

int ask_weiwang();

void create()
{
        set_name("徐天川", ({ "xu tianchuan", "xu", "tianchuan" }));
        set("nickname", "八臂猿猴");
        set("gender", "男性");
        set("long","他是青木堂数一数二的好手，手上功夫十分了得，尤其擅使一套猴拳。\n");
        set("age", 55);
        set("int", 30);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("shen_type", 1);

        set("combat_exp", 75000);
        set("attitude", "friendly");

        set_skill("force", 70);
        set_skill("dodge", 70);
        set_skill("parry", 90);
        set_skill("unarmed", 90);
        set_skill("yunlong-shengong", 70);
        set_skill("yunlong-shenfa", 70);
        set_skill("houquan", 100);

        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 35);
        set("env/wimpy", 50);

        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("hand", "houquan");
        map_skill("unarmed", "houquan");
        map_skill("parry", "houquan");

        set("chat_chance", 3);
        set("chat_msg", ({
                "徐天川想了想，说：有人想要进出皇宫，我得想个法子才好啊。\n",
                "徐天川说道: 江湖威望很重要，威望值高大有好处啊。\n",
                "徐天川突然说：自此传得众兄弟，后来相认团圆时。\n",
                "徐天川突然说：初进洪门结义兄，对天明誓表真心。\n",
        }));

        set("inquiry", ([
                "陈近南" : "想见总舵主可不容易啊。\n",
                "天地会" : "只要是英雄好汉，都可以入我天地会(join tiandihui)。\n",
                "入会" : "只要入了我天地会，可以向会中各位好手学武功。\n",
                "威望" : (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
                "去清复明膏" : "去药铺内室里仔细瞧瞧吧！\n",
                "去清复明" : "去药铺内室里仔细瞧瞧吧！\n",
                "反清复明" : "去药铺内室里仔细瞧瞧吧！\n",
                "暗号" : "敲三下！\n",
                "切口" : "敲三下！\n",
        ]) );
        set("party/party_name", "天地会");
        set("party/rank", HIG"青木堂"NOR"护法");
        create_family("云龙门", 2, "弟子");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold", 5);
}

void init()
{
        ::init();
        add_action("do_skills","skills");
        add_action("do_skills","cha");
        add_action("do_join","join");
}

int ask_weiwang()
{
command("tell"+query("id", this_player())+"你现在的江湖威望是"+(query("weiwang", this_player())));
say("\n徐天川说：如果你威望值很高，有些人见了你不但不会杀你，还会教你武功，送你宝贝。\n"
+"而且你还可以加入帮会，率领会众去攻打目标，就连去钱庄取钱也会有利息 。。。。。\n");
say("徐天川又说：杀某些坏人或救某些好人可以提高江湖威望。\n");
return 1;
}

int recognize_apprentice(object ob)
{
        if( query("weiwang", ob)<50 )
        {
                message_vision("$N摇了摇头。\n",this_object());
                command("tell"+query("id", ob)+"不是天地会弟子我不教。\n");
        }
        return 1;
}
#include "tiandihui.h";
