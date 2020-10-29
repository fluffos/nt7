// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东方不败[2;37;0m[2;37;0m", ({"dfbb"}));        
        set("gender", "男性");                
        set("long", "help nick[2;37;0m
它是喂小饱的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wxb");
        set("owner_name", "喂小饱");
        set_temp("owner", "wxb");
        set_temp("owner_name", "喂小饱");
        ::setup();
}
