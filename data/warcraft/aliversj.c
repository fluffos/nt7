// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("穹顶之下[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "穹顶之下[2;37;0m
它是阿尔十的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aliversj");
        set("owner_name", "阿尔十");
        set_temp("owner", "aliversj");
        set_temp("owner_name", "阿尔十");
        ::setup();
}
