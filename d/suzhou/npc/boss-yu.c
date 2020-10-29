// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "sz"     //扬州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任务的反省时间



mapping bunch_bad = ([
        "bunch_name" : "修罗门",
        "id"   : "xlm",
        "place": "sz",
        "boss" : "玉罗刹",
        "place_name": "苏州",
        "type" : "bad",
]);

void create()
{
        set_name("玉罗刹", ({ "yu luosha", "yu","luosha" }));
        set("gender", "女性");
        set("age", 28);
        set("long", "她看起来冷冷的，面部好象僵住了一般，没有一点表情变化。她就是" + bunch_bad["bunch_name"] + "的门主。\n");
        set("title",HIB"修罗门门主"NOR);
        set("per",30);
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
#include <boss_bad.h>

