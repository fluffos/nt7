// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m终极暗器地雷[2;37;0m[2;37;0m", ({"kingpiga"}));        
        set("gender", "男性");                
        set("long", "一颗反步兵地雷[2;37;0m
它是糖球球的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kingpig");
        set("owner_name", "糖球球");
        set_temp("owner", "kingpig");
        set_temp("owner_name", "糖球球");
        ::setup();
}
