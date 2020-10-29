// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m神雕[2;37;0m[2;37;0m", ({"sdiao"}));        
        set("gender", "男性");                
        set("long", "这是救过断臂杨过的远古大雕[2;37;0m
它是东方不败的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dfbb");
        set("owner_name", "东方不败");
        set_temp("owner", "dfbb");
        set_temp("owner_name", "东方不败");
        ::setup();
}
