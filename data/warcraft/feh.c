// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是和谢的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "feh");
        set("owner_name", "和谢");
        set_temp("owner", "feh");
        set_temp("owner_name", "和谢");
        ::setup();
}
