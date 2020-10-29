// gui3-2.c
// Modified by haiyan

#include <ansi.h>
inherit NPC;

string comeon = HIW"忽然间一道白影闪过，你正惊疑，小腿一紧，已被裹尸布缠住。\n"NOR; 

string *stya = ({ 
HIB"$N眼前一花，脖子已被裹尸布紧紧勒住，顿感气息不畅，双眼发黑。\n"NOR, 
HIB"$N腿上的裹尸布被一股怪力一拉，立足不稳，向前扑倒在地。\n"NOR, 
HIB"只听噗嗤一声，$N觉得身上已被十指戳入，不禁面色惨白。\n"NOR, 
HIB"$N脚下被裹尸布一绊，仰天摔倒。\n"NOR
}); 

string *styb = ({ 
HIC"$N对$n喝道：“何处妖魔，来此作孽？本道爷今日要将你变成死鬼！”\n"NOR,
HIW"$N挥动手中的"HIM"桃木剑"HIW"，道道剑光将裹尸布震成碎片，漫天飞舞。\n"NOR
});

void check_time();

void create()
{
    set_name("木乃伊", ({ "mummy ghost", "ghost" }));
    set("gender", "男性");
    set("race", "妖魔");
    set("age", 200);
    set("per", 15);
    set("long",
        "一种人死后尸体不腐而变成的鬼魂。身上缠满了裹尸布，十分可怖。\n");
    set("combat_exp", 100000);
    set("shen_type", -1);
    set("attitude", "peaceful");
    set("limbs", ({ "牙齿", "手爪" }) );
    set("verbs", ({ "bite", "claw" }) );
    set("env/invisible", 1);
    set("water", 200);
    set("food", 200);
    set("apply/attack", 350);
    set("apply/defense", 350);
    set_skill("parry", 350);
    set_skill("dodge", 400);

    set("chat_chance", 80);
    set("chat_msg", ({ (: check_time :) })); 
    setup();
    keep_heart_beat();
}

#include "ghoster.h"
