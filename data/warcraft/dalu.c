// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("跑得快[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "看起来不错哟[2;37;0m
它是大哥不在的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dalu");
        set("owner_name", "大哥不在");
        set_temp("owner", "dalu");
        set_temp("owner_name", "大哥不在");
        ::setup();
}
