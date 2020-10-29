// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("是红颜[2;37;0m[2;37;0m", ({"shyshy"}));        
        set("gender", "男性");                
        set("long", "啊 [2;37;0m
它是白起的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bruce");
        set("owner_name", "白起");
        set_temp("owner", "bruce");
        set_temp("owner_name", "白起");
        ::setup();
}
