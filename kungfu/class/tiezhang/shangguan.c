// shangguan.c

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("上官剑南", ({ "shangguan jiannan", "jiannan", "shangguan"}));
        set("long", "他就是威震川湘的铁掌帮的上代帮主-上官剑南。\n");
        set("gender", "男性");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 35);
        set("int", 30);
        set("con", 28);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 200);
        set("combat_exp", 1000000);
        set("score", 400000);

        set_skill("force", 600);
        set_skill("guiyuan-tunafa", 600);
        set_skill("dodge", 600);
        set_skill("shuishangpiao", 600);
        set_skill("club", 600);
        set_skill("tiexue-qiang", 600);
        set_skill("zhongping-qiang", 600);
        set_skill("strike", 600);
        set_skill("zhusha-zhang", 600);
        set_skill("tie-zhang", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);

        map_skill("force", "guiyuan-tunafa");
        map_skill("dodge", "shuishangpiao");
        map_skill("club", "tiexue-qiang");
        map_skill("strike", "tie-zhang");
        map_skill("parry", "tie-zhang");
        prepare_skill("strike", "tie-zhang");

        set("env/wimpy", 60);
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: command("unwield qiang") :),
                (: command("wield qiang") :),
                (: perform_action, "strike.zhangdao" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );

        create_family("铁掌帮", 13, "帮主");
        setup();
        carry_object(__DIR__"obj/yellowcloth")->wear();
        //carry_object(WEAPON_DIR+"spear/yinqiang")->wield();
}

void attempt_apprentice(object me)
{
        if(me->query_skill("guiyuan-tunafa", 1) < 100)
                command("say 你的归元吐纳法根基太弱了。\n");
        else
        {
                command( "say 好吧，我就收下你了。否则我的武功就要和我这把老骨头一起埋在这个山洞里了。");
                command("recruit "+query("id", me));
        }
}
