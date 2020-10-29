// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("及时雨[2;37;0m[2;37;0m", ({"lsjsy"}));        
        set("gender", "男性");                
        set("long", "及时雨[2;37;0m
它是打包七号的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bagg");
        set("owner_name", "打包七号");
        set_temp("owner", "bagg");
        set_temp("owner_name", "打包七号");
        ::setup();
}
