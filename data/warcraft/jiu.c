// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m泡泡泡沫[2;37;0m[2;37;0m", ({"pao"}));        
        set("gender", "男性");                
        set("long", "胡莉莉[2;37;0m
它是九尽的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jiu");
        set("owner_name", "九尽");
        set_temp("owner", "jiu");
        set_temp("owner_name", "九尽");
        ::setup();
}
