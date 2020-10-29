//boss-cheng.c

#include <ansi.h>


inherit NPC;

#define PLACE "xy"      //长安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_good = ([
        "bunch_name" : "无极帮",
        "id"   : "wjb",
        "place": "xy",
        "boss" : "金无极",
        "type" : "good",
]);

void create()
{
        set_name("金无极", ({ "jin wuji", "jin" }));
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是鼎鼎大名的" + bunch_good["bunch_name"] + "的帮主。\n");
        set("nickname",HIY"无极神笔"NOR);
        set("title","无极帮帮主");
        set("per",26);
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
