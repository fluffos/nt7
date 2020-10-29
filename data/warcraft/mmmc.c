// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m玉竹棍[2;37;0m[2;37;0m", ({"mjt"}));        
        set("gender", "女性");                
        set("long", "玉竹棍[2;37;0m
它是月舞者的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mmmc");
        set("owner_name", "月舞者");
        set_temp("owner", "mmmc");
        set_temp("owner_name", "月舞者");
        ::setup();
}
