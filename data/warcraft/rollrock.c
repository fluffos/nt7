// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"tkyjls"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是东心雷的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "rollrock");
        set("owner_name", "东心雷");
        set_temp("owner", "rollrock");
        set_temp("owner_name", "东心雷");
        ::setup();
}
