// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("苍井空[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "女性");                
        set("long", "苍井空[2;37;0m
它是泄立停的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xlt");
        set("owner_name", "泄立停");
        set_temp("owner", "xlt");
        set_temp("owner_name", "泄立停");
        ::setup();
}
