// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("图图[2;37;0m[2;37;0m", ({"tta"}));        
        set("gender", "男性");                
        set("long", "xx[2;37;0m
它是图一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ttza");
        set("owner_name", "图一");
        set_temp("owner", "ttza");
        set_temp("owner_name", "图一");
        ::setup();
}
