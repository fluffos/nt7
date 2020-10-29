// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //扬州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任务的反省时间



mapping bunch_bad = ([
        "bunch_name" : "小刀会",
        "id"    : "xdh",
        "place" : "yz",
        "boss"  : "鞠老大",
        "place_name": "扬州",
        "type"  : "bad",
]);

void create()
{
        set_name("鞠老大", ({ "ju laoda", "laoda","ju" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "他是一个长得很英俊的男子，看上去风流倜傥，让人无法相信他就本城地头蛇" + bunch_bad["bunch_name"] + "的首领。\n");
        set("title","小刀会头子"NOR);
        set("nickname",HIY"花花太岁"NOR);
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

