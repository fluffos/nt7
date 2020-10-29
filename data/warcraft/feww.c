// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白与西[2;37;0m[2;37;0m", ({"ask_zeng_about_job"}));        
        set("gender", "女性");                
        set("long", "白与西[2;37;0m
它是擎天柱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "feww");
        set("owner_name", "擎天柱");
        set_temp("owner", "feww");
        set_temp("owner_name", "擎天柱");
        ::setup();
}
