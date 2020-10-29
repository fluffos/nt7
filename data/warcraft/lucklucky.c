// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m招[5m[1;33m财[2;37;0m[1;36m进[5m[1;33m宝[2;37;0m[2;37;0m[2;37;0m", ({"treasure"}));        
        set("gender", "男性");                
        set("long", "财宝！！[2;37;0m
它是招财猫的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lucklucky");
        set("owner_name", "招财猫");
        set_temp("owner", "lucklucky");
        set_temp("owner_name", "招财猫");
        ::setup();
}
