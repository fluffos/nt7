#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //长安
#define TYPE  "bad"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_bad = ([
        "bunch_name" : "小刀会",
        "id"   : "xdh",
        "place": "hz",
        "boss" : "马六",
        "place_name" : "杭州",
        "type" : "bad",
]);

void create()
{
        set_name("马六", ({ "ma liu", "ma" }));
        set("gender", "男性");
        set("age", 29);
        set("long", "他就是本地的地头蛇组织" + bunch_bad["bunch_name"] + "的头子。\n");
        set("nickname",HIY"无恶不作"NOR);
        set("title","小刀会杭州分舵头子");
        set("per",20);
        set("combat_exp", 1000000);
        set("shen_type", -1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}

#include "boss_bad.h"
