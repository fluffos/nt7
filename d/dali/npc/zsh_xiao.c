//zsh_xiao.c

#include <ansi.h>

inherit NPC;

#define PLACE "dl"     //大理分会
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任务的反省时间

mapping bunch_good = ([ 
        "bunch_name" : "紫衫会",
        "id"   : "zsh",
        "place": "dl",      //总会
        "boss" : "公孙啸",
        "place_name" : "大理", //分会
        "type" : "good",
]);

void create()
{
        set_name("公孙啸", ({ "gongsun xiao", "xiao" }));
        set("gender", "男性");
        set("age", 60);
        set("long", "他就是" + bunch_good["bunch_name"] + "设在" + bunch_good["place_name"] + "的分会会长。\n");
        set("nickname",HIY"妙笔丹青"NOR);
        set("title",GRN"紫衫会大理分会会长"NOR);
        set("per",25);
        set("combat_exp", 800000);
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
