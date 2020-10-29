// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大乌龟[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "大乌龟[2;37;0m
它是采花贼的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "caihua");
        set("owner_name", "采花贼");
        set_temp("owner", "caihua");
        set_temp("owner_name", "采花贼");
        ::setup();
}
