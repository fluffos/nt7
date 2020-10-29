// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m晓风[2;37;0m[2;37;0m", ({"zen"}));        
        set("gender", "男性");                
        set("long", "[2;37;0m
它是无明氏的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zmax");
        set("owner_name", "无明氏");
        set_temp("owner", "zmax");
        set_temp("owner_name", "无明氏");
        ::setup();
}
