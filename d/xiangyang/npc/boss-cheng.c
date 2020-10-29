//boss-cheng.c

#include <ansi.h>

inherit NPC;

#define PLACE "ca"      //长安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_good = ([
        "bunch_name" : "侠义盟",
        "id"   : "xym",
        "place": "ca",
        "boss" : "成中岳",
        "type" : "good",
]);

void create()
{
        set_name("成中岳", ({ "cheng zhongyue", "cheng" }));
        set("gender", "男性");
        set("age", 45);
        set("long", "他就是鼎鼎大名的" + bunch_good["bunch_name"] + "的总瓢把子。\n");
        set("nickname",HIY"侠肝义胆"NOR);
        set("title","侠义盟大当家");
        set("per",20);
        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}

#include "boss_good.h"
