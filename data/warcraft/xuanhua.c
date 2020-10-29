// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("咣[2;37;0m[2;37;0m", ({"guang"}));        
        set("gender", "男性");                
        set("long", "咣[2;37;0m
它是喧哗的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xuanhua");
        set("owner_name", "喧哗");
        set_temp("owner", "xuanhua");
        set_temp("owner_name", "喧哗");
        ::setup();
}
