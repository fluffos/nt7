// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "一只雌性的小青龙[2;37;0m
它是绯月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "slema");
        set("owner_name", "绯月");
        set_temp("owner", "slema");
        set_temp("owner_name", "绯月");
        ::setup();
}
