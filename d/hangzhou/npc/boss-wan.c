#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //长安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_good = ([
        "bunch_name" : "无极帮",
        "id"   : "wjb",
        "place": "hz",
        "boss" : "万剑愁",
        "place_name" : "杭州",
        "type" : "good",
]);

void create()
{
        set_name("万剑愁", ({ "wan jianchou", "wan" }));
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是人人敬仰的万大侠。\n");
        set("nickname",HIY"江南大侠"NOR);
        set("title","无极帮杭州分舵");
        set("per",28);
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

#include <boss_good.h>
