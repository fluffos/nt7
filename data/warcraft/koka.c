// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("靠哦[2;37;0m[2;37;0m", ({"kokaa"}));        
        set("gender", "男性");                
        set("long", "很多地方[2;37;0m
它是敲阿拉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "koka");
        set("owner_name", "敲阿拉");
        set_temp("owner", "koka");
        set_temp("owner_name", "敲阿拉");
        ::setup();
}
