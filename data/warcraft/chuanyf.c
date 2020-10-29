// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m二[1;33m货[2;37;0m[2;37;0m", ({"erhuo"}));        
        set("gender", "男性");                
        set("long", "迷迷糊糊的揉揉了眼睛，左看看右看看，怎么还没开饭啊。[2;37;0m
它是二货糊涂的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chuanyf");
        set("owner_name", "二货糊涂");
        set_temp("owner", "chuanyf");
        set_temp("owner_name", "二货糊涂");
        ::setup();
}
