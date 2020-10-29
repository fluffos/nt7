// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("变兽三[2;37;0m[2;37;0m", ({"btc"}));        
        set("gender", "男性");                
        set("long", "爽[2;37;0m
它是变态米三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btmudc");
        set("owner_name", "变态米三");
        set_temp("owner", "btmudc");
        set_temp("owner_name", "变态米三");
        ::setup();
}
