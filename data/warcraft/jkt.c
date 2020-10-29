// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东北虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "hp[2;37;0m
它是于大的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jkt");
        set("owner_name", "于大");
        set_temp("owner", "jkt");
        set_temp("owner_name", "于大");
        ::setup();
}
