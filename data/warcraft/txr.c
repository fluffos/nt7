// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是呔吓人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txr");
        set("owner_name", "呔吓人");
        set_temp("owner", "txr");
        set_temp("owner_name", "呔吓人");
        ::setup();
}
