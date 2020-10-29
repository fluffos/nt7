// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧碧[2;37;0m[2;37;0m", ({"bibi"}));        
        set("gender", "女性");                
        set("long", "血受的碧碧[2;37;0m
它是哈迪斯的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "hadis");
        set("owner_name", "哈迪斯");
        set_temp("owner", "hadis");
        set_temp("owner_name", "哈迪斯");
        ::setup();
}
