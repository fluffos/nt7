// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("花猫[2;37;0m[2;37;0m", ({"xhua"}));        
        set("gender", "男性");                
        set("long", "花猫[2;37;0m
它是小楼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jue");
        set("owner_name", "小楼");
        set_temp("owner", "jue");
        set_temp("owner_name", "小楼");
        ::setup();
}
