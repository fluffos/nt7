// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m白虎[2;37;0m[2;37;0m", ({"whitetiger"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是绯月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "slem");
        set("owner_name", "绯月");
        set_temp("owner", "slem");
        set_temp("owner_name", "绯月");
        ::setup();
}
