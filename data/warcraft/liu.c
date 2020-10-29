// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巴风特[2;37;0m[2;37;0m", ({"ate"}));        
        set("gender", "男性");                
        set("long", "咕叽咕叽[2;37;0m
它是晃悠的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "liu");
        set("owner_name", "晃悠");
        set_temp("owner", "liu");
        set_temp("owner_name", "晃悠");
        ::setup();
}
