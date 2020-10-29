// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小毛驴[2;37;0m[2;37;0m", ({"lyex"}));        
        set("gender", "男性");                
        set("long", "一头小毛驴[2;37;0m
它是小随的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyinet");
        set("owner_name", "小随");
        set_temp("owner", "lyinet");
        set_temp("owner_name", "小随");
        ::setup();
}
