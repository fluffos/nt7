// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("叮叮[2;37;0m[2;37;0m", ({"dingding"}));        
        set("gender", "男性");                
        set("long", "叮叮[2;37;0m
它是冷邪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xieleng");
        set("owner_name", "冷邪");
        set_temp("owner", "xieleng");
        set_temp("owner_name", "冷邪");
        ::setup();
}
