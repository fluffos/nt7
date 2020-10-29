// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黑月追风[2;37;0m[2;37;0m", ({"doo"}));        
        set("gender", "男性");                
        set("long", "坐骑[2;37;0m
它是慕容崛的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "heat");
        set("owner_name", "慕容崛");
        set_temp("owner", "heat");
        set_temp("owner_name", "慕容崛");
        ::setup();
}
