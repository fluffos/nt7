// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "一只凶猛的白老虎[2;37;0m
它是李展白的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lizhanbai");
        set("owner_name", "李展白");
        set_temp("owner", "lizhanbai");
        set_temp("owner_name", "李展白");
        ::setup();
}
