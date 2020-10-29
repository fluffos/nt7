// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"white"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是萧谏纸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "gumuyuan");
        set("owner_name", "萧谏纸");
        set_temp("owner", "gumuyuan");
        set_temp("owner_name", "萧谏纸");
        ::setup();
}
