// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红牛[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是黑猪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dook");
        set("owner_name", "黑猪");
        set_temp("owner", "dook");
        set_temp("owner_name", "黑猪");
        ::setup();
}
