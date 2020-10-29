// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m石[2;37;0m[35m可[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "一只笨笨的小乌龟[2;37;0m
它是白吃白玩的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lxass");
        set("owner_name", "白吃白玩");
        set_temp("owner", "lxass");
        set_temp("owner_name", "白吃白玩");
        ::setup();
}
