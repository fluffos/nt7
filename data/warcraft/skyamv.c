// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("筋斗云[2;37;0m[2;37;0m", ({"jdy"}));        
        set("gender", "男性");                
        set("long", "筋斗云[2;37;0m
它是无言以对的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skyamv");
        set("owner_name", "无言以对");
        set_temp("owner", "skyamv");
        set_temp("owner_name", "无言以对");
        ::setup();
}
