// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("家家[2;37;0m[2;37;0m", ({"xjiia"}));        
        set("gender", "女性");                
        set("long", "胖胖的[2;37;0m
它是熊嘉梦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xja");
        set("owner_name", "熊嘉梦");
        set_temp("owner", "xja");
        set_temp("owner_name", "熊嘉梦");
        ::setup();
}
