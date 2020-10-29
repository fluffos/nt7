// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是呔心情的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txq");
        set("owner_name", "呔心情");
        set_temp("owner", "txq");
        set_temp("owner_name", "呔心情");
        ::setup();
}
