// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m骑麟[2;37;0m[2;37;0m", ({"lin"}));        
        set("gender", "男性");                
        set("long", "这只是坐骑，没啥可看的[2;37;0m
它是不懂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "budong");
        set("owner_name", "不懂");
        set_temp("owner", "budong");
        set_temp("owner_name", "不懂");
        ::setup();
}
