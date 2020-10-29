// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m牛鼻子专车[2;37;0m[2;37;0m", ({"pigkinga"}));        
        set("gender", "男性");                
        set("long", "牛鼻子专车[2;37;0m
它是屠倭道士的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pigking");
        set("owner_name", "屠倭道士");
        set_temp("owner", "pigking");
        set_temp("owner_name", "屠倭道士");
        ::setup();
}
