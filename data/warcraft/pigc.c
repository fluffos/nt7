// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m法制治国[2;37;0m[2;37;0m", ({"pigcc"}));        
        set("gender", "男性");                
        set("long", "法制治国[2;37;0m
它是袭劲瓶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pigc");
        set("owner_name", "袭劲瓶");
        set_temp("owner", "pigc");
        set_temp("owner_name", "袭劲瓶");
        ::setup();
}
