// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大马[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "大马[2;37;0m
它是阿多五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "adonise");
        set("owner_name", "阿多五");
        set_temp("owner", "adonise");
        set_temp("owner_name", "阿多五");
        ::setup();
}
