// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m大土马[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "大土马[2;37;0m
它是穆念慈的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "muzi");
        set("owner_name", "穆念慈");
        set_temp("owner", "muzi");
        set_temp("owner_name", "穆念慈");
        ::setup();
}
