// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "正是那四圣兽之一的白虎[2;37;0m
它是乞丐王子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "warriera");
        set("owner_name", "乞丐王子");
        set_temp("owner", "warriera");
        set_temp("owner_name", "乞丐王子");
        ::setup();
}
