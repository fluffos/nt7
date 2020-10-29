// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神仙虎[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "神仙虎[2;37;0m
它是痴情的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "chi");
        set("owner_name", "痴情");
        set_temp("owner", "chi");
        set_temp("owner_name", "痴情");
        ::setup();
}
