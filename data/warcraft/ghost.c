// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m鬼厉[2;37;0m[2;37;0m", ({"gui"}));        
        set("gender", "男性");                
        set("long", "浑身发着幽幽磷火的小龙兽[2;37;0m
它是幽魂的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ghost");
        set("owner_name", "幽魂");
        set_temp("owner", "ghost");
        set_temp("owner_name", "幽魂");
        ::setup();
}
