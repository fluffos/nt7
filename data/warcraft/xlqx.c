// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m青色地瓜[2;37;0m[2;37;0m", ({"xlqxa"}));        
        set("gender", "女性");                
        set("long", "实在太丑了[2;37;0m
它是西门星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xlqx");
        set("owner_name", "西门星");
        set_temp("owner", "xlqx");
        set_temp("owner_name", "西门星");
        ::setup();
}
