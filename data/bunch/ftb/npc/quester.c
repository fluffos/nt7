// Create by BUNCH_D written by Lonely
// quester.c

#include <ansi.h>
inherit NPC;
#define PLACE          "yz"
#define TYPE           "good"
#define WAIT_TIME      60

mapping bunch_good = ([
	"bunch_name" : "斧头帮",
	"id" : "ftb",
	"place" : "yz",
	"boss" : "鸬咔",
	"place_name" : "扬州城",
	"type"  : "good",
	]);

void create()
{
        set_name("任务使者", ({ "quester" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "他是一个长得很英俊的男子，看上去风流倜傥。\n");
        set("bunch/bunch_name", bunch_good["bunch_name"]);
        set("shen_type", 1);
        set("per", 29);
        set("combat_exp", 1000000);

        set("attitude", "peaceful");

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}

#include <boss_good.h>
