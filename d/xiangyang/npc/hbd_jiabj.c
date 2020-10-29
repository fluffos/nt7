//hbd_jiabj.c

#include <ansi.h>

inherit NPC;

#define PLACE "xy"
#define TYPE  "bad"
#define WAIT_TIME 60

mapping bunch_bad = ([ 
        "bunch_name" : "黑白道",
        "id"   : "hbd",
        "place": "xy",      //总会
        "boss" : "贾不假",
        "place_name" : "襄阳", //分会
        "type" : "bad",
]);

void create()
{
        set_name("贾不假", ({ "jia bujia", "jia" }));
        set("gender", "男性");
        set("age", 30);
        set("long", "他就是" + bunch_bad["bunch_name"] + "设在" + bunch_bad["place_name"] + "的分坛首领。\n");
        set("nickname",HIY"白玉为堂金作马"NOR);
        set("title",HIB"黑"HIW"白"NOR"道分坛主"NOR);
        set("per",20);
        set("combat_exp", 800000);
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
