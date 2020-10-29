// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大孔雀明王[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "大孔雀明王[2;37;0m
它是悟色的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ooooo");
        set("owner_name", "悟色");
        set_temp("owner", "ooooo");
        set_temp("owner_name", "悟色");
        ::setup();
}
