// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("东方巨龙[2;37;0m[2;37;0m", ({"long"}));        
        set("gender", "女性");                
        set("long", "无所不能的东方巨龙。[2;37;0m
它是高不胜寒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lonely");
        set("owner_name", "高不胜寒");
        set_temp("owner", "lonely");
        set_temp("owner_name", "高不胜寒");
        ::setup();
}
