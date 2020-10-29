// gui1-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIC"你忽然看见一个妙龄少女在草丛中呻吟不止，你快步走近，上前察看，" +
                   "不料少女蓦的在你眼前消失。\n" +
                HIB"周围景物刹那间忽地变的诡异莫测。\n"NOR; 

string *stya = ({ 
HIB"周围不见活物，却听得女子的嬉笑声从四面八方传来，$N的神志有些迷糊。\n"NOR, 
HIB"一阵红烟喷到面前，$N不由吸了一口，只觉五脏六腑犹如怒海孤舟般翻滚不止，说不出来的难受。\n"NOR, 
HIB"$N突觉脖颈上似有舌头在轻轻舐舔，奇痒难忍，心中大骇。\n"NOR, 
HIB"$N感到一双腻滑的双手在身上抚摸，大惊失色，连忙后退数步。\n"NOR
}); 

string *styb = ({
HIC"$N对$n大喝道：“害人精，今日撞到本道爷手里，让你永不得超生！”\n"NOR,
HIC"$N将手中"HIY"符纸"HIC"拍出，一道强光射向$n。\n"NOR,
HIY"$N抖动手中的"HIM"桃木剑"HIY"，发出耀眼的光芒，道道金光向$n刺去。\n"NOR
});

void check_time();

void create()
{
    set_name("狐狸精", ({ "fox ghost", "ghost" }));
    set("gender", "女性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 30);
    set("long",
        "一个由千年狐狸修炼而成的精灵。常常变成美貌少女害人。\n");
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
