// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("刷刷刷[2;37;0m[2;37;0m", ({"goldsss"}));        
        set("gender", "男性");                
        set("long", "刷刷刷[2;37;0m
它是金上的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldss");
        set("owner_name", "金上");
        set_temp("owner", "goldss");
        set_temp("owner_name", "金上");
        ::setup();
}
