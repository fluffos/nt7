// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大马[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "大马[2;37;0m
它是阿多六的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonisf");
        set("owner_name", "阿多六");
        set_temp("owner", "adonisf");
        set_temp("owner_name", "阿多六");
        ::setup();
}
