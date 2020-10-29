// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("铛[2;37;0m[2;37;0m", ({"dang"}));        
        set("gender", "女性");                
        set("long", "铛[2;37;0m
它是冷凄寒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qihan");
        set("owner_name", "冷凄寒");
        set_temp("owner", "qihan");
        set_temp("owner_name", "冷凄寒");
        ::setup();
}
