// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小泽玛利亚[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "36D完美身材。巨乳，童颜，美尻。[2;37;0m
它是人间凶器的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "yama");
        set("owner_name", "人间凶器");
        set_temp("owner", "yama");
        set_temp("owner_name", "人间凶器");
        ::setup();
}
