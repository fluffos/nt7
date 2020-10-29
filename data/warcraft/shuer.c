// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎飞[2;37;0m[2;37;0m", ({"feio"}));        
        set("gender", "女性");                
        set("long", "什么也没有留下[2;37;0m
它是苏尔白的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shuer");
        set("owner_name", "苏尔白");
        set_temp("owner", "shuer");
        set_temp("owner_name", "苏尔白");
        ::setup();
}
