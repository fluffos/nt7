// huangboliu.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("黄伯流", ({ "huang boliu","huang","boliu"}) );
        set("gender", "男性" );
        set("title", "日月神教风雷堂香主");
        set("nickname", HIW"银髯蛟"NOR);
        set("age", 85);
        set("long", "一部白须，直垂至胸，身材魁梧之极。\n");
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("combat_exp", 350000);
        set("jiali", 100);
        set("score", 30000);

        set_skill("force", 110); 
        set_skill("riyue-xinfa", 110); 
        set_skill("dodge", 110); 
        set_skill("piaomiao-shenfa", 110); 
        set_skill("hand", 110); 
        set_skill("huanmo-longtianwu", 110); 
        set_skill("cuff", 110); 
        set_skill("xuwu-piaomiao", 110);
        set_skill("parry", 110);
        set_skill("literate", 80);
        set_skill("sword", 110);
        set_skill("riyue-jian", 110);
        set_skill("blade", 110);
        set_skill("tianmo-dao", 110); 

        map_skill("force", "riyue-xinfa"); 
        map_skill("dodge", "piaomiao-shenfa"); 
        map_skill("hand", "huanmo-longtianwu"); 
        map_skill("cuff", "xuwu-piaomiao"); 
        map_skill("sword", "riyue-jian"); 
        map_skill("parry", "tianmo-dao"); 
        map_skill("blade", "tianmo-dao"); 

        prepare_skill("hand", "huanmo-longtianwu"); 
        prepare_skill("cuff", "xuwu-piaomiao"); 

        set("apply/dodge", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/armor", 120);

        set("coagents", ({
        ([ "startroom" : "/d/heimuya/neishi",
           "id"        : "dongfang bubai" ]),
        }));

        create_family("日月神教",2,"弟子 风雷堂香主");

        set("master_ob",2);
        setup();
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

