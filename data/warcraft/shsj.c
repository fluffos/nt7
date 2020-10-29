// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小泥鳅[2;37;0m[2;37;0m", ({"snakehoho"}));        
        set("gender", "男性");                
        set("long", "小泥鳅[2;37;0m
它是上海海上的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shsj");
        set("owner_name", "上海海上");
        set_temp("owner", "shsj");
        set_temp("owner_name", "上海海上");
        ::setup();
}
