// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红[2;37;0m[2;37;0m", ({"xxflong"}));        
        set("gender", "男性");                
        set("long", "感恩的心[2;37;0m
它是玉佩的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxf");
        set("owner_name", "玉佩");
        set_temp("owner", "xxf");
        set_temp("owner_name", "玉佩");
        ::setup();
}
