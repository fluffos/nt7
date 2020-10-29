// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m哔哔[2;37;0m[2;37;0m", ({"bibi"}));        
        set("gender", "男性");                
        set("long", "哔哔[2;37;0m
它是忽忽悠悠的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyinetb");
        set("owner_name", "忽忽悠悠");
        set_temp("owner", "lyinetb");
        set_temp("owner_name", "忽忽悠悠");
        ::setup();
}
