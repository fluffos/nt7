// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("默默[2;37;0m[2;37;0m", ({"mypet"}));        
        set("gender", "男性");                
        set("long", "默默[2;37;0m
它是段盖伦的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "remm");
        set("owner_name", "段盖伦");
        set_temp("owner", "remm");
        set_temp("owner_name", "段盖伦");
        ::setup();
}
