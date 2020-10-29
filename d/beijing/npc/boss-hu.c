// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "bjw"     //扬州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任务的反省时间



mapping bunch_bad = ([
        "bunch_name" : "修罗门",
        "id"   : "xlm",
        "place": "bjw",
        "boss" : "胡媚娘",
        "place_name": "北京西城",
        "type" : "bad",
]);

void create()
{
        set_name("胡媚娘", ({ "hu meiniang", "hu","meiniang" }));
        set("gender", "女性");
        set("age", 26);
        set("long", "她装扮的妖艳无比，一双眼睛能摄人魂魄。\n");
        set("title",HIB"修罗门北京坛主"NOR);
        set("per",29);
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

