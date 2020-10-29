// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老黄牛[2;37;0m[2;37;0m", ({"minerride"}));        
        set("gender", "男性");                
        set("long", "老黄牛[2;37;0m
它是牛八的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "minerf");
        set("owner_name", "牛八");
        set_temp("owner", "minerf");
        set_temp("owner_name", "牛八");
        ::setup();
}
