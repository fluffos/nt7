// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("梁朝伟[2;37;0m[2;37;0m", ({"sadfajl"}));        
        set("gender", "男性");                
        set("long", "阿斯顿发生了[2;37;0m
它是绿一的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lichb");
        set("owner_name", "绿一");
        set_temp("owner", "lichb");
        set_temp("owner_name", "绿一");
        ::setup();
}
