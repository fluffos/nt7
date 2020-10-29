// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("沙发[2;37;0m[2;37;0m", ({"mmx"}));        
        set("gender", "男性");                
        set("long", "111[2;37;0m
它是扫地的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xmm");
        set("owner_name", "扫地");
        set_temp("owner", "xmm");
        set_temp("owner_name", "扫地");
        ::setup();
}
