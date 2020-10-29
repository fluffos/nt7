// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日本香烟[2;37;0m[2;37;0m", ({"usetosleep"}));        
        set("gender", "男性");                
        set("long", "日本香烟[2;37;0m
它是七星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mildseven");
        set("owner_name", "七星");
        set_temp("owner", "mildseven");
        set_temp("owner_name", "七星");
        ::setup();
}
