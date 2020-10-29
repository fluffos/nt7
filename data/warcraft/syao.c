// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽医[2;37;0m[2;37;0m", ({"aos"}));        
        set("gender", "男性");                
        set("long", "老虎[2;37;0m
它是大宋药丸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "syao");
        set("owner_name", "大宋药丸");
        set_temp("owner", "syao");
        set_temp("owner_name", "大宋药丸");
        ::setup();
}
