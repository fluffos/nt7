// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m来捧场[2;37;0m[2;37;0m", ({"lpcs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是泥语的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lpc");
        set("owner_name", "泥语");
        set_temp("owner", "lpc");
        set_temp("owner_name", "泥语");
        ::setup();
}
