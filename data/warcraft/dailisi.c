// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("慧云[2;37;0m[2;37;0m", ({"huiyun"}));        
        set("gender", "男性");                
        set("long", "天音嫌者,美丽的人与[2;37;0m
它是戴丽丝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dailisi");
        set("owner_name", "戴丽丝");
        set_temp("owner", "dailisi");
        set_temp("owner_name", "戴丽丝");
        ::setup();
}
