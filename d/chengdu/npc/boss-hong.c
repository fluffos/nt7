#include <ansi.h>

inherit NPC;

#define PLACE "cd"     //长安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_good = ([
        "bunch_name" : "侠义盟",
        "id"   : "xym",
        "place": "cd",
        "boss" : "洪义",
        "type" : "good",
]);

void create()
{
        set_name("洪义", ({ "hong yi", "hong" }));
        set("gender", "男性");
        set("age", 39);
        set("long", "他就是鼎鼎大名的" + bunch_good["bunch_name"] + "的成都分舵主。\n");
        set("nickname",HIY"蜀都大侠"NOR);
        set("title","侠义盟成都分舵舵主");
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
