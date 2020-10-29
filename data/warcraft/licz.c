// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啦啦啦[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "啦啦啦[2;37;0m
它是王五的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "licz");
        set("owner_name", "王五");
        set_temp("owner", "licz");
        set_temp("owner_name", "王五");
        ::setup();
}
