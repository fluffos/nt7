// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m和你拼网速[2;37;0m[2;37;0m", ({"sdmst"}));        
        set("gender", "男性");                
        set("long", "快就是快。[2;37;0m
它是四灯大师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sideng");
        set("owner_name", "四灯大师");
        set_temp("owner", "sideng");
        set_temp("owner_name", "四灯大师");
        ::setup();
}
