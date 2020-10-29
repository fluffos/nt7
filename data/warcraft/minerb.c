// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦[2;37;0m[2;37;0m", ({"minerbride"}));        
        set("gender", "女性");                
        set("long", "阿斯顿发[2;37;0m
它是牛二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "minerb");
        set("owner_name", "牛二");
        set_temp("owner", "minerb");
        set_temp("owner_name", "牛二");
        ::setup();
}
