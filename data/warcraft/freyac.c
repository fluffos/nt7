// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("裂神[2;37;0m[2;37;0m", ({"dragonii"}));        
        set("gender", "男性");                
        set("long", "裂神[2;37;0m
它是思敏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "freyac");
        set("owner_name", "思敏");
        set_temp("owner", "freyac");
        set_temp("owner_name", "思敏");
        ::setup();
}
