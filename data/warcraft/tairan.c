// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m开天混沌兽[1;37m[2;37;0m[2;37;0m", ({"flyer"}));        
        set("gender", "女性");                
        set("long", "宇宙初开时的旷世神兽，传说为万物之源！[2;37;0m
它是马行空的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tairan");
        set("owner_name", "马行空");
        set_temp("owner", "tairan");
        set_temp("owner_name", "马行空");
        ::setup();
}
