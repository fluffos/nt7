// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m避水金晶兽[2;37;0m[2;37;0m", ({"glsshou"}));        
        set("gender", "女性");                
        set("long", "郭老湿的坐骑[2;37;0m
它是郭老湿的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gls");
        set("owner_name", "郭老湿");
        set_temp("owner", "gls");
        set_temp("owner_name", "郭老湿");
        ::setup();
}
