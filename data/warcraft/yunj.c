// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m小飞[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是云卷的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yunj");
        set("owner_name", "云卷");
        set_temp("owner", "yunj");
        set_temp("owner_name", "云卷");
        ::setup();
}
