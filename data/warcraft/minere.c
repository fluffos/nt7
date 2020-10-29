// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老黄牛[2;37;0m[2;37;0m", ({"minerride"}));        
        set("gender", "男性");                
        set("long", "老黄牛[2;37;0m
它是牛七的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "minere");
        set("owner_name", "牛七");
        set_temp("owner", "minere");
        set_temp("owner_name", "牛七");
        ::setup();
}
