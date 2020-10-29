// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嗷呜[2;37;0m[2;37;0m", ({"kilin"}));        
        set("gender", "男性");                
        set("long", "嗷呜嗷呜嗷呜[2;37;0m
它是莫信的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ashin");
        set("owner_name", "莫信");
        set_temp("owner", "ashin");
        set_temp("owner_name", "莫信");
        ::setup();
}
