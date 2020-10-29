// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("古墓麒麟[2;37;0m[2;37;0m", ({"gumumiqilin"}));        
        set("gender", "女性");                
        set("long", "古墓麒麟[2;37;0m
它是爱斗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gumumi");
        set("owner_name", "爱斗");
        set_temp("owner", "gumumi");
        set_temp("owner_name", "爱斗");
        ::setup();
}
