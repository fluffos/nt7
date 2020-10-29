// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无自由[2;37;0m[2;37;0m", ({"nofree"}));        
        set("gender", "男性");                
        set("long", "无自由的玄武[2;37;0m
它是丁田的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jtin");
        set("owner_name", "丁田");
        set_temp("owner", "jtin");
        set_temp("owner_name", "丁田");
        ::setup();
}
