// gui1-1.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIB"你刚走过来，就觉一股阴冷的寒气迎面袭来，不禁打了个哆嗦。\n"NOR;

string *stya = ({
HIB"一阵阴风袭来，$N忽然觉得全身血液似乎都被这股阴风冻住。\n"NOR,
HIB"$N感到一股寒气顺经脉流遍周身，不禁痛苦的闷哼了一声。\n"NOR,
HIR"$N感到身上一阵剧痛。\n"NOR,
HIB"$N突觉身上被野鬼紧紧抓住，大惊失色，连忙后退数步。\n"NOR
});

string *styb = ({
HIC"$N对$n大喝道：“妖魔，你屡番害人性命，本道爷今日让你永不得超生！”\n"NOR,
HIY"$N抖动手中的"HIM"桃木剑"HIY"，发出耀眼的光芒，道道金光向$n刺去。\n"NOR,
HIC"$N手中"HIM"桃木剑"HIC"划出无数个金环，一圈一圈套向$n。\n"NOR
});

void check_time();

void create()
{
    set_name("野鬼", ({ "wild ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 10);
    set("long",
        "一个凶神恶刹、面目狰狞的鬼魂。它脸色惨白，牙齿又长又尖，十指仍在滴着
鲜血，正死死地盯着你。\n");
    set("combat_exp", 50000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 120);
    set("apply/defense", 120);
    set_skill("parry", 150);
    set_skill("dodge", 200);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
