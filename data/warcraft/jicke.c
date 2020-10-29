// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m花花[2;37;0m[2;37;0m", ({"pxj"}));        
        set("gender", "女性");                
        set("long", "一只发情的母老虎~~[2;37;0m
它是葵花公子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jicke");
        set("owner_name", "葵花公子");
        set_temp("owner", "jicke");
        set_temp("owner_name", "葵花公子");
        ::setup();
}
