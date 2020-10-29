// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m怒蛟[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "江雪寒的坐骑——青龙[2;37;0m
它是江雪寒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "drin");
        set("owner_name", "江雪寒");
        set_temp("owner", "drin");
        set_temp("owner_name", "江雪寒");
        ::setup();
}
