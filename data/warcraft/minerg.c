// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老黄牛[2;37;0m[2;37;0m", ({"minerride"}));        
        set("gender", "男性");                
        set("long", "老黄牛[2;37;0m
它是牛九的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "minerg");
        set("owner_name", "牛九");
        set_temp("owner", "minerg");
        set_temp("owner_name", "牛九");
        ::setup();
}
