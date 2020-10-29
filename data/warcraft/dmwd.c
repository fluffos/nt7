// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m貂蝉[2;37;0m[2;37;0m", ({"cut"}));        
        set("gender", "男性");                
        set("long", "三国第一喵[2;37;0m
它是屠夫的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dmwd");
        set("owner_name", "屠夫");
        set_temp("owner", "dmwd");
        set_temp("owner_name", "屠夫");
        ::setup();
}
