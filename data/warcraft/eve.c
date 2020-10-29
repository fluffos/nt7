// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m泡泡泡沫[2;37;0m[2;37;0m", ({"pao"}));        
        set("gender", "女性");                
        set("long", "最爱的莉莉[2;37;0m
它是伊人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "eve");
        set("owner_name", "伊人");
        set_temp("owner", "eve");
        set_temp("owner_name", "伊人");
        ::setup();
}
