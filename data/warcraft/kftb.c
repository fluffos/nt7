// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是过破路的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kftb");
        set("owner_name", "过破路");
        set_temp("owner", "kftb");
        set_temp("owner_name", "过破路");
        ::setup();
}
